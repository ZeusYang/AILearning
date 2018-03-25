#include "bpneuronnet.h"

bpNeuronNet::bpNeuronNet(int numInputs, double learningRate)
    :mNumInputs(numInputs),
    mNumOutputs(0),
    mNumHiddenLayers(0),
    mLearningRate(learningRate),
    mErrorSum(9999)
{
}

bpNeuronNet::~bpNeuronNet()
{

    for (size_t i = 0; i < mNeuronLayers.size(); i++)
    {
        if (mNeuronLayers[i])
        {
            delete mNeuronLayers[i];
        }
    }

}

void bpNeuronNet::reset()
{
    for (int i = 0; i < mNumHiddenLayers + 1; ++i)
    {
        mNeuronLayers[i]->reset();
    }

    mErrorSum = 9999;
}

void bpNeuronNet::addNeuronLayer(int numNeurons)
{
    int numInputsPerNeuron = (mNeuronLayers.size() > 0) ? mNeuronLayers[mNumHiddenLayers]->mNumNeurons : mNumInputs;

    mNeuronLayers.push_back(new neuronLayer(numNeurons, numInputsPerNeuron));

    mNumHiddenLayers = (mNeuronLayers.size() > 0) ? (mNeuronLayers.size() - 1) : 0;
}

double bpNeuronNet::sigmoidActive(double activation, double response)
{
    /** sigmoid function: f(x) = 1 /(1 + exp(-x)) */
    return (1.0 / (1.0 + exp(-activation * response)));
}

void bpNeuronNet::updateNeuronLayer(neuronLayer& nl, const double inputs[])
{
    int numNeurons = nl.mNumNeurons;
    int numInputsPerNeuron = nl.mNumInputsPerNeuron;
    double* curOutActivations = nl.mOutActivations;

    for (int n = 0; n < numNeurons; ++n)
    {
        double* curWeights = nl.mWeights[n];

        double netinput = 0;
        int k;

        for (k = 0; k < numInputsPerNeuron; ++k)
        {
            netinput += curWeights[k] * inputs[k];
        }

        netinput += curWeights[k] * BIAS;

        curOutActivations[n] = sigmoidActive(netinput, ACTIVATION_RESPONSE);
    }
}

void bpNeuronNet::process(const double inputs[], double* outputs[])
{
    for (int i = 0; i < mNumHiddenLayers + 1; i++)
    {
        updateNeuronLayer(*mNeuronLayers[i], inputs);
        inputs = mNeuronLayers[i]->mOutActivations;
    }

    *outputs = mNeuronLayers[mNumHiddenLayers]->mOutActivations;

}

double bpNeuronNet::backActive(double x)
{
    /**calculate the error value with
     f(x) = x * (1 - x) is the derivatives of sigmoid active function
    */
    return x * (1 - x);
}

void bpNeuronNet::trainUpdate(const double inputs[], const double targets[])
{
    for (int i = 0; i < mNumHiddenLayers + 1; i++)
    {
        updateNeuronLayer(*mNeuronLayers[i], inputs);
        inputs = mNeuronLayers[i]->mOutActivations;
    }

    neuronLayer& outLayer = *mNeuronLayers[mNumHiddenLayers];
    double* outActivations = outLayer.mOutActivations;
    double* outErrors = outLayer.mOutErrors;
    int numNeurons = outLayer.mNumNeurons;

    mErrorSum = 0;
    /** update the out error of output neuron layer */
    for (int i = 0; i < numNeurons; i++)
    {
        double err = targets[i] - outActivations[i];
        outErrors[i] = err;
        mErrorSum += err * err;
    }
}


void bpNeuronNet::trainNeuronLayer(neuronLayer& nl, const double prevOutActivations[], double prevOutErrors[])
{
    int numNeurons = nl.mNumNeurons;
    int numInputsPerNeuron = nl.mNumInputsPerNeuron;
    double* curOutErrors = nl.mOutErrors;
    double* curOutActivations = nl.mOutActivations;


    for (int i = 0; i < numNeurons; i++)
    {
        double* curWeights = nl.mWeights[i];
        double coi = curOutActivations[i];

        //f'(x) = x * (1 - x)
        double err = curOutErrors[i] * backActive(coi);

        int w;
        for (w = 0; w < numInputsPerNeuron; w++)
        {
            if (prevOutErrors)
            {
                prevOutErrors[w] += curWeights[w] * err;
            }
            curWeights[w] += err * mLearningRate * prevOutActivations[w];
        }
        curWeights[w] += err * mLearningRate * BIAS;
    }
}

bool bpNeuronNet::training(const double inputs[], const double targets[])
{
    const double* prevOutActivations = NULL;
    double* prevOutErrors = NULL;
    trainUpdate(inputs, targets);

    for (int i = mNumHiddenLayers; i >= 0; i--)
    {
        neuronLayer& curLayer = *mNeuronLayers[i];

        if (i > 0)
        {
            neuronLayer& prev = *mNeuronLayers[(i - 1)];
            prevOutActivations = prev.mOutActivations;
            prevOutErrors = prev.mOutErrors;
            memset(prevOutErrors, 0, prev.mNumNeurons * sizeof(double));

        }
        else
        {
            prevOutActivations = inputs;
            prevOutErrors = NULL;
        }

        trainNeuronLayer(curLayer, prevOutActivations, prevOutErrors);
    }

    return true;
}
