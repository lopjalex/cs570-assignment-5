//
// producer.cpp
// Jacqueline Gronotte and Jesus Lopez
// CS 570 a05
//

#include <semaphore.h>
#include <pthread.h>
#include "producer.h"
#include "belt.h"
/*
 * Function that producer thread calls to produce candy.
 */
void *produce(void *arg) {
    THREAD_ARGUMENTS *producer = (THREAD_ARGUMENTS *) arg;
    bool cfb = (producer->producerID == 0); //True when we have a crunch frog bite
    struct timespec time; //Declare variable time or type struct timespec used for calculating delays
    time.tv_sec = producer->sleep/MILLI; //Initialize tv_sec
    time.tv_nsec = (producer->sleep % MILLI)*(NANO/MILLI); //Initialize tv_nsec

    while(true) {
        nanosleep(&time, NULL);
        if(cfb) {
            sem_wait(producer->frogLimit); //Wait if frog limit of 3 is reached
        }
        sem_wait(producer->empty); //Wait for space on the belt
        sem_wait(producer->mutex); //Can we enter the critical section
        bool success = producer->belt->push(producer->producerID);
        sem_post(producer->mutex);

        if(success) {
            sem_post(producer->belt_space); //Less belt space
            if (cfb) {
                producer->frogTotal++; //Increment total frogs
            }
            else {
                producer->escargotTotal++; //Increment total escargots
            }
        }
        else pthread_exit(NULL);
    }
}
