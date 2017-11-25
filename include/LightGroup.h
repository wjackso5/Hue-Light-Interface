/**  
* <h1>LightGroup Model Class Header File</h1>
* used for creating and maintaining LightGroup objects and their states
* @author  William Jackson
*/
#ifndef LightGroup_H_
#define LightGroup_H_
#include <string>
#include <vector>
#include "Light.h"

class LightGroup{
	private:
	//vars
	std::vector<Light> list;
	std::string name;
	std::string bridgeName;
	bool switch_;
	int brightness;
	int color;
	int transitionTime;
	public:
	LightGroup();
	~LightGroup();
	//getters
	std::string getName();
	std::string getBridgeName();
	bool getSwitch();
	int getBrightness();
	int getColor();
	int getTransitionTime();
	std::string getState();
	//setters
	void setName(std::string n);
	void setBridgeName(std::string bn);
	void setSwitch(bool s);
	void setBrightness(int b);
	void setColor(int c);
	void setTransitionTime(int t);
	void setState(bool s, int b, int c);
	void addLight(Light l);
	void removeLight(Light l);
	void Update();
	};

#endif//LightGroup_H_
