#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <time.h>

#include "bpneuronnet.h"
#include "data_input.h"

/** indicate 0 ~ 9 */
#define NUM_NET_OUT 10
#define NUM_HIDDEN 88
#define NET_LEARNING_RATE 0.4

#define TRAIN_IMAGES_URL "docs/train-images.idx3-ubyte"
#define TRAIN_LABELS_URL "docs/train-labels.idx1-ubyte"

#define TEST_IMANGES_URL "docs/t10k-images.idx3-ubyte"
#define TEST_LABELS_URL  "docs/t10k-labels.idx1-ubyte"

#define PictureHeight 28
#define PictureWidth 28

namespace ComFunc{

inline int RandInt(int x, int y)
{
    return rand() % (y - x + 1) + x;
}

//returns a random float between zero and 1
inline double RandFloat()
{
    return (rand()) / (RAND_MAX + 1.0);
}

inline int showRecognizedNumber(double net_out[])
{
    int idx = -1;
    double max_value = -99999;
    for (int i = 0; i < NUM_NET_OUT; i++)
    {
        if (net_out[i] > max_value)
        {
            max_value = net_out[i];
            idx = i;
        }
    }
    //cout << "the number is: " << idx << endl;
    return idx;
}

inline void showNumber(double pic[], int width, int height)
{
    int idx = 0;
    const double EXP = 0.000001;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (pic[idx]>EXP||pic[idx]<-EXP)
            {
                cout << "1";
            }
            else
            {
                cout << "0";
            }
            idx++;
        }

        cout << endl;
    }
}

inline void showNumber(unsigned char pic[], int width, int height)
{
    int idx = 0;
    for (int i=0; i < height; i++)
    {
        for (int j = 0; j < width; j++ )
        {

            if ((int)pic[idx++]>=128)
            {
                cout << "1";
            }
            else
            {
                cout << " ";
            }
        }

        cout << endl;
    }
}

inline void preProcessInputData(const unsigned char src[], double out[], int size)
{
    for (int i = 0; i < size; i++)
    {
        out[i] = (src[i] >= 128) ? 1.0 : 0.0;
    }
}

inline void preProcessInputDataWithNoise(const unsigned char src[], double out[], int size)
{
    for (int i = 0; i < size; i++)
    {
        out[i] = ((src[i] >= 128) ? 1.0 : 0.0) + RandFloat() * 0.1;
    }
}

inline double trainEpoch(dataInput& src, bpNeuronNet& bpnn, int imageSize, int numImages)
{
    double net_target[NUM_NET_OUT];
    char* temp = new char[imageSize];

    double* net_train = new double[imageSize];
    for (int i = 0; i < numImages; i++)
    {
        int label = 0;
        memset(net_target, 0, NUM_NET_OUT * sizeof(double));

        if (src.read(&label, temp))
        {
            net_target[label] = 1.0;
            preProcessInputDataWithNoise((unsigned char*)temp, net_train, imageSize);
            bpnn.training(net_train, net_target);

        }
        else
        {
            cout << "read train data failed" << endl;
            break;
        }
    }

    cout << "the error is:" << bpnn.getError() << " after training " << endl;

    delete []net_train;
    delete []temp;

    return bpnn.getError();
}

inline int testRecognition(dataInput& testData, bpNeuronNet& bpnn, int imageSize,
                           int numImages)
{
    int ok_cnt = 0;
    double* net_out = NULL;
    char* temp = new char[imageSize];
    double* net_test = new double[imageSize];
    for (int i = 0; i < numImages; i++)
    {
        int label = 0;

        if (testData.read(&label, temp))
        {
            preProcessInputData((unsigned char*)temp, net_test, imageSize);
            bpnn.process(net_test, &net_out);
            //if (i <= 100)
            //{
            showNumber((unsigned char*)temp, testData.imageWidth(), testData.imageHeight());//
            showRecognizedNumber(net_out);//
           // }
            int idx = -1;
            double max_value = -99999;
            for (int i = 0; i < NUM_NET_OUT; i++)
            {
                if (net_out[i] > max_value)
                {
                    max_value = net_out[i];
                    idx = i;
                }
            }

            if (idx == label)
            {
                ok_cnt++;
            }
        }
        else
        {
            cout << "read test data failed" << endl;
            break;
        }
    }


    delete []net_test;
    delete []temp;

    return ok_cnt;

}

}
#endif // COMMON_H
