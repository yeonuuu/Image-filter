#ifndef Filter_h
#define Filter_h

class Image;

class Filter {
public:
    Filter();
    ~Filter();
    
public:
    virtual void apply(Image *image) = 0;
};

#endif /* Filter_h */
