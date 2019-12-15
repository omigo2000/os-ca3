#include <iostream>
#include <vector>
#include <map>
#include <semaphore.h>
#include <fstream>
#include <mutex>

using namespace std;


class Section
{ 
public:
    int h;
    string entryNode;
    string exitNode;
    sem_t semVal;
    mutex mut;

    Section(int h1, string enter, string exit);
    void run(int threadnum, int p, ofstream& file);
    int calcPollution(int p, int h);
}; 
