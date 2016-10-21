#ifndef _MSLEEP_OPTIONS_H
#define _MSLEEP_OPTIONS_H

typedef struct options Options;
struct options {
    int thread_no;
    int verbose;
    long long time;
};

void printhelp();

void set_opt(char opt, Options *opts);

void setdefaultopts(Options *opt);

Options* parseopt(int argc, char *argv[]);

void freeopt(Options *opt);

#endif
