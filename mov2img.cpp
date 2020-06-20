#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <opencv2/core/types.hpp>


int main(int argc, char *argv[])
{
    //cv::VideoCapture::VideoCapture(const String &filename);cons
    //cv::VideoCapture *input_mov = new cv::VideoCapture("./HEVM_HW/true/baby.mp4");//OK
    //cv::VideoCapture src("./HEVM_HW/true/baby.mp4");//OK

    printf("input: %s \n",argv[1]);
    cv::VideoCapture src = cv::VideoCapture(argv[1]);//OK

    if(argc <= 1){
        std::cout << "Please input param!" << std::endl;
        return -1;    
    }

    if(! (src.isOpened())){
        printf("Unable to open input video files!\n");
        return -1;
    }



    int input_video_width = src.get(CV_CAP_PROP_FRAME_WIDTH);
    int input_video_height = src.get(CV_CAP_PROP_FRAME_HEIGHT);
    int input_video_frame_num = src.get(CV_CAP_PROP_FRAME_COUNT);
    int input_video_fps = src.get(CV_CAP_PROP_FPS);
    
    
    printf("width : %d\n", input_video_width);
    printf("height : %d\n", input_video_height);
    printf("frame_num : %d\n", input_video_frame_num);
    printf("fps : %d\n", input_video_fps);

    cv::Mat input_img = cv::Mat::zeros(input_video_height, input_video_width, CV_8UC3);
    cv::Mat output_img = cv::Mat::zeros(input_video_height, input_video_width, CV_8UC3);
    int frame_count = 0;

    cv::Mat dst = cv::Mat::zeros(544, 1220, CV_8UC3);//()

    while(1){
        //input_mov->read(input_img);
        src.read(input_img);

        if(input_img.empty()){
            break;
        }

        std::cout << " frame : " << frame_count << "/" << input_video_frame_num << std::endl;
        
        cv::Mat temp = cv::Mat(input_img, cv::Rect(480, 0, 4, 544));//Rect(x, y, width, heighr)
        
        if(frame_count != 0  )
        {   
            cv::Mat rec(dst, cv::Rect(frame_count*4, 0, 4, 544));
            temp.copyTo(rec);
        }

        cv::imshow("sample", dst);
        cv::waitKey(40);//10ms
        frame_count++;
    }
    cv::imwrite("./img/mag_time1.jpg", dst);

    return 0;
}
