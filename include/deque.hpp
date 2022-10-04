#include "vector.hpp"
#pragma once

template<typename T>
class deque{
public:
    deque() = default;

public:
    T& operator[](unsigned int index){return m_Buffer[index];}
    T& at(unsigned int index){assert(index<this->size()); return m_Buffer[index];}

    T& front() {return m_Buffer.front();}
    const T& front() const {return m_Buffer.front();}

    T& back() {return m_Buffer.back();}
    const T& back() const {return m_Buffer.back();}

    T* begin() {return m_Buffer.begin();}
    const T* begin() const {return m_Buffer.begin();}

    T* end() {return m_Buffer.end();}
    const T* end() const {return m_Buffer.end();}

    unsigned int size() {return m_Buffer.size();}
    bool empty() {this->size() == 0;}

    void resize(unsigned int new_size) {m_Buffer.resize(new_size);}

    void push_back(const T& new_value){m_Buffer.push_back(new_value);}
    void push_front(const T& new_value){m_Buffer.insert(m_Buffer.begin(), new_value);}
    
    void pop_back() {m_Buffer.pop_back();}
    void pop_front() {m_Buffer.erase(m_Buffer.begin());}

    void insert(T* index, const T& new_value){m_Buffer.insert(index, new_value);}
    void erase(T* index){m_Buffer.erase(index);}

private:
    vector<T> m_Buffer;
};