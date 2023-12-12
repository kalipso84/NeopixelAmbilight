cmake_minimum_required(VERSION 2.8)
project(video1)

set(OpenCV_INCLUDE_DIRS
  /usr/local/include/opencv4
  /usr/local/include
  /home/pi/c/spidev2/spidevpp/libs
  
)


set(OpenCV_LIB_DIR
  /home/pi/c/spidev2/build/libs/spidevpp
  /home/pi/c/spidev2/spidevpp/libs
  /home/pi/c/spidev2/spidevpp/libs
  /home/pi/c/spidev2/spidevpp
  /home/pi/c/build/lib
  /usr/local/lib
  /usr/local/opencv/lib
  /usr/include
)

set(OpenCV_LIBS
  spidevpp
  #bcm2835
  opencv_videoio
  opencv_imgproc
  opencv_core
  opencv_highgui
  opencv_imgcodecs
)

include_directories(${OpenCV_INCLUDE_DIRS})
link_directories(${OpenCV_LIB_DIR})
add_executable( video1 video1.cpp )
target_link_libraries( video1 ${OpenCV_LIBS} )
