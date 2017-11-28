/**  
* <h1>LightGroup Group Model Class Implementation File</h1>
* used for creating and maintaining LightGroup objects and their states
* @author  William Jackson
*/
#include <string>
#include <vector>
#include "Light.h"
#include "LightGroup.h"

/**
*constructor for LightGroup
*@param none
*@return none
*/
LightGroup::LightGroup(){}

/**
*deconstructor for LightGroup
*@param none
*@return none
*/
LightGroup::~LightGroup(){}

//getters
/**
*name getter method for LightGroup
*@param none
*@return std::string name
*/
std::string LightGroup::getName(){
	return name;
}

/**
*bridgeName getter method for LightGroup
*@param none
*@return std::string bridgeName
*/
std::string LightGroup::getBridgeName(){
	return  bridgeName;
}

/**
*switch getter method for LightGroup
*@param none
*@return bool switch_
*/
bool LightGroup::getSwitch(){
	return switch_;
}

/**
*brightness getter method for LightGroup
*@param none
*@return int brightness;
*/
int LightGroup::getBrightness(){
	return brightness;
}

/**
*switch getter method for transitionTime
*@param none
*@return int transitionTime
*/
int LightGroup::getTransitionTime(){
	return transitionTime;
}

/**
*color getter method for LightGroup
*@param none
*@return std::string color
*/
int LightGroup::getColor(){
	return color;
}

/**
*special getter that gets all info about this LightGroup object's 'state',  will stream-line interactions hueAPI
*@return state string (JSON with all the info about this LightGroup to be passed along the bridge)
*@param none
*/
std::string LightGroup::getState(){
	bool s = getSwitch();
	int b = getBrightness();
    int c = getColor();
    //might have to change the format of this but according to the HueAPI docs this is what a state looks like.
    std::string state = std::string("{\"on\": ") + std::to_string(s) + std::string(",\"bri\": ") + std::to_string(b) + std::string(",\"hue\": ") + std::string(std::to_string(c)) + std::string(",}");
	return state;
}
/**
*special getter that gets list of all lights in this lightgroup
*@return state string (JSON with all the info about this LightGroup to be passed along the bridge)
*@param none
*/
std::vector<Light> LightGroup::getList(){
	return list;
}
//setters
/**
*name setter method for LightGroup
*@param std:string name
*@return none
*/
void LightGroup::setName(std::string n){
	name=n;
}
/**
*bridgeName setter method for LightGroup
*@param std:string bn
*@return none
*/
void LightGroup::setBridgeName(std::string bn){
	bridgeName=bn;
}

/**
*switch_ setter method for LightGroup
*@param bool s
*@return none
*/
void LightGroup::setSwitch(bool s){
	switch_=s;
}

/**
*brightness setter method for LightGroup
*@param int b
*@return none
*/
void LightGroup::setBrightness(int b){
	brightness=b;
}

/**
*color setter method for LightGroup
*@param int c
*@return none
*/
void LightGroup::setColor(int c){
	color=c;
}

/**
*color setter method for LightGroup
*@param int t
*@return none
*/
void LightGroup::setTransitionTime(int t){
	transitionTime=t;
}

/**
*special setter that updates all info about this LightGroup objects 'state', will stream-line interactions hueAPI
*@param name
*@param bridgename
*@param switch_
*@param brightness
*@param color
*@param transitionTime
*@return none
*/
void LightGroup::setState(bool s, int b, int c){
	setSwitch(s);
	setBrightness(b);
	setColor(c);
}
/**
*add a light to the lightgroup.
*@param name
*@param bridgename
*@param switch_
*@param brightness
*@param color
*@param transitionTime
*@return none
*/
void LightGroup::addLight(int i){
	lightids.push_back(i);
}
/**
*removes a light from the light group.
*@param light
*@return none
*/
void LightGroup::removeLight(Light light){
	std::string name = light.getName();
	for (int i=0; i<list.size()-1; i++){
		if (list.at(i).getName()==name){
			list.erase(list.begin() + i);
		}
	}
}
/**
*updates the state of the actual lights in the group.
*@param none
*@return none
*/
void LightGroup::Update(){
	for (int i=0; i<list.size()-1; i++){
		list.at(i).setName(getName());
		list.at(i).setBridgeName(getBridgeName());
		list.at(i).setSwitch(getSwitch());
		list.at(i).setBrightness(getBrightness());
		list.at(i).setColor(getColor());
		list.at(i).setTransitionTime(getTransitionTime());
	}
}
