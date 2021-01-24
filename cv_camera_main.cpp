#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>

int main() {
  cv::VideoCapture capture(0);

  cv::namedWindow("Camera", cv::WINDOW_AUTOSIZE);

  int threshold1 = 250;
  int threshold2 = 350;

  cv::createTrackbar("threshold 1", "Camera", &threshold1, 1000, nullptr,
                     nullptr);
  cv::createTrackbar("threshold 2", "Camera", &threshold2, 1000, nullptr,
                     nullptr);

  bool log = true;

  while (true) {
    cv::Mat img;
    capture.read(img);

    cv::Mat imgGrayscale;
    cv::cvtColor(img, imgGrayscale, cv::COLOR_BGR2GRAY);

    cv::Mat imgBlur;
    cv::GaussianBlur(imgGrayscale, imgBlur, cv::Size(3, 3), 3, 0);

    cv::Mat out;
    cv::Canny(imgBlur, out, static_cast<double>(threshold1) / 10.0,
              static_cast<double>(threshold2) / 10.0, /*apertureSize*/ 3,
              /*L2gradient*/ true);

    if (log) {
      std::cout << CV_8S << '\n';
      std::cout << CV_8UC1 << ' ' << CV_8UC2 << ' ' << CV_8UC3 << ' ' << CV_8UC4
                << '\n';
      std::cout << CV_8SC1 << ' ' << CV_8SC2 << ' ' << CV_8SC3 << ' ' << CV_8SC4
                << '\n';
      std::cout << "img: " << img.cols << ' ' << img.rows << ' '
                << img.elemSize() << ' ' << img.type() << ' ' << img.size()
                << '\n';
      std::cout << "out: " << out.cols << ' ' << out.rows << ' '
                << out.elemSize() << ' ' << out.type() << ' ' << out.size()
                << '\n';
      for (int i = 0; i < 10; ++i) {
        std::cout << static_cast<int>(img.at<uchar>(i)) << '\n';
      }

      log = false;
    }

    CV_Assert(img.type() == CV_8UC3);
    CV_Assert(out.type() == CV_8UC1);
    for (int i = 0; i < img.rows; ++i) {
      for (int j = 0; j < img.cols; ++j) {
        if (*out.ptr(i, j) == 255) {
          uchar* el = img.ptr(i, j);
          el[0] = 255;
          el[1] = 255;
          el[2] = 255;
        }
      }
    }

    cv::imshow("Camera", img);
    // cv::imshow("Camera", out);
    cv::waitKey(10);
  }
}
