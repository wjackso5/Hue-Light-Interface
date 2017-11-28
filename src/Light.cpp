/**  
* <h1>Light Model Class Implementation File</h1>
* used for creating and maintaining Light objects and their states
* @author  William Jackson
*/
#include <string>
#include "Light.h"
#include <Wt/WApplication>

/**
*constructor for light
*@param none
*@return none
*/
Light::Light(){
}

/**
*deconstructor for light
*@param none
*@return none
*/
Light::~Light(){}

//getters
/**
*name getter method for light
*@param none
*@return std::string name
*/
std::string Light::getName(){
	return name;
}

/**
*bridgeName getter method for light
*@param none
*@return std::string bridgeName
*/
std::string Light::getBridgeName(){
	return  bridgeName;
}

/**
*switch getter method for light
*@param none
*@return bool switch_
*/
bool Light::getSwitch(){
	return switch_;
}

/**
*brightness getter method for light
*@param none
*@return int brightness;
*/
int Light::getBrightness(){
	return brightness;
}

/**
*switch getter method for transitionTime
*@param none
*@return int transitionTime
*/
int Light::getTransitionTime(){
	return transitionTime;
}

/**
*color getter method for light
*@param none
*@return std::string color
*/
int Light::getColor(){
	return color;
}
/**
*id getter method for light
*@param none
*@return int id
*/
int Light::getId(){
	return id;
}

/**
*special getter that gets all info about this light object's 'state',  will stream-line interactions hueAPI
*@return state string (JSON with all the info about this light to be passed along the bridge)
*@param none
*/
std::string Light::getState(){
	bool s = getSwitch();
	int b = getBrightness();
    int c = getColor();
    //might have to change the format of this but according to the HueAPI docs this is what a state looks like.
    std::string state = std::string("{\"on\": ") + std::to_string(s) + std::string(",\"bri\": ") + std::to_string(b) + std::string(",\"hue\": ") + std::string(std::to_string(c)) + std::string(",}");
	return state;
}
//setters
/**
*name setter method for light
*@param std:string name
*@return none
*/
void Light::setName(std::string n){
	name=n;
}

/**
*bridgeName setter method for light
*@param std:string bn
*@return none
*/
void Light::setBridgeName(std::string bn){
	bridgeName=bn;
}

/**
*switch_ setter method for light
*@param bool s
*@return none
*/
void Light::setSwitch(bool s){
	switch_=s;
}

/**
*brightness setter method for light
*@param int b
*@return none
*/
void Light::setBrightness(int b){
	brightness=b;
}

/**
*color setter method for light
*@param int c
*@return none
*/
void Light::setColor(int c){
	color=c;
}

/**
*color setter method for light
*@param int t
*@return none
*/
void Light::setTransitionTime(int t){
	transitionTime=t;
}

/**
*color setter method for light
*@param int t
*@return none
*/
void Light::setId(int t){
	id=t;
}
/**
*special setter that updates all info about this light objects 'state', will stream-line interactions hueAPI
*@param name
*@param bridgename
*@param switch_
*@param brightness
*@param color
*@param transitionTime
*@return none
*/
void Light::setState(bool s, int b, int c){
	setSwitch(s);
	setBrightness(b);
	setColor(c);
}