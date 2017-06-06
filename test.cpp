#include "Detect.h"
#include "sherlockDetect.h"
#include "HashFactory.h"

int main(int argc, char *argv[])
{
    int numNtoken, numHash;
    cout<<"Please input a number of Ntoken to ensure how many words do you want to taken to use sherlock.(default value is 3)"<<endl;
    cin>>numNtoken;
    cout<<"Please input a number of the way to compute the value of hash."<<endl;
    HashFactory print;
    print.printInfo();
    cin>>numHash;
    Detect* p = new Sherlock(numNtoken, numHash);
    p -> startDetect(argc, argv);
    delete p;
    //Sherlock p;
    //p.startDetect(argc, argv);

    return 0;
}
