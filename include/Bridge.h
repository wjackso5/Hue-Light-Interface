#ifndef BRIDGE_H_
#define BRIDGE_H_
#include <Wt/Dbo/Dbo>
#include <string>

namespace dbo=Wt::Dbo;

class Bridge{
	public:
	std::string name;
	std::string location;
	std::string ip;
	int bridgeNum;
	std::string userName;
  	template<class Action>
	void persist(Action& a)
	{
		dbo::field(a,name,"name");
		dbo::field(a,location,"location");
		dbo::field(a,ip,"ip");
		dbo::field(a,bridgeNum,"bridgeNum");
		dbo::field(a,userName,"userName");
	}

//	Bridge* createBridge(std::string name,std::string location,std::string ip,int bridgeNum,std::string userName);

	~Bridge();
	
	std::string getName();
	std::string getLocation();
	std::string getIp();
	int getNum();
	void setName(std::string name);
void setLocation(std::string location);
void setIp(std::string ip);
void setNum(int bridgeNum);
void setUsername(std::string userName);


		

	
	};






#endif//BRIDGE_H_
