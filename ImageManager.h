#ifndef ImageManager_h
#define ImageManager_h

#include <sstream>
#include <vector>
#include "Filter.h"
#include "GrayScaleFilter.h"
#include "WarmFilter.h"
#include "CoolFilter.h"
#include "SepiaFilter.h"
#include "PencilFilter.h"
#include "InvertFilter.h"
#include "CustomFilter.h"
#include "FilterManager.h"
#include "Image.h"

class ImageManager {
private:
    FilterManager* filterManager;
    GrayScaleFilter gray;
    WarmFilter warm;
    CoolFilter cool;
    SepiaFilter sepia;
    PencilFilter pencil;
    InvertFilter invert;
    std::vector<CustomFilter> custom;
    std::vector<std::string> image_name;
    void showList();
    void showImage();
    void apply_filter();
    void TakePhoto();
    void DeleteImage();
public:
    ImageManager(FilterManager* filter);
    void run();
};

#endif /* ImageManager_h */
