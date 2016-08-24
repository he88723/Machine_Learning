#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

float weight[3] = {1,7,0};

int functionTest(float x,float y)
{

	float sumRt(0.0);

	sumRt = x*weight[0] + y*weight[1] + weight[2];
	return sumRt>0?1:-1;

}

int main(void)
{
	float rate = 1.0;
	int falseT = 0;

	float datas[11][2] = {{1,7},{1,2},{1,4},{-1,3},{-4,-2},{-3,2}
		,{3,-2},{-2,-11},{2.5,-15},{-1,-12},{1, 22}};

	int target[] = {1,1,1,-1,-1,-1,1, -1, 1, 1, -1,1};

	while(true)
	{
		falseT = 0;	
		for(int i=0; i<11 ;++i)
		{
		
			if(functionTest(datas[i][0],datas[i][1]) != target[i])
			{
				++falseT;
			
				weight[0] += target[i]*datas[i][0]*rate;
				weight[1] += target[i]*datas[i][1]*rate;
				weight[2] += target[i]*rate;
			
			}
		
		}
	
		if(!falseT)
			break;

		cout << "weight :" << weight[0] << "," << weight[1] << "," << weight[2] << endl;
		cout << "fasle: " << falseT <<endl;

	}

	cout << weight[0] << " " << weight[1] << " " << weight[2] << endl;

	return 0;

}
