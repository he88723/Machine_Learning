#include <iostream>
#include <cstdio> 
#include <string>

#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>

#include "matrixOP.h"

using namespace cv;
using namespace Math;

struct Pic
{
	MatrixOP<double> matrix;
	unsigned char num;
};

inline void endian_swap(unsigned int& x);
inline void showImg(char data[28][28]);

class MNIST
{ 

public:

	MNIST(std::string impath, std::string lapath):fpIm{fopen(impath.c_str(), "r")}, fpLa{fopen(lapath.c_str(), "r")}, enable{false}
	{
		unsigned int header{0};
		
		fread(&header, 4, 1, fpIm);
		endian_swap(header);
		if(header != 2051)
		{
			std::cerr << "\033[1;31mWarning\033[0m:: The file path may not mnist image database." << std::endl;
			fclose(fpIm);
			
			return;
		}

		fread(&header, 4, 1, fpLa);
		endian_swap(header);
		if(header != 2049)
		{
			std::cerr << "\033[1;31mWarning\033[0m:: The file path may not mnist lable database." << std::endl;
			fclose(fpIm);
			fclose(fpLa);

			return;
		}

		fseek(fpIm, 16, SEEK_SET);
		fseek(fpLa, 8,  SEEK_SET);

		enable = true;
	}

	inline Pic getPic()
	{
		if(!enable)
		{
			std::cerr << "\033[1;31mWarning\033[0m:: The file is close." << std::endl;
			exit(-1);
		}

		MatrixOP<double> rt1{28,28};
		unsigned char rt{0};

		unsigned char buffer[28][28];
		
		fread(buffer, 1, 784, fpIm);
		fread(&rt, 1, 1, fpLa);

		for(int i=0; i<28 ;++i)
			for(int j=0; j<28 ;++j)
				rt1.set(i, j, static_cast<double>(buffer[i][j]));		

		return Pic{rt1,rt};
	}

	inline unsigned char getArr(char dataSet[28][28])
	{
		if(!enable)
		{
			std::cerr << "\033[1;31mWarning\033[0m:: The file is close." << std::endl;
			exit(-1);
		}

		unsigned char rt{0};

		fread(dataSet, 1, 784, fpIm);
		fread(&rt, 1, 1, fpLa);

		return rt;
	}

 

	FILE* fpIm;
	FILE* fpLa;

	bool enable;
};

inline void endian_swap(unsigned int& x)
{
	x = (x>>24) |
	    ((x<<8) & 0x00FF0000) |
    	((x>>8) & 0x0000FF00) |
    	(x<<24);
}

inline void showImg(char data[28][28])
{
	Mat img{28, 28, CV_8UC1, data};

	namedWindow( "Display window", WINDOW_AUTOSIZE );
	imshow( "Display window", img);

	waitKey(0);
}
