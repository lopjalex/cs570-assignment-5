//
// main.cpp
// Jacqueline Gronotte and  Jesus Lopez
// CS 570 a05
//

#include <string>
#include <semaphore.h>
#include "belt.h"
#include "producer.h"
#include "consumer.h"
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char ** argv) {
    Belt *belt = new Belt();

    //Struct arguments for each producer and consumer
    THREAD_ARGUMENTS frogInfo = {&belt->mutex, &belt->belt_space, &belt->empty, &belt->frogLimit, &belt->totalLimit,
                                 0, 0, 0, 0, 0,belt};
    THREAD_ARGUMENTS escargotInfo = {&belt->mutex, &belt->belt_space, &belt->empty, &belt->frogLimit, &belt->totalLimit,
                                     1, 0, 0, 0, 0, belt};
    THREAD_ARGUMENTS lucyInfo = {&belt->mutex, &belt->belt_space, &belt->empty, &belt->frogLimit, &belt->totalLimit,
                                 0, 0, 0, 0, 0, belt};
    THREAD_ARGUMENTS ethelInfo = {&belt->mutex, &belt->belt_space, &belt->empty, &belt->frogLimit, &belt->totalLimit,
                                  0, 1, 0, 0, 0, belt};
    int Option;
    while ( (Option = getopt(argc, argv, "E:L:f:e:")) != -1) {
        switch (Option) {
            case 'E': //Number of milliseconds that Ethel consumes candy
                ethelInfo.sleep = atoi(optarg);
                break;
            case 'L': //Number of milliseconds that Lucy consumes candy
                lucyInfo.sleep = atoi(optarg);
                break;
            case 'f': //Number of milliseconds required to produce crunch frog bite
               frogInfo.sleep = atoi(optarg);
                break;
            case 'e': //Number of milliseconds required to produce escargot suckers
                escargotInfo.sleep = atoi(optarg);
                break;
            default:
                break;
        }
    }
    pthread_t frog;
    pthread_t escargot;
    pthread_t lucy;
    pthread_t ethel;

    pthread_create(&frog, NULL, produce, (void*) &frogInfo);
    pthread_create(&escargot, NULL, produce, (void*) &escargotInfo);
    pthread_create(&lucy, NULL, consume, (void*) &lucyInfo);
    pthread_create(&ethel, NULL, consume, (void*) &ethelInfo);

    sem_wait(&belt->totalLimit);

    productionResults(&frogInfo, &escargotInfo, &lucyInfo, &ethelInfo);

    return 0;
}
