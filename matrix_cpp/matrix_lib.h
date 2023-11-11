
#ifndef MATRIX_LIB_H
#define MATRIX_LIB_H
const double EPS = 1e-6;

class Matrix_Exception : public std::domain_error
{
public:
    Matrix_Exception(const char *const &msg) : domain_error(msg)
    {
    }
};

Matrix_Exception NOTSQUARE("Error:the matrix must be square(should have nxn size)\n");
Matrix_Exception NOTEQUAL("Error: the matrix should have a same size\n");
Matrix_Exception MULTIPLYERROR("Error: first matrix cols not equal to second matrix row.\n");
Matrix_Exception ZERODIVISION("Error: divide by zero\n");
Matrix_Exception MEM_ERROR("Error: memory are not allocated\n");
Matrix_Exception EMPTY_MATRIX("Error: Function can't return empty matrix\n");

class Matrix
{
private:
    unsigned int rows;
    unsigned int cols;
    double *values;

public:
    Matrix(unsigned int, unsigned int, double *);
    Matrix(unsigned int, unsigned int);
    Matrix();
    Matrix(const Matrix &);
    Matrix(Matrix &&) noexcept;
    ~Matrix();

    void output();
    unsigned int getrow();
    unsigned int getcol();

    Matrix set_zero();
    Matrix fill_random(unsigned int);
    Matrix fill_from_array(double *);
    Matrix set_identity();
    Matrix exponent(unsigned int);
    Matrix set_transpose();
    Matrix minor(const unsigned int, const unsigned int);
    Matrix reverse(const Matrix *, const unsigned int);
    double determinant(const Matrix *);

    Matrix &operator=(Matrix &&) noexcept;
    Matrix &operator=(const Matrix &);
    Matrix &operator+=(const Matrix &);
    Matrix &operator-=(const Matrix &);
    Matrix &operator*=(const Matrix &);
    Matrix &operator*=(const double);
    Matrix &operator/=(const double);

    Matrix operator+(const Matrix &);
    Matrix operator-(const Matrix &);
    Matrix operator*(const Matrix &);
    Matrix operator*(const double);
    Matrix operator/(const double);

    bool operator!=(const Matrix &mat);
    bool operator==(const Matrix &mat);
    friend std::ostream &operator<<(std::ostream &out, const Matrix m);
};

Matrix::Matrix() : rows(0), cols(0), values(nullptr) {}

Matrix::Matrix(const Matrix &mat) : rows(mat.rows), cols(mat.cols)
{
    values = new double[rows * cols];
    if (!values)
        throw MEM_ERROR;
    memcpy(values, mat.values, rows * cols * sizeof(double));
}

Matrix::Matrix(unsigned int num_row, unsigned int num_col, double *value)
{
    rows = num_row;
    cols = num_col;
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        values[idx] = value[idx];
    }
}

Matrix::Matrix(unsigned int num_row, unsigned int num_col)
{
    rows = num_row;
    cols = num_col;
    values = new double[rows * cols];
    if (!values)
        throw MEM_ERROR;
}

Matrix::Matrix(Matrix &&mat) noexcept : values(mat.values), rows(mat.rows), cols(mat.cols)
{
    mat.values = nullptr;
    mat.rows = 0;
    mat.cols = 0;
}

Matrix::~Matrix()
{
    if (this->values != nullptr)
    {
        delete[] this->values;
    }
}

std::ostream &operator<<(std::ostream &out, const Matrix matrix)
{
    {
        for (unsigned int row = 0; row < matrix.rows; row++)
        {
            for (unsigned int col = 0; col < matrix.cols; col++)
            {
                out << matrix.values[row * matrix.cols + col] << "\t";
            }
            out << std::endl;
        }
        out << std::endl;
        return (out);
    }
}

bool Matrix::operator==(const Matrix &A)
{
    if (this->cols != A.cols || this->rows != A.rows)
        return false;
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx++)
    {
        if (abs(this->values[idx] - A.values[idx]) > EPS)
            return false;
    }
    return true;
}

bool Matrix::operator!=(const Matrix &mat)
{
    return !(*this == mat);
}

Matrix Matrix::fill_random(unsigned int n = 10)
{
    for (unsigned int index = 0; index < cols * rows; index++)
    {
        this->values[index] = double(rand() % n);
    }
    return (*this);
}

Matrix Matrix::fill_from_array(double *array)
{
    memcpy(values, array, rows * cols * sizeof(double));
    return *this;
}

Matrix Matrix::set_zero()
{
    for (unsigned int idx = 0; idx < this->rows * this->cols; idx++)
    {
        this->values[idx] = 0;
    }
    return *this;
}

Matrix Matrix::set_identity()
{
    set_zero();
    for (unsigned int idx = 0; idx < this->cols * this->rows; idx += rows + 1)
    {
        this->values[idx] = 1.0;
    }
    return *this;
}

void Matrix::output()
{
    std::cout << *this << std::endl;
}

unsigned int Matrix::getrow()
{
    return (rows);
}

unsigned int Matrix::getcol()
{
    return (cols);
}

Matrix Matrix::minor(const unsigned int minor_row, const unsigned int minor_col)
{
    if (this->rows == 0 || this->cols == 0)
    {
        throw EMPTY_MATRIX;
    }
    Matrix minor(this->rows - 1, this->cols - 1);
    unsigned int minor_index = 0;
    for (unsigned int row = 0; row < this->rows; row++)
    {
        for (unsigned int col = 0; col < this->cols; col++)
        {
            if (row == minor_row || col == minor_col)
                continue;
            minor.values[minor_index++] = this->values[row * this->cols + col];
        }
    }
    return minor;
}

Matrix Matrix::set_transpose()
{
    Matrix trans(this->cols, this->rows);
    for (unsigned int row = 0; row < trans.rows; row++)
    {
        for (unsigned int col = 0; col < trans.cols; col++)
        {
            trans.values[row * trans.cols + col] = this->values[col * trans.rows + row];
        }
    }
    *this = trans;
    return (*this);
}

Matrix Matrix::operator+(const Matrix &B)
{
    Matrix add(*this);
    add += B;
    return (add);
}

Matrix Matrix::operator-(const Matrix &B)
{
    Matrix sub(*this);
    sub -= B;
    return (sub);
}

Matrix Matrix::operator*(const double k)
{
    Matrix multiply(*this);
    return (multiply *= k);
}

Matrix Matrix::operator*(const Matrix &B)
{
    Matrix temp(*this);
    temp *= B;
    return (temp);
}

Matrix Matrix::operator/(const double k)
{
    Matrix multiply(*this);
    multiply /= k;
    return multiply;
}

Matrix &Matrix::operator*=(const Matrix &matrix)
{
    if (cols != matrix.rows)
        throw MULTIPLYERROR;
    Matrix multiplication(rows, matrix.cols);
    for (unsigned int row = 0; row < multiplication.rows; row++)
    {
        for (unsigned int col = 0; col < multiplication.cols; col++)
        {
            double sum = 0;
            for (unsigned int k = 0; k < matrix.rows; k++)
            {
                sum += values[row * cols + k] * matrix.values[k * matrix.cols + col];
            }
            multiplication.values[row * multiplication.cols + col] = sum;
        }
    }
    *this = multiplication;
    return (*this);
}

Matrix &Matrix::operator+=(const Matrix &matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->values[index] += matrix.values[index];
    }
    return *this;
}

Matrix &Matrix::operator-=(const Matrix &matrix)
{
    if (rows != matrix.rows || cols != matrix.cols)
        throw NOTEQUAL;
    for (unsigned int index = 0; index < rows * cols; ++index)
    {
        this->values[index] -= matrix.values[index];
    }
    return *this;
}

Matrix &Matrix::operator*=(const double k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        this->values[idx] *= k;
    }
    return *this;
}

Matrix &Matrix::operator/=(const double k)
{
    for (unsigned int idx = 0; idx < rows * cols; idx++)
    {
        this->values[idx] /= k;
    }
    return *this;
}

Matrix &Matrix::operator=(const Matrix &A)
{
    if (this == &A)
        return *this;
    delete[] values;
    rows = A.rows;
    cols = A.cols;
    this->values = new double[rows * cols];
    if (!values)
        throw MEM_ERROR;
    memcpy(this->values, A.values, rows * cols * sizeof(double));
    return *this;
}

Matrix &Matrix::operator=(Matrix &&A) noexcept
{
    if (this == &A)
        return *this;
    delete[] A.values;
    rows = A.rows;
    cols = A.cols;
    values = A.values;
    A.values = nullptr;
    return *this;
}

double Matrix::determinant(const Matrix *matrix)
{
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    double det = 0;
    int k = 1;
    if (matrix->rows == 0)
        return 0;
    if (matrix->rows == 1)
        return matrix->values[0];
    if (matrix->rows == 2)
    {
        return (matrix->values[0] * matrix->values[3] - matrix->values[2] * matrix->values[1]);
    }
    for (unsigned int idx = 0; idx < matrix->cols; idx++)
    {
        Matrix temp = minor(0, idx);
        det += k * matrix->values[idx] * determinant(&temp);
        k = -k;
    }
    return det;
}

Matrix Matrix::reverse(const Matrix *matrix, const unsigned int size)
{
    double d = determinant(matrix);
    if (matrix->rows != matrix->cols)
        throw NOTSQUARE;
    Matrix reverse(matrix->rows, matrix->cols);
    int k = 1;
    for (unsigned int row = 0; row < reverse.rows; row++)
    {
        for (unsigned int col = 0; col < reverse.cols; col++)
        {
            Matrix temp = minor(row, col);
            reverse.values[row * size + col] = k * determinant(&temp);
            k = -k;
        }
    }
    reverse.set_transpose();
    if (fabs(d) < EPS)
        throw ZERODIVISION;
    reverse /= d;
    return reverse;
}

Matrix Matrix::exponent(unsigned int n = 30)
{
    if (rows != cols)
        throw NOTSQUARE;
    Matrix ex(rows, cols);
    Matrix temp(rows, cols);
    temp.set_identity();
    ex.set_identity();
    double fact = 1.0;
    for (unsigned int i = 1; i < n; i++)
    {
        fact *= i;
        temp *= (*this);
        ex += temp / fact;
    }
    return ex;
}
#endif // MATRIX_LIB_H