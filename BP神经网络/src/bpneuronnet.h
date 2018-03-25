#ifndef __BP_NEURON_NET_H__
#define __BP_NEURON_NET_H__

#include <vector>
#include <math.h>
#include "neuronlayer.h"

using namespace std;

/** range, 0 < x <= 1.0 */
#define ACTIVATION_RESPONSE 0.7

#define BIAS                1

class bpNeuronNet
{
public:
    bpNeuronNet(int numInputs, double learningRate);
    ~bpNeuronNet();
public:
    inline double getError(void) { return mErrorSum; }

    bool training(const double inputs[], const double targets[]);
    void process(const double inputs[], double* outputs[]);

    void reset(void);
    void addNeuronLayer(int numNeurons);

private:


    inline double sigmoidActive(double activation, double response);


    void updateNeuronLayer(neuronLayer& nl, const double inputs[]);

    inline double backActive(double x);
    void trainUpdate(const double inputs[], const double targets[]);

    void trainNeuronLayer(neuronLayer& nl,  const double prevOutActivations[], double prevOutErrors[]);

private:
    int mNumInputs;
    int mNumOutputs;
    int mNumHiddenLayers;
    double mLearningRate;
    double mErrorSum;
    vector<neuronLayer*> mNeuronLayers;
};

#endif
