#ifndef CoolFilter_h
#define CoolFilter_h

#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>

#include "Image.h"
#include "Filter.h"

using namespace cv;
using namespace std;

class CoolFilter : Filter {

public:
    CoolFilter();
    ~CoolFilter();

public:
    void apply(Image *image);

};

#endif /* CoolFilter_h */
