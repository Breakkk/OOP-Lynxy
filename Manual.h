#ifndef MANUAL_H
#define MANUAL_H

#include <iostream>
using std::string;
using std::cout;
class Manual
{
public:
    Manual() {}
    void printInfo(string name);
    void judusing(int argc, char *argv[]);
    ~Manual() {}
};

#endif //MANUAL_H
