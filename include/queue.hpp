#pragma once

template<typename T>
class queque{
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

    void push(const T& new_value){m_Buffer.push_back(new_value);}
    void pop() {m_Buffer.erase(m_Buffer.begin());}
private:
    vector<T> m_Buffer;
};