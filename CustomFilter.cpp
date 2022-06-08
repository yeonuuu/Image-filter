#include "CustomFilter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;


CustomFilter::CustomFilter() { // Default value setting when called without parameters.
    this->filtername = "Base";
    this->brightness = 0; // 밝기  범위 -100, 100
    this->contrast = 0; // 대비(명암) 범위 0~255
    this->inversion = 0; // 채도 범위 0~255
    this->blurring = 0; // 흐리게 0~3
    this->sharpness = 0; // 선명하게 0~9
}
CustomFilter::CustomFilter(std::string filtername,int brightness,double contrast,int inversion,int blurring,int sharpness)
{
    this->filtername = filtername;
    this->brightness = brightness;
    this->contrast = contrast;
    this->inversion = inversion;
    this->blurring = blurring;
    this->sharpness = sharpness;
}

// getter, setter
std::string CustomFilter::getFilterName() { return this->filtername; } // 필터 이름 반환
int CustomFilter::getbrightness() { return this->brightness; }
double CustomFilter::getcontrast() { return this->contrast; }
int CustomFilter::getinversion() { return this->inversion; }
int CustomFilter::getblurring() { return this->blurring; }
int CustomFilter::getsharpness() { return this->sharpness; }
cv::Mat CustomFilter::getresult() { return this->result; }

void CustomFilter::setFilterName(std::string newname) { this->filtername = newname; }
void CustomFilter::setbrightness(int a) { this->brightness = a; }
void CustomFilter::setcontrast(double b) { this->contrast = b; }
void CustomFilter::setinversion(int c) { this->inversion = c; }
void CustomFilter::setblurring(int d) { this->blurring = d; }
void CustomFilter::setsharpness(int f) { this->sharpness = f; }



void CustomFilter::apply(Image* image) {

    this->result = image->getImage();
    if (this->brightness < 0) {
        this->result = this->result * (0.8);
    }
    if ((this->brightness != 0) || (this->contrast != 0)) {
        Mat new_image = Mat::zeros(this->result.size(), this->result.type());
        double alpha = this->contrast; // 대비
        int beta = this->brightness; // 밝기
        if (this->contrast != 0) {
            float a = 1.f;
            this->result = this->result + (this->result - 128) * a;
        }
        else {
            alpha = 1;
        }
        for (int y = 0; y < this->result.rows; ++y) {
            for (int x = 0; x < this->result.cols; ++x) {
                for (int c = 0; c < this->result.channels(); ++c) {
                    new_image.at<Vec3b>(y, x)[c] =
                        saturate_cast<uchar>(alpha * this->result.at<Vec3b>(y, x)[c] + beta);

                }
            }
        }
        double gamma = 0.4;
        CV_Assert(gamma >= 0);
        Mat lookUpTable(1, 256, CV_8U);
        uchar* p = lookUpTable.ptr();
        for (int i = 0; i < 256; ++i)
            p[i] = saturate_cast<uchar>(pow(i / 255.0, gamma) * 255.0);
        Mat res = new_image.clone();
        LUT(new_image, lookUpTable, res);
        this->result = res;
    }

    if (this->blurring == 1) {
        GaussianBlur(this->result, this->result, Size(5, 5), 1);
    }
    if (this->blurring == 2) {
        medianBlur(this->result, this->result, 5);
    }
    if (this->blurring == 3) {
        blur(this->result, this->result, Size(5, 5));
    }
    if (this->sharpness == 1 ) {
        Mat gaussian_blur;
        GaussianBlur(this->result, gaussian_blur, Size(5, 5), 1);
        addWeighted(this->result, 1.5, gaussian_blur, -0.5, 0, this->result);
    }
    if (this->sharpness == 2) {
        float data[9] = { -1,-1,-1,-1,9,-1,-1,-1,-1 };
        Mat kernel(3, 3, CV_32FC1, data);
        filter2D(this->result, this->result, -1, kernel, Point(-1, -1), 0);
    }

    /*
        플래그
        = 0 : 상하대칭
        > 0 : 좌우대칭
        < 0 : 상하대칭 후 좌우대칭
    */
    if (this->inversion == 1) {
        flip(this->result, this->result, 1);
    }
    if (this->inversion == 2) {
        flip(this->result, this->result, 0);
    }
    if (this->inversion == 3) {
        flip(this->result, this->result, -1);
    }
}
