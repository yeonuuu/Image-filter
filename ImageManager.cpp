#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "ImageManager.h"
using namespace cv;
namespace fs = std::filesystem;

ImageManager::ImageManager(FilterManager *filter) {
    this->filterManager = filter;

    // 필터 가져오기.
    this->gray = GrayScaleFilter();
    this->cool = CoolFilter();
    this->warm = WarmFilter();
    this->sepia = SepiaFilter();
    this->pencil = PencilFilter();
    this->invert = InvertFilter();

    // custom filter 정보 가져오기.
    this->custom = filter->getcustom();

    // 이미지 파일 가져오기.
    std::string path = "./images";
    std::string lin, name;

    for (const auto& entry : fs::directory_iterator(path)) {
        lin = entry.path().string();
        name = lin.substr(9);
        image_name.push_back(name); // 이미지 파일 이름 저장.
    }
}
void ImageManager::run() {
    int input;

    while (1) {
        printf("\n");
        printf("+-----------------------+\n");
        printf("| Image Manager Menu    |\n");
        printf("+-----------------------+\n");
        printf("| # | Menu              |\n");
        printf("+---+-------------------+\n");
        printf("| 1 | List images       |\n");
        printf("| 2 | Show image        |\n");
        printf("| 3 | Apply filter      |\n");
        printf("| 4 | Take photo        |\n");
        printf("| 5 | Delete image      |\n");
        printf("| 0 | Back              |\n");
        printf("+---+-------------------+\n");
        std::cout << "Select menu >> ";
        std::cin >> input;

        switch (input) {
        case 1:
            this->showList();
            break;
        case 2:
            this->showImage();
            break;
        case 3:
            this->apply_filter();
            break;
        case 4:
            this->TakePhoto();
            break;
        case 5:
            this->DeleteImage();
            break;
        case 0:
            return;
        default:
            break;
        }
    }
}

void ImageManager::showList() {
    //1. List images -> “./images”에 있는 이미지 파일들 목록 출력
    int i;
    printf("\n");
    printf("+--------------------------+\n");
    printf("| Image file List          |\n");
    printf("+--------------------------+\n");
    printf("| # | Menu                 |\n");
    printf("+---+----------------------+\n");
    for (i = 0; i < image_name.size(); i++) {
        if ((i + 1) > 9)
            std::cout << "| " << i + 1 << " | " << left << setw(20) << image_name.at(i) << "|" << std::endl;
        else
            std::cout << "|  " << i + 1 << " | " << left << setw(20) << image_name.at(i) << "|" << std::endl;
    }
    printf("+--------------------------+\n");
}
void ImageManager::showImage() {
    //2. Show image -> 이미지 하나 선택해서 보여주기 (이미지 목록 출력)
    int input;
    while (1) {
        this->showList();
        std::cout << std::endl;
        std::cout << "Enter the Image number you want to see (Enter 0 to go back.) : ";
        std::cin >> input;

        if (input > this->image_name.size()) {
            std::cout << "Image index out of range!" << std::endl;
            std::cout << "Total image: " << this->image_name.size() << std::endl;
            continue;
        }
        else if (input == 0) {
            break;
        }
        Image image(image_name.at(input-1));
        image.show();
    }
}
void ImageManager::apply_filter() {
    /*
    3. Apply filter
-> 필터를 적용할 이미지를 선택하세요 (이미지 목록 출력)
-> 적용할 필터를 선택하세요 (필터 목록 출력)
-> 1. Save 2. Save As 3. Discard
    */
    int input,f_input;
    this->showList();
    std::cout << std::endl;
    while (1) {
        std::cout << "Select an image to apply the filter : ";
        std::cin >> input;

        if (input > this->image_name.size()) {
            std::cout << "Image index out of range!" << std::endl;
            std::cout << "Total image: " << this->custom.size() << std::endl;
            continue;
        }
        break;
    }
    Image image(image_name.at(input - 1)); // 이미지 선택
    Image* point_img = &image;
    vector<CustomFilter> customFilterList = this->filterManager->getcustom();

    // 기본 필터 목록 출력
    printf("\n");
    printf("+-------------------------+\n");
    printf("| Basic Filter List       |\n");
    printf("+-------------------------+\n");
    printf("| # | Menu                |\n");
    printf("+---+---------------------+\n");
    printf("| 1 | Gray Scale Filter   |\n");
    printf("| 2 | Warm Filter         |\n");
    printf("| 3 | Cool Filter         |\n");
    printf("| 4 | Sepia Filter        |\n");
    printf("| 5 | Pencil Filter       |\n");
    printf("| 6 | Invert Filter       |\n");
    printf("+---+---------------------+\n");

    // custom 필터 출력
    printf("\n");
    printf("+--------------------------+\n");
    printf("| Custom Filter List       |\n");
    printf("+--------------------------+\n");
    printf("| # | Menu                 |\n");
    printf("+---+----------------------+\n");
    for (int i = 0; i < customFilterList.size(); i++) {
        if ((i+7)>9)
            std::cout << "| " << i + 7 << " | " << left << setw(20) << customFilterList.at(i).getFilterName() << "|" << std::endl;
        else
            std::cout << "|  " << i + 7 << " | " << left << setw(20) << customFilterList.at(i).getFilterName() << "|" << std::endl;
    }
    printf("+---+----------------------+\n");

    std::cout << std::endl;
    while (1) {
        std::cout << "Choose a filter to apply to the image: ";
        std::cin >> f_input;
        if (f_input > (customFilterList.size() + 6)) {
            std::cout << "filter index out of range!" << std::endl;
            std::cout << "Total filters: " << this->custom.size() + 6 << std::endl;
            continue;
        }
        break;
    }
    if (f_input > 6) { // custom filter인 경우
        imshow("image", point_img->getImage());
        customFilterList.at(f_input - 7).apply(point_img);
        image.setImage(customFilterList.at(f_input - 7).getresult()); // 수정본으로 변경
        imshow("result", point_img->getImage());
        waitKey(0);
        destroyAllWindows();
    }
    else {
        switch (f_input) {
        case 1:
            imshow("image", point_img->getImage());
            gray.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        case 2:
            imshow("image", point_img->getImage());
            warm.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        case 3:
            imshow("image", point_img->getImage());
            cool.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        case 4:
            imshow("image", point_img->getImage());
            sepia.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        case 5:
            imshow("image", point_img->getImage());
            pencil.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        case 6:
            imshow("image", point_img->getImage());
            invert.apply(point_img);
            imshow("result", point_img->getImage());
            waitKey(0);
            destroyAllWindows();
            break;
        default:
            break;
        }
    }
    int j;
    std::string newname;
    std::cout << "1. Save" << std::endl;
    std::cout << "2. Save as... (Save it as a different name.)" << std::endl;
    std::cout << "3. Discard" << std::endl;
    std::cout << "Do you want to save it? : ";
    std::cin >> j;
    switch (j) {
    case 1:
        image.save();
        std::cout << "Save it" << std::endl;
        break;
    case 2:
        std::cin.ignore();
        std::cout << "Enter a new name: ";
        std::getline(std::cin, newname, '\n');
        image.save(newname+".jpg");
        this->image_name.push_back(newname + ".jpg");
        std::cout << "Save it" << std::endl;
        break;
    case 3:
        break;
    default:
        std::cout << "index out of range!" << std::endl;
        std::cout << "Save it" << std::endl;
        break;
    }
}
void ImageManager::TakePhoto() {
    Mat img;
    std::string photo_name;
    VideoCapture cap(0);

    if (!cap.isOpened())
    {
        std::cout << "Can't find the camera." << std::endl;
    }

    std::cout << "When the camera is on, press the esc key when you want to take a picture." << std::endl;
    std::cout << "If you are ready to take a picture, enter a photo name and press the Enter key." << std::endl<<std::endl;
    std::cout << "If you can't take a picture even after entering the Esc key," << std::endl<< \
        "click the camera screen once, and enter the Esc key again." << std::endl << std::endl;
    std::cin.ignore();
    std::cout << "Enter a photo name: ";
    std::getline(std::cin, photo_name, '\n');
    
    while (1) {
        cap>>img;
        imshow("Camera img", img);
        imwrite("./images/"+photo_name+".jpg", img);
        if (waitKey(1) == 27) {
            destroyAllWindows();
            waitKey(1);
            break; // esc를 누르면 종료한다 (찍고 싶은 순간에 esc 누르면 됨.)
        }
    }
    this->image_name.push_back(photo_name + ".jpg");
    std::cout << "Photos have been saved in the images folder." << std::endl;
}
void ImageManager::DeleteImage() {
    //5. Delete image
    int input;
    this->showList();
    std::cout << std::endl;
    std::cout << "Enter the index of image you want to delete : ";
    std::cin >> input;

    if (input > this->image_name.size()) {
        std::cout << "Image index out of range!" << std::endl;
        std::cout << "Total number of images: " << this->image_name.size() << std::endl;
        return;
    }
    std::string path = "./images/" + this->image_name.at(input - 1);
    fs::remove(path);
    this->image_name.erase(this->image_name.begin() + input - 1);

    std::cout << "Image deleted!" << std::endl;
}
