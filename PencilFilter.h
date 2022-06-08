#ifndef PencilFilter_h
#define PencilFilter_h

#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/photo.hpp>
#include "Filter.h"
#include "Image.h"
using namespace cv;

class PencilFilter : Filter {

    private:

    public:
    PencilFilter();
    ~PencilFilter();
    void apply(Image *image);

};

#endif /* PencilFilter_h */
