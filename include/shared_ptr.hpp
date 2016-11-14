#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    shared_ptr(shared_ptr<T>& other);
    shared_ptr(shared_ptr && other);
    auto operator= (shared_ptr & other)->shared_ptr &;
    auto operator =(shared_ptr && other) -> shared_ptr &;
    auto operator ->() const -> T *;
    auto operator *() const -> T *;
    ~shared_ptr();
    auto count() const->size_t;
    auto swap(shared_ptr& other) noexcept -> void;
    
private:
    T* ptr;
    size_t *count;
};

template<typename T> 
auto shared_ptr<T>::swap(shared_ptr & other) noexcept -> void 
{
	std::swap(ptr, other.ptr);
	std::swap(count, other.count);
}

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
 shared_ptr<T>::shared_ptr(shared_ptr && other): ptr_(other.ptr_),count_(other.count_)
    {
        other.ptr_ = nullptr;
	 other.count_=nullptr;
    }
template<typename T>
auto shared_ptr<T>::operator =(const shared_ptr & other) -> shared_ptr &
{
	if (this != &other) 
	{
		(shared_ptr<T>(other)).swap(*this);
	}
	return *this;
}	
/*{
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
        count=other.count;b 
        (*count)++;
    }
    return *this;
}*/

template<typename T>
auto shared_ptr<T>::operator =(shared_ptr && other) -> shared_ptr &
{
        if(this !=&other)
	this->swap(std::move(other));
	return *this;
}

template<typename T>
 shared_ptr<T>::shared_ptr(shared_ptr && other): ptr(other.ptr),count(other.count)
    {
        other.ptr = nullptr;
	 other.count=nullptr;
    }
    
template<typename T>
shared_ptr<T>::~shared_ptr()
{
    if (count) {
        if (*count == 1) {
            delete count;
            delete ptr;
        }
        else (*count)--;
    }
}

template<typename T>
auto shared_ptr<T>::count() const->size_t
{
   return (count != nullptr ? *count : 0);
}
template<typename T> 
auto shared_ptr<T>::operator ->() const -> T *
{
        if(count) 
	{
	return ptr;
	}
        else 
	{
		throw std::logic_error("Error");
	}
}
template<typename T>
auto shared_ptr<T>::operator *() const -> T &
{
       if(count) 
       {
       		return *ptr;
       }
       else 
       {
      		 throw std::logic_error("Error");
       }
}

