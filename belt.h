//
// belt.h
// Jacqueline Gronotte and  Jesus Lopez
// CS 570 a05
//
#ifndef belt_h
#define belt_h
#include <string>

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <queue>

#define BUFFER_SIZE 10
#define MAX_FROGS 3
#define TOTAL 100
#define CFB "crunchy frog bite"
#define EES "everlasting escargot sucker"
#define NANO 1000000000
#define MILLI 1000

using namespace std;
bool push(int producerID);
int pop(int producerID);

class Belt {
public:
    Belt(); //Constructor
    queue<int> buffer; //Holds items on belt
    sem_t mutex; //Semaphore to enter and exit critical region
    sem_t belt_space; //Semaphore to keep track of number of items on belt
    sem_t empty; //Semaphore to keep track of space on belt
    sem_t frogLimit; //Semaphore to keep track of number of frogs on belt
    sem_t totalLimit; //Semaphore used as barrier
    int produceTotal; //Total number of items produced
    int consumeTotal; //Total number of items consumed
    int frogCount; //Numbers of frogs on the belt
    int escargotCount; //Number of escargot on the belt
    bool push(int ID); //Function to push items onto belt
    string pop(int ID); //Function to pop items off belt
};

/*
 * Arguments that will be passed into each function in each thread.
 */
typedef struct {
    sem_t *mutex; //Semaphore pointer for critical region
    sem_t *belt_space; //Semaphore pointer for belt space
    sem_t *empty; //Semaphore pointer for empty
    sem_t *frogLimit; //Semaphore pointer for frog limit
    sem_t *totalLimit; //Semaphore pointer for total limit
    int producerID; //ID for frog is 0, ID for escargot is 1
    int consumerID; //ID for Lucy is 0, ID for Ethel is 1
    int frogTotal; //Total number of frogs, used in production report
    int escargotTotal; //Total number of escargot, used in production report
    int sleep; //Used for delay argument
    Belt *belt; //Pointer to belt object
} THREAD_ARGUMENTS;

/*
 * Function to print the production results including total number of frogs and escargot produced and amount consumed
 * by Lucy and Ethel.
 */
void productionResults(THREAD_ARGUMENTS *frogInfo, THREAD_ARGUMENTS *escargotInfo, THREAD_ARGUMENTS *lucyInfo,
        THREAD_ARGUMENTS *ethelInfo);

#endif /* belt_h */
