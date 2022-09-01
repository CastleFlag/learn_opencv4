#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void grays(){
    //imread로 불러오기
    Mat img1 = imread("lena.bmp", IMREAD_GRAYSCALE);
    //빈 Mat
    Mat img2(480, 640, CV_8UC1, Scalar(0));
    //convert
    Mat img3;
    cvtColor(img1, img3, COLOR_BGR2GRAY);
    //gray인지 확인 
    if(img1.type() == CV_8UC1);
}
void bright(){
    Mat img = imread("lena.bmp", IMREAD_GRAYSCALE);
    //밝기 올리기 
    Mat dst = img + 100;
    //or add(src, 100, dst);

    //밝기 직접 올리기
    Mat dst2(img.rows, img.cols, img.type());
    for(int i=0; i<img.rows; i++){
        for(int j=0; j<img.cols; j++){
            //범위에 맞게 포화 연산
            dst2.at<uchar>(i,j) = saturate_cast<uchar>(img.at<uchar>(i,j) + 155);
        }
    }


    imshow("dst2", dst2);
    imshow("img", img);
    waitKey();
    destroyAllWindows();
}

void on_brightness(int pos, void* userdata);
void brighttrackbar(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    namedWindow("dst");
    createTrackbar("Brightness", "dst", 0, 100, on_brightness, (void*)& src);

    waitKey();
    destroyAllWindows();
}
void on_brightness(int pos, void* userdata){
    Mat src = *(Mat*)userdata;
    Mat dst = src+ pos;
    imshow("dst", dst);
}

int main(){
    brighttrackbar();
}