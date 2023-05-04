#ifndef ITERATOR_H
#define ITERATOR_H

#include "matrix.h"

template <typename T>
class Iterator
{
private:
    size_t it_r;
    size_t it_c;
    Matrix <T> &mat;
public:
    explicit Iterator <T> (Matrix <T> &container_obj, size_t rows, size_t cols);

    Iterator <T> next();
    Iterator <T> &operator++();

    T value();
    T &operator*();

    bool is_end();
    bool is_begin();

    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
};

//конструктор принимающий объект контейнерного класса
template <typename T>
Iterator <T>::Iterator(Matrix <T> &container_obj, size_t rows, size_t cols):mat(container_obj), it_r(rows), it_c(cols)
{
    if (rows == -1 || cols == -1) {
        it_r = mat.get_rows();
        it_c = mat.get_cols();
    }
}

template <typename T> //перейти к следующему объекту в контейнере
Iterator <T> Iterator<T>::next()
{
    if (!(this->is_end())){
        if ((it_c == mat.get_cols()-1)) {
            it_r++;
            it_c = 0;
        } else
            it_c++;
    }
    return *this;
}

template <typename T> //указывает ли итератор на конечный (фиктивный) элемент контейнера
bool Iterator <T>::is_end()
{
    bool result;
    if (it_r == mat.get_rows() && it_c == 0)
        result = true;
    return result;
}

template <typename T> //указывает ли итератор на первый элемент контейнера
bool Iterator<T>::is_begin()
{
    bool result;
    if (it_r == 0 && it_c == 0)
        result = true;
    return result;
}

template <typename T> //значение текущего объекта в контейнере
T Iterator <T>::value()
{
    return **this;
}

template <typename T> //перейти к следующему объекту в контейнере
Iterator<T> & Iterator<T>::operator++()
{
    if (!(this->is_end())){
        if (it_c == mat.get_cols()-1) {
            it_r++;
            it_c = 0;
        } else
            it_c++;
    }
    return *this;
}

template <typename T> //значение текущего объекта в контейнере
T & Iterator<T>::operator*()
{
    return mat(it_r,it_c);
}

template <typename T> //оператор сравнения
bool Iterator<T>::operator ==(Iterator<T> &b)
{
    return ((it_r == b.it_r) && (it_c == b.it_r));
}

template <typename T> //оператор сравнения
bool Iterator<T>::operator !=(Iterator<T> &b)
{
    return ((it_r != b.it_r) || (it_c != b.it_r));
}

#endif // ITERATOR_H
