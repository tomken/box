#ifndef __LINK_H__
#define __LINK_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

class Node {
public:
    int   value;
    Node* next;
};

class List {
public:
    List();
    ~List();

public:
    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    void dump();

private:
    Node* _head;
    Node* _tail;

};

#endif // __LINK_H__
