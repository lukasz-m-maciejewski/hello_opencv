cmake_minimum_required(VERSION 3.15)
project(hello_opencv CXX)

find_package(PkgConfig REQUIRED)

pkg_check_modules(OPENCV REQUIRED opencv4)


add_executable(cv_camera cv_camera_main.cpp)

target_link_libraries(cv_camera ${OPENCV_LIBRARIES})
target_include_directories(cv_camera PUBLIC ${OPENCV_INCLUDE_DIRS})
target_compile_options(cv_camera PUBLIC ${OPENCV_CFLAGS_OTHER})
