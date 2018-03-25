
#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include "data_input.h"


dataInput::dataInput()
    :mLabelLen(0),
    mImageLen(0),
    mNumLabel(0),
    mNumImage(0),
    mImageStartPos(16),
    mLableStartPos(8)
{

}

dataInput::~dataInput()
{
    mLabelFile.close();
    mImageFile.close();
}


bool dataInput::openLabelFile(const char* url)
{
    mLabelFile.open(url, ios::binary | ios::in);

    if (mLabelFile.is_open())
    {
        int num = 0;
        char temp[4];

        mLabelFile.read(temp, 4);

        if (mLabelFile.gcount() == 4)
        {
            num = GRB4(temp);
            if (DATA_INPUT_LABEL_FLAG == num)
            {
                mLabelFile.read(temp, 4);

                if (mLabelFile.gcount() == 4)
                {
                    mNumLabel = GRB4(temp);
                    mLabelLen = 1;
                    return true;
                }
                else
                {
                    cout << "read label count failed" << endl;
                }
            }
            else
            {
                cout << "this file isn't label file,the flag is:" << num << endl;
            }
        }
    }

    return false;
}

bool dataInput::openImageFile(const char* url)
{
    mImageFile.open(url, ios::binary | ios::in);

    if (mImageFile.is_open())
    {
        int num = 0;

        char temp[4];

        mImageFile.read(temp, 4);

        if (mImageFile.gcount() == 4)
        {
            int flag = DATA_INPUT_IMAGE_FLAG;
            num = GRB4(temp);
            if (DATA_INPUT_IMAGE_FLAG == num)
            {
                mImageFile.read(temp, 4);

                if (mImageFile.gcount() == 4)
                {
                    mNumImage = GRB4(temp);

                    int width = 0;
                    int height = 0;

                    mImageFile.read((char*)&width, 4);

                    if (mImageFile.gcount() == 4)
                    {
                        width = GRB4(&width);
                        mImageFile.read((char*)&height, 4);

                        if (mImageFile.gcount() == 4)
                        {
                            height = GRB4(&height);
                            mImageWidth = width;
                            mImageHeight = height;
                            mImageLen = width * height;
                        }
                    }

                    return true;
                }
                else
                {
                    cout << "read image count failed" << endl;
                }



            }
            else
            {
                cout << "this file isn't image file,the flag is:" << num << endl;
            }
        }
    }

    return false;
}

bool dataInput::readIndex(int* label)
{
    if (mLabelFile.is_open() && !mLabelFile.eof())
    {
        mLabelFile.read((char*)label, mLabelLen);
        return mLabelFile.gcount() == mLabelLen;
    }

    return false;
}

bool dataInput::readImage(char imageBuf[])
{
    if (mImageFile.is_open() && !mImageFile.eof())
    {
        mImageFile.read(imageBuf, mImageLen);

        return mImageFile.gcount() == mImageLen;
    }

    return false;
}

bool dataInput::read(int* label, char imageBuf[])
{
    if (readIndex(label))
    {
        return readImage(imageBuf);
    }

    return false;
}

void dataInput::reset()
{
    if (mImageFile.is_open())
    {
        mImageFile.clear();
        mImageFile.seekg(mImageStartPos);
    }

    if (mLabelFile.is_open())
    {
        mLabelFile.clear();
        mLabelFile.seekg(mLableStartPos);
    }
}
