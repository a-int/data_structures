#include "vector.hpp"
#include "list.hpp"

template<typename T>
class astack{
public:
    astack() = default;
    
    T& top() {return m_Buffer.back();}
    const T& top() const {return m_Buffer.back();}

    unsigned int size() const {return m_Buffer.size();}
    bool empty() const {return m_Buffer.empty();}

    void push(const T& new_value){m_Buffer.push_back(new_value);}
    void pop() {m_Buffer.pop_back();}
private:
    vector<T> m_Buffer;
};

template<typename T>
class lstack{
public:
    lstack() = default;
    
    T& top() {return m_Buffer.front();}
    const T& top() const {return m_Buffer.front();}

    unsigned int size() const {return m_Buffer.size();}
    bool empty() const {return m_Buffer.empty();}

    void push(const T& new_value){m_Buffer.push_front(new_value);}
    void pop() {m_Buffer.pop_front();}
private:
    list<T> m_Buffer;
};