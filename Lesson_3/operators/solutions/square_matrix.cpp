#include <iomanip>
#include <cmath>
#include "square_matrix.h"
#include "utility.h"

Matrix::Matrix()
  : m_size(0)
  , m_data(nullptr) {
}

Matrix::Matrix(size_t size)
  : m_size(size)
  , m_data(new Matrix::pointer_type[size]) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data[i] = new Matrix::value_type[m_size];
  }
}

Matrix::Matrix(size_t size, Matrix::value_type value)
  : m_size(size)
  , m_data(new Matrix::pointer_type[size]) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data[i] = new Matrix::value_type[m_size];
    for (size_t j = 0; j < m_size; ++j) {
      m_data[i][j] = value;
    }
  }
}

Matrix::Matrix(size_t size, Matrix::pointer_type array[])
  : m_size(size)
  , m_data(new Matrix::pointer_type[size]) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data[i] = new Matrix::value_type[m_size];
    for (size_t j = 0; j < m_size; ++j) {
      m_data[i][j] = array[i][j];
    }
  }
}

Matrix::Matrix(const Matrix& obj)
  : m_size(obj.m_size)
  , m_data(new Matrix::pointer_type[obj.m_size]) {
  for (size_t i = 0; i < m_size; ++i) {
    m_data[i] = new Matrix::value_type[m_size];
    for (size_t j = 0; j < m_size; ++j) {
      m_data[i][j] = obj.m_data[i][j];
    }
  }
}

Matrix::Matrix(const Matrix& obj, size_t row, size_t col)
  : m_size(obj.m_size - 1)
  , m_data(new Matrix::pointer_type[m_size]) {  // Note: 'm_size' has already been initialized
  size_t rk = 0;
  for (size_t r = 0; r < obj.m_size; ++r) {
    if (r == row) {
      rk = -1;
      continue;
    }
    m_data[r + rk] = new Matrix::value_type[m_size];
    size_t ck = 0;
    for (size_t c = 0; c < obj.m_size; ++c) {
      if (c == col) {
        ck = -1;
        continue;
      }
      m_data[r + rk][c + ck] = obj.m_data[r][c];
    }
  }
}

Matrix::~Matrix() {
  for (size_t i = 0; i < m_size; ++i) {
    if (m_data[i] != nullptr) {
      delete [] m_data[i];
      m_data[i] = nullptr;
    }
  }
  delete [] m_data;
  m_data = nullptr;
  m_size = 0;
}

/* Operators group */
// ----------------------------------------------------------------------------
Matrix& Matrix::operator = (Matrix rhs) {
  std::swap(m_size, rhs.m_size);
  std::swap(m_data, rhs.m_data);
  return *this;
}

Matrix Matrix::operator + () const {
  return Matrix(*this);
}

Matrix Matrix::operator - () const {
  Matrix result = *this;
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      result.m_data[row][col] *= -1.0;
    }
  }
  return result;
}

Matrix Matrix::operator + (const Matrix& rhs) const {
  Matrix result = *this;
  result += rhs;
  return result;
}

Matrix Matrix::operator + (Matrix::value_type value) const {
  Matrix result = *this;
  result += value;
  return result;
}

Matrix Matrix::operator - (const Matrix& rhs) const {
  Matrix result = *this;
  result -= rhs;
  return result;
}

Matrix Matrix::operator - (Matrix::value_type value) const {
  Matrix result = *this;
  result -= value;
  return result;
}

Matrix Matrix::operator * (const Matrix& rhs) const {
  Matrix result = *this;
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      Matrix::value_type sum = 0.0;  // implicit conversion
      for (size_t k = 0; k < m_size; ++k) {
        sum += m_data[row][k] * rhs.m_data[k][col];
      }
      result.m_data[row][col] = sum;
    }
  }
  return result;
}

Matrix Matrix::operator * (Matrix::value_type value) const {
  Matrix result = *this;
  result *= value;
  return result;
}

Matrix& Matrix::operator += (const Matrix& rhs) {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      m_data[row][col] += rhs[row][col];
    }
  }
  return *this;
}

Matrix& Matrix::operator += (Matrix::value_type value) {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      m_data[row][col] += value;
    }
  }
  return *this;
}

Matrix& Matrix::operator -= (const Matrix& rhs) {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      m_data[row][col] -= rhs[row][col];
    }
  }
  return *this;
}

Matrix& Matrix::operator -= (Matrix::value_type value) {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      m_data[row][col] -= value;
    }
  }
  return *this;
}

Matrix& Matrix::operator *= (const Matrix& rhs) {
  Matrix result = *this * rhs;
  *this = result;
  return *this;
}

Matrix& Matrix::operator *= (Matrix::value_type value) {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      m_data[row][col] *= value;
    }
  }
  return *this;
}

// ----------------------------------------------
bool Matrix::operator == (const Matrix& rhs) const {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      if (m_data[row][col] != rhs[row][col]) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator != (const Matrix& rhs) const {
  return !(*this == rhs);
}

bool Matrix::operator < (const Matrix& rhs) const {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      if (m_data[row][col] >= rhs.m_data[row][col]) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator <= (const Matrix& rhs) const {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      if (m_data[row][col] > rhs.m_data[row][col]) {
        return false;
      }
    }
  }
  return true;
}

bool Matrix::operator > (const Matrix& rhs) const {
  return !(*this <= rhs);
}

bool Matrix::operator >= (const Matrix& rhs) const {
  return !(*this < rhs);
}

// ----------------------------------------------
Matrix::pointer_type Matrix::operator [] (size_t row) {
  return m_data[row];
}

const Matrix::pointer_type Matrix::operator [] (size_t row) const {
  return m_data[row];
}

Matrix::reference_type Matrix::operator () (size_t row, size_t col) {
  return m_data[row][col];
}

Matrix::value_type Matrix::operator () (size_t row, size_t col) const {
  return m_data[row][col];
}

/* Maths group */
// ----------------------------------------------------------------------------
Matrix Matrix::Identity(size_t size) {
  Matrix::value_type value = static_cast<value_type>(0);
  Matrix identity(size, value);
  for (size_t i = 0; i < size; ++i) {
    identity[i][i] = static_cast<value_type>(1);
  }
  return identity;
}

Matrix Matrix::submatrix(size_t row, size_t col) {
  Matrix submatrix(m_size - 1);
  size_t rk = 0;
  for (size_t r = 0; r < m_size; ++r) {
    if (r == row) {
      rk = -1;
      continue;
    }
    submatrix.m_data[r + rk] = new Matrix::value_type[m_size];
    size_t ck = 0;
    for (size_t c = 0; c < m_size; ++c) {
      if (c == col) {
        ck = -1;
        continue;
      }
      submatrix.m_data[r + rk][c + ck] = m_data[r][c];
    }
  }
  return submatrix;
}

Matrix& Matrix::transpose() {
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = row; col < m_size; ++col) {
      std::swap(m_data[row][col], m_data[col][row]);
    }
  }
  return *this;
}

Matrix Matrix::getTransposed() const {
  Matrix transposed(m_size);
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      transposed[row][col] = m_data[col][row];
    }
  }
  return transposed;
}

Matrix::value_type Matrix::determinant() const {
  return determinant(0);  // 0-th row decomposition
}

Matrix::value_type Matrix::determinant(size_t row) const {
  if (m_size == 1) {
    return m_data[0][0];
  }
  Matrix::value_type result = 0;  // implicit cast
  for (size_t col = 0; col < m_size; ++col) {
    Matrix adjugate(*this, row, col);
    result += std::pow(-1.0, col) * m_data[row][col] * adjugate.determinant();
  }
  return result;
}

Matrix::value_type Matrix::trace() const {
  Matrix::value_type trace = 0;  // implicit cast
  for (size_t i = 0; i < m_size; ++i) {
    trace += m_data[i][i];
  }
  return trace;
}

void Matrix::diag(Matrix::pointer_type output) const {
  for (size_t i = 0; i < m_size; ++i) {
    output[i] = m_data[i][i];
  }
}

Matrix& Matrix::inverse() {
  *this = getInversed();
  return *this;
}

Matrix Matrix::getInversed() const {
  Matrix::value_type det = determinant();
  if (util::equals(det, 0.0)) {
    ERR("Determinant is zero!");
    throw MatrixInversionException();
  }
  Matrix inversed(m_size);
  for (size_t row = 0; row < m_size; ++row) {
    for (size_t col = 0; col < m_size; ++col) {
      Matrix adjugate(*this, col, row);  // note the inversion of 'row' and 'col'
      Matrix::value_type cofactor = adjugate.determinant();
      double sign = util::equals(cofactor, 0.0) ? 1.0 : std::pow(-1.0, row + col);
      inversed[row][col] = sign * cofactor / det;
    }
  }
  return inversed;
}

// ----------------------------------------------
Matrix power(const Matrix& matrix, int power) {
  if (power == 0) { return Matrix::Identity(matrix.size()); }

  Matrix result, inversed;
  if (power > 0) {
    result = matrix;  // Note: assignment operator invoked
    while (power > 1) {
      result *= matrix;
      --power;
    }
  } else {
    inversed = matrix.getInversed();
    result = inversed;
    while (power < -1) {
      result *= inversed;
      ++power;
    }
  }
  return result;
}

/* I/O */
// ----------------------------------------------------------------------------
std::ostream& operator << (std::ostream& out, const Matrix& obj) {
  double precision = 0.0001;
  for (size_t row = 0; row < obj.size(); ++row) {
    for (size_t col = 0; col < obj.size(); ++col) {
      Matrix::value_type value = obj[row][col];
      double intpart = 0.0;
      double decimalpart = std::modf(std::abs(value), &intpart);
      if (decimalpart < precision) {  // trunc decimal part if it consists only from zeroes
        out << intpart << " ";
      } else {
        Matrix::value_type value = (std::abs(obj[row][col]) < precision) ? 0.0 : obj[row][col];
        out << std::fixed << std::setprecision(4) << value << " ";
      }
    }
    out << "\n";
  }
  return out;
}

std::istream& operator >> (std::istream& in, Matrix& obj) {
  for (size_t row = 0; row < obj.size(); ++row) {
    for (size_t col = 0; col < obj.size(); ++col) {
      in >> obj[row][col];
    }
  }
  return in;
}

