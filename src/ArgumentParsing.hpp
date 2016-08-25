//
//  ArgumentParsing.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//

#ifndef ArgumentParsing_hpp
#define ArgumentParsing_hpp
#include "Common.hpp"

class ArgumentParsing
{
public:
    int c,p;
    std::string port, ip, prefix, speedup, filename, scan;
    std::string segment;
    size_t pos1, pos2;
    std::string character1;
    std::string character2;
    sockaddr_in test;
    sockaddr_in test6;
    
    std::vector<std::string> portNo;
    std::vector<std::string> portRange;
    std::vector<std::string> scanlist;
    std::vector<std::string> ip_prefix;
    std::vector<std::string> ipAddress;
    
    ArgumentParsing();
    
    void validate_ip(std::string ip);
    void readFile(std::string file);
    void calculate_prefix(std::string pre);
    void parsing_args(int argc, char ** argv);
 
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
    {
        std::stringstream ss(s);
        std::string item;
        while (getline(ss, item, delim))
        {
            elems.push_back(item);
        }
        return elems;
    }
    std::vector<std::string> split(const std::string &s, char delim)
    {
        std::vector<std::string> elems;
        split(s, delim, elems);
        return elems;
    }
    				
};

//functions for tcp checksums. Need to check something called psedu_header in tcp
unsigned short generate_tcp_checksum(iphdr *ip_header, tcphdr *tcp_header, u_int16_t length);
unsigned short generate_udp_checksum(iphdr *ip_header, udphdr *udp_header, u_int16_t length);
unsigned short csum(unsigned short *pointer , int bytes );
//random number for the sequence number in tcp
void dns_format_convert(unsigned char* dns, unsigned char* host);
unsigned int generate_random_number(unsigned int modulus);
//pseudo header structure

struct tcp_pseudo_header
{
    u_int32_t source_address;
    u_int32_t destination_address;
    u_int8_t  reserved;
    u_int8_t  protocol;
    u_int16_t tcp_segment_length;
};

struct udp_pseudo_header
{
    u_int32_t source_address;
    u_int32_t destination_address;
    u_int8_t  reserved;
    u_int8_t  protocol;
    u_int16_t udp_segment_length;
};

#endif /* ArgumentParsing_hpp */
