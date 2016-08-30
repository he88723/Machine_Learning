#include <iostream>
#include <math.h>

using namespace std;

struct Point
{
	double x;
	double y;
};

double countDistance(Point first, Point second)
{
	double sum;

	sum =  (first.x-second.x)*(first.x-second.x);
	sum += (first.y-second.y)*(first.y-second.y);

	return sqrt(sum);
}

int Test(Point* datsSet, Point inData, int* target, int dataCount)
{

	double smaller = countDistance(inData, datsSet[0]);
	int smallerT   = target[0];

	for(int i=1; i<dataCount ;++i)
	{
		double now = countDistance(inData, datsSet[i]);
		if(smaller > now)
			continue;

		smaller = now;
		smallerT= target[i];
	}

	return smallerT;
}

int main(void)
{

	Point datas[11]		 = {{1,7},{1,2},{1,4},{-1,3},{-4,-2},{-3,2}
						  ,{3,-2},{-2,-11},{2.5,-15},{-1,-12},{1, 22}};

	int target[]         = {1,1,1,-1,-1,-1,1, -1, 1, 1, -1,1};

	Point test{-2,3};

	cout << Test(datas, test, target, 11) << endl;

	return 0;
}
