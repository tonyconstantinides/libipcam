//
//  ArgumentParsing.cpp
//  ipcam
//
//  Created by Tony Constantinides on 5/11/16.
//

#include "ArgumentParsing.hpp"


#include "ArgumentParsing.hpp"
#include "PortScanner.hpp"

ArgumentParsing::ArgumentParsing()
{
    std::string character1= ",";
    std::string character2="-";
    
}

void ArgumentParsing::validate_ip(std::string ip)
{
    if(ip.find(".") == std::string::npos)
    {
        logdbg("invalid ip");
    }
    int count;
    int a,b,c,d;
    count = sscanf(ip.c_str(),"%d.%d.%d.%d", &a, &b, &c, &d);
    if (count!= 4)
    {
        logdbg("invalid ip");
    }
    
    if ( a <0 || a >255 || b < 0 || b >255 || c<0 || c >255 || d < 0 || d > 255)
        logdbg("invalid ip");
}

std::vector<std::string>  scan;
std::vector<std::string>  result_scan;
std::vector<in_port_t>    scanip;
std::vector<std::string>  versionip;
std::vector<std::string>  host;
std::vector<std::string>  result;


void Report::store_output()
{
    scanip.push_back(destination_port);
    scan.push_back(scan_type);
    result_scan.push_back(status);
    versionip.push_back(version);
    host.push_back(destination_host);
}

std::vector<in_port_t>printed_port;

void Report::print_output(int p, std::string ipAdd)
{
    in_port_t temp;
    std::string temp1;
    std::string res;
    int counter=0;
    int sum=0;
    
    if(p == 0)
    {
        for(int i=0; i < scanip.size(); i++)
        {
            if(ipAdd==host[i])
            {
                if(result_scan[i]=="OPEN")
                {
                   for(int j=0;j<printed_port.size();j++)
                    {
                        if(printed_port[j]==scanip[i])
                        {
                            counter=1;
                        }
                    }
                    int count=0;
                    if(counter==0)
                    {
                        logdbg( std::setw(10)  << scanip[i] << std::setw(35) << versionip[i] << std::setw(30));
                        temp=scanip[i];
                        temp1=host[i];
                        for(int t=0; t < scanip.size(); t++)
                        {
                            if(temp==scanip[t] && temp1==host[t])
                            {
                                if(scan[i]=="SYN" && result_scan[i]=="CLOSED")
                                {
                                    res="CLOSED";
                                }
                                if(scan[i]=="SYN" && result_scan[i]=="FILTERED")
                                {
                                    res="FILTERED";
                                }
                                if(scan[i]=="SYN" && result_scan[i]=="OPEN")
                                {
                                    res="OPEN";
                                }
                                if(count==0)
                                {
                                    sum++;
                                    logdbg( scan[i] << "(" << result_scan[i] << " )" << std::setw(25) << res );
                                }
                                else
                                {
                                    sum++;
                                    logdbg(std::setw(74) << scan[t] << "(" << result_scan[t] << ")" << std::setw(35));
                                }
                                count++;
                            }
                        }
                        i=i+sum-1;
                        sum=0;
                        printed_port.push_back(scanip[i]);
                    }
                }
            }
        }
    }
    
    if(p == 1)
    {
        for(int i=0; i < scanip.size(); i++)
        {
            if(ipAdd == host[i])
            {
                int count = 0;
                if(result_scan[i]=="CLOSED" || result_scan[i]=="FILTERED"
                   || result_scan[i]=="UNFILTERED" || result_scan[i]=="OPEN|FILTERED")
                {
                   for(int j=0; j < printed_port.size(); j++)
                    {
                        if(printed_port[j] == scanip[i])
                        {
                            counter=1;
                        }
                    }
                    temp1  =   host[i];
                    temp    =   scanip[i];
                    if(counter  ==  0)
                    {
                        logdbg( std::setw(10)
                                    << scanip[i]
                                    << std::setw(35)
                                    << versionip[i]
                                    << std::setw(30));
                        for(int t=0; t < scanip.size(); t++)
                        {
                            if(temp == scanip[t] && temp1==host[t] )
                            {
                                if(scan[i]=="SYN" && result_scan[i]=="CLOSED")
                                {
                                    res="CLOSED";
                                }
                                if(scan[i]=="SYN" && result_scan[i]=="FILTERED")
                                {
                                    res="FILTERED";
                                }
                                if(scan[i]=="SYN" && result_scan[i]=="OPEN")
                                {
                                    res="OPEN";
                                }
                                if(scan[i]=="UDP" && result_scan[i]=="CLOSED" )
                                {
                                    res="CLOSED";
                                }
                                if(  (scan[i] == "UDP" && result_scan[i] == "OPEN|FILTERED")
                                   ||  (scan[i]=="ACK" && result_scan[i] == "FILTERED"))
                                {
                                    res="FILTERED";
                                }
                                if(count==0)
                                {
                                    sum = sum + 1;
                                    logdbg( scan[i] << "(" << result_scan[i] << ")" << std::setw(25) << res);
                                }
                                else
                                {
                                    sum =   sum +   1;
                                    logdbg( std::setw(74) << scan[t] << "(" << result_scan[t] << ")");
                                }
                                count++;
                            }
                        }
                        i = i + sum-1;
                        sum=0;
                        printed_port.push_back(scanip[i]);
                    }
                }
            }
        }
    }
    if(p == 2)
    {
        printed_port.erase (printed_port.begin(),printed_port.end());
    }
}

void ArgumentParsing::calculate_prefix(std::string ip)
{
    int i,k,l,m;
    char post[3];
    int pos,preRange,pos1;
    std::string ipPre, ipaddr;
    long double ip_num;
    if((pos = ip.find("/",0))>0)
    {
        ipPre        = ip.substr(0,pos);
        preRange = 32 - atoi(ip.substr(pos+1,ip.size()).c_str());
        ip_num     = (int)pow(2.0,preRange);
        
        pos1 = -1;
        switch(preRange)
        {
            case 32:
                for(i=0;i<256;i++)
                    for(k=0;k<256;k++)
                        for(l=0;l<256;l++)
                            for(m=0;m<256;m++)
                            {
                                sprintf(post,"%d.%d.%d.%d",i,k,l,m);
                                ipaddr=ipPre+"."+post;
                                ipAddress.push_back(ipaddr);
                                validate_ip(ipaddr);
                            }
                break;
            case  8:
                for( i=0;i<3;i++)
                {
                    pos1 = ip.find(".",pos1+1);
                }
                ipPre = ip.substr(0,pos1);
                for(i=0;i<256;i++)
                {
                    sprintf(post,"%d",i);
                    ipaddr=ipPre+"."+post;
                    ipAddress.push_back(ipaddr);
                    validate_ip(ipaddr);
                }
                break;
            case 16:
               for(i=0;i<2;i++)
                {
                    pos1 = ip.find(".",pos1+1);
                }
                ipPre = ip.substr(0,pos1);
                for(i=0; i < 256; i++)
                    for(k=0; k < 256; k++)
                    {
                        sprintf(post,"%d.%d",i,k);
                        ipaddr=ipPre+"."+post;
                        ipAddress.push_back(ipaddr);
                        validate_ip(ipaddr);
                    }
                break;
            case 24:
                for(i = 0; i < 1; i++)
                {
                    pos1 = ip.find(".",pos1+1);
                }
                ipPre = ip.substr(0,pos1);
                for(i = 0; i < 256; i++)
                    for(k = 0; k < 256; k++)
                        for(l = 0; l < 256; l++)
                        {
                            sprintf(post,"%d.%d.%d",i,k,l);
                            ipaddr=ipPre+"."+post;
                            ipAddress.push_back(ipaddr);
                            validate_ip(ipaddr);
                        }
                break;
            default:
                logdbg("   Invalid prefix. Please check the IP address ");
                break;
        }
    }
}

//Use the built-in IP header structure from ip.h and populate accordingly

void ArgumentParsing::parsing_args(int argc, char ** argv)
{
    int count=0;
    std::string arg;
    for(int i =0;  i < argc; i++)
    {
        if(strcmp(argv[i],"--ip")==0)
        {
            count = count+1;
        }
        if(strcmp(argv[i],"--ports")==0)
        {
            count=count+1;
        }
        if(strcmp(argv[i],"--scan")==0)
        {
            count=count+1;
        }
        if(strcmp(argv[i],"--file")==0)
        {
            count=count+1;
        }
    }
    if(count==3 || count>3)
    {
        for(int i=1;i<argc;i++)
        {
            arg = argv[i];
            if(arg.compare("--help")==0)
            {
                logdbg("--help <display invocation options>");
                logdbg("--ports <ports to scan>");
                logdbg("--ip <IP address to scan>");
                logdbg("--prefix <IP prefix to scan>");
                logdbg("--file <file name containing IP addresses to scan>");
                logdbg("--speedup <parallel threads to use>");
                logdbg("--scan <one or more scans>");
            }
            
            if(arg.compare("--ports")==0)
            {
                port = argv[i+1];
                int pos;
                int count=0;
                
                if((pos = port.find(",",0)) > 0)
                {
                    count++;
                    portNo = split(port, ',');
                }
                if((pos = port.find("-",0)) > 0)
                {
                    count++;
                    portRange = split(port, '-');
                    
                    int r1,r2;
                    
                    r1=atoi(portRange[0].c_str());
                    r2=atoi(portRange[1].c_str());
                    
                    for(int k=r1;k<(r2+1);k++)
                    {
                        std::stringstream ss;
                        ss << k;
                        std::string s= ss.str();
                        portNo.push_back(s);
                        
                    }
                }
                if(count==0)
                {
                    portNo.push_back(port);
                }
                
            }
            if(arg.compare("--ip")==0)
            {
                
                ipAddress.push_back(argv[i+1]);
                ip=argv[i+1];
                validate_ip(ip);
                
            }
            if(arg.compare("--prefix")==0)
            {
                prefix=argv[i+1];
                calculate_prefix(prefix);
            }
            if(arg.compare("--file")==0)
            {
                filename=argv[i+1];
                readFile(filename);
            }
            if(arg.compare("--speedup")==0)
            {
                speedup=argv[i+1];
                //Create the thread array
            }
            
            if(arg.compare("--scan")==0)
            {
                scan=argv[i+1];
                scanlist = split(scan, ',');
                
            }
        }
    }
    
    
    else
    {
        logdbg("Please enter an IP address, Port numbers and Scan Type ");
        logdbg("--help <display invocation options>");
        logdbg("--ports <ports to scan>");
        logdbg("--ip <IP address to scan>");
        logdbg("--prefix <IP prefix to scan>");
        logdbg("--file <file name containing IP addresses to scan>");
        logdbg("--speedup <parallel threads to use>");
        logdbg("--scan <one or more scans>");
    }
}

void ArgumentParsing::readFile(std::string file)
{
    std::ifstream infile(file.c_str());
    int pos;
    std::string line;
    
    while (getline(infile, line))
    {
        std::istringstream iss(line);
        int a;
        if (!(iss >> a)) { break; } // error
        //find prefix address in the file
        if((pos = line.find("/",0))>0)
        {
            calculate_prefix(line);
        }
        else
        {
            //       cout<<"ip address :"<<line<<endl;
            ipAddress.push_back(line);
            validate_ip(line);
        }
    }
}

//Generate the final checksum value



u_int16_t csum(unsigned short *pointer, int bytes )
{
    
    /* As per RFC 793 the checksum algorithm is:
     1's complement sum of the 16-bit values to be checksummed.
     If the length happens to be odd then 1 byte of 0 is appended to end of data.
     This is the generic checksum calculation function. bytes is the length
     */
    
    /*sum here is an accumulator (32bit). Just keep adding sequential 16 bit words and fold back the carry bits from top
     16 bits to lower bits */
    
    uint32_t sum = 0;   //might wanna make it of type register since it will change a lot.
    uint16_t check_sum=0;
    int bytes_left = bytes;
   
    while(bytes_left > 1)
    {
        sum += *pointer++;
        bytes_left -= 2;
    }
    
    
    /* Check for odd length. Pad remaining stuff */
    
    if ( bytes_left == 1)
    {
        check_sum=0;
        *((unsigned char *)&check_sum) = *(unsigned char *) pointer;
        sum += check_sum;
        
    }
    
    /* add carries to lower 16 bits */
    
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    
    
    check_sum = ~(sum); //negate
    pointer = NULL;
    return check_sum;
    
}


unsigned int generate_random_number(unsigned int modulus)
{
    //Use clock time to generate a random number between 0 and modulus
    srand(clock());
    unsigned int random_number = rand() % modulus;
    return random_number;
}


//Generate the final checksum value
unsigned short generate_tcp_checksum(iphdr *ip_header,
                                                                tcphdr *tcp_header,
                                                                u_int16_t length)
{
    tcp_pseudo_header pseudo_header;
    int packet_size;
    char *pseudo_packet=NULL;
    unsigned short check_sum;
    
    memset(&pseudo_header,0,sizeof(tcp_pseudo_header));
    
    //Populate the header with IP values
    //Source and destination addresses
    pseudo_header.source_address         = ip_header->saddr;
    pseudo_header.destination_address = ip_header->daddr;
    
    //Reserved bits all 0
    pseudo_header.reserved = 0;
    
    //protocol is TCP and length
    pseudo_header.protocol = IPPROTO_TCP;
    pseudo_header.tcp_segment_length = htons(length);
    
    packet_size = sizeof(tcp_pseudo_header) + length;
    
    //Calculate the checksum on combined packet
    pseudo_packet = new char [packet_size];
    memcpy(pseudo_packet, (char*)&pseudo_header, sizeof(tcp_pseudo_header));
    //finished adding IPv4 pseudo header, now add the actual tcp header
    memcpy(pseudo_packet + sizeof(tcp_pseudo_header), tcp_header, length);
    
    check_sum=csum((unsigned short*)pseudo_packet, packet_size);
    delete[] pseudo_packet;
    return check_sum;
}

unsigned short generate_udp_checksum(iphdr *ip_header,
                                                                 udphdr *udp_header,
                                                                 u_int16_t length)
{
    udp_pseudo_header pseudo_header;
    int packet_size;
    char *pseudo_packet;
    unsigned short check_sum;
    
    memset(&pseudo_header,0,sizeof(udp_pseudo_header));
    
    //Populate the header with IP values
    //Source and destination addresses
    pseudo_header.source_address = ip_header->saddr;
    pseudo_header.destination_address = ip_header->daddr;
    
    //Reserved bits all 0
    pseudo_header.reserved = 0;
    
    //protocol is UDP and length
    pseudo_header.protocol = IPPROTO_UDP;
    pseudo_header.udp_segment_length = htons(length);
    packet_size = sizeof(udp_pseudo_header) + length;
    
    //Calculate the checksum on combined packet
    pseudo_packet = new char [packet_size];
    memcpy(pseudo_packet, (char*)&pseudo_header,sizeof(udp_pseudo_header));
    //finished adding IPv4 pseudo header, now add the actual tcp header
    memcpy(pseudo_packet+sizeof(udp_pseudo_header), udp_header, length);
    
    check_sum=csum((unsigned short*)pseudo_packet, packet_size);
    delete[] pseudo_packet; //array
    return check_sum;
    
}

void dns_format_convert(unsigned char* dns,unsigned char* host) {
    int lock = 0 , i;
    strcat((char*)host,".");
    
    for(i = 0 ; i < strlen((char*)host) ; i++) {
        if(host[i]=='.') {
            *dns++ = i-lock;
            for(;lock<i;lock++) {
                *dns++=host[lock];
            }
            lock++; //or lock=i+1;
        }
    }
    *dns++='\0';
}






