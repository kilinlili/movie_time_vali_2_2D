#include <iostream>
#include <opencv2/opencv.hpp>
#include <sys/time.h>
#include <opencv2/core/types.hpp>


int main(int argc, char *argv[])
{

    cv::VideoCapture src0 = cv::VideoCapture("./mov/baby_mag_sw_opencv.avi");
    cv::VideoCapture src1 = cv::VideoCapture("./mov/baby_mag_hw.avi");

    int opencv_video_width = src0.get(CV_CAP_PROP_FRAME_WIDTH);
    int opencv_video_height = src0.get(CV_CAP_PROP_FRAME_HEIGHT);
    int halide_video_width = src1.get(CV_CAP_PROP_FRAME_WIDTH);
    int halide_video_height = src1.get(CV_CAP_PROP_FRAME_HEIGHT); 
    
    int opencv_video_frame_num = src0.get(CV_CAP_PROP_FRAME_COUNT);
    int opencv_video_fps = src0.get(CV_CAP_PROP_FPS);
    int halide_video_frame_num = src1.get(CV_CAP_PROP_FRAME_COUNT);
    int halide_video_fps = src1.get(CV_CAP_PROP_FPS);

    printf("opencv:width/height:%d / %d\n", opencv_video_width, opencv_video_height);
    printf("opencv:fps/frame:%d / %d\n", opencv_video_fps, opencv_video_frame_num);
    printf("halide:width/height:%d / %d\n", halide_video_width, halide_video_height);
    printf("halide:fps/frame:%d / %d\n", halide_video_fps, halide_video_frame_num);

    cv::Mat opencv_img = cv::Mat::zeros(opencv_video_height, opencv_video_width, CV_8UC3);
    cv::Mat halide_img = cv::Mat::zeros(halide_video_height, halide_video_width, CV_8UC3);

    int frame_count = 0;

    while(1){

        src0.read(opencv_img);
        src1.read(halide_img);

        int all = 0;
        int error = 0;
        for(int y = 0; y < opencv_img.rows; y++){
          for(int x = 0; x < opencv_img.cols; x++){
            for(int c = 0; c < opencv_img.channels(); c++){

              int diff = opencv_img.at<cv::Vec3b>(y, x)[c] - halide_img.at<cv::Vec3b>(y, x)[c];

              if(std::fabs(diff) > 1){
                ++error;
              }
              ++all;
            }
          }
        }
        std::cout << "frame:" << frame_count << "/ error:" << error;
        std::cout << "/ all:" << all;
        std::cout << "/ error_rate:" << double(error)/double(all) *100 << std::endl;

        frame_count++;
    }

  
    return 0;
}
