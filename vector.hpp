#include <memory>
#pragma once

template<typename T>
class vector{
public:
    vector(): m_Size(0), m_Capacity(1), m_Buffer(m_Allocator.allocate(m_Capacity))                {}
    vector(unsigned int N): m_Size(0), m_Capacity(N), m_Buffer(m_Allocator.allocate(m_Capacity))  {}
    vector(unsigned int N, const T& val);
    vector(const vector& orig);
    vector& operator=(const vector& rhs);
    ~vector()   {free();}

public:
    unsigned int    size()      const   {return m_Size;}
    unsigned int    capacity()  const   {return m_Capacity;}
    bool            empty()     const   {return m_Size == 0;}
    
    T*              begin()             {return m_Buffer;}
    const T*        begin()     const   {return m_Buffer;}
    T*              end()               {return m_Buffer + m_Size;}
    const T*        end()       const   {return m_Buffer + m_Size;}
    T&              back()              {return *(this->end()-1);}
    const T&        back()      const   {return *(this->end()-1);}
    T&              front()             {return *(this->begin());}
    const T&        front()     const   {return *(this->begin());}
    
    T&              operator[](unsigned int i)          {return m_Buffer[i];}
    const T&        operator[](unsigned int i)  const   {return m_Buffer[i];}

    void    resize(unsigned int newCapacity);
    void    fit_to_size();
    T*      push_back(const T&);
    void    pop_back();
    T*      insert(T* pos, const T& obj);
    T*      erase(T* pos);

private:
    void free();
    void checkForShrink();
    void checkForExtend();

private:
    std::allocator<T>   m_Allocator;
    unsigned int        m_Size;
    unsigned int        m_Capacity;
    T*                  m_Buffer;
};

template<typename T>
vector<T>::vector(unsigned int N, const T& val): 
    vector(N)
{
    m_Size = N;
    for (unsigned int i = 0; i < m_Size; i++)
        m_Allocator.construct(this->begin() + i, val);
}

template<typename T>
vector<T>::vector(const vector& orig):
     m_Size(orig.m_Size), m_Capacity(orig.m_Capacity), m_Buffer(m_Allocator.allocate(m_Capacity))
{
    for (unsigned int i = 0; i < m_Size; i++)
        m_Allocator.construct(this->begin() + i, orig.m_Buffer[i]);
}

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs){
    m_Size      = rhs.m_Size;
    m_Capacity  = rhs.m_Capacity;
    m_Buffer    = m_Allocator.allocate(m_Capacity);
    
    for (unsigned int i = 0; i < m_Size; i++)
        m_Allocator.construct(this->begin() + i, rhs.m_Buffer[i]);

    return *this;
}

template<typename T>
void vector<T>::free(){
    for (unsigned int i = 0; i < m_Size; i++)
        m_Allocator.destroy(m_Buffer + i);
    m_Allocator.deallocate(m_Buffer, m_Capacity);
}

template<typename T>
void vector<T>::resize(unsigned int newCapacity){
    T* tmp = m_Allocator.allocate(newCapacity);

    if (newCapacity < m_Size) m_Size = newCapacity;

    for (unsigned int i = 0; i < m_Size; i++)
        m_Allocator.construct(tmp+i, m_Buffer[i]);

    free();

    m_Capacity  = newCapacity;
    m_Buffer    = tmp;
}

template<typename T>
void vector<T>::fit_to_size()       {this->resize(m_Size);}

template<typename T>
void vector<T>::checkForExtend()    {if (m_Size == m_Capacity) this->resize(m_Capacity * 2);}

template<typename T>
void vector<T>::checkForShrink()    {if ( m_Size && (m_Size <= m_Capacity/2) ) this->resize(m_Capacity/2);}


template<typename T>
T* vector<T>::push_back(const T& value){
    checkForExtend();
    m_Allocator.construct(m_Buffer + m_Size, value);
    return m_Buffer + m_Size++;
}
template<typename T>
void vector<T>::pop_back(){
    checkForShrink();
    if (m_Size > 0) m_Allocator.destroy(m_Buffer + (--m_Size));
}

template<typename T>
T* vector<T>::insert(T* pos, const T& obj){
    unsigned int sz = pos - this->begin();
    checkForExtend();

    T* tmp = m_Allocator.allocate(m_Capacity);
    for (unsigned int i = 0; i <= m_Size; i++)
    {
        if      (i < sz)    m_Allocator.construct(tmp+i, m_Buffer[i]);
        else if (i == sz)   m_Allocator.construct(tmp+i, obj);
        else                m_Allocator.construct(tmp+i, m_Buffer[i-1]);
    }
    
    free();
    m_Buffer = tmp;
    m_Size++;
    return tmp+sz;
}

template<typename T>
T* vector<T>::erase(T* pos){
    unsigned int sz = pos - this->begin();

    checkForShrink();
    T* tmp = m_Allocator.allocate(m_Capacity);

    for (unsigned int i = 0; i < m_Size; i++)
    {
        if  (i < sz)    m_Allocator.construct(tmp+i, m_Buffer[i]);
        else            m_Allocator.construct(tmp+i, m_Buffer[i+1]);
    }

    free();
    m_Buffer = tmp;
    m_Size--;
    
    return tmp+sz;
}