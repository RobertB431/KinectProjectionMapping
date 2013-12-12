#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofSetWindowTitle("Kinect Projection Mapping");
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(50, 255);
	ofSetVerticalSync(false);//vsync off
    ofDisableArbTex(); // we need GL_TEXTURE_2D for our models coords.
	
    model.loadModel("surface2.obj", true);// this is the default model we want to project onto. must be in the data folder
    model.setPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75 , 0);//set initial position of model
    model.enableTextures();//needed for video texture
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableDepthTest();
	glShadeModel(GL_SMOOTH); 

	
	//initialize our variables
	play = false;//this determines if the video should be played or not
	helpText = true;//turns the help displayed on the screen on or off
	scale = 1;//controls the size of the model
	rotateX = 0;//x-axis rotation
	rotateY = 0;//y-axis rotation
	moveX = 0;//x-axis movement
	moveY = 0;//y-axis movement
	fileType = true;//true means we want to load a 3d model, false means we want to load a video
	fullScreen = false;//dont allow dialog boxes to be open during fullscreen operation(the dialog box wont show up)
	playing = false;//video is not playing
	ofBackground(200,200,200);//color of background

	
}

//--------------------------------------------------------------
void testApp::update(){
	if(play)
	{
		movie.update();//get the next frame of the video
	}
    model.update();//update the model position
}

//--------------------------------------------------------------
void testApp::draw(){
	
    ofSetColor(255,255,255);//color of mesh

    ofPushMatrix();
	ofTranslate(model.getPosition().x, model.getPosition().y-200, 0);
	ofRotate(rotateX,0,1,0);//rotate the model by the chosen amount
	ofRotate(rotateY,1,0,0);
	ofScale(scale,scale,scale);//scale the model by the chosen amount
	ofTranslate(moveX, moveY, 0);//move the model by the chosen amount
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
	
	if(play)//update the video texture of the model
	{
		movie.getTextureReference().bind();
		model.drawFaces();
		movie.getTextureReference().unbind();
	}
	else //if the video isnt playing just draw the textureless model
	{
		model.drawFaces();
	}
	ofPopMatrix();

	//use opengl programmable renderer
	if(ofGetGLProgrammableRenderer()){
		glPushAttrib(GL_ALL_ATTRIB_BITS);
		glPushClientAttrib(GL_CLIENT_ALL_ATTRIB_BITS);
    }
    glEnable(GL_NORMALIZE);

    if(ofGetGLProgrammableRenderer()){
    	glPopAttrib();
    }
	if(helpText)//help text displayed on screen
	{
		stringstream ss;
		ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
		ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);
		ofDrawBitmapString("press 1 to load the model, and 2 to play the video", 10, 30);
		ofDrawBitmapString("press wasd to move, ijkl to rotate, and ,. to scale", 10, 45);
		ofDrawBitmapString("press 0 to toggle fullScreen mode", 10, 60);
		ofDrawBitmapString("press m to pick a 3D model, and v to pick a video", 10, 75);
		ofDrawBitmapString("press p to open kinect 3D modeling software", 10, 90);
		ofDrawBitmapString("press q to hide the help text", 10, 105);
	}
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    ofPoint modelPosition(ofGetWidth() * 0.5, (float)ofGetHeight() * 0.75);

	//cant be part of switch because ofFileDialogResult can be bypasses by the switch
	if (key == 'm')
	{
		if(fullScreen)//must exit fullscreen in order to use dialog box
		{
			ofToggleFullscreen();
			fullScreen = false;//no longer fullscreen
		}
		//we want to load a 3d model, set filetype to true
		fileType = true;
		//Open the Open File Dialog
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a STL, OBJ, or 3DS file"); 
		
		//Check if the user opened a file
		if (openFileResult.bSuccess)
		{
			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);
			model.loadModel(modelName);
			model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
			ofEnableSeparateSpecularLight();
			play = false;
			
		}
	}
	if (key == 'v')
	{
		if(fullScreen)//must exit fullscreen in order to use dialog box
		{
			ofToggleFullscreen();
			fullScreen = false;//no longer fullscreen
		}
		//we want to load a video, set filetype to true
		fileType = false;
		//Open the Open File Dialog
		ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a MP4 file"); 
		
		//Check if the user opened a file
		if (openFileResult.bSuccess)
		{
			//We have a file, check it and process it
			processOpenFileSelection(openFileResult);
			movie.loadMovie(videoName);//get the video from the folder data/movies
			movie.play();//start playing
			movie.setVolume(0);//mute the video
			play = true;
		}
	}
	

	//list of key presses
	switch (key) {
    case '1':
        model.loadModel(modelName);
        model.setPosition(modelPosition.x, modelPosition.y, modelPosition.z);
        ofEnableSeparateSpecularLight();
		play = false;

        break;
    case '2':
		movie.loadMovie(videoName);//get the video from the folder data/movies
		movie.play();//start playing
		movie.setVolume(0);//mute the video
		play = true;
		break;
	case ',':
		scale += 0.05;
		break;
	case '.':
		scale -= 0.05;
		break;
	case 'i':
		rotateY -= 0.5;
		break;
	case 'k':
		rotateY += 0.5;
		break;
	case 'j':
		rotateX -= 0.5;
		break;
	case 'l':
		rotateX += 0.5;
		break;
	case 'a':
		moveX += 3;
		break;
	case 'd':
		moveX -= 3;
		break;
	case 'w':
		moveY -= 3;
		break;
	case 's':
		moveY += 3;
		break;
	case 'q':
		if(helpText)
			helpText = false;
		else
			helpText = true;
		break;
	case '0':
		ofToggleFullscreen();//switch to fullScreen mode
		fullScreen = !fullScreen;
		break;
	case 'p':
		startupKinect();
		break;
            
        break;
    default:
        break;
    }
}

void testApp::processOpenFileSelection(ofFileDialogResult openFileResult){
	
	ofLogVerbose("getName(): "  + openFileResult.getName());
	ofLogVerbose("getPath(): "  + openFileResult.getPath());
	
	ofFile file (openFileResult.getPath()); 

	if (file.exists())
	{
		string fileExtension = ofToUpper(file.getExtension());
		
		//filetype decides if we were brought to this dialog for opening a model, or for opening a video
		if(fileType)//We only want 3d model formats assimp model loader can use
		{
			if (fileExtension == "OBJ" || fileExtension == "STL" || fileExtension == "3DS")
			{
				modelName = openFileResult.getPath();//this is the path of the 3d model
			}
			else
			{
				ofDrawBitmapString("invalid file format", 50, 150);
			}
		}
		else
		{
			if (fileExtension == "MP4")//we only want a video file of type mp4(h.264 encoding preferred)
			{
				videoName = openFileResult.getPath();//this is the path of the 3d model
			}
			else
			{
				ofDrawBitmapString("invalid file format", 50, 150);
			}
		}
		
	}
	
}
//open the kinect 3d model scanning program provided by microsoft

void testApp::startupKinect()
{
	TCHAR* appname;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	appname = (TCHAR*)malloc(sizeof(TCHAR)*255);
	//default path to kinect sdk installation
	_tcscpy(appname, TEXT("C:\\Program Files\\Microsoft SDKs\\Kinect\\Developer Toolkit v1.8.0\\bin\\KinectFusionExplorer-D2D.exe"));

	CreateProcessW(NULL, appname, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

	// Close process and thread handles. 
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    //
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    rotateX = x;//the mouse can be used to rotate the model
	rotateY = y;
	
}
//The other functions arent currently used
//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
   
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){

}

