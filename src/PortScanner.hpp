//
//  PortScanner.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//
#ifndef PortScanner_hpp
#define PortScanner_hpp
#include "Common.hpp"

//Constants for flags
#define TH_FIN  0x01
#define TH_SYN  0x02
#define TH_RST  0x04
#define TH_PUSH 0x08
#define TH_ACK  0x10
#define TH_URG  0x20
//DNS header and query strucutre as per http://www.binarytides.com/dns-query-code-in-c-with-linux-sockets/

struct dns_header {
    unsigned short id; // identification number
    
    unsigned char rd :1; // recursion desired
    unsigned char tc :1; // truncated message
    unsigned char aa :1; // authoritive answer
    unsigned char opcode :4; // purpose of message
    unsigned char qr :1; // query/response flag
    
    unsigned char rcode :4; // response code
    unsigned char cd :1; // checking disabled
    unsigned char ad :1; // authenticated data
    unsigned char z :1; // its z! reserved
    unsigned char ra :1; // recursion available
    
    unsigned short q_count; // number of question entries
    unsigned short ans_count; // number of answer entries
    unsigned short auth_count; // number of authority entries
    unsigned short add_count; // number of resource entries
};


struct question {
    unsigned short qtype;
    unsigned short qclass;
};


typedef struct {
    unsigned char *name;
    struct  question *ques;
} query;

class Report
{
public:
    /* Create this classes object to hold all of our reported scan results */
    int check;
    std::string source_host;   /*Source machine IP */
    std::string destination_host; /*Destination machine IP */
    in_port_t source_port, destination_port; /*Source and destination ports used */
    std::string version; /* Service version returned*/
    u_int8_t flags; /* flags for TCP */
    unsigned int code; /*ICMP specific */
    unsigned int type; /*ICMP specific */
    u_int8_t protocol;
    std::string scan_type;
    std::string status;
    
    double timeTaken;
    /* initialize stuff */
    void print_output (int p,   std::string ip);
    void store_output();
    Report()
    {
    }
};

class PortScanner
{
public:
#ifdef __linux__    

    void begin_scan(int argc, char ** argv);
    void create_ip_header(iphdr *ip_header, 
                          unsigned long source,
                          unsigned long destination,
                          unsigned int length,
                          unsigned short protocol);
    void create_tcp_header(tcphdr *tcp_header,
                           iphdr *ip_header,
                           unsigned int source_port, 
                           unsigned int dest_port, 
                           u_int8_t flags);
    void create_udp_header(udphdr *udp_header,
                           iphdr *ip_header,
                           unsigned short source_port,
                           unsigned short dest_port);
    void tcp_scan( const char *dest, unsigned int d_port, std::string scan_type);
    std::string get_source_ip(sockaddr_in &source);
    void service_scan ( const char* host, const char* service_type);
    void udp_scan ( const char *dest, unsigned int d_port);
    void port_services (int port);
    int  time_remaining(time_t start_time);
    double get_time();
#endif    
protected:
    int number_of_threads = 0;
};

#endif /* PortScanner_hpp */
