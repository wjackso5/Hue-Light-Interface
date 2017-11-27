/**  
* <h1>Light Model Class Header File</h1>
* used for creating and maintaining Light objects and their states
* @author  William Jackson
*/
#ifndef LIGHT_H_
#define LIGHT_H_
#include <string>

class Light{
	private:
	//vars
	std::string name;
	std::string bridgeName;
	bool switch_;
	int brightness;
	int color;
	int transitionTime;
	int id;
	public:

	Light(int _id,std::string _name,bool state,int _brightness,int hue,std::string bridgename);
	~Light();
	//getters
	std::string getName();
	std::string getBridgeName();
	bool getSwitch();
	int getBrightness();
	int getColor();
	int getTransitionTime();
	std::string getState();
	int getId();
	//setters
	void setName(std::string n);
	void setBridgeName(std::string bn);
	void setSwitch(bool s);
	void setBrightness(int b);
	void setColor(int c);
	void setTransitionTime(int t);
	void setState(bool s, int b, int c);
	void setId(int id);
	};

#endif//LIGHT_H_
