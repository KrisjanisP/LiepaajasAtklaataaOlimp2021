#include <bits/stdc++.h>

typedef unsigned int uint;

template<class T>
class Matrix{
public:
    Matrix(uint rowCount, uint colCount);
    Matrix(uint rowCount, uint colCount, T defValue);
    ~Matrix();
    uint rowCount, colCount;
    T *& operator[](uint index);
private:
    T ** matrix;
};