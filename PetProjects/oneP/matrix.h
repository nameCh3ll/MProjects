#include "./PoolAllocator.cpp"
#include "./matrix_traits.cpp"
#include <algorithm>
#include <alloca.h>
#include <cstddef>
#include <cwchar>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>

#define DEFAULT_TEMPLATE_MATRIX                                                \
  size_t otherRows, size_t otherCols, typename otherT, typename otherAlloc

#define DEFAULT_ARGUMENTS_MATRIX otherRows, otherCols, otherT, otherAlloc

#define ENABLE_IF_EQUAL_MATRIX                                                 \
  typename = std::enable_if_t<                                                 \
      std::conjunction_v<is_same_matrix<Rows, Cols, otherRows, otherCols>,     \
                         std::is_same<T, otherT>>>

template <size_t Rows, size_t Cols, typename T = double,
          typename Alloc = std::allocator<T>>
class Matrix {
  T *_arr;
  [[no_unique_address]] Alloc _alloc;

  using Allocator_traits = std::allocator_traits<Alloc>;

  template <bool IsConst> class base_iterator {
    friend Matrix;

  public:
    using iterator_type = typename std::forward_iterator_tag;
    using value_type = typename std::conditional_t<IsConst, const T, T>;
    using pointer_type = typename std::conditional_t<IsConst, const T *, T *>;
    using reference_type = typename std::conditional_t<IsConst, const T &, T &>;

  private:
    pointer_type _ptr;

    base_iterator(T *ptr) : _ptr(ptr) {}

  public:
    base_iterator &operator++() {
      ++_ptr;
      return *this;
    }

    base_iterator operator++(int) {
      base_iterator tmp(_ptr);
      ++_ptr;
      return tmp;
    }

    reference_type operator*() { return *_ptr; }

    bool operator!=(base_iterator other) const noexcept {
      return _ptr != other._ptr;
    }
  };

public:
  using value_type = T;
  using matrix_type = is_square_t<Rows, Cols>;
  using const_iterator = base_iterator<true>;
  using iterator = base_iterator<false>;

  // TODO::sfinae have a construct default
  Matrix() : _arr(Allocator_traits::allocate(_alloc, Rows * Cols)) {
    for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
      Allocator_traits::construct(_alloc, _arr + i, T());
    }
  }

  ~Matrix() {
    for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
      Allocator_traits::destroy(_alloc, _arr + i);
    }
    Allocator_traits::deallocate(_alloc, _arr, Rows * Cols);
  }

  // why const choise default copy constrct.
  template <DEFAULT_TEMPLATE_MATRIX, ENABLE_IF_EQUAL_MATRIX>
  Matrix(const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) : Matrix() {
    for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
      *(_arr + i) = *(other._arr + i);
    }
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  // template <typename = std::enable_if_t<std::false_type::value>>
  Matrix(const Matrix &other) {
    std::cout << __PRETTY_FUNCTION__ << '\n';
    for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
      *(_arr + i) = *(other._arr + i);
    }
    std::cout << "SAdadsa";
  }
  // Matrix(const Matrix &other) = delete;
  //   for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
  //     *(_arr + i) = *(other._arr + i);
  //   }
  //   std::cout << __PRETTY_FUNCTION__ << '\n';
  // }

  template <DEFAULT_TEMPLATE_MATRIX, ENABLE_IF_EQUAL_MATRIX>
  Matrix &operator=(const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) {
    for (size_t i = 0, end = Rows * Cols; i < end; ++i) {
      *(_arr + i) = *(other._arr + i);
    }
    return this;
  }

  template <DEFAULT_TEMPLATE_MATRIX, ENABLE_IF_EQUAL_MATRIX>
  Matrix(Matrix<DEFAULT_ARGUMENTS_MATRIX> &&other) noexcept : _arr(other._arr) {
    other._arr = nullptr;
  }

  template <DEFAULT_TEMPLATE_MATRIX, ENABLE_IF_EQUAL_MATRIX>
  Matrix &operator=(Matrix<DEFAULT_ARGUMENTS_MATRIX> &&other) noexcept {
    this->~Matrix();
    _arr = other._arr;
    other._arr = nullptr;
    return this;
  }

  Matrix &transpose();

  // TODO: sfinae have a oprator *.
  template <DEFAULT_TEMPLATE_MATRIX,
            typename = std::enable_if_t<std::conjunction_v<
                is_compatible<Cols, otherRows>, std::is_same<T, otherT>>>>
  Matrix<Rows, otherCols, otherT, otherAlloc>
  operator*(Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) {}

  iterator begin() const { return iterator(_arr); }

  iterator end() const { return iterator(_arr + Rows * Cols + 1); };

  const_iterator cbegin() const { return const_iterator(_arr); }

  const_iterator cend() const {
    return const_iterator(_arr + Rows * Cols + 1);
  };
};

template <size_t N, typename T> using SquareMatrix = Matrix<N, N, T>;

// TODO: optimization matrix for L1 and L2 cahe.
// TODO: Algorithm of Strassen matrix multiplication.
// TODO: TODO.
