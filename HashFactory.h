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
    int numHash;                              //the label of hash method
public:
    HashFactory()
    {
        addInfo("multiply");
        addInfo("FNV");
        addInfo("SDBM");
    }
    void printInfo();
    void addInfo(string _info);

    unsigned long ChoseHash(char *tok[],  int Ntoken);
    unsigned long hash1(char *tok[], int Ntoken);
	unsigned long hash2(char *tok[], int Ntoken);
	unsigned long hash3(char *tok[], int Ntoken);

    void set_numHash(int num) {numHash = num;}
    int  get_numHash() {return numHash;}
};

#endif //HASHFACTORY_H
