#ifndef GrayScaleFilter_h
#define GrayScaleFilter_h

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "Image.h"
#include "Filter.h"

using namespace cv;
using namespace std;

class GrayScaleFilter : Filter {

public:
    GrayScaleFilter();
    ~GrayScaleFilter();

public:
    void apply (Image *image);

};

#endif /* GrayScaleFilter_h */
