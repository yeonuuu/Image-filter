#include <iostream>
#include "Image.h"
#include "Filter.h"

Image::Image(const string filename) {
    this->filename = filename;
    
    string image_path = findFile(filename);
    image = imread(image_path, IMREAD_COLOR);
    
    if (image.empty()) {
        cout << "Could not read the image: " << image_path << endl;
    }
}

Image::~Image() {
}

void Image::show() {
    imshow(filename, image);
    setWindowProperty(filename, WND_PROP_TOPMOST, 1);
    waitKey(0);
    destroyAllWindows();
    waitKey(1);
}

void Image::applyFilter(Filter *filter) {
    filter->apply(this);
}

void Image::save() {
    imwrite("./images/" + filename, image);
}

void Image::save(string filename) {
    imwrite("./images/" + filename, image);
}

Mat Image::getImage() {
    return image;
}

void Image::setImage(Mat image) {
    this->image = image;
}

string Image::findFile(string filename) {
    return "./images/" + filename;
}
