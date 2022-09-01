#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

void templateMatch(){
    Mat img = imread("circuit.bmp", IMREAD_COLOR);
    Mat temp1 = imread("crystal.bmp", IMREAD_COLOR);

    img = img+Scalar(50,50,50);

    Mat noise(img.size(), CV_32SC3);
    randn(noise, 0, 10);
    add(img, noise, img, Mat(), CV_8UC3);

    Mat res, res_norm;
    matchTemplate(img, temp1, res, TM_CCOEFF_NORMED);
    normalize(res, res_norm, 0,255,NORM_MINMAX, CV_8U);

    double maxv;
    Point maxloc;
    minMaxLoc(res, 0,&maxv, &maxloc);
    cout << maxv << endl;

    rectangle(img, Rect(maxloc.x, maxloc.y, temp1.cols, temp1.rows), Scalar(0,0,255), 2);

    imshow("resnorm", res_norm);
    imshow("tmp", temp1);
    imshow("img", img);

    waitKey();
    destroyAllWindows();
}
void detect_face(){
    Mat src = imread("kids.png");

    CascadeClassifier classifier("haarcascade_frontalface_default.xml");
    CascadeClassifier eye_classifier("haarcascade_eye.xml");

    vector<Rect> faces;
    classifier.detectMultiScale(src, faces);

    for(Rect rc : faces){
        rectangle(src, rc, Scalar(255,0,255),2);

        Mat faceroi = src(rc);
        vector<Rect> eyes;
        eye_classifier.detectMultiScale(faceroi, eyes);
        for(Rect i : eyes){
            Point center(i.x + i.width/2, i.y + i.height/2);
            circle(faceroi, center, i.width/2, Scalar(255,0,0), 2, LINE_AA);
        }
    }
    imshow("src", src);
    waitKey();
    destroyAllWindows();
}
void QRcode(){
    VideoCapture cap(0);

    QRCodeDetector detector;
    Mat frame;
    while(true){
        cap >> frame;
        vector<Point> points;
        String info = detector.detectAndDecode(frame, points);
        if(!info.empty()){
            polylines(frame, points, true, Scalar(0,0,255), 2);
            putText(frame, info, Point(10,30), FONT_HERSHEY_DUPLEX, 1, Scalar(0,0,255));
        }
        imshow("fr", frame);
        if(waitKey(1)==27)
            break;
    }
    destroyAllWindows();
}
int main(){
    QRcode();
}