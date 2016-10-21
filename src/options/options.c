#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "options.h"

static int parsetime(char *str, long long *time) {
    char *inv;
    *time = strtoll(str, &inv, 10);
    if(strlen(inv) > 1) return 1;
    switch(inv[0]){
        case 's':
            return 0;
        case 'm':
            *time *= 60;
            return 0;
        case 'h':
            *time *= 60 * 60;
            return 0;
        default:
            return 1;
    }
}

void printhelp() {
    char *fmt = "USAGE: msleep [OPTIONS] [TIME]\n"
                "OPTIONS:\n"
                "\t-h\tprint this help\n"
                "\t-v\tverbose\n"
                "\t-n T\tspawn T threads\n";
    fputs(fmt, stderr);
}

void set_opt(char opt, Options *opts) {
    char *invalid;
    int n;
    switch(opt) {
        case 'h':
            printhelp();
            exit(EXIT_SUCCESS);
        case 'n':
            n = strtol(optarg, &invalid, 10);
            if(strlen(invalid)) {
                fprintf(stderr, "format error\n");
                printhelp();
                exit(EXIT_FAILURE);
            }
            opts->thread_no = n;
            break;
        case 'v':
            opts->verbose = 1;
            break;
        case '?':
            if(optopt == 'n') {
                fprintf(stderr, "option n needs an argument\n");
                printhelp();
                exit(EXIT_FAILURE);
            }
            else {
                fprintf(stderr, "option %c not recognized\n", optopt);
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printhelp();
            exit(EXIT_FAILURE);
    }
}

void setdefaultopts(Options *opt) {
    opt->thread_no = 1;
    opt->time = 0;
    opt->verbose = 0;
}

Options* parseopt(int argc, char *argv[]) {
    Options *ret = calloc(sizeof(Options), 1);
    setdefaultopts(ret);

    opterr = 0;

    char c;
    while((c = getopt(argc, argv, "hn:v")) != -1)
        set_opt(c, ret);

    if(!(argc - optind) || parsetime(argv[optind], &(ret->time))) {
        fprintf(stderr, "format error\n");
        exit(EXIT_FAILURE);
    }

    return ret;
}

void freeopt(Options *opt) {
    free(opt);
}

