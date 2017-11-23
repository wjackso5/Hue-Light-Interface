// #include <Wt/WDateTime>
// #include <Wt/Dbo/Types>
// #include <Wt/Dbo/WtSqlTraits>
#include <string>
#include "Bridge.h"
#include <Wt/WApplication>
// #include "LightController.h"

//Bridge* Bridge::createBridge(std::string _name,std::string _location,std::string _ip,int _bridgeNum,std::string _userName){
//	name=_name;
//	location=_location;
//	ip=_ip;
//	bridgeNum=_bridgeNum;
//	userName=_userName;
//	Wt::log("info") <<"Construstor: "+name;
//}
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
std::string Bridge::getPort(){
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
void Bridge::setPort(std::string bridgeNum){
	bridgeNum=bridgeNum;
}
void Bridge::setUsername(std::string userName){
	userName=userName;

}


// void Bridge::addBridge(std::string name,std::string location,std::string ip,int bridgeNum){

// }

// void Bridge::editBridge(std::string name,std::string location,std::string ip,int bridgeNum){
// 	name=name;
// 	location=location;
// 	ip=ip;
// 	bridgeNum=bridgeNum;
// }

// bool Bridge::validityCheck(std::string ipOrHost, std::string port, std::string user) {
//         Wt::Http::Client *httpC = new Wt::Http::Client;

//         std::string url;
//         url = "http://" + ipOrHost + ':' + port + "/api/" + user;

//         return httpC->get(url);
// }

// //Without username
// bool Bridge::validityCheck(std::string ipOrHost, std::string port) {
//         Wt::Http::Client *httpC = new Wt::Http::Client;

//         std::string url;
//         url = "http://" + ipOrHost + ':' + port + "/api/newdeveloper";

//         return httpC->get(url);
// }
