#ifndef DETECT_H
#define DETECT_H
/********************************************************************
//      这个类为一个抽象类，在以后可以增加不同的Detect来检查两个文件的相
//      似度。
//
********************************************************************/
class Detect
{

public:
    Detect() {}
    virtual ~Detect() {}
    virtual void startDetect(int , char **) = 0;
};


#endif //DETECT_H
