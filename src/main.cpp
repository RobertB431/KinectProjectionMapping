/* Robert Barron
   Projection Mapping project using openframeworks, opengl, and kinect
   This project is based off of the "assimpExample" example project provided by openframeworks
	
*/

#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	//OF_WINDOW or OF_FULLSCREEN
	ofSetupOpenGL(1024,768, OF_WINDOW);//setup the GL context
	
	//start app
	ofRunApp( new testApp());

}
