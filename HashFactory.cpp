#include "HashFactory.h"

void HashFactory::addInfo(string _info)
{
    info.push_back(_info);
    return ;
}
void HashFactory::printInfo()
{
    int start = 1;
    for(auto i : info)
    {
        cout<<start++<<".Using "<<i<<" to ensure the value of hash."<<endl;
    }
}
