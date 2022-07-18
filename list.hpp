#include <memory>
#include "node.hpp"
#pragma once

template<typename T>
class list;

template<class list>
class list_iterator{
    friend list;
public:
    using value_type        =   typename list::value_type;
    using pointer_type      =   value_type*;
    using reference_type    =   value_type&;
public:
    list_iterator(Node<value_type>* ptr): m_Pointer(ptr){};

    reference_type  operator*()     {return (m_Pointer->value());}
    reference_type  operator->()    {return &(*this->operator*());}
    list_iterator&  operator++()    {
        m_Pointer = m_Pointer->next();
        return *this;
    }
    list_iterator&  operator++(int) {
        auto tmp = *this;
        m_Pointer = m_Pointer->next();
        return tmp;
    }
    list_iterator&  operator--()    {
        m_Pointer = m_Pointer->previous();
        return *this;
    }
    list_iterator&  operator--(int) {
        auto tmp = *this;
        m_Pointer = m_Pointer->previous();
        return tmp;
    }
    
    list_iterator   operator+(unsigned int off)         {
        auto tmp = this;
        for (unsigned int i = 0; i < off; i++)
            tmp->m_Pointer = tmp->m_Pointer->next();
        return m_Pointer;
    }
    list_iterator&  operator+=(unsigned int off)        {
        for (unsigned int i = 0; i < off; i++)
            m_Pointer = m_Pointer->next();
        return *this;
    }
    list_iterator   operator-(unsigned int off)         {
        auto tmp = this;
        for (unsigned int i = 0; i < off; i++)
            tmp->m_Pointer = tmp->m_Pointer->previous();
        return m_Pointer;
    }
    unsigned int    operator-(const list_iterator& off) {
        return m_Pointer - off.m_Pointer;
    }
    list_iterator&  operator-=(unsigned int off)        {
        for (unsigned int i = 0; i < off; i++)
            m_Pointer = m_Pointer->previous();
        return *this;
    }
    
    bool operator==(const list_iterator& it){return m_Pointer == it.m_Pointer;}
    bool operator!=(const list_iterator& it){return !(m_Pointer == it.m_Pointer);}
protected:
    Node<value_type>* get_ptr() {return m_Pointer;}
private:
    Node<value_type>* m_Pointer;
};

template<typename T>
class list{

public:
    typedef T                   value_type;
    typedef value_type*         pointer_type;
    typedef const value_type*   const_pointer_type;
    typedef value_type&         reference_type;
    typedef const value_type&   const_reference_type;
    using iterator =            list_iterator<list<T>>;

public:
    list(): m_Head(m_Allocator.allocate(1)), m_Back(m_Head), m_Size(0){}
    ~list() {free();}

    reference_type          front()         {return m_Head;}
    const_reference_type    front() const   {return m_Head;}

    reference_type          back()          {return m_Back;}
    const_reference_type    back()  const   {return this->empty()? T():m_Back->value();}

    iterator                begin()         {return m_Head;};
    const iterator          begin() const   {return m_Head;};

    iterator                end()           {return m_Back;}
    const iterator          end()   const   {return m_Back;}
    
    unsigned int            size()  const   {return m_Size;}
    bool                    empty() const   {return m_Size == 0;}

    void                    clear()         {free();}

    virtual void            push_back(const_reference_type new_Value);
    virtual void            push_front(const_reference_type new_Value);

    virtual void            pop_back();
    virtual void            pop_front();

    virtual iterator        insert(iterator pos, const_reference_type new_value);
    virtual iterator        erase(iterator pos);

protected:
    void free();

    std::allocator<Node<T>> m_Allocator;
    Node<T>*                m_Head;
    Node<T>*                m_Back;
    unsigned int            m_Size;
};

template<typename T>
void list<T>::free(){
    Node<T>* current;
    for(auto i = 0; i < m_Size; i++)
    {
        current = m_Head;
        m_Head = m_Head->next();
        m_Allocator.destroy(current);
        m_Allocator.deallocate(current, 1);
        m_Size--;
    }
}

template<typename T>
void list<T>::push_back(const_reference_type new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value);

    //There are no nodes e.g. head points to nullptr
    if(!m_Size){
        m_Head = new_node;
        m_Back = m_Head;
        m_Size++;
        return;
    }
    m_Back->set_next(new_node);
    new_node->set_previous(m_Back);
    m_Back = new_node;
    m_Size++;
}

template<typename T>
void list<T>::push_front(const_reference_type new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value);

    if (m_Size > 0) new_node->set_next(m_Head);
    else m_Back = new_node;
    m_Head->set_previous(new_node);
    m_Head = new_node;
    m_Size++;
}

template<typename T>
void list<T>::pop_back(){
    if(this->empty()) return;

    m_Back = m_Back->previous();
    m_Allocator.destroy(m_Back->next());
    m_Allocator.deallocate(m_Back->next(),1);
    m_Back->set_next(nullptr);

    m_Size--;
}

template<typename T>
void list<T>::pop_front(){
    if(this->empty()) return;

    m_Head = m_Head->next();
    m_Allocator.destroy(m_Head->previous());
    m_Allocator.deallocate(m_Head->previous(), 1);
    m_Head->set_previous(nullptr);
    m_Size--;
}

template<typename T>
typename list<T>::iterator list<T>::insert(iterator ittr, const_reference_type new_value){
    //create new node and update links in list
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_value);

    if(!m_Size){
        m_Head = new_node;
        m_Back = m_Head;
    }
    else{
        auto pos = ittr.get_ptr();
        if(pos->previous() != nullptr) {pos->previous()->set_next(new_node);}
        pos->set_previous(new_node);
        new_node->set_next(pos);
        if(pos == m_Head) {m_Head = new_node;}
    }
    m_Size++;
    return ittr;
}

template<typename T>
typename list<T>::iterator list<T>::erase(iterator ittr){
    if(m_Size){
        auto pos = ittr.get_ptr();
        if(pos->previous() != nullptr) pos->previous()->set_next(pos->next());
        if(pos->next() != nullptr) pos->next()->set_previous(pos->previous());
    
        if (pos == m_Back)  m_Back = pos->previous();
        else if(pos == m_Head) m_Head = pos->next();
        m_Allocator.destroy(pos);
        m_Allocator.deallocate(pos, 1);
        

        m_Size--;
    }
    return ittr;
}