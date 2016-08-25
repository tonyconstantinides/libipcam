//
//  IPCamSearch.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/3/16.
//

#ifndef IPCamSearch_hpp
#define IPCamSearch_hpp
#include "Common.hpp"
#include "PortScanner.hpp"
#include <evartp/CamParamsEncryption.hpp>

class IPCamSearch
{
public:
    static  IPCamSearchRef createIPCamSearch();
    virtual ~IPCamSearch();
    IPCamSearch(IPCamSearch const&)              = delete;   // Copy construct
    IPCamSearch(IPCamSearch&&)                   = delete;   // Move construct
    IPCamSearch& operator=(IPCamSearch const& )  = delete;   // Copy assign
    IPCamSearch& operator=(IPCamSearch&&)        = default;  // Move assign
  
    ApiStatus connectToCam(CamParamsEncryptionRef camAuthRef);
    ApiStatus beginScan(std::string ipstring);
    
    // for testing purposes
    IPCamSearchRef getTestInstance() { return  instance; }
    PortScannerRef getTestPortScanner()  { return scanner;}

protected:
    IPCamSearch();
    static IPCamSearchRef instance;
    static PortScannerRef scanner;
    static void onConnected(std::string status);
    static void onError(std::string status);	
    ApiStatus ApiState;

};

#endif /* IPCamSearch_hpp */
