#include "Matrix.h"
#include "windows.h"

template class Matrix<std::string>;

template<class T>
Matrix<T>::Matrix(uint _rowCount, uint _colCount)
{
    rowCount = _rowCount;
    colCount = _colCount;
    matrix = new T*[rowCount];
    for(int i=0;i<rowCount;i++){
        T * matrixRow = new T[colCount];
        matrix[i] = matrixRow;
    }
}

template<class T>
Matrix<T>::Matrix(uint _rowCount, uint _colCount, T defValue)
{
    rowCount = _rowCount;
    colCount = _colCount;
    matrix = new T*[rowCount];
    for(int i=0;i<rowCount;i++){
        T * matrixRow = new T[colCount];
        for(int j=0;j<colCount;j++) matrixRow[j] = defValue;
        matrix[i] = matrixRow;
    }
}

template<class T>
Matrix<T>::~Matrix()
{
    for(int i=0;i<rowCount;i++){
        delete[ ] matrix[i];
    }
    delete[ ] matrix;
}

template<class T>
T*& Matrix<T>::operator[](uint index)
{
    return matrix[index];
}  
