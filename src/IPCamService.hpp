//
//  IPCamService.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//

#ifndef IPCamService_hpp
#define IPCamService_hpp
#include "Common.hpp"
#include <evartp/Common.hpp>
#include <evartp/CamParamsEncryption.hpp>
#include <evartp/StreamManager.hpp>
#include "IPCamSearch.hpp"

class IPCamService
{
public:
    IPCamService();
    virtual ~IPCamService();
    IPCamService(IPCamService const&)                     = delete;    // Copy construct
    IPCamService(IPCamService&&)                          = delete;   // Move construct
    IPCamService& operator=(IPCamService const& )         = delete;  // Copy assign
    IPCamService& operator=(IPCamService&&)               = default;  // Move assign
    ApiStatus beginScan(std::string ipaddress);
    ApiStatus detectIPCam(std::string ipaddress);
    ApiStatus isCamDetected(std::string ipAddress);
    ApiStatus connectToCam(CamParamsEncryptionRef camAuthRef);
    ApiStatus disconnectCam(CamParamsEncryptionRef camAuthRef);
    void addOnConnectCallback(ConnectedCallBackFunc callback) { IPCamService::connectFunc = callback; }
    void addOnErrorCallback(ErrorCallBackFunc callback) { IPCamService::errorFunc = callback; }
    static void onConnected(char* Cam);
    static void onError(char* Cam);
protected:
    IPCamSearchRef  camSearchOneRef;
    IPCamSearchRef  camSearchTwoRef;
    IPCamSearchRef  camSearchThreeRef;
    IPCamSearchRef  camSearchFourRef;
    StreamManagerRef 	streamManagerRef;
    CamParamsEncryption encryption;
    ApiStatus ApiState;
    std::mutex mutex;
    static ConnectedCallBackFunc connectFunc;
    static ErrorCallBackFunc     errorFunc;
    static bool StreamCameraOneActive;
    static bool StreamCameraTwoActive;
    static bool StreamCameraThreeActive;
    static bool StreamCameraFourActive;
 };


#endif /* IPCamService_hpp */
