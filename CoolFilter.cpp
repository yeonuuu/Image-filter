#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>

#include "CoolFilter.h"

using namespace cv;
using namespace std;

CoolFilter::CoolFilter() {
}

CoolFilter::~CoolFilter() {
}


void CoolFilter::apply(Image *image) {

    Mat img, img_cool;

    img = image->getImage();


    float originalValue[] = { 0,64,128,256 };

    float redValue[] = { 0,50,100,256 };
    float blueValue[] = { 0,80,160,256 };


    vector<Mat> channels(3);
    split(img, channels);

    Mat lookupTable_red(1, 256, CV_8U);
    uchar* lut = lookupTable_red.ptr();


    for (int i = 0; i < 256; i++) {
        int j = 0;
        float xval = (float)i;
        while (xval > originalValue[j]) {
            j++;
        }
        if (xval == originalValue[j]) {
            lut[i] = redValue[j];
            continue;
        }
        float slope = ((float)(redValue[j] - redValue[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
        float constant = redValue[j] - slope * originalValue[j];
        lut[i] = slope * xval + constant;
    }

    //Applying mapping and check for underflow/overflow in Red channel
    LUT(channels[2], lookupTable_red, channels[2]);

    cv::min(channels[2], 256, channels[2]);
    cv::max(channels[2], 0, channels[2]);

    Mat lookupTable_blue(1, 256, CV_8U);
    uchar* lut2 = lookupTable_blue.ptr();

    //Linear Interpolation applied to get values for all the points on X-Axis
    for (int i = 0; i < 256; i++) {
        int j = 0;
        float xval = (float)i;
        while (xval > originalValue[j]) {
            j++;
        }
        if (xval == originalValue[j]) {
            lut2[i] = blueValue[j];
            continue;
        }
        float slope = ((float)(blueValue[j] - blueValue[j - 1])) / ((float)(originalValue[j] - originalValue[j - 1]));
        float constant = blueValue[j] - slope * originalValue[j];
        lut2[i] = slope * xval + constant;
    }

    LUT(channels[0], lookupTable_blue, channels[0]);
    cv::min(channels[0], 256, channels[0]);
    cv::max(channels[0], 0, channels[0]);


    merge(channels, img_cool);




    imshow("image", img);
    imshow("result", img_cool);

    waitKey(0);

    image->setImage(img_cool);
}
