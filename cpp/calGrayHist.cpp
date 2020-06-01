#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;


Mat calHistrom(Mat image){

    //步骤一：分通道显示
	vector<Mat>bgr_planes;
	split(image, bgr_planes);
	//split(// 把多通道图像分为多个单通道图像 const Mat &src, //输入图像 Mat* mvbegin）// 输出的通道图像数组
 
	//步骤二：计算直方图
	int histsize = 256;
	float range[] = { 0,256 };
	const float*histRanges = { range };
	Mat b_hist, g_hist, r_hist;
	calcHist(&bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&bgr_planes[1], 1, 0, Mat(), g_hist, 1, &histsize, &histRanges, true, false);
	calcHist(&bgr_planes[2], 1, 0, Mat(), r_hist, 1, &histsize, &histRanges, true, false);
//归一化
	int hist_h = 400;//直方图的图像的高
	int hist_w = 512;////直方图的图像的宽
	int bin_w = hist_w / histsize;//直方图的等级
	Mat histImage(hist_w, hist_h, CV_8UC3, Scalar(0, 0, 0));//绘制直方图显示的图像
	normalize(b_hist, b_hist, 0, hist_h, NORM_MINMAX, -1, Mat());//归一化
	normalize(g_hist, g_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, hist_h, NORM_MINMAX, -1, Mat());
 
	//步骤三：绘制直方图（render histogram chart）
	for (int i = 1; i < histsize; i++)
	{
		//绘制蓝色分量直方图
		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(b_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2);
		//绘制绿色分量直方图
		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(g_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2);
		//绘制红色分量直方图
		line(histImage, Point((i - 1)*bin_w, hist_h - cvRound(r_hist.at<float>(i - 1))),
			Point((i)*bin_w, hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2);
	}

    return histImage;
}


int main(int argc,char *argv[]){

    Mat src;
    src = imread( "../Resources/cathy.png", 1 );
	if (!src.data)
	{
		printf("could not load image...\n");
		return -1;
	}
	char input[] = "input image";
	
    Mat srcHist;
    srcHist = calHistrom(src);

    Mat dst,dstHist;

    normalize(src,dst,255,0,NORM_MINMAX,CV_8U);
    dstHist = calHistrom(dst);

    Mat fI;
    src.convertTo(fI,CV_64F,1.0/255,0);
    double gmma = 0.5;

    Mat o,oHist;
    pow(fI,gmma,o);

    namedWindow("input", WINDOW_AUTOSIZE);
	namedWindow("input hist", WINDOW_AUTOSIZE);
	imshow(input, src);
	imshow("input hist", srcHist);

    namedWindow("output", WINDOW_AUTOSIZE);
	namedWindow("ouput hist", WINDOW_AUTOSIZE);
	imshow("output", dst);
	imshow("output hist", dstHist);

    namedWindow("gmma output", WINDOW_AUTOSIZE);
	imshow("gmma output", o);
    namedWindow("gmma output hist", WINDOW_AUTOSIZE);
	imshow("gmma output hist", o);
	waitKey(0);


    return 0;
}