#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void emboss(){
    Mat src = imread("lena.bmp");

    float embfilter[] = {-1,-1,0, -1, 0, 1, 0, 1, 1};
    Mat emboss(3, 3, CV_32FC1, embfilter);

    Mat dst;
    filter2D(src, dst, -1,  emboss, Point(-1,-1), 128);

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void blurrr(){
    Mat src = imread("lena.bmp");

    float embfilter[] = {-1,-1,0, -1, 0, 1, 0, 1, 1};
    Mat emboss(3, 3, CV_32FC1, embfilter);

    Mat dst;
    for(int i=3;i<=7; i+=2){
        blur(src, dst, Size(i, i));

        String desc = format("Mean: %dx%d", i, i);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
        imshow("dst", dst);
        waitKey();
    }
    destroyAllWindows();
}
void gaussian_blur(){
    Mat src = imread("lena.bmp");

    imshow("src", src);

    Mat dst;
    for(int i=1;i<=5; i++){
        GaussianBlur(src, dst, Size(), double(i));

        String desc = format("sigma: %d", i);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
        imshow("dst", dst);
        waitKey();
    }
    destroyAllWindows(); 
}

void sharpning(){
    Mat src = imread("lena.bmp");

    imshow("src", src);

    for(int i=1; i<=5; i++){
        Mat blurred;
        GaussianBlur(src, blurred, Size(), i);

        float alpha = 1.f;
        Mat dst = (1+ alpha) * src - alpha * blurred;

        String desc = format("sigma: %d", i);
        putText(dst, desc, Point(10, 30), FONT_HERSHEY_SIMPLEX, 1.0, Scalar(255), 1, LINE_AA);
        imshow("dst", dst);
        waitKey();
    }

}
void gaunoise(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);

    imshow("src", src);
    for(int i=10; i<=30; i+=10){
        Mat noise(src.size(), CV_32SC1);
        randn(noise, 0, i);

        Mat dst;
        add(src, noise, dst, Mat(), CV_8U);
        imshow("dst", dst);
        waitKey();
    }
}
void biateral(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    Mat noise(src.size(), CV_32SC1);
    randn(noise, 0, 5);
    add(src, noise, src, Mat(), CV_8U);

    Mat dst1;
    GaussianBlur(src, dst1, Size(), 5);

    Mat dst2;
    bilateralFilter(src, dst2, -1, 10, 5);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);
    waitKey();
    destroyAllWindows();
}
void medianfilter(){
    Mat src = imread("lena.bmp", IMREAD_GRAYSCALE);
    int num = (int)(src.total() * 0.1);
    for(int i=0;i<num;i++){
        int x = rand() % src.cols;
        int y = rand() % src.rows;
        src.at<uchar>(y,x) = (i%2)*255;
    }
    Mat dst1;
    GaussianBlur(src, dst1, Size(), 1);
    Mat dst2;
    medianBlur(src, dst2, 3);

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey(0);
    destroyAllWindows();
}
int main(){
    medianfilter();
}