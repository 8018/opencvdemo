#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

int PeakSplit(Mat &img, int th, int itertime)
{
	int hist[256] = {}; //直方图数据
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			hist[img.at<uchar>(i, j)]++;
		}
	}
 
	int p1 = 0, p1_v = 0; //峰值坐标 和 峰值数值
	int p2 = 255, p2_v = 0;
	int pth = th;
	while (itertime--)
	{
		for (int i = p1; i <= pth; i++)
		{
			if (hist[i] > p1_v)
			{
				p1_v = hist[i];
				p1 = i;
			}
 
		}
		for (int i = p2; i > pth; i--)
		{
			if (hist[i] > p2_v)
			{
				p2_v = hist[i];
				p2 = i;
			}
		}
		int tmp_th = (p1 + p2) / 2; //更新阈值为两个峰值坐标中心
		if (pth == tmp_th)
			break;
		else
			pth = tmp_th;
 
	}
	return pth;
}
//注释是自己理解，若有错误，欢迎批评指正！
Mat getGrayHistograph(const Mat grayImage)
{
	//定义求直方图的通道数目，从0开始索引
	int channels[]={0};
	//定义直方图的在每一维上的大小，例如灰度图直方图的横坐标是图像的灰度值，就一维，bin的个数
	//如果直方图图像横坐标bin个数为x，纵坐标bin个数为y，则channels[]={1,2}其直方图应该为三维的，Z轴是每个bin上统计的数目
	const int histSize[]={256};
	//每一维bin的变化范围
	float range[]={0,256};
 
	//所有bin的变化范围，个数跟channels应该跟channels一致
	const float* ranges[]={range};
 
	//定义直方图，这里求的是直方图数据
	Mat hist;
	//opencv中计算直方图的函数，hist大小为256*1，每行存储的统计的该行对应的灰度值的个数
	calcHist(&grayImage,1,channels,Mat(),hist,1,histSize,ranges,true,false);//cv中是cvCalcHist
 
	//找出直方图统计的个数的最大值，用来作为直方图纵坐标的高
	double maxValue=0;
	//找矩阵中最大最小值及对应索引的函数
	minMaxLoc(hist,0,&maxValue,0,0);
	//最大值取整
	int rows=cvRound(maxValue);
	//定义直方图图像，直方图纵坐标的高作为行数，列数为256(灰度值的个数)
	//因为是直方图的图像，所以以黑白两色为区分，白色为直方图的图像
	Mat histImage=Mat::zeros(rows,256,CV_8UC1);
 
	//直方图图像表示
	for(int i=0;i<256;i++)
	{
		//取每个bin的数目
		int temp=(int)(hist.at<float>(i,0));
		//如果bin数目为0，则说明图像上没有该灰度值，则整列为黑色
		//如果图像上有该灰度值，则将该列对应个数的像素设为白色
		if(temp)
		{
			//由于图像坐标是以左上角为原点，所以要进行变换，使直方图图像以左下角为坐标原点
			histImage.col(i).rowRange(Range(rows-temp,rows))=255; 
		}
	}
	//由于直方图图像列高可能很高，因此进行图像对列要进行对应的缩减，使直方图图像更直观
	Mat resizeImage;
	resize(histImage,resizeImage,Size(256,256));
	return resizeImage;
}


int thresholdTwoPeaks(const Mat src,const Mat out){
	Mat histogram = getGrayHistograph(src);
	Point firstPeakLoc;
	minMaxLoc(histogram,NULL,NULL,NULL,&firstPeakLoc);
	int firstPeak = firstPeakLoc.x;

	Mat measureDists = Mat::zeros(Size(256,1),CV_32FC1);
	for (int i = 0; i < 256; i++)
	{
		int hist_i = histogram.at<int>(0,i);
		measureDists.at<float>(0,i) = pow(float(i-firstPeak),2)*hist_i;
	}

	Point secondPeakLoc;
	minMaxLoc(measureDists,NULL,NULL,NULL,&secondPeakLoc);
	int secondPeak = secondPeakLoc.x;

	Point thresHoldLoc;
	int thresh = 0;

	if (firstPeak < secondPeak)
	{
		minMaxLoc(histogram.colRange(firstPeak,secondPeak),NULL,NULL,&thresHoldLoc);
		thresh = firstPeak + thresHoldLoc.x+1;
	}else{
		minMaxLoc(histogram.colRange(secondPeak,firstPeak),NULL,NULL,&thresHoldLoc);
		thresh = secondPeak + thresHoldLoc.x+1;
	}
	
	threshold(src,out,thresh,255,THRESH_BINARY);
	return thresh;

}

int main(int argc,char *argv[]){

    Mat src;
    src = imread( "../../Resources/anita.png", 1 );
	if (!src.data)
	{
		printf("could not load image...\n");
		return -1;
	}

    //定义灰度图像，转成灰度图
	Mat grayImage;
	cvtColor(src,grayImage,COLOR_BGR2GRAY);
    
	double the = 200;
    Mat globalThreshold;
	threshold(grayImage,globalThreshold,the,255,THRESH_BINARY);

	double otsuThe = 0;
    Mat otsuThreshold;
	threshold(grayImage,otsuThreshold,otsuThe,255,THRESH_OTSU+THRESH_BINARY);

	double triThe = 0;
    Mat triThreshold;
	threshold(grayImage,triThreshold,triThe,255,THRESH_TRIANGLE+THRESH_BINARY);

    Mat thresholdTwoPeak = grayImage;

	PeakSplit(thresholdTwoPeak,150,100);
	//PeakSplit(grayImage,thresholdTwoPeak);

	imshow("Origin Image", src);
	imshow("Gray Image", grayImage);
	imshow("Global Image", globalThreshold);
	imshow("OTSU Image", otsuThreshold);
	imshow("Triangle Image", triThreshold);
	imshow("TwoPeaks Image", thresholdTwoPeak);

	waitKey(0);


    return 0;
}