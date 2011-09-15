#pragma once

#include "define.hpp"

namespace util
{

//要素削除なし、末尾追加のみ
//アクセスはイテレータのみ
template<class T> 
class linked_list
{
    private:
    class node
    {
        public:
        const T data;
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
        iterator operator++() { pos = pos->next; return *this; }
        T operator*() { return pos->data; }
        bool operator==(iterator it) { return it.pos == this->pos; }
        bool operator!=(iterator it) { return it.pos != this->pos; }
    };
        
    private:
    node* first;
    node* last;
    
    public:
    linked_list() : first(NULL), last(NULL) { }
    ~linked_list();
    void add(const T& data);
    iterator begin() { return iterator(first); }
    iterator end() { return iterator(last); }

};

template<class T> 
void linked_list<T>::add(const T& data)
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
linked_list<T>::~linked_list()
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