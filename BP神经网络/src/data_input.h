#ifndef __DATA_INPUT_H__
#define __DATA_INPUT_H__

#include <fstream>

using namespace std;

#define GRB4(a)  ((unsigned int)((((unsigned char*)(a))[0] << 24) | (((unsigned char*)(a))[1] << 16) |  \
                (((unsigned char*)(a))[2] <<  8) | ((unsigned char*)(a))[3]))

#define DATA_INPUT_IMAGE_FLAG 0x00000803

#define DATA_INPUT_LABEL_FLAG 0x00000801

class dataInput
{
public:
    dataInput();
    ~dataInput();
public:
    void reset();
    bool openLabelFile(const char* url);
    bool openImageFile(const char* url);

    bool readIndex(int* label);
    bool readImage(char imageBuf[]);

    bool read(int* label, char imageBuf[]);

    inline int numLable() { return mNumLabel; }
    inline int numImage() { return mNumImage; }

    inline int labelLength() { return mLabelLen; }
    inline int imageLength() { return mImageLen; }

    inline int imageWidth() { return mImageWidth; }
    inline int imageHeight() { return mImageHeight; }
private:
    int mNumLabel;
    int mNumImage;

    int mLabelLen;
    int mImageLen;
    int mImageWidth;
    int mImageHeight;
    int mImageStartPos;
    int mLableStartPos;
    fstream mLabelFile;
    fstream mImageFile;
};

#endif
