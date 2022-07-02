#include "vector.hpp"

template<typename T>
class stack{
public:
    stack() = default;
    
    T& top() {return m_Buffer.back();}
    const T& top() const {return m_Buffer.back();}

    unsigned int size() const {return m_Buffer.size();}
    bool empty() const {return m_Buffer.size() == 0;}

    void push(const T& new_value){m_Buffer.push_back(new_value);}
    void pop() {m_Buffer.pop_back();}
private:
    vector<T> m_Buffer;
};