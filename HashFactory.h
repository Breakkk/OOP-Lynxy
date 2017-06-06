#ifndef HASHFACTORY_H
#define HASHFACTORY_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

//*******************************************************//
//      Using this class to print what we have about how //
//  to compute the hash value of the string.             //
//                                                       //
//*******************************************************//
class HashFactory
{
    vector<string> info;
public:
    HashFactory()
    {
        addInfo("multiply");
        addInfo("FNV");
        addInfo("SDBM");
    }
    void printInfo();
    void addInfo(string _info);
};

#endif //HASHFACTORY_H
