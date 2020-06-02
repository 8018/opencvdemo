#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;
using namespace std;


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

Mat getEqualHistograph(const Mat image){
	CV_Assert(image.type() == CV_8UC1);
	int rows = image.rows;
	int cols = image.cols;

	Mat grayHist = getGrayHistograph(image);

	Mat zeroCumuMoment = Mat::zeros(Size(256,1),CV_32SC1);
	for(int p = 0;p<256;p++){
		if(p == 0){
			zeroCumuMoment.at<int>(0,p) = grayHist.at<int>(0,0);
		}else{
			zeroCumuMoment.at<int>(0,p) = zeroCumuMoment.at<int>(0,p-1)
			+grayHist.at<int>(0,p);
		}
	}

	Mat outPut_q = Mat::zeros(Size(256,1),CV_8UC1);
	float cofficient = 256.0/(rows*cols);

	for(int p = 0;p<256;p++){
		float q = cofficient * zeroCumuMoment.at<int>(0,p) -1;
		if(q>=0){
			outPut_q.at<uchar>(0,p) = uchar(floor(q));;
		}else{
			outPut_q.at<uchar>(0,p) = 0;
		}
	}

	Mat equalHist = Mat::zeros(image.size(),CV_8UC1);
	for(int r = 0;r< rows;r++){
		for(int c = 0;c<cols;c++){
			int p = image.at<uchar>(r,c);
			equalHist.at<uchar>(r,c) = outPut_q.at<uchar>(0,p);
		}
	}
	return equalHist;
}

Mat getRGBHistograph(const Mat image){

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

    Mat image;
    image = imread( "../../Resources/cathy.png", 1 );
	if (!image.data)
	{
		printf("could not load image...\n");
		return -1;
	}


	//定义灰度图像，转成灰度图
	Mat grayImage;
	cvtColor(image,grayImage,COLOR_BGR2GRAY);
	//double x=compareHist(hist,hist,/*CV_COMP_CORREL、CV_COMP_INTERSECT*/CV_COMP_BHATTACHARYYA);
	//直方图图像
	Mat grayHist=getGrayHistograph(grayImage);
	Mat originRGBHist = getRGBHistograph(image);


	Mat normalized;
	normalize(image,normalized,255,0,NORM_MINMAX,CV_8U);

	//定义灰度图像，转成灰度图
	Mat normalizedGrayImage;
	cvtColor(normalized,normalizedGrayImage,COLOR_BGR2GRAY);
	//double x=compareHist(hist,hist,/*CV_COMP_CORREL、CV_COMP_INTERSECT*/CV_COMP_BHATTACHARYYA);
	//直方图图像
	Mat normalizedGrayHist=getGrayHistograph(normalizedGrayImage);
	Mat normalizedRGBHist = getRGBHistograph(normalized);

	 Mat fI,gmmaedImage;
    image.convertTo(fI,CV_64F,1.0/255,0);
    double gmma = 0.5;

    pow(fI,gmma,gmmaedImage);

	gmmaedImage.convertTo(gmmaedImage,CV_8U,255,0);
	Mat gmmaedRGBHist = getRGBHistograph(gmmaedImage);

	Mat equalImage;
	equalImage = getEqualHistograph(grayImage);

 
	imshow("Origin Image",image);
	imshow("Gray hist",grayHist);
	imshow("Origin RGB hist",originRGBHist);
	imshow("normalized image",normalized);
	imshow("normalized Gray hist",normalizedGrayHist);
	imshow("normalized RGB hist",normalizedRGBHist);
	imshow("Gmmaed Image",gmmaedImage);
	imshow("Gmmaed RGB hist",gmmaedRGBHist);
	imshow("Equal hist",grayImage);
	waitKey(0);

    return 0;
}