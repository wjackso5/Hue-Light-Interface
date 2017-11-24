/**  
* <h1>Bridge Model Class Implementation File</h1>
* used for creating and maintaining bridge objects
* @author  Yu Wu (Vivian)
*/
#include <string>
#include "Bridge.h"
#include <Wt/WApplication>

Bridge::~Bridge(){}

std::string Bridge::getName(){
	return name;
}
std::string Bridge::getLocation(){
	return Bridge::location;
}
std::string Bridge::getIp(){
	return ip;
}
int Bridge::getNum(){
	return bridgeNum;
}
void Bridge::setName(std::string name){
	name=name;
}
void Bridge::setLocation(std::string location){
	location=location;
}
void Bridge::setIp(std::string ip){
	ip=ip;
}
void Bridge::setNum(int bridgeNum){
	bridgeNum=bridgeNum;
}
void Bridge::setUsername(std::string userName){
	userName=userName;

}
