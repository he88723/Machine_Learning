#ifndef VECTORS_H
#define VECTORS_H

#include <initializer_list>

template<class Type>
class Vectors
{

public:


//Constructor=======================================================

	Vectors() : size{0}
	{this->mainData = nullptr;}

	Vectors(int sizeSet) : size{sizeSet}
	{
		if(sizeSet)
		{
			this->mainData = new Type[size];

			for(int i=0; i<size ;++i)
				this->mainData[i] = 0;
		}
		else
			this->mainData = nullptr;
	}

	Vectors(const Vectors<Type>& vector) : size{vector.size}
	{
		this->mainData = new Type[this->size];

		for(int i=0; i<this->size ;++i)
			this->mainData[i] = vector[i];
	}

	Vectors(std::initializer_list<Type> initList) : size{initList.size}
	{
		this->mainData = new Type[this->size];

		for(int i=0; i<this->size ;++i)
			this->mainData[i] = *(initList+i);
	}

	~Vectors()
	{delete[] this->mainData;}

//===================================================================

	void set(int count, Type val)
	{this->mainData[count] = val;}	

//Operator ----------------------------------------------------
	Vectors<Type> operator+(const Vectors<Type>& added)
	{
		if(this->size != added.size)
			return Vectors<Type>{};

		Vectors<Type> rt{this->size};

		for(int i=0; i<this->size ;++i)
			rt.set(i,this->mainData[i]+added[i]);

		return rt;
	}

	Vectors<Type> operator-(const Vectors<Type>&	minus)
	{
		if(this->size != minus.size)
			return Vectors<Type>{};

		Vectors<Type> rt{this->size};

		for(int i=0; i<this->size ;++i)
			rt.set(i,this->mainData[i]-minus[i]);

		return rt;
	}

	Type		  operator*(const Vectors<Type>& dotMutiplied)
	{
		Type sumRt;
		
		for(int i=0; i<this->size ;++i)
			sumRt += this->mainData[i] * dotMutiplied[i];

		return sumRt;
	}

	Type		  operator[](int count)const
	{return this->mainData[count];}

	Vectors<Type>*operator=(const Vectors<Type>& designated)
	{
		for(int i=0; i<size ;++i)
			this->mainData[i] = designated[i];

		return *this;
	}

	bool		  operator==(const Vectors<Type>& compare)
	{
		if(this->size != compare)
			return false;

		for(int i=0; i<this->size ;++i)
			if(this->mainData[i] != compare[i])
				return false;

		return true;
	}

	bool		  operator!=(const Vectors<Type>& compare)
	{return !(*this==compare);}

	//===================================================

	int size;

private:
	Type* mainData;

};

#endif	
