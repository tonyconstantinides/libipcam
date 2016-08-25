//
//  IPCamSearchTest.cpp
//  ipcam
//
//  Created by Tony Constantinides on 5/20/16.
//

#include "catch.hpp"
#include "../Common.hpp"
#include "../IPCamSearch.hpp"
#include <evartp/CamParamsEncryption.hpp>
#include <unistd.h>

TEST_CASE("IPCamSearch")
{
    IPCamSearchRef searchRef;
    struct _IPCamSearch : IPCamSearch {
        _IPCamSearch()
        : IPCamSearch() {}
    };
    auto innerRef = std::make_shared<_IPCamSearch>();
    
    SECTION("Testing createIPCamSearch")
    {
        IPCamSearchRef searchRef =  IPCamSearch::createIPCamSearch();
        REQUIRE( searchRef != nullptr);
    }
    
    SECTION("Testing destructor")
    {
        // this takes a while to call te constructor   
        IPCamSearchRef searchRef =  IPCamSearch::createIPCamSearch();
        sleep(5);
        static IPCamSearchRef innerSearchRef = searchRef->getTestInstance();
        static PortScannerRef innerScannerRef  = searchRef->getTestPortScanner();
        sleep(1);
        CHECK(searchRef != nullptr);
        CHECK(innerSearchRef != nullptr);
        CHECK(innerScannerRef != nullptr);
        searchRef.reset();
        CHECK(searchRef == nullptr);
        CHECK(innerSearchRef == nullptr);
        CHECK(innerScannerRef == nullptr);
    }
    
    SECTION("Testing beginScan")
    {
        IPCamSearchRef searchRef =  IPCamSearch::createIPCamSearch();
    }
}










