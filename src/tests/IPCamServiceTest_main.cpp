//
//  IPCamServiceTest_main.cpp
//  ipcam
//
//  Created by Tony Constantinides on 5/19/16.
//


#include "catch.hpp"	
#include "../Common.hpp"
#include "../IPCamService.hpp"
#include <evartp/CamParamsEncryption.hpp>

TEST_CASE("IPCamService")
{
    IPCamServiceRef serviceRef;
    std::string cameraGuid = "9999";
    std::string userName = "";
    std::string passwd = "";
    std::string host = "";
    std::string port = "";
    std::string queryParms = "";
    std::string absPath = "/videoMain";
     auto authRef = std::make_shared<CamParamsEncryption>();
    authRef->setCameraGuid( authRef->base64_encode(reinterpret_cast<const unsigned char*>(cameraGuid.c_str()), cameraGuid.length()) );
    authRef->setUserName(authRef->base64_encode(reinterpret_cast<const unsigned char*>(userName.c_str()), userName.length()));
    authRef->setPassword(authRef->base64_encode(reinterpret_cast<const unsigned char*>(passwd.c_str()), passwd.length()));
    authRef->setHost( authRef->base64_encode(reinterpret_cast<const unsigned char*>(host.c_str()), host.length()) );
    authRef->setPort( authRef->base64_encode(reinterpret_cast<const unsigned char*>(port.c_str()), port.length()) );
    authRef->setQueryParms( authRef->base64_encode(reinterpret_cast<const unsigned char*>(queryParms.c_str()), queryParms.length()) );
    authRef->setAbsPath( authRef->base64_encode(reinterpret_cast<const unsigned char*>(absPath.c_str()), absPath.length()) );

    SECTION("Testing constructor")
    {
        REQUIRE(serviceRef == nullptr);
        serviceRef = IPCamService::getInstance();
        CHECK( serviceRef != nullptr);
    }
    
    SECTION("Testing destructor")
    {
        REQUIRE(serviceRef == nullptr);
        serviceRef = IPCamService::getInstance();
        serviceRef.reset();
        CHECK( serviceRef == nullptr);
    }
    
    SECTION("Testing beginScan")
    {
     //   CHECK(std::strcmp("88" , authRef->base64_decode(authRef->getPort()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  state = serviceRef->beginScan("192.168.3.49");
        CHECK(state == ApiStatus::OK);
    }

    SECTION("Test detetctIPCam")
    {
        CHECK(std::strcmp("tony" , authRef->base64_decode(authRef->getUserName()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  state = serviceRef->detectIPCam("192.168.3.49");
        CHECK(state == ApiStatus::OK);
    }
    
    SECTION("Test isCamDetected")
    {
        CHECK(std::strcmp("tony" , authRef->base64_decode(authRef->getUserName()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  ApiState = serviceRef->isCamDetected("192.168.3.49");
        CHECK(ApiState == ApiStatus::OK);
    }
    
    
    SECTION("Test connectToCam")
    {
        CHECK(std::strcmp("tony" , authRef->base64_decode(authRef->getUserName()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  ApiState = serviceRef->connectToCam(authRef);
        CHECK(ApiState == ApiStatus::OK);
        authRef.reset();
    }
    
    SECTION("Test onConnected")
    {
        CHECK(std::strcmp("tony" , authRef->base64_decode(authRef->getUserName()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  ApiState = serviceRef->connectToCam(authRef);
        CHECK(ApiState == ApiStatus::OK);
        authRef.reset();
   }
    
    SECTION("Test onError")
    {
        CHECK(std::strcmp("tony" , authRef->base64_decode(authRef->getUserName()).c_str()) == 0);
        serviceRef = IPCamService::getInstance();
        ApiStatus  ApiState = serviceRef->connectToCam(authRef);
        CHECK(ApiState == ApiStatus::OK);
        authRef.reset();
    }
}


