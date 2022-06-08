#ifndef Greeter_h
#define Greeter_h

#include "ImageManager.h"
#include "FilterManager.h"

class Greeter {
public:
    Greeter();
    ~Greeter();
    
public:
    void run();
    
private:
    ImageManager* imageManager;
    FilterManager* filterManager;
    
private:
    void printLogo();
};

#endif /* Greeter_h */
