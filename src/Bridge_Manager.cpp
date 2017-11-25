/*
 * Implementation File (.cpp) for the Bridge Class
 *
 * NOT FINISHED
 */
#include <Wt/WApplication>
#include <vector>
#include "Bridge_Manager.h"


//CONSTRUCTOR
Bridge_Manager::Bridge_Manager(Session *s) {
	session_=s;
	session_->initBM(&bridgeList);
}
Bridge_Manager::~Bridge_Manager(){}

//PRIVATE METHODS
/* findBridge method
 *
 * Input: string bridgeName
 * Output: Bridge if the Bridge is in the list return the
 * "The Bridge we are looking for", returns NULL otherwise
 */
int Bridge_Manager::findBridge(std::string bridgeName) {
	/* I think we can do without this line, as
	 * list.end() returns an iterator of the elements
	 * beginning after the last element (i.e. an Empty
	 * List) So the condition of the while loop should
	 * prevent us from trying to access an element of
	 * an empty list.

	if (bridgeList.empty() == true) return NULL;

	*/

	 //Create an iterator over
	for(int i=0;i<bridgeList.size();i++)
	        //The bridgeList
	{
		if(bridgeList.at(i).getName().compare(bridgeName)==0)
			{return i;}
	}

	return -1; //If we reach this line the Bridge is not a member of the
}

//PUBLIC METHODS
//Note: addBridge is overloaded.

/* addBridge method (without username)
 *
 * Input: name, location, IP address or Hostname, port number of the new  Bridge
 * and the username of the person adding the Bridge.
 * Output: Return true if we are succesful in adding the bridge, false otherwise
 */
bool Bridge_Manager::addBridge(std::string name_, std::string location_, std::string ipAddressOrHostname_, std::string portNumber_, std::string userName_){
	 //Initialize the
	Wt::log("info") <<"name of addBridge:"+name_;
	//Try creating the Bridge and adding it to the bridgeList.
	if (findBridge(name_)<0) {
		Wt::log("info") << "This bridge doesnt exist yet, so we will create it";
		//newBridge =createBridge(name, location, ipAddressOrHostname, portNumber, userName);
    if (validityCheck(ipAddressOrHostname_, portNumber_) > 0) {
      newBridge=new Bridge();
  		newBridge->name=name_;
  		newBridge->location=location_;
  		newBridge->ip=ipAddressOrHostname_;
  		newBridge->bridgeNum=portNumber_;
  		newBridge->userName=userName_;
  		//Wt::log("info") <<"God SAVE US";
  		bridgeList.push_back(*newBridge);
  		Wt::log("info") <<newBridge->name;
  		session_->addBridge(newBridge);
      return true;
    }

  }
	/* Note that We add the new Bridge to the front of the list because it's
	 * likely we may do something else with this Bridge shortly after addin
	 * g it.
	 */

	/* If we reach the else statement, there was a problem adding the Bridge
	 * (Either it could not be created or it could not be added to the
	 * bridgeList).
	 */
	else return false;

}

/* addBridge method (without username)
 *
 * Input: name, location, IP address or Hostname, port number of the Bridge
 * Output: Return true if we are succesful in adding the bridge, false otherwise
 *
 * For commments see addBridge with username
 */

	/* Note that We add the new Bridge to the front of the list because it's
	 * likely we may do something else with this Bridge shortly after addin
	 * g it.
	 */

	/* If we reach the else statement, there was a problem adding the Bridge
	 * (Either it could not be created or it could not be added to the
	 * bridgeList).
	 */
bool Bridge_Manager::deleteBridge(std::string name){
	int index=findBridge(name);//Initialize the Bridge

	//Try creating the Bridge and adding it to the bridgeList.
	if (findBridge(name)>=0) {
		bridgeList.erase(bridgeList.begin()+index);
		return true;}




	/* Note that We add the new Bridge to the front of the list because it's
	 * likely we may do something else with this Bridge shortly after addin
	 * g it.
	 */

	/* If we reach the else statement, there was a problem adding the Bridge
	 * (Either it could not be created or it could not be added to the
	 * bridgeList).
	 */
	else return false;

}

bool Bridge_Manager::editBridge(std::string name, std::string location, std::string ipAddressOrHostname, std::string portNumber, std::string userName) {
	if (findBridge(name)>=0){
	Bridge tBC=bridgeList.at(findBridge(name));
	tBC.setName(name);
	tBC.setLocation(location);
	tBC.setIp(ipAddressOrHostname);
	tBC.setPort(portNumber);
	tBC.setUsername(userName);
	return true;
	}else{
	return false;
	}

}

bool Bridge_Manager::validityCheck(std::string ipOrHost, std::string port, std::string user) {
        Wt::Http::Client *httpC = new Wt::Http::Client;

        std::string url;
        url = "http://" + ipOrHost + ':' + port + "/api/" + user;

        return httpC->get(url);
}

//Without username
bool Bridge_Manager::validityCheck(std::string ipOrHost, std::string port) {
        Wt::Http::Client *httpC = new Wt::Http::Client;

        std::string url;
        url = "http://" + ipOrHost + ':' + port + "/api/newdeveloper";
        //Wt::log("austintest") << httpC->get(url);

        return httpC->get(url);
}
std::vector<Bridge> Bridge_Manager::getBridgeList(){
	return bridgeList;
}