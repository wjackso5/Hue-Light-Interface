/**  
* <h1>Bridge Model Class Header File</h1>
* used for creating and maintaining bridge objects
* @author  Yu Wu (Vivian)
*/
#ifndef BRIDGE_H_
#define BRIDGE_H_
#include <Wt/Dbo/Dbo>
#include <string>

namespace dbo=Wt::Dbo;

class Bridge{
	
	private:
	//vars
	std::string name;
	std::string location;
	std::string ip;
	std::string bridgeNum;
	std::string userName;
	
	public:
  	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a,name,"name");
		dbo::field(a,location,"location");
		dbo::field(a,ip,"ip");
		dbo::field(a,bridgeNum,"bridgeNum");
		dbo::field(a,userName,"userName");
	}

	//constructor and deconstructor
	Bridge();
	~Bridge();

	//getter and setters
	std::string getName();
	std::string getLocation();
	std::string getIp();
	std::string getPort();
	std::string getUsername();
	void setName(std::string name);
	void setLocation(std::string location);
	void setIp(std::string ip);
	void setPort(std::string bridgeNum);
	void setUsername(std::string userName);
	};

#endif//BRIDGE_H_
