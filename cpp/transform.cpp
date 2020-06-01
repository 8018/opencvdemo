#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
using namespace std;

int main(int, char**)
{
     Mat src;
    src = imread( "../Resources/cathy.png", 1 );

    //宽度
    cout << "宽度： "<< src.cols << endl;
    //高度
    cout << "高度： " << src.rows << endl;
    //通道数
    cout << "通道数： " << src.channels() << endl;
    //深度
    //elemSize函数返回的是一个像素占用的字节数
    cout << "深度： " << src.elemSize() / src.channels() * 8 << endl;


    if ( !src.data )
    {
        printf("No image data \n");
        return -1;
    }


    namedWindow("origin Image", WINDOW_AUTOSIZE );
    imshow("origin Image", src);

    Mat dst_warp, 
    dst_warpRotateScale, 
    dst_warpTransformation, 
    dst_warpFlip,
    dst_mirror_vertical,
    dst_rotate;

	Point2f srcPoints[3];//原图中的三点 ,一个包含三维点（x，y）的数组，其中x、y是浮点型数
	Point2f dstPoints[3];//目标图中的三点  
 
    //第一种仿射变换的调用方式：三点法
	//三个点对的值,上面也说了，只要知道你想要变换后图的三个点的坐标，就可以实现仿射变换  
	srcPoints[0] = Point2f(0, 0);
	srcPoints[1] = Point2f(0, src.rows);
	srcPoints[2] = Point2f(src.cols, 0);
	//映射后的三个坐标值
	dstPoints[0] = Point2f(0, src.rows*0.3);
	dstPoints[1] = Point2f(src.cols*0.25, src.rows*0.75);
	dstPoints[2] = Point2f(src.cols*0.75, src.rows*0.25);
 
	Mat M1 = getAffineTransform(srcPoints, dstPoints);//由三个点对计算变换矩阵  
													  
 
	warpAffine(src, dst_warp, M1, src.size());//仿射变换  
											 
   //第二种仿射变换的调用方式：直接指定角度和比例                                          
	//旋转加缩放  
	// Point2f center(src.cols / 2, src.rows / 2);//旋转中心  
	Point2f center(src.cols / 2, src.rows / 2);//旋转中心  
	double angle = 45;//逆时针旋转45度  
	double scale = 1;//缩放比例  
 
	//Mat M2 = getRotationMatrix2D(center, angle, scale);//计算旋转加缩放的变换矩阵  

    Mat M2=Mat::ones(2,3,CV_32FC1);
 
	M2.at<float>(0,0)=0.5;
	M2.at<float>(0,1)=0;
	M2.at<float>(0,2)=0;
	M2.at<float>(1,0)=0;
	M2.at<float>(1,1)=0.5;
	M2.at<float>(1,2)=0;

	warpAffine(src, dst_warpRotateScale, M2, Size(src.cols, src.rows), INTER_LINEAR);//仿射变换
 												

    // Point2f srcPoints1[3];
	// Point2f dstPoints1[3];
 
	// srcPoints1[0] = Point2i(0, 0);
	// srcPoints1[1] = Point2i(0, src.rows);
	// srcPoints1[2] = Point2i(src.cols, 0);
 
	// dstPoints1[0] = Point2i(src.cols / 3, 0);
	// dstPoints1[1] = Point2i(src.cols / 3, src.rows);
	// dstPoints1[2] = Point2i(src.cols + src.cols / 3, 0);
 
	// Mat M3 = getAffineTransform(srcPoints1, dstPoints1);
	// warpAffine(src, dst_warpTransformation, M3, Size(src.cols + src.cols / 3, src.rows));


    Mat M3=Mat::ones(2,3,CV_32FC1);

    float delta = -0.5;
 
	M3.at<float>(0,0)=cos(delta);
	M3.at<float>(0,1)=-sin(delta);
	M3.at<float>(0,2)=250;
	M3.at<float>(1,0)=sin(delta);
	M3.at<float>(1,1)=cos(delta);
	M3.at<float>(1,2)=0;

	warpAffine(src, dst_warpTransformation, M3, Size(src.cols, src.rows), INTER_LINEAR);//仿射变换
 												
 
	//仿射变换—翻转、镜像
	Point2f srcPoints2[3];
	Point2f dstPoints2[3];
 
	srcPoints2[0] = Point2i(0, 0);
	srcPoints2[1] = Point2i(0, src.rows);
	srcPoints2[2] = Point2i(src.cols, 0);
 
	dstPoints2[0] = Point2i(src.cols, 0);
	dstPoints2[1] = Point2i(src.cols, src.rows);
	dstPoints2[2] = Point2i(0, 0);
 
	Mat M4 = getAffineTransform(srcPoints2, dstPoints2);
	warpAffine(src, dst_warpFlip, M4, Size(src.cols, src.rows));


//仿射变换—翻转、镜像
	Point2f srcPoints3[3];
	Point2f dstPoints3[3];
 
	srcPoints3[0] = Point2i(0, 0);
	srcPoints3[1] = Point2i(0, src.rows);
	srcPoints3[2] = Point2i(src.cols, 0);
 
	dstPoints3[0] = Point2i(0, src.rows);
	dstPoints3[1] = Point2i(0, 0);
	dstPoints3[2] = Point2i(src.cols, src.rows);
 
	Mat M5 = getAffineTransform(srcPoints3, dstPoints3);
	warpAffine(src, dst_mirror_vertical, M5, Size(src.cols, src.rows));


     Mat M6 = getRotationMatrix2D(center,45,1);

	warpAffine(src, dst_rotate, M6, Size(src.cols, src.rows), INTER_LINEAR);//仿射变换
 	


    // 旋转角度
	// 计算旋转后输出图形的尺寸
	int rotated_width = ceil(src.rows * fabs(sin(angle * CV_PI / 180)) + src.cols * fabs(cos(angle * CV_PI / 180)));
	int rotated_height = ceil(src.cols * fabs(sin(angle * CV_PI / 180)) + src.rows * fabs(cos(angle * CV_PI / 180)));
	
       cout << "宽度： "<< rotated_width << endl;


	// 计算仿射变换矩阵
	Mat rotate_matrix = getRotationMatrix2D(center, -45, 1.0);

	// 防止切边，对平移矩阵B进行修改
	rotate_matrix.at<double>(0, 2) += (rotated_width - src.cols) / 2; 
	rotate_matrix.at<double>(1, 2) += (rotated_height - src.rows) / 2; 

    cout << "宽度： "<< rotate_matrix.at<double>(0, 2) << endl;
    cout << "宽度： "<< rotate_matrix.at<double>(1, 2) << endl;


	// 应用仿射变换
	warpAffine(src, dst_rotate, rotate_matrix, Size(rotated_width, rotated_height), INTER_LINEAR, 0, Scalar(255, 255, 255));


    Mat rotated;
    rotate(src,rotated,ROTATE_90_COUNTERCLOCKWISE);

	//flip(src, dst_warpFlip, 1);//  flipCode：= 0 图像向下翻转
	//> 0 图像向右翻转
	//< 0 图像同时向下向右翻转
 
    // namedWindow("transform_1", WINDOW_AUTOSIZE );
	// imshow("transform_1", dst_warp);

    // namedWindow("transform_2", WINDOW_AUTOSIZE );
	// imshow("transform_2", dst_warpRotateScale);
    
    // namedWindow("transform_3", WINDOW_AUTOSIZE );
	// imshow("transform_3", dst_warpTransformation);
    
    // namedWindow("transform_4", WINDOW_AUTOSIZE );
	// imshow("transform_4", dst_warpFlip);
    
    // namedWindow("transform_5", WINDOW_AUTOSIZE );
	// imshow("transform_5", dst_mirror_vertical);
 
    
    namedWindow("transform_6", WINDOW_AUTOSIZE );
	imshow("transform_6", dst_rotate);

    namedWindow("transform_7", WINDOW_AUTOSIZE );
	imshow("transform_7", rotated);
 
	waitKey(0);



    return 0;
}
