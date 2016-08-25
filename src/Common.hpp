//
//  Common.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/3/16.
//

#ifndef Common_h
#define Common_h
#define _BSD_SOURCE
#define _SVID_SOURCE

#include <foundation/foundation.hpp>
#include <functional>
#include <string>
#include <memory>
#include <vector>
#include <queue>
#include <map>
#include <stdexcept>
#include <cstring>
#include <vector>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <iomanip>
#include <ifaddrs.h>
#include <math.h>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <queue>
#include <unistd.h>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <netdb.h>
#include <cstring>
#include <errno.h>
#include <stdexcept>
#include <poll.h>
#include <pthread.h>
#include <iomanip>
#include <math.h>

//Include packages required for different protocol headers like TCP, IP , UDP etc
#include <mutex>
#include <pthread.h>
#include <arpa/inet.h>        // inet_pton() and inet_ntop()

#ifdef __APPLE__
#include "osx_compat.hpp"     // define iphdr structure on OSX
#include <netinet/if_ether.h>
#include <netinet/in.h>       // IPPROTO_RAW, IPPROTO_UDP, INET_ADDRSTRLEN
#include <netinet/tcp.h>
#include <netinet/ip.h>       // struc ip and IP_MAXPACKET (which is 65535)
#include <netinet/udp.h>      // struct udphdr
#include <sys/ioctl.h>        // macro ioctl is defined
#include <net/if.h>           // struct ifreq≈ddr_ll (see man 7 packet)
#endif

#ifdef __linux__
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/if_ether.h>   // ETH_P_IP = 0x0800, ETH_P_IPV6 = 0x86DD
#include <linux/if_packet.h>  // struct sockaddr_ll (see man 7 packet)
#include <netdb.h>
#endif

#define IPCAM_ONE "IPCAM 1"
#define IPCAM_TWO "IPCAM 2"
#define IPCAM_THREE "IPCAM 3"
#define IPCAM_FOUR "IPCAM 4"

class GstMessage;
class CamParamsEncryption;
class IPStreamManager;
class StreamErrorHandler;

enum   class StreamType {MJPEG_ONLY, H264_ONLY, H264_AND_MJPEG};
enum  class ErrorCategoryDetected {  UNKNOWN, CORE,  STREAM,  LIBRARY,  RESOURCE};
enum  class ErrorCategoryReported { CLEAR, CAM_DISCOVERY_FAILED, AUTH_FAILED, STREAM_STOPPED, MISC_ERROR};
enum   class ApiStatus {OK, CLEAR, FAIL, FATAL_ERROR };

class StreamManager;
typedef std::shared_ptr<StreamManager> StreamManagerRef;
class RtspManager;
typedef std::shared_ptr<RtspManager> RtspManagerRef;
class MjpegManager;
typedef std::shared_ptr<MjpegManager>  MjpegManagerRef;

class IPCamSearch;
typedef std::shared_ptr<IPCamSearch> IPCamSearchRef;
class IPCamService;
typedef std::shared_ptr<IPCamService> IPCamServiceRef;
class PortScanner;
typedef std::shared_ptr<PortScanner>  PortScannerRef;
class StreamManager;
typedef std::shared_ptr<StreamManager> StreamManagerRef;
class CamParamsEncryption;
typedef std::shared_ptr<CamParamsEncryption> CamParamsEncryptionRef;

typedef std::function<void(char* Cam)>  ConnectedCallBackFunc;
typedef std::function<void(char* Cam)>  ErrorCallBackFunc;

typedef unsigned char BYTE;


extern ApiStatus ApiState;
extern int number_of_threads;
extern pthread_t t_id;

#endif /* Common_h */
	
