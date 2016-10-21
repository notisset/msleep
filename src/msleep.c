#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "options/options.h"


void* sleepfn(void *args) {
    int how_much = *(int*)args;
    for(int i = 0; i < how_much; i++)
        sleep(1);
    return NULL;
}

int main(int argc, char *argv[]) {
    Options *opts = parseopt(argc, argv);
    if(opts->verbose)
        printf("threads: %d\nseconds: %lld\n", opts->thread_no, opts->time);

    long long perth = opts->time / opts->thread_no;
    if(opts->time % opts->thread_no) perth++;

    if(opts->verbose)
        printf("seconds per thread: %lld\n", perth);

    pthread_t *threads = calloc(sizeof(pthread_t), opts->thread_no);

    //spawn threads
    for(int i = 0; i < opts->thread_no; i++) {
        int ptherr = pthread_create(&threads[i], NULL, sleepfn, &perth);
        if(ptherr) {
            fprintf(stderr, "can't spawn thread\n");
            exit(EXIT_FAILURE);
        }
    }

    //join threads
    for(int i = 0; i < opts->thread_no; i++)
        pthread_join(threads[i], NULL);

    freeopt(opts);
}
