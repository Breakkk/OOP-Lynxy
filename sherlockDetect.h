#ifndef SHERLOCKDETECT_H
#define SHERLOCKDETECT_H

#include <iostream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Detect.h"
using namespace std;

struct Sig
{
	int		nval;
	unsigned long	*val;
};

class Sherlock : public Detect
{
    char *		Progname;
    int	    	Ntoken;
    int	       	Zerobits;
    unsigned long	zeromask;
    int		    ntoken;
    char **		token;
    FILE *		Outfile;
    int		    Thresh;

    /* characters to ignore at start and end of each word */
    char *		Ignore;

    /* characters to treat as word-separators or words on their own */
    char *		Punct_full;
    char *		Punct;
public:

    void set_Progname(char* _prog = (char*)"sherlock") {Progname = _prog;}
    void set_Zerobits(int num = 4) {Zerobits = num;}
    void set_ntoken(int num = 0) {ntoken = num;}
    void set_Thresh(int num = 20) {Thresh = num;}
    void set_Ignore(char * _ign = (char*)" \t\n") {Ignore = _ign;}
    void set_Punct_full(char* _punct = (char*)",.<>/?;:'\"`~[]{}\\|!@#$%^&*()-+_=") {Punct_full = _punct;}
    void set_Punct(char* _punct = (char*)"") {Punct = _punct;}
    void set_Hash(int _hash) {Hash = _hash;}

    Sherlock(int numNtoken, int numHash);
    void startDetect(int , char **);

    void usage(void);
    char * read_word(FILE *f, int *length, char *ignore, char *punct);
    /* ulcmp:  compare *p1 and *p2 */
    //int ulcmp(const void *p1, const void *p2);
	unsigned long ChoseHash(char *tok[], int numHash);
    unsigned long hash1(char *tok[]);
	unsigned long hash2(char *tok[]);
	unsigned long hash3(char *tok[]);

    void init_token_array(void);
    Sig * signature(FILE *f);
    int compare(Sig *s0, Sig *s1);
    void set_Ntoken(int _Ntoken) {Ntoken = _Ntoken;}

protected:
	int         Hash;
};

int ulcmp(const void *p1, const void *p2);

#endif //SHERLOCKDETECT_H
