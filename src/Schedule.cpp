/**  
* <h1>Schedule Model Class Implementation File</h1>
* used for creating and maintaining Schedule objects and their states
* @author  William Jackson
*/
#include <string>
#include "Light.h"
#include "Schedule.h"

/**
*constructor for Schedule
*@param none
*@return none
*/
Schedule::Schedule(){}

/**
*deconstructor for Schedule
*@param none
*@return none
*/
Schedule::~Schedule(){}

//getters
/**
*name getter method for Schedule
*@param none
*@return std::string name
*/
std::string Schedule::getName(){
	return name;
}

/**
*switch getter method for Schedule
*@param none
*@return bool switch_
*/
bool Schedule::getSwitch(){
	return switch_;
}

/**
*brightness getter method for Schedule
*@param none
*@return int brightness;
*/
int Schedule::getBrightness(){
	return brightness;
}

/**
*switch getter method for transitionTime
*@param none
*@return int delayTime
*/
int Schedule::getDelayTime(){
	return delayTime;
}

/**
*color getter method for Schedule
*@param none
*@return std::string color
*/
int Schedule::getColor(){
	return color;
}

/**
*special getter that gets all info about this Schedule object's 'state',  will stream-line interactions hueAPI
*@return state string (JSON with all the info about this Schedule to be passed along the bridge)
*@param none
*/
std::string Schedule::getState(){
	bool s = getSwitch();
	int b = getBrightness();
    int c = getColor();
    //might have to change the format of this but according to the HueAPI docs this is what a state looks like.
    std::string state = std::string("{\"on\": ") + std::to_string(s) + std::string(",\"bri\": ") + std::to_string(b) + std::string(",\"hue\": ") + std::string(std::to_string(c)) + std::string(",}");
	return state;
}
/**
*special getter that gets list of all lights in this Schedule
*@return state string (JSON with all the info about this Schedule to be passed along the bridge)
*@param none
*/
Light Schedule::getLight(){
	return light;
}

//setters

/**
*name setter method for Schedule
*@param std:string name
*@return none
*/
void Schedule::setName(std::string n){
	name=n;
}

/**
*switch_ setter method for Schedule
*@param bool s
*@return none
*/
void Schedule::setSwitch(bool s){
	switch_=s;
}

/**
*brightness setter method for Schedule
*@param int b
*@return none
*/
void Schedule::setBrightness(int b){
	brightness=b;
}

/**
*color setter method for Schedule
*@param int c
*@return none
*/
void Schedule::setColor(int c){
	color=c;
}

/**
*delayTime setter method for Schedule
*@param int t
*@return none
*/
void Schedule::setDelayTime(int t){
	delayTime=t;
}

/**
*special setter that updates all info about this Schedule objects 'state', will stream-line interactions hueAPI
*@param switch_
*@param brightness
*@param color
*@return none
*/
void Schedule::setState(bool s, int b, int c){
	setSwitch(s);
	setBrightness(b);
	setColor(c);
}
/**
*add a light to the Schedule.
*@param light
*@return none
*/
void Schedule::setLight(Light l){
	light = l;
}

/**
*Called after delay time has occured.
*@param none
*@return none
*/
void Schedule::Execute(){
		//update the light
		light.setName(getName());
		light.setSwitch(getSwitch());
		light.setBrightness(getBrightness());
		light.setColor(getColor());
	
}
