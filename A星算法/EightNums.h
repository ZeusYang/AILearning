#pragma once
#include <algorithm> 
#include <cstdio> 
#include <set> 
#include <vector>
#include <utility> 
#include <ctime> 
#include <cassert> 
#include <string> 
#include <cstring>
#include <iostream>

using namespace std;

const int MAXSTEPS = 100000;
const int xtran[4] = {-1, 0, 1, 0};           
const int ytran[4] = { 0, 1, 0,-1};            
const int p[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

struct node  
{          
	int state;          
	int blank;         
	int g;         
	int h;           
	int pre; 

	node(){
		state = blank = g = h = pre = 0;	
	}
};

ostream& operator<<(ostream& out,node target){
	out << target.state << " " << target.blank << " " << target.g << " "
		<< target.h << " " << target.pre << endl;
	return out;
}

class cmp{
public: 
	inline bool operator()(node t1,node t2)
	{
		return (t1.g + t1.h) > (t2.g + t2.h);
	}
};

class EightNumbers{
private:
	node head;	
	node open[MAXSTEPS]; 
	pair<int, int> closed[MAXSTEPS];
	vector<int> path;
	set<int>states;
	int steps;
	int Target;
	int Current;
	
	inline bool CouldMove(int a,int b){
		return (a >= 0 && a < 3 && b >= 0 && b < 3);	
	}

	inline bool CouldSolve(int current,int target){
		int targetNum = GetNixuNum(target);
		int currentNum = GetNixuNum(current);
		return ((currentNum&1)&&(targetNum&1))||
			   (!(currentNum&1)&&!(targetNum&1));
	}
	
	inline int GetZeroLocation(int target){
		int ret = 0;
		while(target != 0){
			if(target%10 == 0)break;
			++ ret;
			target /= 10;
		}
		return ret;
	}

	void GetPath(int index);

public:
	EightNumbers(int cur,int tar){
		Current = cur;
		Target = tar;
		steps = 0;
	}

	~EightNumbers(){}

	void SetInit(int current,int target);
	int Calculate(int current,int target);	
	int Calculate1(int current,int target);
	int GetNixuNum(int state);
	bool aStarAlgorithm();
	void ShowPath();
	void GetSolution();
};

void EightNumbers::GetSolution(){
	bool ret = aStarAlgorithm();
	if(ret)ShowPath();
	else cout << "Solution doesn't exists!" << endl;
}

void EightNumbers::SetInit(int current,int target){
	Target = target;
	Current = current;
}

void EightNumbers::ShowPath(){
	int len = path.size();
	for(int x = 0;x < len;x ++){
		cout << path[x];
		if(x != len-1)cout << "->";
	}
	cout << endl;
}

int EightNumbers::Calculate(int current, int target)  
{          
	int c[9], t[9];         
	int ret = 0;          
	for(int x = 0;x < 9; ++ x){                  
		c[current % 10] = t[target % 10] = x;                 
		current /= 10;                
		target /= 10;         
	}  

	for(int x = 1;x < 9;++ x)                  
		ret += abs(c[x] / 3 - t[x] / 3) + abs(c[x] % 3 - t[x] % 3);         
	return ret; 
}

int EightNumbers::Calculate1(int current,int target)
{
	int c[9], t[9];         
	int ret = 0;          
	for(int x = 0;x < 9; ++ x){                  
		c[current % 10] = t[target % 10] = x;                 
		current /= 10;                
		target /= 10;         
	}  

	for(int x = 1;x < 9;++ x){
		if(abs(c[x]/3 - t[x]/3)+abs(c[x]%3-t[x]%3) > 0)++ ret;	
	}
	return ret; 

}

void EightNumbers::GetPath(int index) {          
	if (index == 0){                  
		path.push_back(closed[index].first);
		return;         
	}          
	GetPath(closed[index].second);         
	path.push_back(closed[index].first);
	++steps; 
}

int EightNumbers::GetNixuNum(int state) {
	int ret = 0;
	int result[9];
	memset(result, 0, sizeof(result));

	char buf[10];
	sprintf(buf,"%d",state);
	int k = 0;
	while(buf[k] != '\0'){
		result[9-k-1] = buf[k] - '0';
		k++;
	}

	for( int x = 0; x < 9; x++ ){
		for( int y = x + 1; y < 9;y ++){
			if( result[x] && result[y] && result[x] > result[y]){
				ret++;
			}
		}
	}
	return ret; 
}

bool EightNumbers::aStarAlgorithm(){
	int NextNode;
	pair<int,int>start,targets;
	start.first = Current;start.second = GetZeroLocation(Current);
	targets.first = Target;targets.second = GetZeroLocation(Target);
	if(!CouldSolve(start.first,targets.first))
		return false;
	
	open[0].state = start.first;
	open[0].h = Calculate1(start.first,targets.first);
	open[0].blank = start.second;
	open[0].pre = -1;
	open[0].g = 0;
	int index = 0;
	states.insert(start.first);
	int nums = 1;
	for(;nums > 0;++ index){
		//cout << "1" << endl;
		assert(index < MAXSTEPS);
		head = open[0];

		//Get the smallest f(n) to closed table
		closed[index].first = open[0].state;
		closed[index].second = open[0].pre;
		pop_heap(open,open+nums,cmp());
		-- nums;

		//already got the solution
		if(head.state == targets.first){
			GetPath(index);
			break;
		}
	
		int x = head.blank / 3;
		int y = head.blank % 3;

		//expand the sub nodes
		for(int i = 0;i < 4;i ++){
			int nx = x + xtran[i];
			int ny = y + ytran[i];

			if(!CouldMove(nx,ny))
				continue;
			int na = head.blank;
			int nb = 3*nx + ny;
			//the next sub node
			NextNode = head.state + 
					((head.state % p[na+1]) / p[na] - 
					(head.state % p[nb + 1]) / p[nb]) *p[nb]
					+
					((head.state % p[nb + 1]) / p[nb] -
					(head.state % p[na + 1]) / p[na]) *p[na];
			if(!CouldSolve(NextNode,targets.first))continue;
			if(states.find(NextNode) != states.end())continue;
			states.insert(NextNode);
			open[nums].pre = index;
			open[nums].blank = nb;
			open[nums].state = NextNode;
			open[nums].h = Calculate1(NextNode,targets.first);
			open[nums].g = head.g + 1;
			++ nums;
			push_heap(open,open+nums,cmp());
		}
	}
	
	cout << "states->" << states.size() << endl;
	states.clear();
	steps = 0;
	return nums > 0;	
}
