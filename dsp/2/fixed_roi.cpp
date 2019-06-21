#include <opencv2/highgui/highgui.hpp>
#include <stdio.h>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
    Mat img = imread("sample.jpg", -1);

    int h = img.rows;
    int w = img.cols;

    printf("h = %d, w= %d\n", h, w);

    if(img.empty())
        return -1;

    printf("h -155=%d, w -269 = %d, h -60 = %d, w - 236 = %d\n",
           h -155, w -269, h - 60, w- 236);

    Mat roi = img(Range(10,269), Range(290,300));

    imshow("Origin Image", img);
    imshow("ROI Image", roi);

    imwrite("ROI_image.jpg", roi);

    waitKey(0);

    destroyWindow("Origin Image");
    destroyWindow("ROI Image");

    return 0;
}
