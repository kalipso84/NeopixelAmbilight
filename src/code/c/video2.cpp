#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;
using namespace cv;

void get_average(src) {
  channels = cv2.mean(src)
  return channels[0], channels[1], channels[2]
}

int main(){
	

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("Ambilight.mp4"); 
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(CAP_PROP_FPS, 30);
   
  num_leds_top = 8;
  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
	
  while(1){

    Mat frame;
    Mat src;
    // Capture frame-by-frame
    cap >> frame;
    src << frame.copy();
    
    int width = 640;
    int height = 480;

    int num_leds_top = 8;
    int patch_top = width / num_leds_top;
    
    for(int i=0; i<width; i+=patch_top) {
        cout << i << "\n";
    }
    
 
    // If the frame is empty, break immediately
    if (frame.empty())
      break;

    // Display the resulting frame
    imshow( "Frame", frame );

    // Press  ESC on keyboard to exit
    char c=(char)waitKey(25);
    if(c==27)
      break;
  }
 
  // When everything done, release the video capture object
  cap.release();

  // Closes all the frames
  destroyAllWindows();
	
  return 0;
}
