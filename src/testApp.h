#ifndef _TEST_APP
#define _TEST_APP

#pragma once
#include "ofMain.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include "ofxAssimpModelLoader.h"
#include "ofVboMesh.h"
#include <ostream>


class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		
		void processOpenFileSelection(ofFileDialogResult openFileResult);
		void startupKinect();
		ofImage texture;
		ofVideoGrabber vidGrabber;
		int mode;
        ofxAssimpModelLoader model;
		ofVideoPlayer movie;
		bool frameByframe;
		bool helpText;
        bool play;
        ofMesh mesh;
        ofLight	light;
		string posY;
		float scale;
		float rotateX;
		float rotateY;
		float moveX;
		float moveY;
		string modelName;
		string videoName;
		bool fullScreen;
		bool playing;
		bool fileType;
};

#endif
