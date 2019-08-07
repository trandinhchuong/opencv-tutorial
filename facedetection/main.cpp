#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <stdio.h>
#include <opencv2/imgproc/types_c.h>
using namespace std;
using namespace cv;
void detect(Mat image_input);
Size size(600,400);
CascadeClassifier face_cascade;
int main( )
{
    // VideoCapture class for playing video for which faces to be detected
       VideoCapture capture;
       Mat frame, image;
       // Load Face cascade (.xml file)

       face_cascade.load( "/home/chuong/opencv/data/haarcascades/haarcascade_frontalface_alt2.xml" );

       // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
       capture.open("/home/chuong/Videos/face1080p.mp4");
      // capture.open(0);
       if( capture.isOpened() )
       {
           // Capture frames from video and detect faces
           cout << "Face Detection Started...." << endl;
           while(1)
           {
               capture >> frame;
               if( frame.empty() )
                   break;
               Mat frame1 = frame.clone();

               resize(frame1,frame1,size,1,1,INTER_AREA); //thay doi kich thuoc anh
               //imshow("Color_image",Gray_image); // hien thi anh mau
               cvtColor(frame1,frame1,CV_RGB2GRAY); //chuyen anh da muc xam


               detect(frame1);

               char c = (char)waitKey(10);
               // Press q to exit from window
               if( c == 27 || c == 'q' || c == 'Q' )
                   break;
           }
       }
       else
           cout<<"Could not Open Camera";
       return 0;
}
void detect(Mat image_input)
{


    // Detect faces
    std::vector<Rect> faces;
    face_cascade.detectMultiScale( image_input, faces, 1.1, 2, 0, Size(30, 30) );  //size -> speed load

    // Draw circles on the detected faces
    for( int i = 0; i < faces.size(); i++ )
    {
        Point center( faces[i].x + faces[i].width*0.5, faces[i].y + faces[i].height*0.5 );
        ellipse( image_input, center, Size( faces[i].width*0.5, faces[i].height*0.5), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
        cout << "x:" << faces[i].x << "y:" << faces[i].y << endl;
    }

    imshow( "Detected Face", image_input );
    char c = (char)waitKey(10);
}
