//
// belt.cpp
// Jacqueline Gronotte and Jesus Lopez
// CS 570 a05
//

#include "belt.h"
#include <iostream>
#include "producer.h"
using namespace std;
/*
 * Arguments that will be passed into each function in each thread.
 */
Belt::Belt() {
    sem_init(&mutex, 0, 1);
    sem_init(&belt_space, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&frogLimit, 0, MAX_FROGS);
    sem_init(&totalLimit, 0, 0);
    produceTotal = 0;
    consumeTotal = 0;
    frogCount = 0;
    escargotCount = 0;
};
/*
 * Function to add either frogs or escargot onto the belt and increment its count.
 */
bool Belt::push(int ID) {
    string candyName;

    if (produceTotal >= TOTAL) { //Cannot add candy to the belt
        return false;
    }
    buffer.push(ID); //Add the candy to the belt
    produceTotal++;

    if (ID == 0) {
        candyName = CFB;
        frogCount++;
    }
    else {
        candyName = EES;
        escargotCount++;
    }
    cout << "Belt: " << frogCount << " frogs + " << escargotCount << " escargots = " << (frogCount + escargotCount) <<
    ". Produced: " << produceTotal << "   Added " << candyName << ". \n";
    return true;
}
/*
 * Function to remove either frogs or escargot from the belt and decrement its count.
 */
string Belt::pop(int ID) {
    int consumeCandy;
    if (consumeTotal >= TOTAL) {
        return "full";
    }
    consumeCandy = buffer.front(); //Get the item at the front
    buffer.pop(); //Pop it off

    consumeTotal++;
    bool cfb = consumeCandy == 0? true:false;
    if (cfb) frogCount--;
    else escargotCount--;

    cout << "Belt: " << frogCount << " frogs + " << escargotCount << " escargots = " << (frogCount + escargotCount) <<
         ". Produced: " << produceTotal << "   Consumed " << (cfb? CFB : EES) <<
         ". \n";

    if (consumeTotal >= TOTAL) //If the consumer consumed the last candy
        sem_post(&totalLimit); //Sets to 1

    return (consumeCandy == 0 ? CFB : EES);
}

void productionResults(THREAD_ARGUMENTS *frogInfo, THREAD_ARGUMENTS *escargotInfo, THREAD_ARGUMENTS *lucyInfo,
        THREAD_ARGUMENTS *ethelInfo) {

    cout << "\nPRODUCTION REPORT" << endl;
    cout << "----------------------------" << endl;

    cout << CFB << " producer generated " << frogInfo->frogTotal << " candies" << endl;
    cout << EES << " producer generated " << escargotInfo->escargotTotal << " candies" << endl;

    cout << "Lucy consumed " << lucyInfo->frogTotal <<  " " CFB " + " << lucyInfo->escargotTotal << " " EES " = " <<
    (lucyInfo->frogTotal + lucyInfo->escargotTotal) << endl;
    cout << "Ethel consumed " << ethelInfo->frogTotal <<  " " CFB " + " << ethelInfo->escargotTotal << " " EES " = " <<
    (ethelInfo->frogTotal + ethelInfo->escargotTotal) << endl;
}
