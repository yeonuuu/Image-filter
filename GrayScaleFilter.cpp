#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "GrayScaleFilter.h"


using namespace cv;
using namespace std;

GrayScaleFilter::GrayScaleFilter() {
}

GrayScaleFilter::~GrayScaleFilter() {
}


void GrayScaleFilter::apply(Image *image) {

    Mat img, img_gray;

    img = image->getImage();
    cvtColor(img, img_gray, COLOR_BGR2GRAY);

    image->setImage(img_gray);
}
