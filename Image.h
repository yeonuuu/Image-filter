#ifndef Image_h
#define Image_h

#include <opencv2/highgui.hpp>

class Filter;

using namespace std;
using namespace cv;

class Image {
public:
    Image(const string filename);
    ~Image();
    
public:
    void show();
    void applyFilter(Filter *filter);
    void save();
    void save(string filename);
    
    Mat getImage();
    void setImage(Mat image);
    
private:
    string filename;
    Mat image;
    
private:
    string findFile(string filename);
};

#endif /* Image_h */
