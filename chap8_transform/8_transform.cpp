#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void affinetransform(){
    Mat src = imread("lena.bmp");

    Point2f srcPts[3], dstPts[3];
    srcPts[0] = Point2f(0,0);
    srcPts[1] = Point2f(src.cols-1, 0);
    srcPts[2] = Point2f(src.cols-1, src.rows-1);
    dstPts[0] = Point2f(50, 50);
    dstPts[1] = Point2f(src.cols-100,100);
    dstPts[2] = Point2f(src.cols-50,src.rows-50);
    
    Mat M = getAffineTransform(srcPts, dstPts);

    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void affine_shift(){
    Mat src = imread("lena.bmp");
    Mat M = Mat_<double>({2,3},{1,0,150,0,1,100});
    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();
}

void affine_shear(){
    Mat src = imread("lena.bmp");

    double mx = 0.3;
    Mat M = Mat_<double>({2,3}, {1,mx,0,0,1,0});

    Mat dst;
    warpAffine(src, dst, M, Size(cvRound(src.cols+src.rows*mx), src.rows));

    imshow("src", src);
    imshow("dst", dst);

    waitKey();
    destroyAllWindows();

}
void affine_scale(){
    Mat src = imread("lena.bmp");
    Mat dst1,dst2;
    resize(src, dst1, Size(), 4, 4, INTER_NEAREST);
    resize(src, dst2, Size(1920,1080));

    imshow("src", src);
    imshow("dst1", dst1);
    imshow("dst2", dst2);

    waitKey();
    destroyAllWindows();

}
void affine_rotate(){
    Mat src = imread("lena.bmp");
    Point2f cp(src.cols / 2.f, src.rows /2.f);
    Mat M = getRotationMatrix2D(cp, 20, 1);

    Mat dst;
    warpAffine(src, dst, M, Size());

    imshow("src", src);
    imshow("dst1", dst);

    waitKey();
    destroyAllWindows();

}

void affine_flip(){
    Mat src = imread("lena.bmp");

    imshow("src", src);
    Mat dst;
    flip(src, dst, 0);
    imshow("dst", dst);
    waitKey();
    destroyAllWindows();
}
Mat src;
Point2f srcQuad[4], dstQuad[4];
void on_mouse(int event, int x, int y, int flags, void* userdata){
    static int cnt = 0;
    if(event == EVENT_LBUTTONDOWN){
        if(cnt<4){
            srcQuad[cnt++] = Point2f(x,y);

            circle(src, Point(x,y), 5, Scalar(0,0,255), -1);
            imshow("src", src);

            if(cnt==4){
                int w= 200, h = 300;
                dstQuad[0] = Point2f(0,0);
                dstQuad[1] = Point2f(w-1,0);
                dstQuad[2] = Point2f(w-1,h-1);
                dstQuad[3] = Point2f(0, h-1);
                Mat pers = getPerspectiveTransform(srcQuad, dstQuad);

                Mat dst;
                warpPerspective(src, dst, pers, Size(w,h));
                imshow("dst", dst);
            }
        }
    }
}


int main(){
    src = imread("card.bmp");

    namedWindow("src");
    setMouseCallback("src", on_mouse);

    imshow("src", src);
    waitKey();

    return 0;
}