#ifndef __NEURON_H__
#define __NEURON_H__
#include <stdlib.h>
#include <string.h>

struct neuronLayer
{
public:
    neuronLayer(int numNeurons, int numInputsPerNeuron);

    neuronLayer(neuronLayer& nl);
    ~neuronLayer();

    void reset(void);
public:
    int mNumInputsPerNeuron; /** the count of input node per neuron */
    int mNumNeurons; /** the count of neuron(or node) of current layer */

    double** mWeights; /** 2D array,row: indicate neuron, column: the weights per neuron */
    double* mOutActivations; /** the output activation of neuron. 1D array, the index of array indicate neuron */
    double* mOutErrors; /** the error of output of neuron. 1D array, the index of array indicate neuron */

};

#endif
