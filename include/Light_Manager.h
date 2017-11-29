/* Light Manager Class
 *
 * Controller Class for Light, editing Lights, etc.
 *
 * FINISHED
 */

#ifndef LIGHT_MANAGER_H
#define LIGHT_MANAGER_H

/* FROM STL */
#include <string>
#include <vector>
#include <Wt/Http/Client>

/* LOCAL FILES */

#include "Light.h"
#include "LightGroup.h"
#include "Bridge.h"


class Light_Manager {
	private :
		//CLASS VARIABLES

		/*
		 * I chose to use a linked list instead of an array
		 * Since it's size needs to be dynamic and it's easy
		 * to work with. Might be a better data structure to
		 * implement here though.
		 */
		Bridge* bridge;
		std::string lightList;
		std::string groupList;
		std::vector<LightGroup *> *lightgrouplist;

		//PRIVATE METHODS
	


	public :
		//CONSTRUCTOR
		Light_Manager(Bridge* b);
		~Light_Manager();
		
		//PUBLIC METHODS
		bool getLights();
		bool getGroups();
		bool createGroup(std::string ids,std::string name);
		bool deleteGroup(std::string id);
		bool setGroupName(std::string id,std::string name);
		bool setGroupLights(std::string id,std::string name);
		bool setGroupState(std::string id,std::string statename,std::string state,int transitiontime);
		bool setGroupState(std::string id,std::string statename,bool state,int transitiontime);
		bool setLightName(std::string id,std::string name);
		bool setLightState(std::string id,std::string statename,std::string state,int transitiontime);
		bool setLightState(std::string id,std::string statename,bool state,int transitiontime);
		void handleLightResponse(boost::system::error_code err,const Wt::Http::Message& response);
		void handleGroupResponse(boost::system::error_code err,const Wt::Http::Message& response);
		bool setGroup();
		Bridge* getBridge();
		std::string	getLightList();
		std::string getGroupList();

};

#endif