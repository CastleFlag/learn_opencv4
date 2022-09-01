#include "opencv2/opencv.hpp"
#include <iostream>
using namespace std;
using namespace cv;

int main()
{
    VideoCapture cam(0); // 카메라 
    VideoCapture videofile("video.mp4"); //파일 열기
    cout << cam.isOpened() << endl; // 열렸는지 확인
    //한 프레임 받아오기 & 출력
    Mat frame;
    //카메라나 동영상파일 속성 받아오기(flag)
    int w = cvRound(cam.get(CAP_PROP_FRAME_WIDTH));
    int h = cvRound(cam.get(CAP_PROP_FRAME_HEIGHT));
    //속성 설정하기
    videofile.set(CAP_PROP_POS_FRAMES, 100); //100프레임으로이동
    //동영상 fps
    double fps = cam.get(CAP_PROP_FPS);
    //동영상 delay(동영상 출력할 때 waitKey에 사용)
    int delay = cvRound(1000 / fps);
    //동영상 저장하기(카메라 받아서)
    int fourcc = VideoWriter::fourcc('m', 'p', '4', 'v');
    VideoWriter videosave;
    videosave.open("cameravideo.mp4", fourcc, fps, Size(w, h));
    while(true){
        cam.read(frame);
        if(frame.empty()) break;
        videosave.write(frame);
        imshow("frame", frame);

        if(waitKey(delay)==27) break;

    }
    destroyAllWindows();
}