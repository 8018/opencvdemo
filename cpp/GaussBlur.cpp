#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

int main(int argc,char *argv[]){

    Mat src;
    src = imread( "../../Resources/cathy.png", 1 );
	if (!src.data)
	{
		printf("could not load image...\n");
		return -1;
	}


	Size size;
	size = Size(25,25);

    Mat gaussSmothOut;
    GaussianBlur(src,gaussSmothOut,size,0,(double)5.0,4);
	
	imshow("origin Image", src);
	imshow("Blured Image", gaussSmothOut);
	waitKey(0);


    return 0;
}