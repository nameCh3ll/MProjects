#include <alloca.h>

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <cwchar>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>

#include "./PoolAllocator.cpp"
#include "./matrix_traits.cpp"

#define SM (CLS / sizeof(double))

#define DEFAULT_TEMPLATE_MATRIX \
  size_t otherRows, size_t otherCols, typename otherT, typename otherAlloc

#define DEFAULT_ARGUMENTS_MATRIX otherRows, otherCols, otherT, otherAlloc

#define ENABLE_IF_COMPATIBLE_MATRICES                                     \
  typename =                                                              \
      std::enable_if_t<std::conjunction_v<is_compatible<Cols, otherRows>, \
                                          std::is_same<T, otherT>>>

#define ENABLE_IF_EQUAL_MATRIX                                             \
  typename = !std::enable_if_t<                                            \
      std::conjunction_v<is_same_matrix<Rows, Cols, otherRows, otherCols>, \
                         std::is_same<T, otherT>>>

#define PRINT_ALL                                                 \
  std::cout << "Rows:" << Rows << ' ' << "Cols:" << Cols << '\n'; \
  std::cout << "otherRows:" << otherRows << ' ' << "otherCols:" << otherCols

template <size_t Rows, size_t Cols, typename T = double,
          typename Alloc = std::allocator<T>>
class Matrix {
  static constexpr size_t _ROWS{Rows};
  static constexpr size_t _COLS{Cols};
  static constexpr size_t _SIZE = Rows * Cols;

  T *_arr;
  [[no_unique_address]] Alloc _alloc;

  template <DEFAULT_TEMPLATE_MATRIX>
  friend class Matrix;

  using Allocator_traits = std::allocator_traits<Alloc>;

  template <bool IsConst>
  class base_iterator {
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
  Matrix() : _arr(Allocator_traits::allocate(_alloc, _SIZE)) {
    for (size_t i = 0; i < _SIZE; ++i) {
      Allocator_traits::construct(_alloc, _arr + i, T());
    }
  }

  ~Matrix() {
    for (size_t i = 0; i < _SIZE; ++i) {
      Allocator_traits::destroy(_alloc, _arr + i);
    }
    Allocator_traits::deallocate(_alloc, _arr, _SIZE);
  }

  Matrix(const Matrix &other) : Matrix() {
    memcpy(this->_arr, other._arr, sizeof(other));
    std::cout << __PRETTY_FUNCTION__ << '\n';
  }

  template <DEFAULT_TEMPLATE_MATRIX>
  Matrix(const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other)
      : Matrix<otherCols, otherRows>() {
    for (size_t i = 0; i < Cols; ++i) {
      for (size_t g = 0; g < Rows; ++g) {
        *(this->_arr + i * Rows + g) = *(other._arr + i + g * Cols);
      }
    }
  }

  Matrix(Matrix &&other) noexcept : _arr(other._arr) { other._arr = nullptr; }

  Matrix &operator=(Matrix &other) {
    this->~Matrix();
    memcpy(this, other, sizeof(other));
    return this;
  }

  Matrix &operator=(Matrix &&other) noexcept {
    this->~Matrix();
    _arr = other._arr;
    other._arr = nullptr;
    return this;
  }

  // template <DEFAULT_TEMPLATE_MATRIX, ENABLE_IF_EQUAL_MATRIX>
  // Matrix(const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) = delete;

  template <DEFAULT_TEMPLATE_MATRIX>
  Matrix &operator=(const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) = delete;

  template <DEFAULT_TEMPLATE_MATRIX>
  Matrix(Matrix<DEFAULT_ARGUMENTS_MATRIX> &&other) = delete;

  template <DEFAULT_TEMPLATE_MATRIX>
  Matrix &operator=(Matrix<DEFAULT_ARGUMENTS_MATRIX> &&other) = delete;

  Matrix<Cols, Rows, T, Alloc> get_transpose() const {
    Matrix<Cols, Rows, T, Alloc> tmp;
    for (size_t i = 0; i < Cols; ++i) {
      for (size_t g = 0; g < Rows; ++g) {
        *(tmp._arr + i * Rows + g) = *(this->_arr + i + g * Cols);
      }
    }
    return tmp;
  }

  // TODO: sfinae have a operator *.
  template <DEFAULT_TEMPLATE_MATRIX> /* , ENABLE_IF_COMPATIBLE_MATRICES> */
  Matrix<Rows, otherCols, T> operator*(
      const Matrix<DEFAULT_ARGUMENTS_MATRIX> &other) {
    Matrix<otherCols, otherRows, T> tmp = other.get_transpose();
    Matrix<Rows, otherCols, T> result;
    for (size_t i = 0; i < _SIZE; ++i) {
      for (size_t g = 0; g < Cols; ++g) {
        *(result._arr + i) += *(this->_arr + i + g) * *(tmp._arr + i + g);
      }
    }
    return result;
  }

  void print() const {
    for (size_t i = 0; i < Rows; ++i) {
      for (size_t g = 0; g < Cols; ++g)
        std::cout << *(_arr + i * Cols + g) << ' ';
      std::cout << '\n';
    }
  }

  iterator begin() const { return iterator(_arr); }

  iterator end() const { return iterator(_arr + _SIZE); };

  const_iterator cbegin() const { return const_iterator(_arr); }

  const_iterator cend() const { return const_iterator(_arr + _SIZE); };
};

template <size_t N, typename T = double, typename Alloc = std::allocator<T>>
using SquareMatrix = Matrix<N, N, T, Alloc>;

// TODO: optimization matrix for L1 and L2 cahe.
// TODO: Algorithm of Strassen matrix multiplication.
// TODO: TODO.
