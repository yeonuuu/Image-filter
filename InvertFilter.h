#ifndef InvertFilter_h
#define InvertFilter_h

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include "Filter.h"
#include "Image.h"

using namespace cv;

class InvertFilter : Filter {

    private:

    public:
    InvertFilter();
    ~InvertFilter();
    void apply(Image *image);

};

#endif /* InvertFilter_h */
