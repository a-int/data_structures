#include <memory>
#include "node.hpp"
#include "list.hpp"
#pragma once

template<typename T>
class forward_list: public list<T>{
public:
    forward_list(): list<T>(){}
    ~forward_list() {this->free();}

    void push_back(const T& new_Value) override;
    void push_front(const T& new_Value) override;

    void pop_back() override;
    void pop_front() override;
};

template<typename T>
void forward_list<T>::push_back(const T& new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = this->m_Allocator.allocate(1);
    this->m_Allocator.construct(new_node, new_Value);

    //There are no nodes e.g. head points to nullptr
    if(!this->m_Size){
        this->m_Head = new_node;
        this->m_Back = this->m_Head;
        this->m_Size++;
        return;
    }
    this->m_Back->set_next(new_node);
    this->m_Back = new_node;
    this->m_Size++;
}

template<typename T>
void forward_list<T>::push_front(const T& new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = this->m_Allocator.allocate(1);
    this->m_Allocator.construct(new_node, new_Value);

    if (this->m_Size > 0) new_node->set_next(this->m_Head);
    else this->m_Back = new_node;
    this->m_Head = new_node;
    this->m_Size++;
}

template<typename T>
void forward_list<T>::pop_back(){
    if(this->empty()) return;

    Node<T>* penultimate = this->m_Head;

    if(this->m_Size != 1)
        while(penultimate->next() != this->m_Back) penultimate = penultimate->next();

    penultimate->set_next(nullptr);
    //if size==1 m_Back points to the only node
    this->m_Allocator.destroy(this->m_Back);
    this->m_Allocator.deallocate(this->m_Back, 1);
    this->m_Back = penultimate;
    // if (m_Size == 1) {
    //     m_Head = nullptr;
    //     m_Back = nullptr;
    // }
    this->m_Size--;
}

template<typename T>
void forward_list<T>::pop_front(){
    if(this->empty()) return;

    Node<T>* first = this->m_Head;
    
    this->m_Head = this->m_Head->next();
    this->m_Allocator.destroy(first);
    this->m_Allocator.deallocate(first, 1);
    // if (m_Size == 1) {
    //     m_Head = nullptr;
    //     m_Back = nullptr;
    // }
    this->m_Size--;
}
