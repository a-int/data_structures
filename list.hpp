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
    list(): m_Head(nullptr), m_Back(m_Head), m_Size(0){}
    ~list() {free();}

    T& front() {return m_Head->value();}
    const T& front() const {return this->empty()? T():m_Head->value();}

    T& back() {return m_Back->value();}
    const T& back() const {return this->empty()? T():m_Back->value();}

    Node<T>* begin() {return m_Head;};
    const Node<T>* begin() const {return m_Head;};

    Node<T>* end() {return m_Back;}
    const Node<T>* end() const {return m_Back;}
    
    unsigned int size() const {return m_Size;}
    bool empty() const {return m_Size == 0;}

    void clear() {free();}

    void push_back(const T& new_Value);
    void push_front(const T& new_Value);

    void pop_back();
    void pop_front();

private:
    void free();

    std::allocator<Node<T>> m_Allocator;
    const unsigned int m_Single = 1;
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
void list<T>::push_back(const T& new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value);

    //There are no nodes e.g. head points to nullptr
    if(!m_Size){
        m_Head = new_node;
        m_Back = m_Head;
        return;
    }
    m_Back->set_next(new_node);
    m_Back = new_node;
    m_Size++;
}

template<typename T>
void list<T>::push_front(const T& new_Value){
    //Allocate memory for new object and construct it with provided argument
    Node<T>* new_node = m_Allocator.allocate(1);
    m_Allocator.construct(new_node, new_Value);

    if (m_Size > 0) new_node->set_next(m_Head);
    else m_Back = new_node;
    m_Head = new_node;
    m_Size++;
}

template<typename T>
void list<T>::pop_back(){
    if(this->empty()) return;

    Node<T>* penultimate = m_Head;

    if(m_Size != 1)
        while(penultimate->next() != m_Back) penultimate = penultimate->next();

    penultimate->set_next(nullptr);
    //if size==1 m_Back points to the only node
    m_Allocator.destroy(m_Back);
    m_Allocator.deallocate(m_Back, 1);
    m_Back = penultimate;
    // if (m_Size == 1) {
    //     m_Head = nullptr;
    //     m_Back = nullptr;
    // }
    m_Size--;
}

template<typename T>
void list<T>::pop_front(){
    if(this->empty()) return;

    Node<T>* first = m_Head;
    
    m_Head = m_Head->next();
    m_Allocator.destroy(first);
    m_Allocator.deallocate(first, 1);
    // if (m_Size == 1) {
    //     m_Head = nullptr;
    //     m_Back = nullptr;
    // }
    m_Size--;
}