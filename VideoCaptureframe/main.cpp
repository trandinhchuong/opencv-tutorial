/*
###############################################################
#author  : chuongtd4
#email    : chuongtd4@gmail.com
#########################chuongtd4#############################
*/
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;

int main()
{
    // VideoCapture class for playing video for which faces to be detected
       VideoCapture capture;
       Mat frame, image;

       // Start Video..1) 0 for WebCam 2) "Path to Video" for a Local Video
       capture.open("/home/chuong/Videos/class.mp4");
       if( capture.isOpened() )
       {
           // Capture frames from video and detect faces
           cout << "Face Detection Started...." << endl;
           while(1)
           {
               capture >> frame;
               if( frame.empty())
                   break;
               Mat frame1 = frame.clone();
              imshow("capture",frame1);
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
