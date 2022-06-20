#include <memory>

template<typename T>
class vector{
public:
    vector(): __size(0), __capacity(0), __vals(nullptr) {}
    vector(unsigned int N): __size(0), __capacity(N), __vals(__allocator.allocate(N)) {}
    vector(unsigned int N, const T& val);
    ~vector(){free(__vals, __capacity);}

public:
    unsigned int size() const {return __size;}
    unsigned int capacity() const {return __capacity;}

    T* begin() {return __vals;}
    const T* begin() const {return __vals;}
    
    T* end() {return __vals + __size;}
    const T* end() const {return __vals + __size;}

    T& operator[](unsigned int i) {return __vals[i];}
    const T& operator[](unsigned int i) const {return __vals[i];}

    void resize(unsigned int newCapacity);
    void fit_to_size();

    T* push_back(const T&);
    void pop_back();
private:
    void free(T* mem, unsigned int capacity);
    void checkForShrink();
    void checkForExtend();
private:
    std::allocator<T> __allocator;
    unsigned int __size;
    unsigned int __capacity;
    T* __vals;
};

template<typename T>
vector<T>::vector(unsigned int N, const T& val): vector(N) {
    for (unsigned int i = 0; i < __capacity; i++)
    {
        __allocator.construct(this->begin() + i, val);
    }
}

template<typename T>
void vector<T>::free(T* mem, unsigned int capacity){
    for (unsigned int i = 0; i < capacity; i++)
    {
        __allocator.destroy(mem + i);
    }
    __allocator.deallocate(mem, capacity);
}

template<typename T>
void vector<T>::resize(unsigned int newCapacity){
    T* tmp = __allocator.allocate(newCapacity);

    if (newCapacity < __size) __size = newCapacity;

    for (unsigned int i = 0; i < __size; i++)
    {
        __allocator.construct(tmp+i, __vals[i]);
    }

    free(__vals, __capacity);

    __capacity = newCapacity;
    __vals = tmp;
}
template<typename T>
void vector<T>::fit_to_size(){
    this->resize(__size);
}

template<typename T>
void vector<T>::checkForExtend(){
    if (__size == __capacity)
    {
        __capacity *= 2;
        this->resize(__capacity);
    }
}

template<typename T>
void vector<T>::checkForShrink(){
    if ( __size && (__size <= __capacity/2) ) this->resize(__capacity/2);
}


template<typename T>
T* vector<T>::push_back(const T& value){
    checkForExtend();
    __allocator.construct(__vals + __size, value);
    return __vals + __size++;
}
template<typename T>
void vector<T>::pop_back(){
    checkForShrink();
    if (__size > 0)
    {
        __allocator.destroy(__vals + (--__size));
    }
}