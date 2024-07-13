import cv2
import spidev
import math
import numpy as np
import time

 
cap = cv2.VideoCapture('Ambilight.mp4')
division = 100
resolution = (1280/division,720/division)
fps = 30
width = 20
cap.set(cv2.CAP_PROP_FPS,fps )
cap.set(cv2.CAP_PROP_FRAME_WIDTH,resolution[0] )
cap.set(cv2.CAP_PROP_FRAME_HEIGHT,resolution[1] )

spi_bus=0
spi_device=0

spi=spidev.SpiDev()
spi.open(spi_bus, spi_device)
spi.max_speed_hz = 5000000

num_leds_top   = 8

if (cap.isOpened()== False):
  print("Error opening video stream or file")

def get_average(src):
    src = src.copy()
    channels = cv2.mean(src)
    src[:,:] = np.array([(channels[2] , channels[1] , channels[0])])[0]
    return [int(channels[2]) , int(channels[1]) , int(channels[0])]


while(cap.isOpened()):
  ret, frame = cap.read()
  src = frame.copy()
  w,h = resolution
  w,h = int(w),int(h)
  frame1 = cv2.resize(frame, (w,h) ,interpolation=cv2.INTER_AREA)
  if ret == True:
	  top_strip = []
	  for k in range(num_leds_top):
		  #cv2.rectangle(frame ,(0,0),((k+1)*int(resolution[0]/num_leds_top),width) , (255,0,0) , 1)
		  top_strip.append(get_average(frame1[0:width,(k)*int(resolution[0]/num_leds_top):(k+1)*int(resolution[0]/num_leds_top)]))
		  #left to right
			
	  top_strip = np.array(top_strip)
	  #print(top_strip)
	  tab_out =[]
	  for led in top_strip.tolist():
		  tab_out.append(led[1])
		  tab_out.append(led[0])
		  tab_out.append(led[2])
	  print(tab_out)

	  rcv_byte=spi.xfer2(tab_out)
	  #time.sleep(0.005)
	  cv2.imshow('Frame',frame)

	  if cv2.waitKey(25) & 0xFF == ord('q'):
		  break
  else:
    break
    
cap.release()
cv2.destroyAllWindows()
