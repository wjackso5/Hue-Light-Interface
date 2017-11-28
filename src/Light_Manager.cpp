/* Light Manager Class
 *
 * Controller Class for Light, editing Lights, etc.
 *
 * FINISHED
 */


/* FROM STL */
#include <string>
#include <vector>

#include <Wt/WApplication>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
/* LOCAL FILES */
#include "Light_Manager.h"
#include "Light.h"
#include "LightGroup.h"
#include "Schedule.h"



		Light_Manager::Light_Manager(Bridge *b)
		{
			bridge=b;
			lightList = new std::vector<Light *>();
			getLights();
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
			if(httpC->get("https://gentle-forest-89278.herokuapp.com/api/lights")){
				Wt::log("LIGHT")<<"in if";
				Wt::WApplication::instance()->deferRendering();
				return true;
			}
			Wt::log("LIGHT")<<"after if";
			free(httpC);
			return false;
		}

		bool Light_Manager::getGroups(){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::string url;
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			url = "http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/groups";
			if(httpC->get(url)){
				Wt::WApplication::instance()->deferRendering();
				return true;
			}
			free(httpC);
			return false;
		}
		
		bool Light_Manager::setLightName(std::string id,std::string name){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::string body="{\"name\" : \""+name+"\"}";
			std::string url;
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

		bool Light_Manager::setLightState(std::string id,std::string statename,std::string state){
			Wt::Http::Client *httpC = new Wt::Http::Client;
			std::string body="{\"+statename+\" : "+ state+"}";
			std::string url;
			Wt::Http::Message *message=new Wt::Http::Message();
			message->setHeader("Content-type","application/Json");
			message->addBodyText(body);
			httpC->done().connect(boost::bind(&Light_Manager::handleLightResponse,this,_1,_2));
			url="http://" + bridge->ip + ':' + bridge->port + "/api/"+bridge->username+"/lights/"+id+"/state";
			if(httpC->put(url,*message)){
				Wt::WApplication::instance()->deferRendering();
				return true;
			}
			return false;
		}

		// bool createGroup(std::string ids,std::string name,){

		// }

		bool setGroup(){}

		void Light_Manager::handleLightResponse(boost::system::error_code err,const Wt::Http::Message& response)
		{
			Wt::WApplication::instance()->resumeRendering();
			Wt::log("HANDLE")<<"HANDLING LIGHT LISTS";
			if (!err && response.status() == 200) {
				const std::string &input = response.body();
				Wt::log("LIGHTINFO") << input;
				//Wt::Json::Value *jval = new Wt::Json::Value();
				//Wt::Json::Value &jvalref = jval; 
				Wt::Json::Object ob;
				Wt::Json::parse(input,ob,false);
				int size=ob.size();
				for (int i=0;i<size;i++){

					Wt::Json::Object val=ob.get(std::to_string(i+1));
					std::string light_name=val.get("name").toString().orIfNull("name:(((");
					Wt::Json::Object states=val.get("state");	
					bool isOn=states.get("on").toBool().orIfNull(false);
					int light_brightness=states.get("bri").toNumber().orIfNull(-11111);
					int light_hue=states.get("hue").toNumber().orIfNull(-222222);
					Light *l = new Light(i+1,light_name,isOn,light_brightness,light_hue,bridge->username);
					Wt::log("LIGHTINFO") << l->getName();
					lightList->push_back(new Light(i+1,light_name,isOn,light_brightness,light_hue,bridge->username));
					Wt::log("LIGHTINFO") << "PUSHED TO BACK OF LIGHTLIST";
					/*on,bri,*/
				}
			}
   		}

  //  		void Light_Manager::handleGroupResponse(boost::system::error_code err,const Wt::Http::Message& response)
		// {
		// 	Wt::log("HANDLE")<<"HANDLING GROUOP LISTS";
		// 	if (!err && response.status() == 200) {
		// 		const std::string &input = response.body();
		// 		Wt::log("LIGHTINFO") << input;
		// 		Wt::Json::Object ob;
		// 		int size=ob.size();
		// 		for (int i=0;i<size;i++){
		// 			Wt::Json::Value val=ob.get(std::to_string(i+1));
		// 			std::string light_name=val.get("name");
		// 			Wt::Json::Value states=val.get("state");
		// 			boolean isOn=states.get("on");
		// 			int light_brightness=states.get("bri");
		// 			int light_hue=states.get("hue");
		// 			Light *l=new Light(i+1,light_name,isOn,light_brightness,light_hue);
		// 			lightlist.push(l);
		// 			/*on,bri,*/
		// 		}

				
		// 	}
  //  		}

   		Bridge* Light_Manager::getBridge()
   		{
   			return bridge;
   		}
   		/**
   		*gets the lightlist
   		*@param none
   		*@return lightList
   		*/
   		std::vector<Light*>* Light_Manager::getLightList(){
   			return lightList;
   		}




		
