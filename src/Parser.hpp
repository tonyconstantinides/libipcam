//
//  Parser.hpp
//  ipcam
//
//  Created by Tony Constantinides on 5/30/16.1
//

#ifndef Parser_hpp
#define Parser_hpp

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "TinyXml2.hpp"

class UPnPParser
{
public:
    UPnPParser(const std::string&);
    std::map<std::string, tinyxml2::XMLElement*> parse_description();
    std::vector<std::pair<std::string, std::string>> get_device_info();
    
private:
    tinyxml2::XMLElement* parse(tinyxml2::XMLElement*, std::string, std::string);
    
    tinyxml2::XMLDocument igd_xml;
    tinyxml2::XMLElement *InternetGatewayDevice;
    tinyxml2::XMLElement *WANDevice;
    tinyxml2::XMLElement *WANConnectionDevice;
    tinyxml2::XMLElement *WANIPConnection;
};
#endif /* Parser_hpp */
