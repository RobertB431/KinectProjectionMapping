Kinect Projection Mapping 
Robert Barron

This program allows you to project video onto any real life object using Kinect and openFrameworks.
Included with this program are sample models and videos to use.

User Guide
Prerequisites: Net Framework 4.0 or later, Microsoft Kinect SDK 1.8 or later, Microsoft Kinect developer toolkit 1.8 or later,  openFrameworks 0.8 or later, QuickTime player, a projector, a Microsoft Kinect, and a DirectX 11 compatible graphics card*.

Kinect compatibility is only currently supported in windows.

Tested on Windows 7 using an AMD HD 5850 1GB graphics card.

1.	Place the Kinect Projection Mapping program inside of the “myApps” folder in openFrameworks (openFrameworks installation \of_v0.8.0_vs_release\apps\myApps).

2. Open the KinectProjectionMapping executable, located in openFrameworks installation \of_v0.8.0_vs_release\apps\myApps\KinectProjectionMapping\bin. If you already have a 3D model you want to use, skip to step 4. Otherwise press ‘p’ on the keyboard to bring up the “Kinect Fusion Explorer” program provided by the Kinect SDK.
 
3. This program allows you to create a 3D model using the Kinect and save it in the OBJ file format. The depth slider can be adjusted to isolate the object(s) you want to scan, which will be shown in the video window in real time. 
 

4.	Once the object(s) is isolated, select “OBJ” mesh format and then click “Create Mesh.” Navigate to a folder you would like to store the 3D model in and save it. You can now exit Kinect Fusion Explorer.
4.	To open a saved 3D model, press “m’” to open a windows explorer dialog, and select the desired model.
 

5.	Now the video that is going to be projected onto the object must be chosen. This video must be saved on your computer in the MP4 file format. To open a video, press “v” to open a windows explorer dialog, and select the desired video.

6.	The video should now be playing, and projected onto the 3D model. You can move the model around the screen using the “wasd” keys. You can rotate the model using the “ijkl” keys, or by clicking and dragging with the mouse. Finally, you can increase or decrease the size of the model using the “,” and “.” keys, respectively. These can be used to adjust the model until it fits onto the real object it is projected onto.

7.	You can enter full screen mode using the “0” key, and hide the help text displayed on screen by pressing the “q” key.
 

*A DirectX 11 card is only required if you want to use the Kinect 3D modeling software. The KinectProjectionMapping program will work on hardware that supports OpenGL 2 or higher. You can create 3D models using free software such as Blender if your hardware does not support Kinect. Or if you find the 3D model Kinect created needs minor editing, you can use Blender to edit the model.

To compile the project yourself in Windows, navigate to your openFrameworks installation \of_v0.8.0_vs_release\apps\myApps\KinectProjectionMapping and open the “KinectProjectionMapping” Visual Studio project file using Microsoft Visual Studio 2012.
