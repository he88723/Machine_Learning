#include "matrixOP.h"

using namespace Math;

/////////////////////////////////////////////////////////////////////////MatrixOP

void merge_recursive(int in[], int reg[], int start, int end)
{

	if(start>=end)
		return;

	int start1{start};
	int start2{((end-start)>>1)+start};
	int end1{((end-start)>>1)+start+1};
	int end2{end};

	if(!(start1 == start2 || end1 == end2))
	{
		merge_recursive(in, reg, start1, end1);
		merge_recursive(in, reg, start2, end2);
	}

	int k{start};
	while(start1 <= end1 && start2 <= end2)
		reg[k++] = in[start1] < in[start2]?in[start1++]:in[start2++];
	while(start1 <= end1)
		reg[k++] = in[start1++];
	while(start2 <= end2)
		reg[k++] = in[start2++];

	for(k=start; k<end ; ++k)
		in[k] = reg[k];
}

void arrange(int in[], int len)
{

	int reg[len];
	merge_recursive(in, reg, 0, len-1);
}
