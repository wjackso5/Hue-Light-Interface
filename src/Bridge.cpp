/**  
* <h1>Bridge Model Class Implementation File</h1>
* used for creating and maintaining bridge objects
* @author  Yu Wu (Vivian)
*/
#include <string>
#include "Bridge.h"

/**
*constructor for LightGroup
*@param none
*@return none
*/
Bridge::Bridge(){}
/**
*deconstructor for LightGroup
*@param none
*@return none
*/
Bridge::~Bridge(){}

//getters
/**
*name getter method for Bridge
*@param none
*@return std::string name
*/
std::string Bridge::getName(){
	return name;
}
/**
*location getter method for bridge
*@param none
*@return std::string location
*/
std::string Bridge::getLocation(){
	return location;
}
/**
*Ip getter method for Bridge
*@param none
*@return std::string ip
*/
std::string Bridge::getIp(){
	return ip;
}

/**
*port getter method for Bridge
*@param none
*@return std::string port
*/
std::string Bridge::getPort(){
	return port;
}
/**
*port getter method for Bridge
*@param none
*@return std::string port
*/
std::string Bridge::getUsername(){
	return username;
}
//setters
/**
*name setter method for Bridge
*@param name
*@return none
*/
void Bridge::setName(std::string _name){
	name=_name;
}
/**
*location setter method for Bridge
*@param location
*@return none
*/
void Bridge::setLocation(std::string _location){
	location=_location;
}
/**
*ip setter method for Bridge
*@param name
*@return none
*/
void Bridge::setIp(std::string _ip){
	ip=_ip;
}
/**
*port setter method for Bridge
*@param port
*@return none
*/
void Bridge::setPort(std::string port){
	port=port;
}
/**
*name setter method for Bridge
*@param username
*@return none
*/
void Bridge::setUsername(std::string _username){
	username=_username;
}

