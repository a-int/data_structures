#include <memory>
#include "node.hpp"
#pragma once

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
    list_iterator   operator++(int) {
        auto tmp = *this;
        m_Pointer = m_Pointer->next();
        return tmp;
    }
    list_iterator&  operator--()    {
        m_Pointer = m_Pointer->previous();
        return *this;
    }
    list_iterator   operator--(int) {
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
    
    bool operator==(list_iterator it){return m_Pointer == it.m_Pointer;}
    bool operator!=(list_iterator it){return !(m_Pointer == it.m_Pointer);}
private:
    Node<value_type>* as_node() {return m_Pointer;}
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
    list(): m_Head(m_Allocator.allocate(1)), m_Back(m_Head), m_Size(0){m_Allocator.construct(m_Head, nullptr, nullptr);}
    ~list() {free();}

    reference_type          front()         {return *this->begin();}
    const_reference_type    front() const   {return *this->begin();}
    reference_type          back()          {return *--this->end();}
    const_reference_type    back()  const   {return this->empty()? T(): *--this->end();}

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
    void        free();
    Node<T>*    ittr_deref(iterator& ittr) {return ittr.as_node();}
    
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
        m_Head  = m_Head->next();
        m_Allocator.destroy(current);
        m_Allocator.deallocate(current, 1);
    }
    // for (auto current = this->begin(); current != this->end(); current++){
    //     m_Allocator.destroy(ittr_deref(current));
    //     m_Allocator.deallocate(ittr_deref(current), 1);
    // }
    // m_Head = m_Back;
    m_Size = 0;
}

template<typename T>
void list<T>::push_back(const_reference_type new_Value){
    //Create a new node with m_Value = new_value and m_Next = m_Back
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value, m_Back, m_Back->previous());

    
    if(!m_Size) m_Head = new_node;
    else new_node->previous()->set_next(new_node);
    m_Back->set_previous(new_node);
    m_Size++;
}

template<typename T>
void list<T>::push_front(const_reference_type new_Value){
    //Create a new node with m_Value = new_value and m_Next = m_Head and m_Previous = nullptr
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value, m_Head, nullptr);

    m_Head = new_node;
    if(!m_Size){m_Head->set_next(m_Back);}
    m_Size++;
}

template<typename T>
void list<T>::pop_back(){
    if(this->empty()) return;
    auto new_previous = m_Back->previous()->previous();
    m_Allocator.destroy(m_Back->previous());
    m_Allocator.deallocate(m_Back->previous(),1);
    m_Back->set_previous(new_previous);
    if(m_Size>1) m_Back->previous()->set_next(m_Back);
    else m_Head = m_Back;
    
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
    auto        pos         = ittr_deref(ittr);
    Node<T>*    new_node    = m_Allocator.allocate(1);
    
    m_Allocator.construct(new_node, new_value, pos, pos->previous());

    if(!m_Size) m_Head = new_node;
    else{
        if(new_node->previous() != nullptr) new_node->previous()->set_next(new_node);
        if(pos == this->begin().as_node()) m_Head = new_node;
    }

    // else if(pos != this->begin().as_node())   new_node->previous()->set_next(new_node);
    pos->set_previous(new_node);
    m_Size++;
    return ittr;
}

template<typename T>
typename list<T>::iterator list<T>::erase(iterator ittr){
    if(m_Size && (ittr != this->end())){
        auto pos = ittr.as_node();
        if(pos->previous() != nullptr) pos->previous()->set_next(pos->next());
        if(pos->next() != nullptr) pos->next()->set_previous(pos->previous());
    
        if(pos == m_Head) m_Head = pos->next();
        m_Allocator.destroy(pos);
        m_Allocator.deallocate(pos, 1);
        m_Size--;
    }
    return ittr;
}