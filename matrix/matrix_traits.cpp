#include <cstddef>
#include <type_traits>

struct Square_tag;
struct NotSquare_tag;

struct true_type {
  static constexpr bool value = true;
};

struct false_type {
  static constexpr bool value = false;
};

template <size_t Rows, size_t Cols> struct is_square {
  using value_type = NotSquare_tag;
};

template <size_t N> struct is_square<N, N> {
  using value_type = Square_tag;
};

template <size_t Rows, size_t Cols>
using is_square_t = typename is_square<Rows, Cols>::value_type;

template <size_t Cols_l, size_t Rows_r> struct is_compatible : false_type {};

template <size_t N> struct is_compatible<N, N> : true_type {};

template <size_t Cols_l, size_t Rows_r>
constexpr bool is_compatible_v = is_compatible<Cols_l, Rows_r>::value;

template <size_t Rows, size_t Cols, size_t OtherRows, size_t OtherCols>
struct is_same_matrix : false_type {};

template <size_t Rows, size_t Cols>
struct is_same_matrix<Rows, Cols, Rows, Cols> : true_type {};

template <size_t Rows, size_t Cols, size_t OtherRows, size_t OtherCols>
constexpr bool is_same_matrix_v =
    is_same_matrix<Rows, Cols, OtherRows, OtherCols>::value;

/*template <size_t Rows, size_t Cols, size_t OtherRows, size_t OtherCols>*/
/*constexpr bool is_square_matrix_v =*/
/*    std::conjunction_v<is_square<Rows, Cols>, is_square<Rows, OtherCols>,*/
/*                       is_square<OtherRows, OtherCols>>;*/
