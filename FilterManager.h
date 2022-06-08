#ifndef FilterManager_h
#define FilterManager_h

#include <sstream>
#include <vector>
#include "CustomFilter.h"

class FilterManager {
private:
    std::vector<CustomFilter> custom;
    void showbasiclist();
    void showcustomlist();
    void create_custom();
    void show_custom();
    void Edit_custom();
    void Delete_custom();
    void save();

public:
    FilterManager();
    void run();
    std::vector<CustomFilter> getcustom() { return this->custom; }
    // 생성자 호출하면 파일에서 커스텀 필터 정보 가져와서 벡터에 저장하기.
};

#endif /* FilterManager_h */
