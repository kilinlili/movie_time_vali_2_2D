#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <opencv2/core/types.hpp>


int main(int argc, char *argv[])
{
    //cv::VideoCapture::VideoCapture(const String &filename);cons
    //cv::VideoCapture *input_mov = new cv::VideoCapture("./HEVM_HW/true/baby.mp4");//OK
    //cv::VideoCapture src("./HEVM_HW/true/baby.mp4");//OK

    //printf("input: %s \n",argv[1]);
    //cv::VideoCapture src = cv::VideoCapture(argv[1]);//OK


#ifdef AAA
    cv::VideoCapture src = cv::VideoCapture("./mov/baby_mag_hw.avi");
#elif BBB
    cv::VideoCapture src = cv::VideoCapture("./mov/baby_mag_sw_halide.avi");
#elif CCC
    cv::VideoCapture src = cv::VideoCapture("./mov/baby_mag_sw_opencv.avi");
#endif


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

    //run
    cv::Mat dst = cv::Mat::zeros(544, 1220, CV_8UC3);//dst
    while(1){
        //input_mov->read(input_img);
        src.read(input_img);

        if(input_img.empty()){
            break;
        }
        
        if(frame_count == 0)cv::imwrite("./img/base.jpg", input_img);
        std::cout << " frame : " << frame_count << "/" << input_video_frame_num << std::endl;
        
        cv::Mat temp = cv::Mat(input_img, cv::Rect(480, 0, 4, 544));//Rect(x, y, width, heighr)
        //if(frame_count != 0  )
        //{   
            cv::Mat rec(dst, cv::Rect(frame_count*4, 0, 4, 544));
            temp.copyTo(rec);
        //}
        cv::imshow("sample", dst);
        cv::waitKey(40);//10ms
        frame_count++;
    }


#ifdef AAA
    cv::imwrite("./img/hw_halide.jpg", dst);
#elif BBB
    cv::imwrite("./img/sw_halide.jpg", dst);
#elif CCC
    cv::imwrite("./img/sw_opencv.jpg", dst);
#endif

    //cv::imwrite("./img/mag_halide.jpg", dst);
    
    
    return 0;
}
