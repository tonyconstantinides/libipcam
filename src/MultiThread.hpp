//
//  MultiThread.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//

#ifndef __PortScanner__MultiThread__
#define __PortScanner__MultiThread__

#include "Common.hpp"

class Task
{
public:
    std::string ip_address;
    int port;
    std::string scan_type;
    
    ssize_t polling_read(int sockfd,
                                     int flags,
                                     struct sockaddr *address,
                                     unsigned long address_len,
                                     void * read_buffer,
                                     size_t read_length,
                                     int time );
    
    void* start_scans (void *dummy);
};

#endif /* defined(__PortScanner__MultiThread__) */
