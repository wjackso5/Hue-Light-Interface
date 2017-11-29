#include <string>

class Schedule {
        public :
		Schedule(std::string newTime, std::string newName, std::string newOn, std::string newBri, std::string newAddress, std::string newMethod);
		std::string time;
	        std::string name;
		std::string on; 
		std::string bri; 
		std::string address; 
		std::string method;
};

