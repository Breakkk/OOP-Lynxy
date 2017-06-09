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

unsigned long HashFactory::ChoseHash(char *tok[], int Ntoken)
{
    switch(numHash)
    {
        case 1:
            hash1(tok, Ntoken);
            break;
        case 2:
            hash2(tok, Ntoken);
            break;
        case 3:
            hash3(tok, Ntoken);
            break;
        default:
            cout<<"Don't have this number, please try again."<<endl;
            int num = 0;
            cin>>num;
            set_numHash(num);
            ChoseHash(tok, Ntoken);
            break;
    }
}
unsigned long HashFactory::hash1(char *tok[], int Ntoken)
{
    unsigned long h;
	unsigned char *s;
	int i;

	h = 0;
	for (i=0; i < Ntoken; i++)
		for (s = (unsigned char*)tok[i]; *s; s++)
			h = h*31 + *s;
	return h;
}
unsigned long HashFactory::hash2(char *tok[], int Ntoken)
{
    int p = 16777619;
    int hash = (int)2166136261L;
    unsigned char *s;
    for(int i = 0;i < Ntoken; i++)
        for(s = (unsigned char*)tok[i]; *s; s++)
        hash = (hash ^ *s) * p;
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    return hash;
}
unsigned long HashFactory::hash3(char *tok[], int Ntoken)
{
    unsigned long hash = 0;
    unsigned char *s;
    for(int i = 0;i < Ntoken; i++)
        for(s = (unsigned char*)tok[i]; *s; s++)
             hash = *s + (hash << 6) + (hash << 16) - hash;
    return hash;
}
