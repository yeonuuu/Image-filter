#ifndef CustomFilter_h
#define CustomFilter_h
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include"Image.h"
#include"Filter.h"


class CustomFilter:Filter {
private:
    std::string filtername;
    int brightness; // 밝기
    double contrast; // 대비
    int inversion; // 채도
    int blurring; // 노출
    int sharpness; // 그림자
    cv::Mat result; // 수정한 이미지

public:
    CustomFilter();
    CustomFilter(std::string filtername,
        int brightness, // 밝기
        double contrast, // 대비
        int inversion, // 좌우 반전, 상하 반전
        int blurring, // 흐리게
        int sharpness); // 선명하게
    void apply(Image* image);


    // getter, setter
    std::string getFilterName(); // 필터 이름 반환
    int getbrightness();
    double getcontrast();
    int getinversion();
    int getblurring();
    int getsharpness();
    cv::Mat getresult();
    void setFilterName(std::string newname);
    void setbrightness(int a);
    void setcontrast(double b);
    void setinversion(int c);
    void setblurring(int d);
    void setsharpness(int f);
};

#endif /* CustomFilter_h */
