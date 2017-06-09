#include "Manual.h"

void Manual::printInfo(string name)
{
    cout<<name<<": find similar files"<<std::endl;
    cout<<"usage: "<<name;
    cout<<" [options] file1 file2 ..."<<std::endl;
    cout<<"options: ";
    cout<<" [-t threshold%%]";
    cout<<" [-z zerobits]";
    cout<<" [-n chainlength]";
    cout<<" [-o outfile]"<<std::endl;
    cout<<"defaults:";
    cout<<" threshold=20%%";
    cout<<" zerobits=3";
    cout<<" chainlength=4";
    cout<<" outfile=the screen"<<std::endl;
	exit(2);
}

void Manual::judusing(int argc, char* argv[])
{
    /*char *s;
    for (int start = 1; start < argc; start++)
    {
		if (argv[start][0] != '-')
			break;
		switch (argv[start][1])
        {
		case 't':
			s = argv[++start];
			if (s == NULL)
				usage();
			Thresh = atoi(s);
			if (Thresh < 0 || Thresh > 100)
				usage();
			break;
		case 'z':
			s = argv[++start];
			if (s == NULL)
				usage();
			Zerobits = atoi(s);
			if (Zerobits < 0 || Zerobits > 31)
				usage();
			break;
		case 'n':
			s = argv[++start];
			if (s == NULL)
				usage();
			Ntoken = atoi(s);
			if (Ntoken <= 0)
				usage();
			break;
		case 'o':
			s = argv[++start];
			if (s == NULL)
				usage();
			outname = s;
			break;
		default:
			usage();
		}
	}

	nfiles = argc - start;
	if (nfiles < 2)
		usage();*/
}
