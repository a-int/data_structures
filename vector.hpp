template<typename T>
class vector{
public:
    vector(): sz(1), cap(sz), vals(new T[cap]) {}
    vector(const vector&);
    explicit vector(unsigned int N): sz(N), cap(sz), vals(new T[cap]){};
    vector(unsigned int N, const T& var);
    vector(T*, T*);
    ~vector() {delete[] vals;}
    vector& operator=(const vector&);

public:
    T& operator[](unsigned int index) {return vals[index];}
    const T& operator[](unsigned int index) const {return vals[index];}
    
    T* begin() {return vals;}
    T* end() {return vals+sz;}

    unsigned int size() const {return sz;}
    unsigned int capacity() const {return cap;}
    void resize(unsigned int);

    T* push_back(const T&);
    T* insert(T*, const T&);

    void pop_back();
    T* erase(T*);

private:
    void checkForResize();

private:
    unsigned int sz;
    unsigned int cap = 1;
    T* vals;
};

template<typename T>
vector<T>::vector(const vector& orig):sz(orig.size()), cap(orig.capacity()), vals(new T[cap]){
    for(unsigned int i = 0; i<sz; i++) vals[i] = orig[i];
}

template<typename T>
vector<T>::vector(unsigned int N, const T& var):vector(N) {
    for(unsigned int i = 0; i<N; i++) vals[i] = var;
}

template<typename T>
vector<T>& vector<T>::operator=(const vector<T>& rhs){
    sz = rhs.size();
    cap = rhs.capacity();
    T* tmp = new T[cap];
    for(unsigned int i = 0; i<sz; i++) tmp[i] = rhs[i];
    delete[] vals;
    vals = tmp;
    return *this;
}
template<typename T>
vector<T>::vector(T* begin, T* end): sz(end-begin), cap(sz), vals(new T[cap]){
    for(unsigned int i = 0; i<sz; i++) vals[i] = *(begin+i);
}

template<typename T>
void vector<T>::resize(unsigned int newCapacity){
   T* tmp = new T[newCapacity];

   if(newCapacity < sz) sz = newCapacity;

   for(unsigned int i = 0; i < sz; i++) 
   {
        tmp[i] = vals[i];
   }
   delete[] vals;
   vals = tmp;

   cap = newCapacity;
}

template<typename T>
void vector<T>::checkForResize(){
    // Check if need to extend/shrink
    if (sz == cap)
    {
        cap *= 2;
        this->resize(cap);
    }
    else if ( sz && (sz == cap/2) ) this->resize(cap/2);
}

template<typename T>
T* vector<T>::push_back(const T& obj){
    checkForResize();
    vals[sz] = obj;
    return vals + sz++;
}

template<typename T>
T* vector<T>::insert(T* pos, const T& obj){
    checkForResize();

    //Push forward every value from pos
    for (T* current = this->end(); current > pos; current--)
    {
        *current = *(current-1);
    }
    *pos = obj;
    sz++;
    return pos;
}

template<typename T>
void vector<T>::pop_back(){
    checkForResize();    

    T* tmp = new T[--sz];
    for(unsigned int i = 0; i < sz; i++) 
    {
        tmp[i] = vals[i];
    }

    delete[] vals;
    vals = tmp;
}

template<typename T>
T* vector<T>::erase(T* pos){
    checkForResize();
    sz--;
    
    //Push forward every value from pos
    for (T* current = pos; current <= this->end(); current++)
    {
        *current = *(current + 1);
    }

    return pos;
}