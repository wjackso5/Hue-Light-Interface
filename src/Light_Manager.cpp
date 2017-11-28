/* Light Manager Class
 *
 * Controller Class for Light, editing Lights, etc.
 *
 * FINISHED
 */


/* FROM STL */
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <Wt/WApplication>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Array>
#include <Wt/Json/Serializer>
// #include <Wt/Json/Serialize>

/* LOCAL FILES */
#include "Light_Manager.h"
#include "Light.h"
#include "LightGroup.h"
#include "Schedule.h"



		Light_Manager::Light_Manager(Bridge *b)
		{
			bridge=b;
			// lightList = new std::vector<Light *>();
			getLights();
			getGroups();
		}

		Light_Manager::~Light_Manager()
		{
			free(bridge);
		}

		//PUBLIC METHODS
		bool Light_Manager::getLights(){

			Wt::log("LIGHT")<<"In get Lights";
			Wt::Http::Client *httpC = new Wt::Http::Client;
			Wt::log("LIGHT")<<"made http client";
			std::string url;
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			Wt::log("LIGHT")<<"boost::bind";
			url = "http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/lights";
			if(httpC->get(url)){
				Wt::log("LIGHT")<<"in if";
				return true;
			}

			Wt::log("LIGHT")<<"after if";
 

			return false;
		}

		bool Light_Manager::getGroups(){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::string url;
			httpC->done().connect(boost::bind(&Light_Manager::handleGroupResponse,this,_1,_2));
			url = "http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/groups";
			if(httpC->get(url)){
				return true;
			}
			free(httpC);
			return false;
		}
		
		bool Light_Manager::setLightName(std::string id,std::string name){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::string body="{\"name\" : \""+name+"\"}";
			std::string url;
			std::cout << body;
			Wt::Http::Message *message=new Wt::Http::Message();
			message->addBodyText(body);
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			url="http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/lights/"+id;
			if(httpC->put(url,*message)){
				Wt::WApplication::instance()->deferRendering();
				return true;
			}
			free(httpC);
			return false;
		}

		bool Light_Manager::setLightState(std::string id,std::string statename,std::string state,int transitiontime){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::stringstream ss;
			ss<<"{"<<"\""<<statename<<"\" : "<<state<<" , \"transitiontime\" : "<<transitiontime<<"}"<<std::endl;
			std::string body=ss.str();
			std::string url;
			Wt::Http::Message *message=new Wt::Http::Message();
			message->setHeader("Content-type","application/Json");
			message->addBodyText(body);
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			url="http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/lights/"+id+"/state";
			Wt::log("SET LIGHT::: url") << url;
			if(httpC->put(url,*message)){
				return true;
			}
			return false;
		}
		bool Light_Manager::setLightState(std::string id,std::string statename,bool state,int transitiontime){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::stringstream ss;
			ss<<"{"<<"\""<<statename<<"\" : "<<state<<" , \"transitiontime\" : "<<transitiontime<<"}"<<std::endl;
			std::string body=ss.str();
			std::string url;
			Wt::Http::Message *message=new Wt::Http::Message();
			message->setHeader("Content-type","application/Json");
			message->addBodyText(body);
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			url="http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/lights/"+id+"/state";
			Wt::log("SET LIGHT::: url") << url;
			if(httpC->put(url,*message)){
				Wt::WApplication::instance()->deferRendering();
				return true;
			}
			return false;
		}

	
		bool Light_Manager::createGroup(std::string ids,std::string name){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			//parsing the light ids
			Wt::Json::Array vect;
			std::stringstream ss(ids);
			int i;
			 while (ss >> i)
    		{
        		vect.push_back(Wt::Json::Value(i));

        		if (ss.peek() == ',')
            		ss.ignore();
    		}
    		Wt::Json::Object ob=Wt::Json::Object();
    		Wt::Json::Value lists=Wt::Json::Value(vect);
    		ob["lights"]=lists;
			ob["name"]=Wt::Json::Value(name);
			// ss<<"{"<<"\" lights \" : "<<vect<<" , \"name\" : "<<name<<"}"<<std::endl;
			std::string body=Wt::Json::serialize(ob);
			Wt::log("CREATEGROUPBODY")<<body;
			std::string url = "http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/groups";
			Wt::Http::Message *message=new Wt::Http::Message();
			message->setHeader("Content-type","application/Json");
			message->addBodyText(body);
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			if(httpC->post(url,*message)){
				Wt::log("CREATEGROUPPOST")<<"WORKED";
				// Wt::WApplication::instance()->deferRendering();
				return true;
			}
			return false;
		}
		bool Light_Manager::deleteGroup(std::string id){
			std::string url = "http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/groups/"+id;
			Wt::Http::Message *message=new Wt::Http::Message();
			message->setHeader("Content-type","application/Json");
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			if(httpC->deleteRequest(url,*message)){
				Wt::log("DELETEGROUP")<<"WORKED";
				// Wt::WApplication::instance()->deferRendering();
				return true;
			}
			return false;

		}
		bool Light_Manager::setGroup(){}

		void Light_Manager::handleLightResponse(boost::system::error_code err,const Wt::Http::Message& response)
		{
			// Wt::WApplication::instance()->resumeRendering();
			Wt::log("HANDLE")<<"HANDLING LIGHT LISTS";
			if (!err && response.status() == 200) {
				const std::string &input = response.body();
				lightList=input;	
				//Wt::Json::Value *jval = new Wt::Json::Value();
				//Wt::Json::Value &jvalref = jval; 
				// Wt::Json::Object ob;
				// Wt::Json::parse(input,ob,false);
				// int size=ob.size();
				// for (int i=0;i<size;i++){

				// 	Wt::Json::Object val=ob.get(std::to_string(i+1));
				// 	std::string light_name=val.get("name").toString().orIfNull("name:(((");
				// 	Wt::Json::Object states=val.get("state");	
				// 	bool isOn=states.get("on").toBool().orIfNull(false);
				// 	int light_brightness=states.get("bri").toNumber().orIfNull(-11111);
				// 	int light_hue=states.get("hue").toNumber().orIfNull(-222222);
// <<<<<<< HEAD
// 					Light *l = new Light(i+1,light_name,isOn,light_brightness,light_hue,bridge->username);
// 					Wt::log("LIGHTINFO") << l->getName();
// 					lightList->push_back(new Light(i+1,light_name,isOn,light_brightness,light_hue,bridge->username));

// =======
					// lightList.push_back(new Light());
  			// 		lightList.back()->setId(i+1);
					// lightList.back()->setName(light_name);
					// lightList.back()->setSwitch(isOn);
					// lightList.back()->setBrightness(light_brightness);
					// lightList.back()->setColor(light_hue);

				}
		}
   		

   		void Light_Manager::handleGroupResponse(boost::system::error_code err,const Wt::Http::Message& response)
		{
			Wt::log("HANDLE")<<"HANDLING GROUP LISTS";
			if (!err && response.status() == 200) {
				const std::string &input = response.body();
				groupList=input;	
			// Wt::log("HANDLE")<<"HANDLING GROUOP LISTS";
			// if (!err && response.status() == 200) {
			// 	const std::string &input = response.body();
			// 	lightList=input;
			// 	Wt::Json::Object ob;
  	// 			Wt::Json::parse(input,ob,false);
			// 	int size=ob.size();
			// 	for (int i=0;i<size;i++){
			// 		Wt::Json::Value val=ob.get(std::to_string(i+1));
			// 	    std::string group_name=val.get("name");
			// 	    Wt::Json::Object actions=val.get("action");
			// 	    Wt::Json::Array& lights=val.get("lights");
			// 	    boolean isOn=states.get("on");
			// 	    int light_brightness=states.get("bri");
			// 	    int light_hue=states.get("hue");
			// 	}
			// }
			}
		}

   		Bridge* Light_Manager::getBridge()
   		{
   			return bridge;
   		}

   		/**
   		*gets the lightlist
   		*@param none
   		*@return lightList
   		*/
   		std::string Light_Manager::getLightList(){
   			return lightList;
   		}

   		std::string Light_Manager::getGroupList(){
   			Wt::log("SHOWGROUP=LM")<<groupList;
   			return groupList;
   		}





		
