template<typename T, const unsigned int sz>
class array{
public:
    array() = delete;

public:
    T* begin() {return &vals[0];}
    T* end() {return &vals[sz-1];}

    constexpr int size() const {return sz;}

    T& operator[](unsigned int index){return vals[index];}
    const T& operator[](unsigned int index) const {return vals[index];}

    T& at(unsigned int);
    const T& at(unsigned int) const;

private:
    T vals[sz];
};

template<typename T, const unsigned int sz>
T& array<T, sz>::at(unsigned int index){
    if ((index>=sz))
        throw"Worng index is used";
    return vals[index];
}

template<typename T, const unsigned int sz>
const T& array<T, sz>::at(unsigned int index) const {
    if ((index>=sz))
        throw"Worng index is used";
    return vals[index];
}
