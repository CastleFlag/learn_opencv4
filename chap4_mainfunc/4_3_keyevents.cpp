// #include "opencv2/opencv.hpp"
// #include <iostream>
// using namespace std;
// using namespace cv;

// // Mat img;
// // Point pt0ld;

// // void on_mouse(int event, int x, int y, int flags, void*){
// //     switch(event){
// //         case EVENT_LBUTTONDOWN:
// //         pt0ld = Point(x,y);
// //         cout << "LBUTTONDOWN" << endl;
// //         break;
// //         case EVENT_MOUSEMOVE:
// //         if(flags & EVENT_FLAG_LBUTTON){
// //             line(img, pt0ld, Point(x, y), Scalar(0,255,255), 2);
// //             imshow("img", img);
// //             pt0ld = Point(x,y);
// //         }
// //         default:
// //         break;
// //     }
// // 
// void on_level_change(int pos, void* userdata);

// int main(){
//     // img = imread("lena.bmp");
//     // namedWindow("img");
//     // setMouseCallback("img", on_mouse);
    
//     // imshow("img", img);
//     // waitKey(0);

//     //trackbar
//     Mat img = Mat::zeros(400, 400, CV_8UC1);

//     namedWindow("image");
//     createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img);
//     imshow("image", img);
//     waitKey(0);

//     return 0;
// }

// void on_level_change(int pos, void* userdata){
//     Mat img = *(Mat*)userdata;
    
//     img.setTo(pos * 16);
//     imshow("image", img);
// }

#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void on_level_change(int pos, void* userdata);


int main(void)
{
    Mat img = Mat::zeros(400, 400, CV_8UC1);


    namedWindow("image");
    createTrackbar("level", "image", 0, 16, on_level_change, (void*)&img);


    imshow("image", img);
    waitKey(0);


    return 0;
}


void on_level_change(int pos, void* userdata)
{
    Mat img = *(Mat*)userdata;


    img.setTo(pos * 16);
    imshow("image", img);
}