#include <memory>

template<typename T>
class Node{
public:
    Node(): m_Value(m_Allocator.allocate(m_Size)), m_Next(nullptr) {m_Allocator.construct(m_Value);}
    Node(const T& val): m_Value(m_Allocator.allocate(m_Size)), m_Next(nullptr){m_Allocator.construct(m_Value, val);}
    Node(const T& val, Node<T>& node): m_Value(m_Allocator.allocate(m_Size)), m_Next(&node){m_Allocator.construct(m_Value, val);}
    Node(const T& val, const Node<T>& node): m_Value(m_Allocator.allocate(m_Size)), m_Next(&node){m_Allocator.construct(m_Value, val);}
    ~Node(){free();}
private:
    void free();

public:
    Node<T>* next() {return m_Next;}
    Node<T>* next() const {return m_Next;}
    void set_next(Node<T>* node) {m_Next = node;}

    T& value() {return *m_Value;}
    const T& value() const {return *m_Value;}
    void set_value(const T& new_Value);
private:
    std::allocator<T> m_Allocator;
    const unsigned int m_Size = 1;
    T* m_Value;
    Node<T>* m_Next;
};

template<typename T>
void Node<T>::free(){
    m_Allocator.destroy(m_Value);
    m_Allocator.deallocate(m_Value, m_Size);
}

template<typename T>
void Node<T>::set_value(const T& new_Value){
    m_Allocator.destroy(m_Value);
    m_Allocator.construct(m_Value, new_Value);
}

template<typename T>
class list{
public:
    list(): m_Head(), m_Size(1) {};
    list(unsigned int count, const T& value);

public:
    T& front() {return m_Head->m_Value;}
private:
    std::allocator<Node<T>> m_Allocator;
    Node<T>* m_Head;
    Node<T>* m_Back;
    unsigned int m_Size;
};

template<typename T>
list<T>::list(unsigned int count, const T& value): m_Head(value), m_Size(count){
    Node<T>* current = m_Head;
    for (unsigned int i = 1; i < count; i++)
    {
        Node<T>* next = new Node<T>(value);
        current.set_next(next);
        current = next;
        if (i == count - 1)
        {
            m_Back
        }
        
    }
}