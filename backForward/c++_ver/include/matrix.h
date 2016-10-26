#ifndef Matrix_H
#define Matrix_H

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
			this->mainData = new Type[rowCount * colCount];

			int size = rowCount * colCount;
			for(int i=0; i<size ;++i)
				this->mainData[i] = 0;
		}
		else
			this->mainData = nullptr;
	}

	Matrix(Type** copied, int row, int col) : rowCount{row} , colCount{col}
	{
		this->mainData = new Type[rowCount * colCount];
		int basic{0};

		for(int i=0; i<rowCount ;++i)
		{
			for(int j=0; j<colCount ;++j)
				this->mainData[basic + j] = copied(i, j);
			basic += colCount;
		}
	}

	Matrix(const Matrix<Type>& matrix) : rowCount{matrix.rowCount} , colCount{matrix.colCount}
	{	
		this->mainData = new Type[rowCount * colCount];
		int basic{0};

		for(int i=0; i<rowCount ;++i)
		{
			for(int j=0; j<colCount ;++j)
				this->mainData[basic + j] = matrix(i, j);
			basic += colCount;
		}	
	}

	Matrix(std::initializer_list<std::initializer_list<Type>> initList)
	   	: rowCount{(int)initList.size()} , colCount{(int)(*initList.begin() ).size()}
	{
		this->mainData = new Type[rowCount * colCount];
		int basic{0};

		for(int i=0; i<rowCount ;++i)
		{
			for(int j=0; j<colCount ;++j)
				this->mainData[basic + j] = *(((initList.begin()+i)->begin()) + j);
			basic += colCount;
		}
	}
	
	~Matrix()
	{
		delete this->mainData;
	}

//===================================================================

	inline bool set(int row, int col, Type val)
	{
		if(!(0 <= row < rowCount || 0 <= col < colCount))
			return false;
		this->mainData[row*colCount + col] = val;
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

	inline Type operator()(int row, int col) const
	{
		return this->mainData[row*colCount +col];
	}


	inline Matrix<Type> operator+(const Matrix<Type>& added)
	{
		if(!is_same_size(added))
			return Matrix<Type>();

		Matrix<Type> rt{this->rowCount, this->colCount};
		int basic{0};

		for(int i=0; i<added.rowCount ;++i)
		{
			for(int j=0; j<added.colCount ;++j)
				rt.set(i, j, this->mainData[basic + j] + added(i, j));
			basic += colCount;
		}

		return rt;
	}
	inline Matrix<Type> operator+(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt(i,j)+opVal);

		return rt;
	}


	inline Matrix<Type>  operator-(const Matrix<Type>& minus)
	{
		if(!is_same_size(minus))
			return Matrix<Type>();

		Matrix<Type> rt{this->rowCount, this->colCount};
		int basic{0};

		for(int i=0; i<minus.rowCount ;++i)
		{
			for(int j=0; j<minus.colCount ;++j)
				rt.set(i, j, this->mainData[basic + j] - minus(i,j));
			basic += colCount;
		}

		return rt;
	}
	inline Matrix<Type>operator-(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt(i,j) - opVal);
	}


	inline Matrix<Type>  operator*(const Matrix<Type>& mutiplied)
	{
		Matrix<Type> rt{this->rowCount, mutiplied.colCount};
		int basic{0};

		for(int i=0; i<this->rowCount;++i)
		{
			for(int j=0; j<mutiplied.colCount ;++j)
				for(int k=0; k<this->colCount ;++k)
					rt.set(i, j, rt(i,j) + (this->mainData[basic + k] * mutiplied(k,j) ) );
			basic += colCount;
		}

		return rt;
	}
	inline Matrix<Type> operator*(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt(i,j)*opVal);

		return rt;
	}


	inline Matrix<Type> operator/(const Type& opVal)
	{
		Matrix<Type> rt{*this};

		for(int i=0; i<rowCount ;++i)
			for(int j=0; j<colCount ;++j)
				rt.set(i, j, rt(i,j)/opVal);

		return rt;
	}

	
	inline Matrix<Type>& operator=(const Matrix<Type>& designated)
	{
		if(!is_same_size(designated))
		{
			this->rowCount = designated.rowCount;
			this->colCount = designated.colCount;

			delete this->mainData;
			this->mainData = new Type[rowCount * colCount];
		}

		int basic{0};
		for(int i=0; i<this->rowCount ;++i)
		{
			for(int j=0; j<this->colCount ;++j)
				this->mainData[basic + j] = designated(i,j);
			basic += colCount;
		}

		return *this;
	}

	inline bool operator==(const Matrix<Type>& matched)
	{
		if(!is_same_size(matched))
			return false;

		int basic{0};	
		for(int i=0; i<this->rowCount ;++i)
		{
			for(int j=0; j<this->colCount ;++j)
				if(this->mainData[basic + j] != matched(i,j))
					return false;
			basic += colCount;
		}

		return true;
	}
	inline bool operator!=(const Matrix<Type>& matched)
	{return !(*this == matched);}

//==================================================================

	int colCount ,rowCount;

protected:
	Type* mainData;
};

};

#endif
