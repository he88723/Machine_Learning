#include "matrixOP.h"
#include <iostream>
#include <math.h>

using namespace std;
using namespace Math;

MatrixOP<double> operator*(double val, MatrixOP<double> ma)
{
	MatrixOP<double> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, val*rt(i,j));

	return rt;
}

MatrixOP<double> operator-(double val, MatrixOP<double> ma)
{
	MatrixOP<double> rt{ma};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, val-rt(i,j));

	return rt;
}

class LOSS
{

public:

	LOSS():loss{}{}
	double forward(MatrixOP<double> y, MatrixOP<double> t); 
	MatrixOP<double> backward()
	{return loss;}


	MatrixOP<double> loss;

};

class FC
{

public:

	FC(int numIn, int numOut, double lr):numberIn{numIn},numberOut{numOut},learningRate{lr},
	weight{numIn, numOut},bias{0.0},topVal{0,0},downVal{0,0},grad_w{0,0},grad_b{0}
	{
		weight.rndSet((double)0.0, (double)1.0);		
	}

	MatrixOP<double> forward(MatrixOP<double> indata);
	MatrixOP<double> sigmoid(MatrixOP<double> indata);
	MatrixOP<double> backward(MatrixOP<double> indata);

//data
	MatrixOP<double> weight;
	MatrixOP<double> topVal;
	MatrixOP<double> downVal;
	MatrixOP<double> grad_w;

	int numberIn;
	int numberOut;
	double learningRate;
	double bias;
	double grad_b;
};

class Net
{

public:

	Net(int inNum = 2, int hidNum = 4, int outNum = 1, double lr = 0.1):fc1{inNum, hidNum, lr},fc2{hidNum, outNum, lr},loss{}
	{}

	void train(MatrixOP<double> X, MatrixOP<double> Y);

	FC	 fc1;
	FC	 fc2;
	LOSS loss;

};

int main(void)
{
	
	MatrixOP<double> X1{{0,0},{0,1},{1,0},{1,1}};
	MatrixOP<double> Y1{{0},{1},{0},{1}};
	Net net{2,4,1,0.1};
	X1 = X1.transpose();
	Y1 = Y1.transpose();
	net.train(X1,Y1);

	return 0;
}

MatrixOP<double> FC::sigmoid(MatrixOP<double> indata)
{
	MatrixOP<double> rt{indata};

	for(int i=0; i<rt.rowCount ;++i)
		for(int j=0; j<rt.colCount ;++j)
			rt.set(i, j, 1/ ( 1+exp(0-rt(i,j)) ) );

	return rt;
}

MatrixOP<double> FC::forward(MatrixOP<double> indata)
{
	topVal = weight.transpose() * indata;

	downVal= indata;	

	for(int i=0; i<topVal.rowCount ;++i)
		for(int j=0; j<topVal.colCount ;++j)
			topVal.set(i, j, topVal(i,j)+bias);

	topVal = sigmoid(topVal);
	return topVal;
}

MatrixOP<double> FC::backward(MatrixOP<double> indata)
{
	MatrixOP<double> z{indata};

	for(int i=0; i<z.rowCount ;++i)
		for(int j=0; j<z.colCount ;++j)
			z.set(i, j, z(i,j)*topVal(i,j)*(1-topVal(i,j)) );

	grad_w = downVal * z.transpose();
	grad_b = z.sum();	

	for(int i=0; i<grad_w.rowCount ;++i)
		for(int j=0; j<grad_w.colCount ;++j)
			grad_w.set(i, j, grad_w(i,j)*learningRate);

	weight =  weight - grad_w;
	bias   -= learningRate * grad_b;

	return weight * z;

}

double LOSS::forward(MatrixOP<double> y, MatrixOP<double> t)
{
	loss = y - t;

	return (0.5*loss).sum();
}

void Net::train(MatrixOP<double> X, MatrixOP<double> Y)
{

	MatrixOP<double> layer1out{};
	MatrixOP<double> layer2out{};

	MatrixOP<double> layer1loss{};
	MatrixOP<double> layer2loss{};

	MatrixOP<double> saliency{};
	double los;

	for(int i=0; i<10000 ;++i)
	{

		layer1out  = fc1.forward(X);
		layer2out  = fc2.forward(layer1out);

		los        = loss.forward(layer2out, Y);
		layer2loss = loss.backward();
		layer1loss = fc2.backward(layer2loss);

		saliency   = fc1.backward(layer1loss);
	}

	layer1out = fc1.forward(X);
	layer2out = fc2.forward(layer1out);

	cout << layer1out << endl << layer2out << endl;

}
