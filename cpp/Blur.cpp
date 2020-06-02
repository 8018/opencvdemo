#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;


int main(int argc,char *argv[]){

    Mat src;
    src = imread( "../../Resources/dot.png", 1 );
	if (!src.data)
	{
		printf("could not load image...\n");
		return -1;
	}

    Size size = Size(15,15);

    Mat averageBlur,gaussBlur,medianOut,bilateralOut;
	//均值滤波
	blur(src,averageBlur,size);
	//高斯滤波
	GaussianBlur(src,gaussBlur,size,5,5);
	//中值滤波
	medianBlur(src, medianOut, 9);
	//双边滤波
	bilateralFilter(src, bilateralOut, 50, 50 * 2, 50 / 2);
	
	imshow("Origin Image", src);
	imshow("Average Blur Image", averageBlur);
	imshow("Gauss Blur Image", gaussBlur);
	imshow("Median Blur Image", medianOut);
	imshow("Bilateral Filter Image", bilateralOut);
	waitKey(0);


    return 0;
}