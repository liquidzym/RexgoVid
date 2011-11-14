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
		//void paint();  //画出画面
		int width();
		int height();
		unsigned char *image();
		//int[] dev;//相机端口0..9

private:

	imageTexture * IT;
	//imageTexture * IT2; 
	videoInput    VI;   //创建捕获
	int imageWidth;
	int imageHeight;
	int rate;

	unsigned char * frame;
	
	//unsigned char * frame2;

		
};