/*
 HW 4 - BTree
 1) BTree Insertion
 2) Inorder Traversal
 3) Print specified level
 Sources:
 1.
 https://uofh.sharepoint.com/sites/Cougartube/Shared%20Documents/Forms/AllItems.aspx?id=%2Fsites%2FCougartube%2FShared%20Documents%2FCougarTube%2FHW5%20btree%20tutorial%2Emp4&parent=%2Fsites%2FCougartube%2FShared%20Documents%2FCougarTube
 2. https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "BTreeFunctions.h"
#include "additionalFunctions.h"
#include "ArgumentManager.h"
using namespace std;
int main(int argc, char * argv[])
{
    ifstream fileInput, fileCommand;
    ofstream fileOutput;
    /*
    fileInput.open("/Users/saiprashanthharihar/Desktop/HW4/input41.txt");
    fileCommand.open("/Users/saiprashanthharihar/Desktop/HW4/command41.txt");
    fileOutput.open("/Users/saiprashanthharihar/Desktop/hw4Output.txt"); */
    
    if (argc < 2)
    {
        return -1;
    }
      
    ArgumentManager am(argc, argv);
    std::string infilename = am.get("input");
    std::string command_File = am.get("command");
    std::string outfilename = am.get("output");
    
    fileInput.open(infilename);
    fileCommand.open(command_File);
    fileOutput.open(outfilename);

    vector<int> input;
    string line;
    int a, i;
    
    
    while(!fileInput.eof())
    {
        line = "";
        getline(fileInput, line);
        istringstream num(line);
        if(line == "" || line == "\r" || line == "\n" || line == "\t")
        {
            continue;
        }
        else
        {
            while(num)
            {
                num >> a;
                if(isThere(input, a))
                {
                    continue;
                }
                else
                {
                    input.push_back(a);
                }
            }
        }
    }
    
    //printVector(input, fileOutput);
    
    string commandInput, strDegree;
    int degree = 0;
    getline(fileCommand, commandInput);
    if(commandInput.find("Degree") == 0)
    {
        for(i = 0; i < (int) commandInput.length(); i++)
        {
            if(isdigit(commandInput[i]))
            {
                strDegree.push_back(commandInput[i]);
            }
        }
        degree = stoi(strDegree);
        //cout << "Degree: " << degree << endl;
    }
    
    bTree myTree(degree);
    for(i = 0; i < (int) input.size(); i++)
    {
        myTree.insert(input[i]);
    }
    
    while(!fileCommand.eof())
    {
        commandInput = "";
        getline(fileCommand, commandInput);
        
        if(commandInput.find("Inorder Traversal") == 0)
        {
            myTree.inOrderTraverse(myTree.getRoot(), input, fileOutput);
        }
        else if(commandInput.find("Level") == 0)
        {
            int level;
            string strLevel;
            for(i = 0; i < (int) commandInput.length(); i++)
            {
                if(isdigit(commandInput[i]))
                {
                    strLevel.push_back(commandInput[i]);
                }
            }
            level = stoi(strLevel);
            //cout << "Level: " << level << endl;
            strLevel = "";
            if(level <= 0)
            {
                fileOutput << "empty" << endl;
            }
            else
            {
                myTree.printLevel(fileOutput, level);
            }
        }
        else if(commandInput.find("") == 0)
        {
            continue;
        }
    }
}
