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
#include "EightNums.h"

using namespace std;

class NightNumbers{
private:
	node head;	
	node open[MAXSTEPS]; 
	pair<int, int> closed[MAXSTEPS];
	vector<int> path;
	set<int>states;
	int steps;
	int Target;
	int Current;
	bool isFirst;
	
	inline bool CouldMove(int a,int b){
		return (a >= 0 && a < 3 && b >= 0 && b < 3);	
	}

	inline bool CouldSolve(int current,int target){
		return true;
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
	NightNumbers(int cur,int tar){
		Current = cur;
		Target = tar;
		steps = 0;
		isFirst = true;
	}

	~NightNumbers(){}

	void SetInit(int current,int target);
	int Calculate(int current,int target);	
	int GetNixuNum(int state);
	bool aStarAlgorithm();
	void ShowPath();
	void GetSolution();
};

void NightNumbers::GetSolution(){
	bool ret = aStarAlgorithm();
	if(ret)ShowPath();
	else cout << "Solution doesn't exists!" << endl;
}

void NightNumbers::SetInit(int current,int target){
	Target = target;
	Current = current;
}

void NightNumbers::ShowPath(){
	int len = path.size();
	for(int x = 0;x < len;x ++){
		cout << path[x];
		if(x != len-1)cout << "->";
	}
	cout << endl;
}
/*
int NightNumbers::Calculate(int current, int target)  
{          
	int c[9], t[9];         
	int ret = 0;          
	for(int x = 0;x < 9; ++ x){                  
		c[current % 10] = t[target % 10] = x;                 
		current /= 10;                
		target /= 10;         
	}  

	for(int x = 0;x < 9;++ x)                  
		ret += abs(c[x] / 3 - t[x] / 3) + abs(c[x] % 3 - t[x] % 3);         
	return ret/2; 
}*/

int NightNumbers::Calculate(int current, int target)
{
    //qDebug() << "calc3";
    int c[9], t[9];
    int ret = 0;
    for(int x = 0;x < 9; ++ x){
        c[current % 10] = t[target % 10] = x;
        current /= 10;
        target /= 10;
    }

    for(int x = 0;x < 9;++ x)
        ret += abs(c[x] / 3 - t[x] / 3) + abs(c[x] % 3 - t[x] % 3);
    return ret/2;
}


void NightNumbers::GetPath(int index) {          
	if (index == 0){                  
		path.push_back(closed[index].first);
		return;         
	}          
	GetPath(closed[index].second);         
	path.push_back(closed[index].first);
	++steps; 
}

int NightNumbers::GetNixuNum(int state) {
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
/*
bool NightNumbers::aStarAlgorithm(){
	int NextNode;
	pair<int,int>start,targets;
	start.first = Current;start.second = GetZeroLocation(Current);
	targets.first = Target;targets.second = GetZeroLocation(Target);
	if(!CouldSolve(start.first,targets.first))
		return false;
	
	open[0].state = start.first;
	open[0].h = Calculate(start.first,targets.first);
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
		
		//expand the sub nodes
		for(int e = 0;e < 9;e ++){
			for(int i = 0;i < 4;i ++){
				int x = e / 3;
				int y = e % 3;

				int nx = x + xtran[i];
				int ny = y + ytran[i];

				if(!CouldMove(nx,ny))
					continue;
				//int na = head.blank;
				int na = e;
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
			//	if(isFirst){
					cout << head.state << " ->" << NextNode << endl;
			//	}

				states.insert(NextNode);
				open[nums].pre = index;
				open[nums].blank = nb;
				open[nums].state = NextNode;
				open[nums].h = Calculate(NextNode,targets.first);
				open[nums].g = head.g + 1;
				++ nums;
				push_heap(open,open+nums,cmp());
			}
		}
		if(isFirst)isFirst = false;
	}
	
	cout << "states->" << states.size() << endl;
	states.clear();
	steps = 0;
	return nums > 0;	
}*/

bool NightNumbers::aStarAlgorithm()
{
    int NextNode;
    pair<int,int>start,targets;
    start.first = Current;start.second = GetZeroLocation(Current);
    targets.first = Target;targets.second = GetZeroLocation(Target);
    if(!CouldSolve(start.first,targets.first))
        return false;

    open[0].state = start.first;
    open[0].h = Calculate(start.first,targets.first);
    open[0].blank = start.second;
    open[0].pre = -1;
    open[0].g = 0;
    int index = 0;
    states.insert(start.first);
    int nums = 1;
    for(;nums > 0;++ index){
        assert(index < MAXSTEPS);
        /*if(index%3000 == 0){
            OpenTable->Clear();
            for(int rt = 0;rt < nums;rt ++)
                AddToTable(OpenTable,open[rt]);
        }*/
        head = open[0];
        closed[index].first = open[0].state;
        closed[index].second = open[0].pre;
       /* QString opt = QString::number(head.state,10);
        if(opt.size() == 8)opt = "0"+opt;
        OptNode->setText(opt);
        board->setData(head.state);
        AddClosedTable(ClosedTable,closed[index]);*/
        pop_heap(open,open+nums,cmp());
        -- nums;

        //already got the solution
        if(head.state == targets.first){
            GetPath(index);
            break;
        }

        //expand the sub nodes
        for(int e = 0;e < 9;e ++){
            for(int i = 0;i < 4;i ++){
                int x = e / 3;
                int y = e % 3;

                int nx = x + xtran[i];
                int ny = y + ytran[i];

                if(!CouldMove(nx,ny))
                    continue;
                //int na = head.blank;
                int na = e;
                int nb = 3*nx + ny;
                //the next sub node
                NextNode = head.state +
                        ((head.state % p[na + 1]) / p[na] -
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
                open[nums].h = Calculate(NextNode,targets.first);
                open[nums].g = head.g + 1;
                ++ nums;
                push_heap(open,open+nums,cmp());
            }
        }
        /*QString str = QString::number(nums,10);
        OpenNums->setText(str);
        QString total = QString::number(states.size(),10);
        TotalNode->setText(total);*/
    }

    states.clear();
    steps = 0;
    return nums > 0;
}
