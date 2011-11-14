// RexgoVid.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include <stdio.h>
#include "videoInput.h"
#include "RexgoVid.h"

int dev = 0;

RexgoVid::RexgoVid(){

}
RexgoVid::~RexgoVid(){

}

void RexgoVid::start(int _w,int _h,int _rate){

	this->imageWidth = _w;
	this->imageHeight = _h;
	this->rate = _rate;
	//this->dev =_dev;
	IT  = new imageTexture(2048,2048, GL_RGB);  
	VI.setUseCallback(true);
	VI.setupDevice(dev,imageWidth, imageHeight, VI_COMPOSITE);
	int width 	= VI.getWidth(dev);
	int height 	= VI.getHeight(dev);
	int size	= VI.getSize(dev);
	
	frame = new unsigned char[VI.getSize(dev)];
	

}

void RexgoVid::update(){
	//check to see if we have got a new frame
	if( VI.isFrameNew(dev) )	
	{
		//we get the pixels by passing in out buffer which gets filled
		VI.getPixels(dev,frame, false,true);		//这里要false否则会镜像,相关的查看videoInput的头文件

		//we then load them into our texture
		IT->loadImageData(frame, VI.getWidth(dev), VI.getHeight(dev),GL_RGB);
	}
	
	IT->renderTexture(0, 0, VI.getWidth(dev), VI.getHeight(dev));


}

void RexgoVid::stop(){
	delete [] IT;
	delete [] this->frame;
	VI.stopDevice(dev);
	//delete VI; 

}

int RexgoVid::width(){
	return this->imageWidth;
}
int RexgoVid::height(){
	return this->imageHeight;
}

unsigned char *RexgoVid::image(){
	return this->frame;
}