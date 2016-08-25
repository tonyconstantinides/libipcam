//
//  IPCamService.cpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//
#include "IPCamService.hpp"
#include "IPCamSearch.hpp"
#include "PortScanner.hpp"
#include "CamNotificationDefs.hpp"
#include <evartp/StreamErrorHandler.hpp>
#include <functional>
#include <mutex>

ConnectedCallBackFunc IPCamService::connectFunc;
ErrorCallBackFunc     IPCamService::errorFunc;
bool IPCamService::StreamCameraOneActive = false;
bool IPCamService::StreamCameraTwoActive = false;
bool IPCamService::StreamCameraThreeActive = false;
bool IPCamService::StreamCameraFourActive = false;
using namespace Jetpack::Foundation;
using namespace std4:placeholders;

IPCamService::IPCamService()		
: ApiState(ApiStatus::OK)  
{
    logdbg("***************************************");
    logdbg("Entering IPCamService constructor......");
    static dispatch_once_t onceToken;
        dispatch_once(&onceToken, ^{
            struct _IPCamService : IPCamService {
                _IPCamService()
                : IPCamService()  {}
            };
            streamManagerRef = std::make_shared<StreamManager>();
        });
    logdbg("Leaving IPCamService constructor.......");
    logdbg("***************************************");
}

IPCamService::~IPCamService()
{
    logdbg("***************************************");
    logdbg("Entering IPCamService destructor......");
    streamManagerRef.reset();
    streamManagerRef = nullptr;
    logdbg("Leaving IPCamService destructor.......");
    logdbg("***************************************");
} 

// you can search for up to 4 cams
ApiStatus IPCamService::beginScan(std::string ipaddress)
{
    logdbg("***************************************");
    logdbg("Entering IPCamService beginScan......");
    ApiState = ApiStatus::CLEAR;

    if (!camSearchOneRef)
    {
      logdbg("Activating camSearchOneRef!");
      camSearchOneRef = IPCamSearch::createIPCamSearch();
      camSearchOneRef->beginScan(ipaddress);
      logdbg("camSearchOneRef running!");
      ApiState = ApiStatus::OK;
    } else if (camSearchTwoRef)
    {
      logdbg("Activating camSearchTwoRef!");
      camSearchTwoRef = IPCamSearch::createIPCamSearch();
      camSearchTwoRef->beginScan(ipaddress);
      logdbg("camSearchTwoRef running!");
      ApiState = ApiStatus::OK;
    } else if (camSearchThreeRef)
    {
      logdbg("Activating camSearchThreeRef!");
      camSearchThreeRef = IPCamSearch::createIPCamSearch();
      camSearchThreeRef->beginScan(ipaddress);
      logdbg("camSearchThreeRef running!");
      ApiState = ApiStatus::OK;
    }else if (camSearchFourRef)
    {
      logdbg("Activating camSearchFourRef!");
      camSearchFourRef = IPCamSearch::createIPCamSearch();
      camSearchFourRef->beginScan(ipaddress);
      logdbg("camSearchFourRef running!");
      ApiState = ApiStatus::OK;
    } else
    {       
        logerr() << "Up to 4 Cam Search Cam be done at any one time!";
       ApiState = ApiStatus::FAIL;
    }
    logdbg("Leaving IPCamService beginScan......");
    logdbg("***************************************");
    return ApiState;
}

ApiStatus IPCamService::detectIPCam(std::string ipaddress)
{
    logdbg("***************************************");
    logdbg("Entering IPCamService detectIPCam......");
    ApiState = ApiStatus::OK;
    logdbg("Leaving  IPCamService detectIPCam......");
    logdbg("***************************************");
    return ApiState;
}

ApiStatus IPCamService::isCamDetected(std::string ipAddress)
{
    logdbg("**************************************");
    logdbg("Entering IPCamService isCamDetected......");
    ApiState = ApiStatus::OK;
    logdbg("Leaving  IPCamService isCamDetected......");
    logdbg("***************************************");
    return ApiState;
}

ApiStatus IPCamService::connectToCam(CamParamsEncryptionRef camAuthRef)
{
   logdbg("**************************************");
   logdbg("Entering IPCamService connectToCam......");
   mutex.lock(); 
   // any locking here prevents the app from running for some reason
   using namespace std::placeholders; 
   ConnectedCallBackFunc   connectionCB = std::bind(   &IPCamService::onConnected, _1 );
   ErrorCallBackFunc       errorCB  =  std::bind(  &IPCamService::onError,   _1 );
   ApiState = streamManagerRef->connectToStream(camAuthRef, connectionCB,  errorCB,  StreamType::H264_AND_MJPEG	);
   mutex.unlock();
   logdbg("Leaving  IPCamService connectToCam......");
   logdbg("***************************************");
   return ApiState;
}

ApiStatus  IPCamService::disconnectCam(CamParamsEncryptionRef authCamRef)
{
   logdbg("**************************************");
   logdbg("Entering IPCamService disconnectCam......");
   mutex.lock(); 
   if (streamManagerRef->disconnectStream(authCamRef) == ApiStatus::OK)
     ApiState = ApiStatus::OK;
   else
     ApiState = ApiStatus::FAIL;
   mutex.unlock();
   logdbg("Leaving  IPCamService disconnectCam......");
   logdbg("***************************************");
   return ApiState;
}

void IPCamService::onConnected(char* Cam) 
{
  logdbg("**************************************");
  logdbg("Entering IPCamService onConnected callback!");
  logdbg("IPCam connected, notification already sent!");
  if (Cam)
  {
    if (strcmp(Cam, IPCAM_ONE) == 0)
    {
      StreamCameraOneActive = true;
    } else if (strcmp(Cam, IPCAM_TWO) == 0)
    {
      StreamCameraTwoActive = true;
    } else if (strcmp(Cam, IPCAM_THREE) == 0)
    {
      StreamCameraThreeActive = true;
    } else if (strcmp(Cam, IPCAM_FOUR) == 0)
    {
      StreamCameraFourActive = true;
    }
  }  
  if (connectFunc)
  {
    connectFunc(Cam);
  }  
  logdbg("Leaving IPCamService onConnected callback!");
  logdbg("**************************************");
}

void IPCamService::onError(char* Cam)
{
  logdbg("**************************************");
  logdbg("Entering IPCamService onError callback!");
  logdbg("IPCam error, Notifications already sent!");
  if (errorFunc)
  {
    errorFunc(Cam);
  }  
  logdbg("Leaving IPCamService onError callback!");
  logdbg("**************************************");
}
     
