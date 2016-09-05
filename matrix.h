#ifndef _MATRIX_H_
#define _MATRIX_H_

#include <initializer_list>
#include <cstdlib>
#include <ostream>

template <class T>
class Matrix {
public:
  Matrix();
  Matrix(const size_t rows, const size_t columns);
  Matrix(const std::initializer_list<std::initializer_list<T>> init);
  Matrix(const Matrix<T> &other);
  Matrix<T> & operator= (const Matrix<T> &other);
  ~Matrix();
  // all operations modify the matrix in-place.
  void resize(const size_t rows, const size_t columns, const T default_value = 0);
  void clear();
  T& operator () (const size_t x, const size_t y);
  const T& operator () (const size_t x, const size_t y) const;
  const T min() const;
  const T max() const;
  inline size_t minsize() { return ((m_rows < m_columns) ? m_rows : m_columns); }
  inline size_t columns() const { return m_columns;}
  inline size_t rows() const { return m_rows;}

  friend std::ostream& operator<<(std::ostream& os, const Matrix &matrix)
  {
      os << "Matrix:" << std::endl;
      for (size_t row = 0 ; row < matrix.rows() ; row++ )
      {
          for (size_t col = 0 ; col < matrix.columns() ; col++ )
          {
              os.width(8);
              os << matrix(row, col) << ",";
          }
          os << std::endl;
      }
      return os;
  }

private:
  T **m_matrix;
  size_t m_rows;
  size_t m_columns;
};

#ifndef USE_EXPORT_KEYWORD
#include "matrix.cpp"
//#define export /*export*/
#endif

#endif /* !defined(_MATRIX_H_) */

