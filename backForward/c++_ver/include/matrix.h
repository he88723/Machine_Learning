#ifndef Matrix_H
#define Matrix_H

#include "vectors.h"
#include <initializer_list>

/* 
 *
 * --------->colCount
 *| [ 1 2 3 ]
 *| [ 4 5 6 ]
 *| [ 7 8 9 ]
 *v [ 3 7 9 ]
 *rowCount
 *
 * Can init Matrix{{1,2,3},{4,5,6}......}
 *
 */

void merge_recursive(int in[], int reg[], int start, int end);
void arrange(int in[], int len);

namespace Math
{

/*
template<class Type>
Type det(const Matrix&)
{}

template<class Type>
Type dot_Product(Matrix first, Matrix second)
{}
*/

enum operate{Add, Minus, Mutiply, Divide};

template<class Type>
class Matrix
{

public:

//Matrix constructor

	Matrix(int row = 0, int col = 0) : rowCount{row} , colCount{col}
	{
		if(col && row)
		{
			this->mainData = new Type*[rowCount];

			for(int i=0; i<rowCount ;++i)
			{
				this->mainData[i] = new Type[colCount];
		
				for(int j=0; j<colCount ;++j)
					this->mainData[i][j] = 0;

			}
		}
		else
			this->mainData = nullptr;
	}

	Matrix(Type** copied, int row, int col) : rowCount{row} , colCount{col}
	{

		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = copied[i][j];
		}
	}

	Matrix(const Matrix<Type>& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{
	
		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
		
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = matrix[i][j];
		
		}
	
	}

	Matrix(std::initializer_list<std::initializer_list<Type>> initList)
	   	: rowCount{(int)initList.size()} , colCount{(int)(*initList.begin() ).size()}
	{

		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = *(((initList.begin()+i)->begin()) + j);
		}
	}
	
	Matrix(const Vectors<Type>* copied, int row, int col) : rowCount{row} , colCount{col}
	{

		this->mainData = new Type*[rowCount];

		for(int i=0; i<rowCount ;++i)
		{
			this->mainData[i] = new Type[colCount];

			for(int j=0; j<colCount ;++j)
				this->mainData[i][j] = copied[i][j];
		}

	}

	~Matrix()
	{
	
		for	(int i=0; i<rowCount ;++i)
			delete this->mainData[i];
		
		delete this->mainData;
	}

//===================================================================

	inline bool set(int row, int col, Type val)
	{
		if(!(0 <= row < rowCount || 0 <= col < colCount))
			return false;
		this->mainData[row][col] = val;
		return true;
	}

	inline bool is_same_size(const Matrix<Type>& matched)
	{

		if(this->colCount != matched.colCount)
			return false;
		else if(this->rowCount != matched.rowCount)
			return false;
		
		return true;

	}

//Matrix operator

	inline Type* operator[](int row) const
	{
		if(row >= rowCount)
			return nullptr;
		return this->mainData[row];
	}


	inline Matrix<Type> operator+(const Matrix<Type>& added)
	{
		if(!is_same_size(added))
			return Matrix<Type>();

		Matrix<Type> rt{this->rowCount, this->colCount};

		for(int i=0; i<added.rowCount ;++i)
			for(int j=0; j<added.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] + added[i][j]);
		return rt;
	}
	inline Matrix<Type> operator+(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt[i][j]+opVal);

		return rt;
	}


	inline Matrix<Type>  operator-(const Matrix<Type>& minus)
	{
		if(!is_same_size(minus))
			return Matrix<Type>();

		Matrix<Type> rt{this->rowCount, this->colCount};

		for(int i=0; i<minus.rowCount ;++i)
			for(int j=0; j<minus.colCount ;++j)
				rt.set(i, j, this->mainData[i][j] - minus[i][j]);
		return rt;
	}
	inline Matrix<Type>operator-(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt[i][j]-opVal);
	}


	inline Matrix<Type>  operator*(const Matrix<Type>& mutiplied)
	{
		Matrix<Type> rt{this->rowCount, mutiplied.colCount};

		for(int i=0; i<this->rowCount;++i)
			for(int j=0; j<mutiplied.colCount ;++j)
				for(int k=0; k<this->colCount ;++k)
					rt.set(i, j, rt[i][j] + (this->mainData[i][k] * mutiplied[k][j]) );
		return rt;
	}
	inline Matrix<Type> operator*(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt[i][j]*opVal);

		return rt;
	}


	inline Matrix<Type> operator/(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt[i][j]/opVal);

		return rt;
	}

	
	inline Matrix<Type>& operator=(const Matrix<Type>& designated)
	{
		if(!is_same_size(designated))
		{
			this->rowCount = designated.rowCount;
			this->colCount = designated.colCount;

			delete this->mainData;
			this->mainData = new Type*[rowCount];

			for(int i=0; i<rowCount ;++i)
				this->mainData[i] = new Type[colCount];
		}

		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				this->mainData[i][j] = designated[i][j];
		return *this;
	}
	inline bool operator==(const Matrix<Type>& matched)
	{
		if(this->rowCount != matched.rowCount ||
		   this->colCount != matched.colCount)
			return false;
	
		for(int i=0; i<this->rowCount ;++i)
			for(int j=0; j<this->colCount ;++j)
				if(this->mainData[i][j] != matched[i][j])
					return false;
		return true;
	}


	inline bool operator!=(const Matrix<Type>& matched)
	{return !(*this == matched);}

//==================================================================

	int colCount ,rowCount;

protected:
	Type** mainData;
};

};

#endif
