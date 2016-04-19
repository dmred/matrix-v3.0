// matrix.cpp: îïðåäåëÿåò òî÷êó âõîäà äëÿ êîíñîëüíîãî ïðèëîæåíèÿ.
//
#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <fstream>
#include <string>
#include "matrixexception.h"
using namespace std;
#ifndef matrix_cpp
#define matrix_cpp
template <typename T>
Matrix<T>::Matrix(unsigned int rows, unsigned int columns) :n(rows), m(columns)
{
	matrix = new T*[n];
	for (int i = 0; i<n; i++)
	{
		matrix[i] = new T[m];
		for (int j = 0; j<m; j++)
		{
			matrix[i][j] = 0;
		}
	}
}
template <typename T>
Matrix<T>::Matrix(const Matrix& copy) :n(copy.n), m(copy.m)
{
	matrix = new T*[n];
	for (int i = 0; i<n; i++)
	{
		matrix[i] = new T[m];
		for (int j = 0; j<m; j++)
		{
			matrix[i][j] = copy.matrix[i][j];
		}
	}
}
template <typename T>
Matrix<T>::~Matrix()
{
	if (matrix != nullptr)
	{
		for (int i = 0; i<n; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}
}
template <typename T>
Matrix<T> Matrix<T>::operator + (const Matrix<T> &matr)
{
		if (this->n!=matr.n || this->m!=matr.m) 
	{
		throw SizeException();
	}
	else if (this->matrix==nullptr || matr.matrix==nullptr)
	{
		throw EmptyException();
	}
	Matrix result(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			result.matrix[i][j] = matrix[i][j] + matr.matrix[i][j];
		}
	}
	return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator - (const Matrix<T> &matr)
{
	if (this->n!=matr.n || this->m!=matr.m) 
	{
		throw SizeException();
	}
	else if (this->matrix==nullptr || matr.matrix==nullptr)
	{
		throw EmptyException();
	}
	Matrix result(n, m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			result.matrix[i][j] = matrix[i][j] - matr.matrix[i][j];
		}
	}
	return result;
}
template <typename T>
Matrix<T> Matrix<T>::operator * (const Matrix<T> &matr)
{
	if (this->n!=matr.m) 
	{
		throw SizeException1();
	}
	else if (this->matrix==nullptr || matr.matrix==nullptr)
	{
		throw EmptyException();
	}
	Matrix result(n, matr.m);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < matr.m; j++)
		{
			T value = 0;
			for (int k = 0; k < m; k++)
			{
				value += matrix[i][k] * matr.matrix[k][j];
			}
			result.matrix[i][j] = value;
		}
	}
	return result;
}
template <typename T>
Matrix<T> &Matrix<T>::operator = (const Matrix<T> &matr)
{
	if (this != &matr)
	{
		if (matrix != nullptr)
		{
			for (int i = 0; i<n; i++)
			{
				delete[] matrix[i];
			}
			delete[] matrix;
		}
		n = matr.n;
		m = matr.m;
		matrix = new T*[n];
		for (int i = 0; i<n; i++)
		{
			matrix[i] = new T[m];
			for (int j = 0; j<m; j++)
			{
				matrix[i][j] = matr.matrix[i][j];
			}
		}
	}
	return *this;
}
template <typename T>
bool Matrix<T>::operator == (const Matrix<T> &matr) 
{
	if (n!=matr.n || m!=matr.m) 
	{
		return false;
	}

	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < m; j++) 
		{
			if (matrix[i][j] != matr.matrix[i][j]) 
			{
				return false;
			}
		}
	}
	return true;
}
template <typename T>
T* Matrix<T>::operator [] (unsigned int index)
{
	if (matrix==nullptr) 
	{
		throw EmptyException();
	}
	else if (index <= this->n)
	{
		return this->matrix[index];
	}
	else
	{
		throw RowException();
	}
}
template <typename T>
unsigned int Matrix<T>::Rows() const
{
	return n;
}
template <typename T>
unsigned int Matrix<T>::Columns() const
{
	return m;
}
template <typename T>
std::ostream &operator << (std::ostream &out, const Matrix<T> &temp)
{
	for (int i = 0; i < temp.n; i++)
	{
		for (int j = 0; j < temp.m; j++)
		{
			out << temp.matrix[i][j] << " ";
		}
		out << endl;
	}
	return out;
};
template <typename T>
std::istream &operator >> (std::istream &input, Matrix<T> &matr)
{
    for (int i = 0; i < matr.n; i++) 
    {
        for (int j = 0; j < matr.m; j++) 
        {
            if (!(input >> matr.matrix[i][j]))
            {
                throw FillException();
            }
        }
    }
    return input;
};
#endif
