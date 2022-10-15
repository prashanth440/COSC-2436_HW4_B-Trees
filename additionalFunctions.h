#ifndef additionalFunctions_h
#define additionalFunctions_h
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool isThere(vector<int> myVector, int a)
{
    for(int i = 0; i < (int) myVector.size(); i++)
    {
        if(myVector[i] == a)
        {
            return true;
        }
    }
    return false;
}

void printVector(vector<int> myVector, ofstream &fileOutput)
{
    for(int i = 0; i < (int) myVector.size(); i++)
    {
        cout << myVector[i] << " ";
        fileOutput << myVector[i] << " ";
    }
    cout << endl;
    fileOutput << endl;
}
#endif
