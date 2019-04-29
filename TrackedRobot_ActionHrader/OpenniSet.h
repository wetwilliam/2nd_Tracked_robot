#include "OpenNI.h"

//Depth Resolution : 320x240 or 640x480
#define OpenNI_Resolution_x 640
#define OpenNI_Resolution_y 480

//---OpenNI set---
//1. Create OpenNI namespace
openni::Device devAnyDevice;  //open a device
openni::VideoStream streamDepth; //create depth stream
openni::VideoMode vmMode; //set video mode
openni::VideoFrameRef frameDepth; //main loop, continue read


void OpenNI_initialize();
void OpenNI_initialize_OB();

void OpenNI_close();

void OpenNI_initialize()
{
    /*---OpenNI initialize set---*/
    // 2. Initialize OpenNI
    openni::OpenNI::initialize();
    // 3. Open a device
    devAnyDevice.open( openni::ANY_DEVICE );
    // 4. Create depth stream
    streamDepth.create( devAnyDevice, openni::SENSOR_DEPTH );
    // 5. Set video mode
    vmMode.setFps(30);
    vmMode.setResolution(OpenNI_Resolution_x,OpenNI_Resolution_y);
    vmMode.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
    if(streamDepth.setVideoMode(vmMode) == openni::STATUS_OK)
    {
        //OK GO
        streamDepth.start();
    }
}

void OpenNI_initialize_OB()
{
    /*---OpenNI initialize set---*/
    // 2. Initialize OpenNI
    openni::OpenNI::initialize();
    // 3. Open a device
    devAnyDevice.open( openni::ANY_DEVICE );
    // 4. Create depth stream
    streamDepth.create( devAnyDevice, openni::SENSOR_DEPTH );
    // 5. Set video mode
    vmMode.setFps(30);
    vmMode.setResolution(320,240);
    vmMode.setPixelFormat(openni::PIXEL_FORMAT_DEPTH_1_MM);
    if(streamDepth.setVideoMode(vmMode) == openni::STATUS_OK)
    {
        //OK GO
        streamDepth.start();
    }
}

void OpenNI_close()
{
    streamDepth.destroy();  //Close video stream.
	devAnyDevice.close();   //Close device.
	openni::OpenNI::shutdown();//Close OpenNI.
}
