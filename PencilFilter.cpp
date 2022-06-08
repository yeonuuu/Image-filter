#include "PencilFilter.h"

PencilFilter::PencilFilter() {

}
PencilFilter::~PencilFilter() {

}
void PencilFilter::apply(Image *image) {

    Mat img; Mat output_img; Mat output_img1;
    img = image->getImage();
    cv::pencilSketch(img, output_img, output_img1, 60, 0.07,  0.1);
    image->setImage(output_img);
}
