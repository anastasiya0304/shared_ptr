#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    auto operator= (shared_ptr & other)->shared_ptr &;
    auto operator =(shared_ptr && other) -> shared_ptr &;
    //auto reset() -> void;
    auto operator ->() const -> T *;
    auto operator *() const -> T *;
    ~shared_ptr();
    auto count() const->size_t;
 
private:
    T* ptr;
    size_t *count;
};

template<typename T>
shared_ptr<T>::shared_ptr():ptr(nullptr), count(nullptr)
{}
template<typename T>
shared_ptr<T>::shared_ptr(T * ptr):ptr(ptr), count(new size_t(1))
{}
template<typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T>& other):count(other.count),ptr(other.ptr)
{
    (*count)++;
}
template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr &
{
    if(this!=&other)
         {
            if(count) {
                if(*count==1)
                {
                    delete count;
                    delete ptr;
                }
                else (*count)--;
            }
        ptr= other.ptr;
        count=other.count;
        (*count)++;
    }
    return *this;
}
template<typename T>
shared_ptr<T>::~shared_ptr(){
    if (count) {
        if (*count == 1) {
            delete count;
            delete ptr_;
        }
        else (*count)--;
    }
}
template<typename T>
auto shared_ptr<T>::count() const->size_t{
   return (count != nullptr ? *count : 0);
}
template<typename T> //разыменовывает указатель
auto shared_ptr<T>::operator ->() const -> T *
{
        if(count_) {return ptr_;}
        else {throw std::logic_error("Error");}
}
template<typename T>
auto shared_ptr<T>::operator *() const -> T *
{
       if(count_) {return *ptr_;}
       else {throw std::logic_error("Error");}
}

