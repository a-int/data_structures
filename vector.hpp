#include <memory>
#pragma once

template<typename vector>
class const_vector_iterator{
public:
    using value_type        =   const typename vector::value_type;
    using const_pointer     =   const value_type*;
    using const_reference   =   const value_type&;

public:
    const_vector_iterator(const_pointer ptr): m_Pointer(ptr) {}

    const_reference operator*(){return *m_Pointer;}
    const_reference operator->() {return &(*this->operator*());}
    const_vector_iterator& operator++(){
        ++m_Pointer;
        return *this;
    }
    const_vector_iterator& operator++(int){
        auto tmp = *this;
        m_Pointer++;
        return tmp;
    }
    const_vector_iterator& operator--(){
        --m_Pointer;
        return *this;
    }
    const_vector_iterator& operator--(int){
        auto tmp = *this;
        m_Pointer--;
        return tmp;
    }
    const_vector_iterator    operator+(unsigned int off){
        return m_Pointer+off;
    }
    const_vector_iterator&    operator+=(unsigned int off){
        m_Pointer += off;
        return *this;
    }
    const_vector_iterator    operator-(unsigned int off){
        return m_Pointer - off;
    }
    unsigned int    operator-(const const_vector_iterator& off){
        return m_Pointer - off.m_Pointer;
    }
    const_vector_iterator&    operator-=(unsigned int off){
        m_Pointer -= off;
        return *this;
    }
    
    bool operator==(const const_vector_iterator& it){return m_Pointer == it.m_Pointer;}
    bool operator!=(const const_vector_iterator& it){return !(m_Pointer == it.m_Pointer);}
private:
    const_pointer m_Pointer;
};

template<typename vector>
class vector_iterator{
public:
    using value_type    =   typename vector::value_type;
    using pointer       =   value_type*;
    using reference     =   value_type&;

public:
    vector_iterator(pointer ptr): m_Pointer(ptr) {}

    reference operator*(){return *m_Pointer;}
    reference operator->() {return &(*this->operator*());}
    vector_iterator&    operator++(){
        ++m_Pointer;
        return *this;
    }
    vector_iterator&    operator++(int){
        auto tmp = *this;
        m_Pointer++;
        return tmp;
    }
    vector_iterator&    operator--(){
        --m_Pointer;
        return *this;
    }
    vector_iterator&    operator--(int){
        auto tmp = *this;
        m_Pointer--;
        return tmp;
    }
    
    vector_iterator    operator+(unsigned int off){
        return m_Pointer+off;
    }
    
    vector_iterator&    operator+=(unsigned int off){
        m_Pointer += off;
        return *this;
    }
    vector_iterator    operator-(unsigned int off){
        return m_Pointer - off;
    }
    unsigned int    operator-(const vector_iterator& off){
        return m_Pointer - off.m_Pointer;
    }
    vector_iterator&    operator-=(unsigned int off){
        m_Pointer -= off;
        return *this;
    }
    
    bool operator==(const vector_iterator& it){return m_Pointer == it.m_Pointer;}
    bool operator!=(const vector_iterator& it){return !(m_Pointer == it.m_Pointer);}
private:
    pointer m_Pointer;
};

template<typename T>
class vector{
public:
    typedef T           value_type;
    typedef T*          pointer;
    typedef const T*    const_pointer;
    typedef T&          reference;
    typedef const T&    const_reference;
public:
    vector(): m_Size(0), m_Capacity(1), m_Buffer(m_Allocator.allocate(m_Capacity))                {}
    vector(unsigned int N): m_Size(0), m_Capacity(N), m_Buffer(m_Allocator.allocate(m_Capacity))  {}
    vector(unsigned int N, const_reference val);
    vector(const vector& orig);
    vector& operator=(const vector& rhs);
    ~vector()   {free();}

public:
    unsigned int    size()      const   {return m_Size;}
    unsigned int    capacity()  const   {return m_Capacity;}
    bool            empty()     const   {return m_Size == 0;}
    
    pointer         begin()             {return m_Buffer;}
    const_pointer   begin()     const   {return m_Buffer;}
    pointer         end()               {return m_Buffer + m_Size;}
    const_pointer   end()       const   {return m_Buffer + m_Size;}
    reference       back()              {return *(this->end()-1);}
    const_reference back()      const   {return *(this->end()-1);}
    reference       front()             {return *(this->begin());}
    const_reference front()     const   {return *(this->begin());}
    
    reference              operator[](unsigned int i)          {return m_Buffer[i];}
    const_reference        operator[](unsigned int i)  const   {return m_Buffer[i];}

    void    resize(unsigned int newCapacity);
    void    fit_to_size();
    pointer push_back(const_reference);
    void    pop_back();
    pointer insert(pointer pos, const_reference obj);
    pointer erase(pointer pos);

private:
    void    free();
    void    checkForShrink();
    void    checkForExtend();

private:
    std::allocator<T>   m_Allocator;
    unsigned int        m_Size;
    unsigned int        m_Capacity;
    pointer             m_Buffer;
};

template<typename T>
vector<T>::vector(unsigned int N, const_reference val): 
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
    pointer tmp = m_Allocator.allocate(newCapacity);

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
typename vector<T>::pointer vector<T>::push_back(const_reference value){
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
typename vector<T>::pointer vector<T>::insert(pointer pos, const_reference obj){
    unsigned int sz = pos - this->begin();
    checkForExtend();

    pointer tmp = m_Allocator.allocate(m_Capacity);
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
typename vector<T>::pointer vector<T>::erase(pointer pos){
    unsigned int sz = pos - this->begin();

    checkForShrink();
    pointer tmp = m_Allocator.allocate(m_Capacity);

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