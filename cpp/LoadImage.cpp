#include <iostream>
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
using namespace cv;
int main(int, char**)
{
     Mat image;
    image = imread( "../Resources/cathy.png", 1 );

    //宽度
    std::cout << "宽度： "<< image.cols << std::endl;
    //高度
    std::cout << "高度： " << image.rows << std::endl;
    //通道数
    std::cout << "通道数： " << image.channels() << std::endl;
    //深度
    //elemSize函数返回的是一个像素占用的字节数
    std::cout << "深度： " << image.elemSize() / image.channels() * 8 << std::endl;


    if ( !image.data )
    {
        printf("No image data \n");
        return -1;
    }
    namedWindow("Display Image", WINDOW_AUTOSIZE );
    imshow("Display Image", image);
    waitKey(0);
    return 0;
}
