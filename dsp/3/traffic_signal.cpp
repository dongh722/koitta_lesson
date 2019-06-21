#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>

#include <sys/types.h>
#include <sys/poll.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>

#include "serial.h"

using namespace std;
using namespace cv;

//extern char *dev0;
int fd;
char *dev0;
jmp_buf env;

unsigned int sig  =0;
int cnt =0;

void call_exit(int signo)
{
    destroyWindow("Origin Image");
    destroyWindow("Custom ROI Image");
    longjmp(env,1);
}

void my_sig(int signo)
{
    sig =  rand() % 3;
 //   printf("%d\n",sig);
}

Mat roi_funce(Mat *img, int signo)
{
    Mat output;
    Point mid[3] ={Point(328,71),Point(337,167),Point(341,265)};
    Mat mask = Mat::zeros(img->size(),img->type());
    circle(mask,mid[signo],30,Scalar(255,255,255),-1);
    bitwise_and((*img),mask,output);
    return output;
}

void color_agv(Mat *img,Point *pt,double *result)
{
    int i = 0,j= 0;
    double color_sum[3] = {0, 0 ,0};

    for(i = 0; i < 30;i++)
    {
        for(j = 0; j < 30; j++)
        {
            color_sum[0] += img->at<Vec3b>(pt->y-15+j,pt->x-15+i)[2];
            color_sum[1] += img->at<Vec3b>(pt->y-15+j,pt->x-15+i)[1];
            color_sum[2] += img->at<Vec3b>(pt->y-15+j,pt->x-15+i)[0];
        }
    }
     *(result) = color_sum[0]/900.0;
     *(result+1) = color_sum[1]/900.0;
     *(result+2) = color_sum[2]/900.0;
}

char detect_color(Mat *img,int sig)
{
    int cnt =0;
    Point mid[3]  = {Point(328,71),Point(337,167),Point(341,265)};
    double color_result[3] = {0,0,0};

    color_agv(img,(mid+sig),color_result);
    printf("r = %f, g = %f, b = %f\n",color_result[0],color_result[1],color_result[2]);
}


int main(int argc, char **argv)
{
    int w, h;
    int ret;
    char buf[2] ={0,0};
    Mat img;
    Mat roi;

//    dev0 ="/dev/ttyACM0";//lauchpad

    signal(SIGINT, call_exit);
    signal(SIGALRM, my_sig);

//    fd = serial_config(dev0);
    img = imread("traffic.jpg",-1);
    if(img.empty())
        return -1;

    h = img.rows;
    w = img.cols;

    printf("h = %d, w = %d\n", h, w);
    GaussianBlur(img, img, Size(3,3), 0, 0);
    imshow("Origin image",img);
    imshow("Traffic Image",img);
    waitKey(1);

    if(!(ret = setjmp(env)))
    {
        for(;;)
        {
            alarm(5);
            pause();
            buf[0] = (char)(sig+1) | 0x30;
            roi = roi_funce(&img,sig);
            imshow("Traffic Image",roi);
            waitKey(100);
            printf("%c\n",buf[0]);
            detect_color(&roi,sig);
//            send_data(fd, buf, 1, 0);
            memset(buf,0x0,2);
            alarm(0);
        }
    }

    buf[0] ='1';
//    send_data(fd,buf,1, 0);
//    wait(10);
    close_dev(fd);
    return 0;
}
