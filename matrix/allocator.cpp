#include <new>
#include <utility>

template <typename T> struct MyAllocator {
  using value_type = T;

  T *allocate(std::size_t count) {
    return static_cast<T *>(::operator new(sizeof(T) * count));
  }

  void deallocate(T *ptr, std::size_t count) { ::operator delete(ptr); }

  template <typename U, typename... Args>
  void construct(U *ptr, Args &&...args) {
    new (ptr) T(std::forward<Args>(args)...);
  }

  void destroy(T *ptr) { ptr->~T(); }
};
