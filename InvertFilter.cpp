#include "InvertFilter.h"

InvertFilter::InvertFilter() {

}
InvertFilter::~InvertFilter() {

}
void InvertFilter::apply(Image *image) {

    Mat img;  Mat output_img;
    img = image->getImage();
    cv::bitwise_not(img, output_img);
    image->setImage(output_img);
}
