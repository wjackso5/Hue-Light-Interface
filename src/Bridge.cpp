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
	return Bridge::location;
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
	return bridgeNum;
}
//setters
/**
*name setter method for Bridge
*@param name
*@return none
*/
void Bridge::setName(std::string name){
	name=name;
}
/**
*location setter method for Bridge
*@param location
*@return none
*/
void Bridge::setLocation(std::string location){
	location=location;
}
/**
*ip setter method for Bridge
*@param name
*@return none
*/
void Bridge::setIp(std::string ip){
	ip=ip;
}
/**
*port setter method for Bridge
*@param port
*@return none
*/
void Bridge::setPort(std::string bridgeNum){
	bridgeNum=bridgeNum;
}
/**
*name setter method for Bridge
*@param username
*@return none
*/
void Bridge::setUsername(std::string userName){
	userName=userName;
}

