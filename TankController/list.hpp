#pragma once

#include "stddef.h"

#include "alert.hpp"

namespace util
{

//std::listの簡易実装
//中身は片方向リンクリスト
template<class T> 
class list
{
    private:
    class node
    {
        public:
        T data;
        node *next;
        node(const T& data) : data(data), next(NULL) { }
    };
    
    public:
    class iterator
    {
        private:
        node* pos;
        
        public:
        iterator(node* pos) : pos(pos) { }
        iterator operator++(int) { iterator i(pos); ++*this; return i; }
        iterator& operator++() { pos = pos->next; return *this; }
        T& operator*() const { return pos->data; }
        bool operator==(const iterator& it) { return it.pos == this->pos; }
        bool operator!=(const iterator& it) { return it.pos != this->pos; }
    };
        
    private:
    node* first;
    node* last;
    
    public:
    list() : first(NULL), last(NULL) { }
    ~list();
    T& front() { return first->data; }
    T& back() { return last->data; }
    bool empty() { return NULL == first; }
    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    //void pop_back();
    iterator begin() { return iterator(first); }
    iterator end() { return iterator(NULL); }

};

template<class T> 
void list<T>::push_front(const T& data)
{
    node* n = new node(data);
    
    if(NULL == first)
    {
        first = n;
        last = first;
        return;
    }
    
    n->next = first;
    first = n;
}

template<class T> 
void list<T>::push_back(const T& data)
{
    node* n = new node(data);
    
    if(NULL == first)
    {
        first = n;
        last = first;
        return;
    }
    
    last->next = n;
    last = n;
}

template<class T>
void list<T>::pop_front()
{
    if(NULL == first)
        return;
    
    node* n = first;
    first = first->next;
    
    delete n;
}

template<class T> 
list<T>::~list()
{
    node* n = first;
	node* next;
    while(NULL != n)
    {
        next = n->next;
        delete n;
        n = next;
    }
}

}