#include <thread>
#include <chrono>
#include <fstream>
#include <string>

#include "func.hpp"
#include "global.h"

Section::Section(int h1, string enter, string exit){
    h = h1;
    entryNode = enter;
    exitNode = exit;
    //sem_init(&semVal, 0, 1);
}

int Section::calcPollution(int p, int h){
    int totalPollution = 0;
    for (int k=0; k<=10000000; k++)
        totalPollution += k / (1000000 * p * h);
    return totalPollution;
}

void Section::run(int threadnum, int p, ofstream& threadResFile){
    //sem_wait(&semVal);
    mut.lock();
    chrono::milliseconds entranceTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    int emission = calcPollution(p, h);
    totalEmission += emission;
    chrono::milliseconds exitTime = chrono::duration_cast<chrono::milliseconds>(chrono::system_clock::now().time_since_epoch());
    mut.unlock();
    threadResFile << entryNode << ", ";
    threadResFile << entranceTime.count() << ", ";
    threadResFile << exitNode << ", ";
    threadResFile << exitTime.count() << ", ";
    threadResFile << to_string(emission) << ", ";
    threadResFile << to_string(totalEmission);
    //sem_post(&semVal);
}