/*
###############################################################
#author  : chuongtd4
#email    : chuongtd4@gmail.com
#########################chuongtd4#############################
*/


#include "mainwindow.h"
#include <QApplication>

#include "iostream"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/types_c.h>   //CV_RGB2GRAY

#include <opencv2/imgproc.hpp>  //cvtColor threshold resize
#include <opencv2/imgproc/imgproc_c.h> //cvAdaptiveThreshold
#include <opencv2/videoio.hpp>

using namespace cv;
using namespace std;

Size size(600,400);

int main()
{
    Mat Gray_image = imread("image/person.jpg");  //doc anh mau
    resize(Gray_image,Gray_image,size,1,1,INTER_AREA); //thay doi kich thuoc anh
    imshow("Color_image",Gray_image); // hien thi anh mau
    cvtColor(Gray_image,Gray_image,CV_RGB2GRAY); //chuyen anh da muc xam

    Mat Binary_image;

    threshold(Gray_image, Binary_image, 150, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    imshow("Gray_image",Gray_image);
    imshow("Binary image",Binary_image);
    waitKey();
    return 0;

}




