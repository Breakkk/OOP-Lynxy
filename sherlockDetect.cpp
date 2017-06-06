#include "sherlockDetect.h"
//: Progname("sherlock"), Zerobits(4), ntoken(0), Thresh(20), Ignore("\t\n"), Punct_full(",.<>/?;:'\"`~[]{}\\|!@#$%^&*()-+_="), Punct("")
Sherlock::Sherlock(int numNtoken, int numHash)
{
    set_Progname();
    set_ntoken();
    set_Thresh();
    set_Punct();
    set_Punct_full();
    set_Ignore();
    set_Zerobits();
    set_Ntoken(numNtoken);
    set_Hash(numHash);
}
void Sherlock::usage(void)
{
	fprintf(stderr, "%s: find similar files\n", Progname);

	fprintf(stderr, "usage: %s", Progname);
	fprintf(stderr, " [options] file1 file2 ...\n");

	fprintf(stderr, "options:");
	fprintf(stderr, " [-t threshold%%]");
	fprintf(stderr, " [-z zerobits]");
	fprintf(stderr, " [-n chainlength]");
	fprintf(stderr, " [-o outfile]");
	fprintf(stderr, "\n");

	fprintf(stderr, "defaults:");
	fprintf(stderr, " threshold=20%%");
	fprintf(stderr, " zerobits=3");
	fprintf(stderr, " chainlength=4");
	fprintf(stderr, " outfile=the screen");
	fprintf(stderr, "\n");

	exit(2);
}

char * Sherlock::read_word(FILE *f, int *length, char *ignore, char *punct)
{
	long max;
    char *word;
    long pos;
    char *c;
    int ch, is_ignore, is_punct;

    /* check for EOF first */
    if (feof(f))
    {
        length = 0;
        return NULL;
    }
    /* allocate a buffer to hold the string */
    pos = 0;
    max = 128;
    word = (char*)malloc(sizeof(char) * max);
    c = & word[pos];

	/* initialise some defaults */
	if (ignore == NULL)
		ignore = (char*)"";
	if (punct == NULL)
		punct = (char*)"";

    /* read characters into the buffer, resizing it if necessary */
    while ((ch = getc(f)) != EOF)
    {
    	is_ignore = (strchr(ignore, ch) != NULL);
    	if (pos == 0)
        {
    		if (is_ignore)
    			/* ignorable char found at start, skip it */
    			continue;
		}
    	if (is_ignore)
    	/* ignorable char found after start, stop */
    		break;
    	is_punct = (strchr(punct, ch) != NULL);
    	if (is_punct && (pos > 0))
        {
    		ungetc(ch, f);
    		break;
    	}
        *c = ch;
        c++;
        pos++;
    	if (is_punct)
    		break;
        if (pos == max)
        {
        /* realloc buffer twice the size */
            max += max;
            word = (char*)realloc(word, max);
            c = & word[pos];
        }
    }

    /* set length and check for EOF condition */
    *length = pos;
    if (pos == 0)
    {
        free(word);
        return NULL;
    }

    /* terminate the string and shrink to smallest required space */
    *c = '\0';
    //cout<<word<<endl;
    word = (char*)realloc(word, pos+1);
    return word;
}

int ulcmp(const void *p1, const void *p2)
{
	unsigned long v1, v2;

	v1 = *(unsigned long *) p1;
	v2 = *(unsigned long *) p2;
	if (v1 < v2)
		return -1;
	else if (v1 == v2)
		return 0;
	else
		return 1;
}
unsigned long Sherlock::ChoseHash(char *tok[], int numHash)
{
    switch(numHash)
    {
        case 1:
            hash1(tok);
            break;
        case 2:
            hash2(tok);
            break;
        case 3:
            hash3(tok);
            break;
        default:
            cout<<"Don't have this number, please try again."<<endl;
            cin>>numHash;
            set_Hash(numHash);
            ChoseHash(tok, numHash);
            break;
    }
}
unsigned long Sherlock::hash1(char *tok[])
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
unsigned long Sherlock::hash2(char *tok[])
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
unsigned long Sherlock::hash3(char *tok[])
{
    unsigned long hash = 0;
    unsigned char *s;
    for(int i = 0;i < Ntoken; i++)
        for(s = (unsigned char*)tok[i]; *s; s++)
             hash = *s + (hash << 6) + (hash << 16) - hash;
    return hash;
}

void Sherlock::init_token_array(void)
{
	int i;

	/* create global array of char* and initialise all to NULL */
	token = (char**)malloc(Ntoken * sizeof(char*));
	for (i=0; i < Ntoken; i++)
		token[i] = NULL;
}

Sig * Sherlock::signature(FILE *f)
{
	int nv, na;
	unsigned long *v, h;
	char *str;
	int i, ntoken;
	Sig *sig;

	/* start loading hash values, after we have Ntoken of them */
	v = NULL;
	na = 0;
	nv = 0;
	ntoken = 0;
	while ((str = read_word(f, &i, Ignore, Punct)) != NULL)
	{
		/* step words down by one */
		free(token[0]);
		for (i=0; i < Ntoken-1; i++)
			token[i] = token[i+1];

		/* add new word into array */
		token[Ntoken-1] = str;

		/* if we don't yet have enough words in the array continue */
		ntoken++;
		if (ntoken < Ntoken)
			continue;

		/* hash the array of words */
		h = ChoseHash(token, Hash);
		if ((h & zeromask) != 0)
			continue;

		/* discard zeros from end of hash value */
		h = h >> Zerobits;

		/* add value into the signature array, resizing if needed */
		if (nv == na)
        {
			na += 100;
			v = (unsigned long *)realloc(v, na*sizeof(unsigned long));
		}
		v[nv++] = h;
	}

	/* sort the array of hash values for speed */
	qsort(v, nv, sizeof(v[0]), ulcmp);

	/* allocate and return the Sig structure for this file */
	sig = (Sig*)malloc(sizeof(Sig));
	sig->nval = nv;
	sig->val = v;
	return sig;
}

int Sherlock::compare(Sig *s0, Sig *s1)
{
	int i0, i1, nboth, nsimilar;
	unsigned long v;

	i0 = 0;
	i1 = 0;
	nboth = 0;
	while (i0 < s0->nval && i1 < s1->nval)
    {
		if (s0->val[i0] == s1->val[i1])
        {
			v = s0->val[i0];
			while (i0 < s0->nval && v == s0->val[i0])
            {
				i0++;
				nboth++;
			}
			while (i1 < s1->nval && v == s1->val[i1])
            {
				i1++;
				nboth++;
			}
			continue;
		}
		if (s0->val[i0] < s1->val[i1])
			i0++;
		else
			i1++;
	}

	if (s0->nval + s1->nval == 0)
		return 0;	/* ignore if both are empty files */

	if (s0->nval + s1->nval == nboth)
		return 100;	/* perfect match if all hash codes match */

	nsimilar = nboth / 2;
	return 100 * nsimilar / (s0->nval + s1->nval - nsimilar);
}

void Sherlock::startDetect(int argc, char *argv[])
{
	FILE *f;
	int i, j, nfiles, start, percent;
	char *s, *outname;
	Sig **sig;
	Outfile = stdout;
	outname = NULL;

	/* handle options */
	for (start=1; start < argc; start++)
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
		usage();

	/* initialise */
	if (outname != NULL)
		Outfile = fopen(outname, "w");
	init_token_array();
	zeromask = (1<<Zerobits)-1;
	sig = (Sig **)(malloc(nfiles * sizeof(Sig *)));

	/* generate signatures for each file */
	for (i=0; i < nfiles; i++)
    {
		/* fprintf(stderr, "%s: Reading %s\n", Progname, argv[i+start]); */
		f = fopen(argv[i+start], "r");
		if (f == NULL)
        {
			fprintf(stderr, "%s: can't open %s:",
				Progname, argv[i+start]);
			perror(NULL);
			continue;
		}
		sig[i] = signature(f);
		fclose(f);
	}

	/* compare each signature pair-wise */
	for (i=0; i < nfiles; i++)
		for (j=i+1; j < nfiles; j++)
        {
			percent = compare(sig[i], sig[j]);
			if (percent >= Thresh)
				fprintf(Outfile, "%s and %s: %d%%\n",
					argv[i+start], argv[j+start], percent);
		}

	return ;
}
