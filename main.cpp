#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <thread>
#include <cstdlib>
#include <iterator>

#include  "func.hpp"

int totalCars = 0;
map<string, int> h;
vector<string> pathes;
vector<int> carNums;
vector<int> p;

void readFile(map<string, int> &h, vector<string> &pathes, vector<int> &carNums, int &totalCars){
    int part = 1;
    ifstream in("input.txt");
    if(!in){
        cout << "Cannot open input.txt." << endl;
        return;
    }
    string str;
    while(getline(in, str)){
        if(str == "#"){
            part = 2;
            continue;
        }
        else if(part == 1){
            string temp;
            temp += str[0];
            temp += str[2];
            h.insert(pair<string, int>(temp, (int)str[4] - 48));
        }
        else if(part == 2){
            if(str.size() == 1){
                carNums.push_back((int)str[0] - 48);
                totalCars += (int)str[0] - 48;
            }
            else{
                string temp;
                for(int i=0; i<str.size(); i++){
                    if(str[i] != '-')   temp += str[i];
                }   
                pathes.push_back(temp);
            }
        }
    }
    in.close();
}

void snap(int threadNum, vector<Section*> road, int pathNumber, int p){
    ofstream threadResFile;
    string name = to_string(pathNumber) + "-" + to_string(threadNum) + ".txt";
    threadResFile.open(name, ios_base::out);

    for(int i=0; i<road.size(); i++){
        road[i]->run(threadNum, p, threadResFile);
        if(i != road.size()-1)
            threadResFile << "\n";
    }
    threadResFile.close();
}

Section* findSame(map<int, vector<Section*> > roads, string start, string end){
    map<int, vector<Section*> >::iterator it;
    for(it = roads.begin(); it != roads.end(); it++){
        for(int j=0; j<it->second.size(); j++){
            if(it->second[j]->entryNode == start && it->second[j]->exitNode == end)
                return it->second[j];
        }
    }
    return NULL;
}

int main(){
    readFile(h, pathes, carNums, totalCars);
    for(int i=0; i<totalCars; i++)
        p.push_back((rand() % 10) + 1);

    map<int, vector<Section*> > roads;
    vector<string> visited;
    for(int i=0; i<pathes.size(); i++){
        vector<Section*> tempSec;
        for(int j=0; j<pathes[i].size()-1; j++){
            string temp1, temp2;
            temp1 += pathes[i][j];
            temp2 += pathes[i][j+1];
            Section* temp = findSame(roads, temp1, temp2);
            if(temp == NULL){
                visited.push_back(temp1+temp2);
                tempSec.push_back(new Section(h.at(temp1+temp2), temp1, temp2));
            }
            else
                tempSec.push_back(temp);
                
        }
        roads.insert(pair<int, vector<Section*> > (i, tempSec));
    }

    vector<thread*> threads;

    int carNo = 0;
    for(int i=0; i<pathes.size(); i++){
        for(int j=0; j<carNums[i]; j++){
            threads.push_back(new thread(snap, carNo, roads.at(i), i, p[carNo]));
            carNo++;
        }
    }
 
    for(int i=0; i<totalCars; i++)
        threads.at(i)->join();
        
    return 1;
}
