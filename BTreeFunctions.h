#ifndef BTreeFunctions_h
#define BTreeFunctions_h
#include<iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "additionalFunctions.h"
using namespace std;

struct node
{
    int level;
    node *parent;
    vector<int> data;
    vector<node *> next;
    node() : level(1), parent(nullptr)
    {
    }
};

class bTree
{
private:
    bool insert(int val, node *cu);
    void split(node *l);
    void updateLevel(node *cu, int level);
    void printLevel(ofstream &fileOutput, int level, node *cu);
    node *root;
    int degree;
public:
    bTree(int d)
    {
        root = nullptr;
        degree = d;
    }
    bool empty()
    {
        return (root == nullptr);
    }
    node *getRoot()
    {
        return root;
    }
    bool insert(int val);
    int height();
    void printLevel(ofstream &out, int level);
    void inOrderTraverse(node *cu, vector<int> &input, ofstream &fileOutput);
};

bool bTree::insert(int val)
{
    if(bTree::empty())
    {
        root = new node();
        root->data.push_back(val);
        root->next.push_back(nullptr);
        root->next.push_back(nullptr);
        return true;
    }
    return insert(val, root);
}

bool bTree::insert(int val, node *cu)
{
    int pos = 0;
    while(pos < cu->data.size() && val > cu->data[pos])
    {
        pos++;
    }
    if(pos < cu->data.size() && val == cu->data[pos])
    {
        return false;
    }
    if(cu->next[pos])
    {
        return insert(val, cu->next[pos]);
    }
    cu->data.insert(cu->data.begin() + pos, val);
    cu->next.push_back(nullptr);
    if(cu->next.size() > degree)
    {
        split(cu);
    }
    return true;
}

void bTree::split(node *l)
{
    int pos = (int) l->data.size()/2 + (int) l->data.size()%2 - 1;
    int val = l->data[pos];
    node *r = new node();
    r->data.insert(r->data.begin(), l->data.begin() + pos + 1, l->data.end());
    r->next.insert(r->next.begin(), l->next.begin() + pos + 1, l->next.end());
    r->level = l->level;
    l->data.erase(l->data.begin() + pos, l->data.end());
    l->next.erase(l->next.begin() + pos + 1, l->next.end());
    
    for(int i = 0; i < r->next.size(); i++)
    {
        if(r->next[i])
        {
            r->next[i]->parent = r;
        }
    }
    if(l == root)
    {
        root = new node();
        root->data.push_back(val);
        root->next.push_back(l);
        root->next.push_back(r);
        l->parent = root;
        r->parent = root;
        updateLevel(root, 1);
    }
    else
    {
        r->parent = l->parent;
        pos = 0;
        while(l->parent->next[pos] != l)
        {
            pos++;
        }
        l->parent->data.insert(l->parent->data.begin() + pos, val);
        l->parent->next.insert(l->parent->next.begin() + pos + 1, r);
        if(l->parent->next.size() > degree)
        {
            split(l->parent);
        }
    }
}

void bTree::updateLevel(node *cu, int level)
{
    cu->level = level;
    level++;
    if(cu->next[0])
    {
        for(int i = 0; i < cu->next.size(); i++)
        {
            updateLevel(cu->next[i], level);
        }
    }
    return;
}

int bTree::height()
{
    if(bTree::empty())
    {
        return 0;
    }
    node *cu = root;
    while(cu->next[0])
    {
        cu = cu->next[0];
    }
    return cu->level;
}


void bTree::printLevel(ofstream &fileOutput, int level)
{
    if(empty() || level > height())
    {
        fileOutput << "empty" << endl;
        cout << "empty" << endl;
    }
    else
    {
        printLevel(fileOutput, level, root);
        fileOutput << endl;
        cout << endl;
        return;
    }
}

void bTree::printLevel(ofstream &fileOutput, int level, node *cu)
{
    if(cu->level == level)
    {
        for(int i = 0; i < cu->data.size(); i++)
        {
            fileOutput << cu->data[i] << " ";
            cout << cu->data[i] << " ";
        }
    }
    else
    {
        for(int i = 0; i < cu->next.size(); i++)
        {
            printLevel(fileOutput, level, cu->next[i]);
        }
    }
    return;
}

void bTree::inOrderTraverse(node *cu, vector<int> &input, ofstream &fileOutput)
{
    /* for(int i = 0; i < (int) cu->next.size() - 1; i++)
    {
        if(cu->next[i] != nullptr)
        {
            inOrderTraverse(cu->next[i], input);
        }
        cout << cu->data[i] << " ";
        i++;
        if(cu->next[i] != nullptr)
        {
            inOrderTraverse(cu->next[i], input);
        }
        i--;
    } */
    sort(input.begin(), input.end());
    printVector(input, fileOutput);
}
#endif
