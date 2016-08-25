//
//  IPCamSearch.cpp
//  ipcam
//
//  Created by Tony Constantinides on 5/3/16.
//

#include "IPCamSearch.hpp"
using namespace Jetpack::Foundation;
IPCamSearchRef IPCamSearch::instance = nullptr;
PortScannerRef IPCamSearch::scanner  = nullptr;

IPCamSearchRef IPCamSearch::createIPCamSearch()
{
    logdbg("***************************************");
    logdbg("Entering createIPCamSearch.......");
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        struct _IPCamSearch : IPCamSearch {
            _IPCamSearch()
            : IPCamSearch() {}
        };
        logdbg("Assigning values to inner IPCamSearch and PortScanner!");
        instance = std::make_shared<_IPCamSearch>();
        scanner  = std::make_shared<PortScanner>();
        logdbg("inner IPCamSearch and PortScanner assign shared pointers!");
    });
  
    logdbg("Leaving createIPCamSearch.......");
    logdbg("***************************************");
    return instance;
}

IPCamSearch::IPCamSearch()
{
    logdbg("***************************************");
    logdbg("Entering IPCamSearch constructor.......");

    logdbg("Leaving IPCamSearch constructor.......");
    logdbg("***************************************");
}
        
IPCamSearch::~IPCamSearch()
{
    logdbg("***************************************");
    logdbg("Entering IPCamSearch destructor.......");
    instance.reset();
    instance = nullptr;
    scanner.reset();
    scanner = nullptr;
    logdbg("Leaving IPCamSearch destructor.......");
    logdbg("***************************************");
}

ApiStatus IPCamSearch::beginScan(std::string ipaddress)
{
    logdbg("***************************************");
    logdbg("Entering IPCamSearch beginScan()");
    char* pBuffer = new char[100];
    std::strcpy(pBuffer, "--ports 100,1000 --scan");
    //scanner->begin_scan(std::atoi(ipaddress.c_str()) , &pBuffer);
    ApiState = ApiStatus::OK;
    logdbg("Leaving IPCamSearch beginScan()");
    logdbg("***************************************");
    return ApiState;
}

