#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

Mat calc_gray_hist(const Mat& img){
    Mat hist;
    int channels[]={0};
    int dims = 1;
    const int histSize[] = {256};
    float graylevel[] = {0,256};
    const float* ranges[] = {graylevel};

    calcHist(&img, 1, channels, Mat(), hist, dims, histSize, ranges);

    return hist;
}

Mat get_gray_hist_image(const Mat& hist){
    double histMax;
    minMaxLoc(hist, 0, &histMax);

    Mat imgHist(100, 256, CV_8UC1, Scalar(255));
    for(int i=0; i<256; i++){
        line(imgHist, Point(i, 100), Point(i, 100-cvRound(hist.at<float>(i,0)*100/histMax)), Scalar(0));
    }
    return imgHist;
}

void showhist(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat hist = calc_gray_hist(src);
    Mat hist_img = get_gray_hist_image(hist);

    imshow("src", src);
    imshow("srcHist", hist_img);

    waitKey();
    destroyAllWindows();
}

//약간 minmax regularization같음
void stretch_hist(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    double gmin, gmax;
    minMaxLoc(src, &gmin, &gmax);
    Mat dst = (src-gmin)*255 / (gmax-gmin);
    imshow("src", src);
    imshow("srcHist", get_gray_hist_image(calc_gray_hist(src)));
    imshow("dst", dst);
    imshow("dstHist", get_gray_hist_image(calc_gray_hist(dst)));
    
    waitKey();
    destroyAllWindows();
}

void equal_hist(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat dst;
    equalizeHist(src, dst);
    imshow("src", src);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();
}

int main(){
    equal_hist();
}