#include "stdafx.h"
#include "rexgo_net_liquid_RexgoVid.h"
#include "RexgoVid.h"
#include "videoInput.h"

//static PS3Eye * ps3eye;
static RexgoVid * rexgovid;

#define COLOR_24BIT 0
#define COLOR_1BIT 1

/**
a helper function that generates dynamic java color-int arrays on the fly from rgb triplets.
*/
jintArray convertToJavaArray(JNIEnv *env,unsigned char*p,int color_depth){
	int w = rexgovid->width();
	int h = rexgovid->height();
	jintArray returnArray = env->NewIntArray(w*h);
	jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
	int a = 255 << 24;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	if(color_depth==COLOR_24BIT){
		int i3;
		for(int i=0;i<w*h;i++){
			i3 = i*3;
			r = ((int)p[i3])<<16;
			g = ((int)p[i3+1])<<8;
			b = ((int)p[i3+2])<<0;
			arrayStart[i] = a|r|g|b;
		}
	}else{
		for(int i=0;i<w*h;i++){
			r = ((int)p[i])<<16;
			g = ((int)p[i])<<8;
			b = ((int)p[i])<<0;
			arrayStart[i] = a|r|g|b;
		}
	}

	env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
	return returnArray;
}




/**
another helper function that generates dynamic java color-int arrays on the fly from rgb triplets.
*/
void convertToJavaArrayCopy(JNIEnv *env,unsigned char*p,jintArray returnArray,int color_depth){
	int w = rexgovid->width();
	int h = rexgovid->height();
	jint *arrayStart = env->GetIntArrayElements(returnArray, 0);
	int a = 255 << 24;
	unsigned int r;
	unsigned int g;
	unsigned int b;

	if(color_depth==COLOR_24BIT){
		int i3;
		for(int i=0;i<w*h;i++){
			i3 = i*3;
			r = ((int)p[i3+2])<<16 ;
			g = ((int)p[i3+1])<<8 ;
			b = ((int)p[i3])<<0 ;
			arrayStart[i] = a|r|g|b;
		}

	}else{
		for(int i=0;i<w*h;i++){
			r = ((int)p[i])<<16 ;
			g = ((int)p[i])<<8 ;
			b = ((int)p[i])<<0 ;
			arrayStart[i] = a|r|g|b;
		}
	}
	env->ReleaseIntArrayElements(returnArray, arrayStart, 0);
}



JNIEXPORT void JNICALL Java_rexgo_net_liquid_RexgoVid_native_1start
(JNIEnv * env, jobject obj, jint w, jint h, jint rate){
	rexgovid = new RexgoVid();
	rexgovid->start(w,h,rate);
}

/*
* Class:     ru_cleoag_PS3Eye
* Method:    native_stop
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_rexgo_net_liquid_RexgoVid_native_1stop
(JNIEnv * env, jobject obj){
	rexgovid->stop();
	delete rexgovid;
	rexgovid = 0;
	printf("stop rexgovid\n");

}
/*
* Class:     ru_cleoag_PS3Eye
* Method:    native_update
* Signature: ()V
*/
JNIEXPORT void JNICALL Java_rexgo_net_liquid_RexgoVid_native_1update
(JNIEnv * env, jobject obj){
	rexgovid->update();
}

/*
* Class:     ru_cleoag_PS3Eye
* Method:    native_imageCopy
* Signature: ([I)V
*/
JNIEXPORT void JNICALL Java_rexgo_net_liquid_RexgoVid_native_1imageCopy
(JNIEnv * env, jobject obj, jintArray dst){
	convertToJavaArrayCopy(env,rexgovid->image(),dst,COLOR_24BIT);
}