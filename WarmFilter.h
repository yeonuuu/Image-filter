#ifndef WarmFilter_h
#define WarmFilter_h

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "Image.h"
#include "Filter.h"

using namespace cv;
using namespace std;

class WarmFilter : Filter {

public:
    WarmFilter();
    ~WarmFilter();

public:
    void apply (Image *image);

};

#endif /* WarmFilter_h */
