#include "opencv2/opencv.hpp"
#include <iostream>
#include <spidevpp/spi.h>
#include <stdlib.h> 
#include <unistd.h>

using namespace std;
using namespace cv;


int main(){
	
  spidevpp::Spi spi("/dev/spidev0.0");
	spi.setBitsPerWord(8);
	spi.setSpeed(1000000);

  // Create a VideoCapture object and open the input file
  // If the input is the web camera, pass 0 instead of the video file name
  VideoCapture cap("Ambilight.mp4"); 
  cap.set(CAP_PROP_FRAME_WIDTH, 640);
  cap.set(CAP_PROP_FRAME_HEIGHT, 480);
  cap.set(CAP_PROP_FPS, 30);
   

  // Check if camera opened successfully
  if(!cap.isOpened()){
    cout << "Error opening video stream or file" << endl;
    return -1;
  }
  int width = 640;
  int width1 = 40;
  int height = 480;
  

  int num_leds_top = 8;
  int patch_top = width / num_leds_top;
  
  //system("/home/pi/c/script.sh");


  while(1){
    
    // Capture frame-by-frame
    cv::Mat frame;
    cap >> frame;
    
    // top LEDS
    cv::Mat area;
    char send_led [24] = {};
    for(int i=0; i<num_leds_top; i++) {
      area= frame( cv::Rect( i*patch_top, 0, (i+1) * patch_top, 40 ) );
      cv::Scalar avg = cv::mean(area);
      cout << "Area" << i << "=" << avg << endl;
      // avg[r, g, b]
      send_led[i * 3    ] = avg[1]; // green
      send_led[i * 3 + 1] = avg[2]; // red
      send_led[i * 3 + 2] = avg[0]; // blue
      
      
      
    }
    //Send to Rapshberry pi
    spi.write(send_led, 24);
    //sleep(0.005);

 
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
