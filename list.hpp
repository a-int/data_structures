#include <memory>
#include "node.hpp"
#pragma once

template<typename T>
class list{
    typedef T                   value_type;
    typedef value_type*         pointer_type;
    typedef const value_type*   const_pointer_type;
    typedef value_type&         reference_type;
    typedef const value_type&   const_reference_type;
public:
    list(): m_Head(m_Allocator.allocate(1)), m_Back(m_Head), m_Size(0){}
    ~list() {free();}

    reference_type          front()         {return m_Head->value();}
    const_reference_type    front() const   {return this->empty()? T():m_Head->value();}

    reference_type back() {return m_Back->value();}
    const_reference_type back() const {return this->empty()? T():m_Back->value();}

    Node<T>* begin() {return m_Head;};
    const Node<T>* begin() const {return m_Head;};

    Node<T>* end() {return m_Back;}
    const Node<T>* end() const {return m_Back;}
    
    unsigned int size() const {return m_Size;}
    bool empty() const {return m_Size == 0;}

    void clear() {free();}

    virtual void push_back(const_reference_type new_Value);
    virtual void push_front(const_reference_type new_Value);

    virtual void pop_back();
    virtual void pop_front();

    virtual Node<T>* insert(Node<T>* pos, const_reference_type new_value);
    virtual Node<T>* erase(Node<T>* pos);

protected:
    void free();

    std::allocator<Node<T>> m_Allocator;
    Node<T>* m_Head;
    Node<T>* m_Back;
    unsigned int m_Size;
};

template<typename T>
void list<T>::free(){
    Node<T>* current = m_Head;
    for(unsigned int i = 0; i < m_Size; i++)
    {
        m_Head = m_Head->next();
        m_Allocator.destroy(current);
        m_Allocator.deallocate(current, 1);
        current = m_Head;  
    }
    m_Size = 0;
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
Node<T>* list<T>::insert(Node<T>* pos, const_reference_type new_value){
    //create new node and update links in list
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_value);

    if(!m_Size){
        m_Head = new_node;
        m_Back = m_Head;
    }
    else{
        if(pos->previous() != nullptr) {pos->previous()->set_next(new_node);}
        pos->set_previous(new_node);
        new_node->set_next(pos);
        if(pos == m_Head) {m_Head = new_node;}
    }
    m_Size++;
    return pos;
}

template<typename T>
Node<T>* list<T>::erase(Node<T>* pos){
    if(m_Size){
        if(pos->previous() != nullptr) pos->previous()->set_next(pos->next());
        if(pos->next() != nullptr) pos->next()->set_previous(pos->previous());
    
        if (pos == m_Back)  m_Back = pos->previous();
        else if(pos == m_Head) m_Head = pos->next();
        m_Allocator.destroy(pos);
        m_Allocator.deallocate(pos, 1);
        

        m_Size--;
    }
    return pos;
}