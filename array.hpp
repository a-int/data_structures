template<typename T, const unsigned int sz>
class array{
private:
    T vals[sz];
public:
    array() = default;
    T* begin() {return &vals[0];}
    T* end() {return &vals[sz-1];}
    constexpr int size() const {return sz;}
    T& operator[](std::size_t index){return vals[index];}
    const T& operator[](std::size_t index) const {return vals[index];}
    T& at(std::size_t);
    const T& at(std::size_t) const;
};

template<typename T, const unsigned int sz>
T& array<T, sz>::at(std::size_t index){
    if ((index>=sz))
        throw"Worng index is used";
    return vals[index];
}

template<typename T, const unsigned int sz>
const T& array<T, sz>::at(std::size_t index) const {
    if ((index>=sz))
        throw"Worng index is used";
    return vals[index];
}