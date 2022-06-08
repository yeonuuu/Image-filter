#include "SepiaFilter.h"

SepiaFilter::SepiaFilter() {

}

SepiaFilter::~SepiaFilter() {

}

void SepiaFilter::apply(Image *image) {
    
    Mat img, output_img;
    img = image->getImage();
    cv::Mat kernel = (cv::Mat_<float>(3, 3)
        <<
        0.272, 0.534, 0.131,
        0.349, 0.686, 0.168,
        0.393, 0.769, 0.189);
    cv::transform(img, output_img, kernel);
    image->setImage(output_img);
}
