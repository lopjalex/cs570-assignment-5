//
// consumer.cpp
// Jacqueline Gronotte and Jesus Lopez
// CS 570 a05
//

#include"consumer.h"
#include "belt.h"
#include <time.h>
using namespace std;
/*
 * Function that consumer thread calls to consume candy.
 */
void *consume(void *arg) {
    THREAD_ARGUMENTS *consumer = (THREAD_ARGUMENTS *) arg;
    struct timespec time; //Declare variable time or type struct timespec used for calculating delays
    time.tv_sec = consumer->sleep/ MILLI; //Initialize tv_sec
    time.tv_nsec = (consumer->sleep % MILLI) * (NANO/MILLI); //Initialize tv_nsec

    while (true) {
        nanosleep(&time, NULL); //Put thread to sleep
        if (consumer->belt->consumeTotal >= TOTAL) {
            pthread_exit(NULL); //Exit if we have consumed 100 candies
        }
        sem_wait(consumer->belt_space); //Checks to see if there is candy to consume
        sem_wait(consumer->mutex); //Enter the critical region
        string candyType = consumer->belt->pop(consumer->consumerID);
        sem_post(consumer->mutex); //Exit the critical region

        if (candyType.compare("full") != 0) {
            sem_post(consumer->empty); //Incrementing available space on belt
            if (candyType.compare(CFB) == 0) {
                sem_post(consumer->frogLimit); //If frog was consumed increment space on the belt for frog
                consumer->frogTotal++;
            } else consumer->escargotTotal++;
        }
        else pthread_exit(NULL);
    }
}
