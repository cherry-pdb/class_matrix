#ifndef MATRIX_H
#define MATRIX_H

#include "exceptions.h"

template <typename T>
class Iterator;

template <typename T>
class Matrix
{
private:
    size_t rows;
    size_t cols;
    T **data;
    void alloc_memory();
public:
    //конструкторы и деструктор
    Matrix();
    explicit Matrix(int n, int m);
    Matrix(const Matrix<T>& mat);
    Matrix (Matrix<T>&& mat);
    explicit Matrix(std::initializer_list<std::initializer_list<T>> lst);
    ~Matrix();

    int get_rows() const;
    int get_cols() const;

    bool is_square();

    void set_elem(unsigned i, unsigned j, const T& elem);
    T& operator () (unsigned i, unsigned j);
    T& get_elem (unsigned i, unsigned j);

    //перегрузка операторов
    Matrix<T>& operator = (const Matrix<T>&mat);
    Matrix<T>& operator += (const Matrix<T>&mat);
    Matrix<T>& operator -= (const Matrix<T>&mat);

    //перегрузка операторов для двух матриц
    Matrix<T> operator + (const Matrix<T>& mat);
    Matrix<T> operator - (const Matrix<T>& mat);
    Matrix<T> operator * (const Matrix<T>& mat);

    //перегрузка операторов для матрицы и числа
    Matrix<T> operator + (double num);
    Matrix<T> operator - (double num);
    Matrix<T> operator * (double num);
    Matrix<T> operator / (double num);

    //перегрузка оператора вывода
    template <typename _T>
    friend std::ostream& operator << (std::ostream& os, const Matrix<_T>& mat);

    //итераторы
    Iterator<T> iterator_begin() {return Iterator<T>(*this, 0, 0);};
    Iterator<T> iterator_end() {return Iterator<T>(*this, get_rows(), 0);};

    //доп методы
    T& find_max(Matrix<T>& mat);
    T& find_min(Matrix<T>& mat);
    T& find_med(Matrix<T>& mat);
    void swap_min_and_max();
    void transpose_main();
    void transpose_side();

};

template <typename T> //выделение памяти - вспомогательная функция
void Matrix <T>::alloc_memory()
{
    try
    {
        data = new T* [rows];
        for (size_t i = 0; i < rows; i++)
            data[i] = new T [cols];
    }
    catch (std::bad_alloc &ex)
    {
        if (data != NULL)
            delete[] data;
        throw Exceptions ("memory allocation error.");
    }
}

template <typename T> //конструктор длины
Matrix <T>::Matrix (int n, int m)
{
    if (n <= 0 || m <= 0)
        throw Exceptions ("incorrect size.");
    rows = (size_t) n;
    cols = (size_t) m;
    alloc_memory();
}

template <typename T>
Matrix <T>::Matrix(const Matrix<T>& mat) //конструктор копирования
{
    rows = mat.get_rows();
    cols = mat.get_cols();
    if (rows == 0 || cols == 0)
        throw Exceptions ("memory allocation error.");
    alloc_memory();
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] = mat.data[i][j];
}

template <typename T> //конструктор перемещения
Matrix <T>::Matrix(Matrix<T>&& mat)
{
    rows = mat.rows;
    cols = mat.cols;
    data = mat.data;
    mat.rows = 0;
    mat.cols = 0;
    mat.data = nullptr;
}

template <typename T>
Matrix <T>::Matrix(std::initializer_list<std::initializer_list<T>> lst) //конструктор со списком инициализации
{
    int ind_i = 0, ind_j = 0;
    rows = lst.size();
    cols = 0;
    for (auto i : lst)
    {
        for (auto j : i)
            cols++;
        break;
    }
    alloc_memory();
    for (auto i : lst)
    {
        ind_j = 0;
        for (auto j : i)
        {
            set_elem(ind_i, ind_j, j);
            ind_j++;
        }
        ind_i++;
    }
}

template <typename T>
Matrix <T>::~Matrix() //деструктор
{
    for (size_t i = 0; i < rows; i++)
        delete[] data[i];
    delete[] data;
}

template <typename T> //метод получения числа столбцов матрицы
int Matrix <T>::get_cols() const
{
    return cols;
}

template <typename T> //метод получения числа строк матрицы
int Matrix <T>::get_rows() const
{
    return rows;
}

template <typename T> //метод проверки матрицы на квадратную
bool Matrix <T>::is_square()
{
    bool result;
    if (rows == cols)
        result = true;
    return result;
}

template <typename _T>
std::ostream& operator << (std::ostream& os, const Matrix<_T>& mat) //перегрузка оператора <<
{
    if (mat.get_rows() == 0 || mat.get_cols() == 0)
        throw Exceptions ("matrix is null.");
    for (int i = 0; i < mat.get_rows(); i++)
    {
        os << "\n";
        for (int j = 0; j < mat.get_cols(); j++)
            os << mat.data[i][j] << "\t";
    }
    os << "\n";
    return os;
}

template <typename T>
void Matrix <T>::set_elem (unsigned int i, unsigned j, const T& elem) //метод изменения элемента матрицы по индексу
{
    if (i < 0 || i >= (size_t)get_rows() || j < 0 || j >= (size_t)get_cols())
        throw Exceptions ("incorrect index");
    data[i][j] = elem;
}

template <typename T>
T& Matrix <T>::operator () (unsigned int i, unsigned int j) //метод получения элемента матрицы по индексу
{
    if (i < 0 || i >= (size_t)get_rows() || j < 0 || j >= (size_t)get_cols())
        throw Exceptions ("incorrect index");
    return data[i][j];
}

template <typename T>
T& Matrix <T>::get_elem (unsigned int i, unsigned int j) //метод получения элемента матрицы по индексу
{
    if (i < 0 || i >= (size_t)get_rows() || j < 0 || j >= (size_t)get_cols())
        throw Exceptions ("incorrect index");
    return data[i][j];
}

template <typename T>
Matrix<T>& Matrix <T>::operator = (const Matrix<T>& mat) //перегрузка оператора присваивания
{
    if (rows != (size_t)mat.get_rows() || cols != (size_t)mat.get_cols())
        throw Exceptions ("different size of matrix.");
    alloc_memory();
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] = mat.data[i][j];
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator +=(const Matrix<T>&mat) //перегрузка оператора +=
{
    if (rows != (size_t)mat.get_rows() || cols != (size_t)mat.get_cols())
        throw Exceptions ("different size of matrix.");
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] += mat.data[i][j];
    return *this;
}

template <typename T>
Matrix<T>& Matrix<T>::operator -= (const Matrix<T> &mat) //перегрузка оператора -=
{
    if (rows != (size_t)mat.get_rows() || cols != (size_t)mat.get_cols())
        throw Exceptions ("different size of matrix.");
    for (size_t i = 0; i < rows; i++)
        for (size_t j = 0; j < cols; j++)
            data[i][j] -= mat.data[i][j];
    return *this;
}

template<typename T>
Matrix<T> Matrix <T>::operator +(const Matrix<T>& mat) //перегрузка оператора +
{
    Matrix <T> new_mat(*this);
    new_mat += mat;
    return new_mat;
}

template<typename T>
Matrix<T> Matrix <T>::operator -(const Matrix<T>& mat) //перегрузка оператора -
{
    Matrix <T> new_mat(*this);
    new_mat -= mat;
    return new_mat;
}

template<typename T>
Matrix<T> Matrix <T>::operator *(const Matrix<T>& mat) //перегрузка оператора *
{
    Matrix <T> new_mat(*this);
    if ((int)rows != mat.get_rows() || (int)cols != mat.get_cols())
        throw Exceptions ("different size of matrix.");
    for (int i = 0; i < mat.get_rows(); i++)
        for (int j = 0; j < mat.get_cols(); j++)
            new_mat.data[i][j] *= mat.data[i][j];
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator +(double num) //перегрузка оператора + с числом
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i < new_mat.get_rows(); i++)
        for (int j = 0; j < new_mat.get_cols(); j++)
            new_mat.data[i][j] += num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator -(double num) //перегрузка оператора - с числом
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i < new_mat.get_rows(); i++)
        for (int j = 0; j < new_mat.get_cols(); j++)
            new_mat.data[i][j] -= num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator *(double num) //перегрузка оператора * с числом
{
    Matrix <T> new_mat(*this);
    for (int i = 0; i < new_mat.get_rows(); i++)
        for (int j = 0; j < new_mat.get_cols(); j++)
            new_mat.data[i][j] *= num;
    return new_mat;
}

template <typename T>
Matrix<T> Matrix <T>::operator /(double num) //перегрузка оператора / с числом
{
    Matrix <T> new_mat(*this);
    if (num == 0)
        throw Exceptions ("division by zero is not allowed.");
    for (int i = 0; i < new_mat.get_rows(); i++)
        for (int j = 0; j < new_mat.get_cols(); j++)
            new_mat.data[i][j] /= num;
    return new_mat;
}

template <typename T>   //конструктор без параметров
Matrix <T>::Matrix()
{
    rows = 0;
    cols = 0;
    data = nullptr;
}
#endif // MATRIX_H
