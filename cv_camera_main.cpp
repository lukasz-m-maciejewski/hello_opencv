#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <string>

int main() {
  cv::VideoCapture capture(0);

  while(true) {
    cv::Mat img;
    capture.read(img);
    cv::imshow("Camera0", img);
    cv::waitKey(10);
  }
}
