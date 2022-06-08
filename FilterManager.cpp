#include "FilterManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "CustomFilter.h"

FilterManager::FilterManager()
{
    std::string line;
    std::ifstream fin("./customs.txt"); // customs파일에서 custom 필터 정보 가져오기.

    if (fin.is_open()) {
        while (getline(fin, line)) {
            std::string filtername;
            int brightness; // 밝기
            int contrast; // 대비
            int inversion; // 채도
            int blurring; // 노출
            int sharpness; // 그림자
            

            std::vector<std::string> parsedLine;
            std::stringstream lineStream(line);

            while (lineStream.good()) {
                std::string substr;
                getline(lineStream, substr, ';');
                parsedLine.push_back(substr);
            }
            filtername = parsedLine.at(0);
            brightness = std::stoi(parsedLine.at(1));
            contrast = std::stoi(parsedLine.at(2));
            inversion = std::stoi(parsedLine.at(3));
            blurring = std::stoi(parsedLine.at(4));
            sharpness = std::stoi(parsedLine.at(5));
            CustomFilter customfilter = CustomFilter(filtername, brightness, contrast, inversion, blurring, sharpness);
            this->custom.push_back(customfilter);
        }
        fin.close();
    }
    else {
        std::cout << "Failed to open Filter list file.";
        exit(0);
    }
};
void FilterManager::run() {
    int input;
    /*
1. List basic filters->기본 필터 목록 출력
2. List custom filters->커스텀 필터 목록 출력
3. Create custom filter
->새로 생성할 필터 이름을 입력하세요
4. Show custom filter->커스텀필터 하나 보기(커스텀필터 목록 출력)
5. Edit custom filter->커스텀필터 수정(목록 먼저 출력)
6. Delete custom filter->커스텀필터 삭제(목록 먼저 출력)
0. Back
*/
    while (1) {
        printf("\n");
        printf("+---------------------------+\n");
        printf("| Filter Manager Menu       |\n");
        printf("+---------------------------+\n");
        printf("| # | Menu                  |\n");
        printf("+---+-----------------------+\n");
        printf("| 1 | List basic filters    |\n");
        printf("| 2 | List custom filters   |\n");
        printf("| 3 | Create custom filter  |\n");
        printf("| 4 | Show custom filter    |\n");
        printf("| 5 | Edit custom filter    |\n");
        printf("| 6 | Delete custom filter  |\n");
        printf("| 0 | Back                  |\n");
        printf("+---+-----------------------+\n");
        std::cout << "Select menu >> ";
        std::cin >> input;

        switch (input) {
        case 1:
            this->showbasiclist();
            break;
        case 2:
            this->showcustomlist();
            break;
        case 3:
            this->create_custom();
            break;
        case 4:
            this->show_custom();
            break;
        case 5:
            this->Edit_custom();
            break;
        case 6:
            this->Delete_custom();
            break;
        case 0:
            this->save();
            return;
        default:
            break;
        }
    }
}
void FilterManager::showbasiclist() {
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
}

void FilterManager::showcustomlist() {
    printf("\n");
    printf("+-------------------------+\n");
    printf("| Custom Filter List      |\n");
    printf("+-------------------------+\n");
    printf("| # | Menu                |\n");
    printf("+---+---------------------+\n");
    for (int i = 0; i < this->custom.size(); i++) {
        std::cout << "| "<<i + 1 << " | " << left<< setw(20) << this->custom.at(i).getFilterName() << "|" << std::endl;
    }
    printf("+---+---------------------+\n");
}

void FilterManager::create_custom() {
    std::string filtername;
    int brightness; // 밝기 범위 -100, 100
    double contrast; // 대비(명암) 범위 0~255
    int inversion; // 채도 범위 0~255
    int blurring; // 흐리게 0~3
    int sharpness; //선명하게 0~9

    std::cout << ("If you don't want to apply the effect, enter 0 in the corresponding element.")<<std::endl;

    std::cout << ("Insert filter name: ");
    std::cin.ignore();
    std::getline(std::cin, filtername, '\n');

    std::cout << ("insert brightness (range -100 ~ 100) : ");
    std::cin >> brightness;

    std::cout << ("insert contrast (range 0 ~ 2, real number) : ");
    std::cin >> contrast;

    std::cout << ("insert inversion (range 0 ~ 3, 1: Left and right inversion, 2: Top and bottom inversion, 3: All of inversion) : ");
    std::cin >> inversion;

    std::cout << ("insert blurring (range 0 ~ 3) : ");
    std::cin >> blurring;

    std::cout << ("insert sharpness (range 0 ~ 2, 0: No apply, 1: Soft, 2: Hard) : ");
    std::cin >> sharpness;

    CustomFilter newfilter = CustomFilter(filtername, brightness, contrast, inversion, blurring, sharpness);

    custom.push_back(newfilter);
    std::cout << ("Complete!!") << std::endl;
}

void FilterManager::show_custom() {
    // Show custom filter->커스텀필터 하나 보기(커스텀필터 목록 출력)
    int input;
    while (1) {
        this->showcustomlist();
        printf("| 0 | Back                |\n");
        printf("+---+---------------------+\n");
        std::cout << "Select menu >> ";
        std::cin >> input;

        if (input > this->custom.size()) {
            std::cout << "custom filter index out of range!" << std::endl;
            std::cout << "Total filter: " << this->custom.size() << std::endl;
            continue;
        }
        else if (input == 0) {
            break;
        }

        std::cout << "Filter name: " << this->custom.at(input-1).getFilterName() << std::endl;
        std::cout << "Brightness: " << this->custom.at(input-1).getbrightness() << std::endl;
        std::cout << "Contrast: " << this->custom.at(input-1).getcontrast() << std::endl;
        std::cout << "Saturation: " << this->custom.at(input-1).getinversion() << std::endl;
        std::cout << "Exposure: " << this->custom.at(input-1).getblurring() << std::endl;
        std::cout << "Shadow: " << this->custom.at(input - 1).getsharpness() << std::endl << std::endl;
    }
}

void FilterManager::Edit_custom() {
    int input,num;
    std::string newName;
    int newdata;
    while (1) {
        this->showcustomlist();
        printf("| 0 | Back                |\n");
        printf("+---+---------------------+\n");
        std::cout << "Select menu >> ";
        std::cin >> input;

        if (input > this->custom.size()) {
            std::cout << "Custom filter index out of range!" << std::endl;
            std::cout << "Total filter: " << this->custom.size() << std::endl;
            continue;
        }
        else if (input == 0) {
            break;
        }
        else {
            while (1) {

                printf("\n");
                printf("+--------------------------------------+\n");
                printf("| Custom Filter                        |\n");
                printf("+---+----------------------------------+\n");
                std::cout << "| 1 | " << left << "Filter name: " << setw(20) << this->custom.at(input - 1).getFilterName() << "|" << std::endl;
                std::cout << "| 2 | " << left << "Brightness:  " << setw(20) << this->custom.at(input - 1).getbrightness() << "|" << std::endl;
                std::cout << "| 3 | " << left << "Contrast:    " << setw(20) << this->custom.at(input - 1).getcontrast() << "|" << std::endl;
                std::cout << "| 4 | " << left << "Inversion:   " << setw(20) << this->custom.at(input - 1).getinversion() << "|" << std::endl;
                std::cout << "| 5 | " << left << "Blurring:    " << setw(20) <<this->custom.at(input - 1).getblurring() << "|" << std::endl;
                std::cout << "| 6 | " << left << "Sharpness:   " << setw(20) <<this->custom.at(input - 1).getsharpness() << "|" << std::endl;
                printf("+---+----------------------------------+\n");
                printf("| 0 | Back                             |\n");
                printf("+---+----------------------------------+\n");
                std::cout << "Select menu >> ";
                std::cin >> num;
                if (num == 0)
                    break;
                switch (num) {
                case 1:
                    std::cin.ignore();
                    std::cout << "Enter new name: ";
                    std::getline(std::cin, newName, '\n');
                    this->custom.at(input - 1).setFilterName(newName);
                    std::cout << "Filter name changed!" << std::endl;
                    continue;
                case 2:
                    std::cout << "Enter new Brightness number: ";
                    std::cin >> newdata;
                    this->custom.at(input - 1).setbrightness(newdata);
                    std::cout << "Brigntness number changed!" << std::endl;
                    continue;
                case 3:
                    std::cout << "Enter new contrast number: ";
                    std::cin >> newdata;
                    this->custom.at(input - 1).setcontrast(newdata);
                    std::cout << "Contrast number changed!" << std::endl;
                    continue;
                case 4:
                    std::cout << "Enter new inversion number: ";
                    std::cin >> newdata;
                    this->custom.at(input - 1).setinversion(newdata);
                    std::cout << "inversion number changed!" << std::endl;
                    continue;
                case 5:
                    std::cout << "Enter new blurring number: ";
                    std::cin >> newdata;
                    this->custom.at(input - 1).setblurring(newdata);
                    std::cout << "blurring number changed!" << std::endl;
                    continue;
                case 6:
                    std::cout << "Enter new sharpness number: ";
                    std::cin >> newdata;
                    this->custom.at(input - 1).setsharpness(newdata);
                    std::cout << "sharpness number changed!" << std::endl;
                    continue;
                default:
                    std::cout << "Custom filter index out of range!" << std::endl;
                    std::cout << "Total filter: " << this->custom.size() << std::endl;
                    continue;
                }
            }
        }
        
    }
}

void FilterManager::Delete_custom() {
    int input;
    this->showcustomlist();
    printf("| 0 | Back                |\n");
    printf("+---+---------------------+\n");
    std::cout << "Select menu >> ";
    std::cin >> input;

    if (input == 0) {
        return;
    }
    if (input > this->custom.size()) {
        std::cout << "custom filter index out of range!" << std::endl;
        std::cout << "Total number of filters: " << this->custom.size() << std::endl;
        return;
    }

    this->custom.erase(this->custom.begin() + input - 1);

    std::cout << "Filter deleted!" << std::endl;
}

void FilterManager::save() {
    std::ofstream fout("./customs.txt");
    if (fout.fail()) {
        std::cout << "File not found: customs.txt" << std::endl;
        std::cout << "Cannot save custom filter!" << std::endl;
    }
    for (CustomFilter customfilter : this->custom) {
        std::string line = "";
        std::string filtername=customfilter.getFilterName();
        int brightness=customfilter.getbrightness(); // 밝기
        int contrast=customfilter.getcontrast(); // 대비
        int inversion=customfilter.getinversion(); // 채도
        int blurring=customfilter.getblurring(); // 노출
        int sharpness=customfilter.getsharpness(); // 그림자
        line.append(filtername);
        line.append(";");
        line.append(std::to_string(brightness));
        line.append(";");
        line.append(std::to_string(contrast));
        line.append(";");
        line.append(std::to_string(inversion));
        line.append(";");
        line.append(std::to_string(blurring));
        line.append(";");
        line.append(std::to_string(sharpness));
        line.append("\n");
        fout << line;
    }
    fout.close();
}
