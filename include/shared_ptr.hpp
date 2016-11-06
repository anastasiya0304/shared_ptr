#include <iostream>
#include <utility>
#include <stdexcept>

template <typename T>
class shared_ptr {
public:
    shared_ptr();
    shared_ptr(T* ptr);
    auto operator= (shared_ptr const & other)->shared_ptr &;
    auto operator =(shared_ptr && other) -> shared_ptr &;
    auto swap(shared_ptr& r) noexcept -> void;
    auto reset() -> void;
    auto operator ->() const -> T *;
    auto operator *() const -> T *;
    ~shared_ptr();
    auto count() const->size_t;
 
private:
    T* ptr_;
    size_t *count_;
};
