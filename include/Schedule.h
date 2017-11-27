/**  
* <h1>Schedule Model Class Header File</h1>
* used for creating and maintaining Schedule objects and their states
* @author  William Jackson
*/
#ifndef Schedule_H_
#define Schedule_H_
#include <string>
#include "Light.h"

class Schedule{
	private:
	//vars
    // Light light;
	std::string name;
	bool switch_;
	int brightness;
	int color;
	int delayTime;
	public:
	Schedule();
	~Schedule();
	//getters
	// Light getLight();
	std::string getName();
	bool getSwitch();
	int getBrightness();
	int getColor();
	int getDelayTime();
	std::string getState();
	//setters
	void setName(std::string n);
	void setSwitch(bool s);
	void setBrightness(int b);
	void setColor(int c);
	void setDelayTime(int t);
	void setState(bool s, int b, int c);
	// void setLight(Light l);
	// void Execute();
	};

#endif//Schedule_H_
