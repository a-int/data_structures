template<typename T, int sz>
class Array{
private:
    T *vals;
public:
    Array();
    ~Array();
    T* begin() {return &vals[0];}
    T* end() {return &vals[sz-1];}
    int size() const {return sz;}
    T& operator[](std::size_t index){return vals[index];}
    const T& operator[](std::size_t index) const {return vals[index];}
    T& at(std::size_t);
};

template<typename T, int sz>
Array<T,sz>::Array() {
    this->vals = new T[sz];
}

template<typename T, int sz>
Array<T,sz>::~Array() {
    delete[] this->vals;
}

template<typename T, int sz>
T& Array<T, sz>::at(std::size_t index){
    if ((index>=sz))
        throw"Worng index is used";
    return vals[index];
}