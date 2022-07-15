#include <memory>
#pragma once

template<typename T>
class Node{
public:
    Node(): m_Value(m_Allocator.allocate(m_Size)), m_Next(nullptr), m_Previous(nullptr) {m_Allocator.construct(m_Value);}
    Node(const T& val): m_Value(m_Allocator.allocate(m_Size)), m_Next(nullptr), m_Previous(nullptr) {m_Allocator.construct(m_Value, val);}
    Node(const T& val, const Node<T>& Next): m_Value(m_Allocator.allocate(m_Size)), m_Next(&Next), m_Previous(nullptr) {m_Allocator.construct(m_Value, val);}
    Node(const T& val, const Node<T>& Next, const Node<T>& Prev): m_Value(m_Allocator.allocate(m_Size)), m_Next(&Next), m_Previous(Prev) {m_Allocator.construct(m_Value, val);}
    ~Node(){free();}
private:
    void free();

public:
    Node<T>* next() {return m_Next;}
    const Node<T>* next() const {return m_Next;}
    
    Node<T>* previous() {return m_Previous;}
    const Node<T>* previous() const {return m_Previous;}
    
    T& value() {return *m_Value;}
    const T& value() const {return *m_Value;}
    
    
    void set_next(Node<T>* Node) {m_Next = Node;}
    void set_previous(Node<T>* Node) {m_Previous = Node;}
    void set_value(const T& new_Value);

private:
    std::allocator<T> m_Allocator;
    const unsigned int m_Size = 1;
    T* m_Value;
    Node<T>* m_Next;
    Node<T>* m_Previous;
};

template<typename T>
void Node<T>::free(){
    m_Allocator.destroy(m_Value);
    m_Allocator.deallocate(m_Value, m_Size);
}

template<typename T>
void Node<T>::set_value(const T& new_value){
    m_Allocator.destroy(m_Value);
    m_Allocator.construct(m_Value, new_value);
}

