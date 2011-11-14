#include <stdio.h>


#include "glfw.h"
#include "videoInput.h"
#include "imageTexture.h"

class RexgoVid{
	
public:
		RexgoVid();
		~RexgoVid();
		void start(int w,int h,int rate);
		//void start(int w,int h,int rate,int[] dev);
		void stop();
		void update();
		//void paint();  //��������
		int width();
		int height();
		unsigned char *image();
		//int[] dev;//����˿�0..9

private:

	imageTexture * IT;
	//imageTexture * IT2; 
	videoInput    VI;   //��������
	int imageWidth;
	int imageHeight;
	int rate;

	unsigned char * frame;
	
	//unsigned char * frame2;

		
};