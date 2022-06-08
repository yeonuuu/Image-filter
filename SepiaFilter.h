#ifndef SepiaFilter_h
#define SepiaFilter_h

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Filter.h"
#include "Image.h"

using namespace cv;

class SepiaFilter : Filter {

    private:

    public:
    SepiaFilter();
    ~SepiaFilter();
    void apply(Image *image);

};

#endif /* SepiaFilter_h */
