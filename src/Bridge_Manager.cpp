/*
 * Implementation File (.cpp) for the Bridge Class
 *
 * NOT FINISHED
 */
#include <Wt/WApplication>
#include <vector>
#include "Bridge_Manager.h"
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/Json/Object>//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

//CONSTRUCTOR
Bridge_Manager::Bridge_Manager(DBSession *s) {
	session_=s;
	bridgeList = new std::vector<Bridge *>();
	session_->initBM(bridgeList);
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

	if (bridgeList->empty() == true) return NULL;

	*/

	 //Create an iterator over
	for(int i=0;i<bridgeList->size();i++)
	        //The bridgeList
	{
		if(bridgeList->at(i)->getName().compare(bridgeName)==0)
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
	//Try creating the Bridge and adding it to the bridgeList->
	if (findBridge(name_)<0) {
		Wt::log("info") << "This bridge doesnt exist yet, so we will create it";
		//newBridge =createBridge(name, location, ipAddressOrHostname, portNumber, userName);
    if (validityCheck(ipAddressOrHostname_, portNumber_) > 0) {
	    Wt::log("info") << "The validity check was succesfull";
	    bridgeList->push_back(new Bridge());
  		bridgeList->back()->name=name_;
		bridgeList->back()->location=location_;
		bridgeList->back()->ip=ipAddressOrHostname_;
		bridgeList->back()->port=portNumber_;
		bridgeList->back()->username=userName_;
		/*
  		newBridge->location=location_;
  		newBridge->ip=ipAddressOrHostname_;
  		newBridge->port=portNumber_;
  		newBridge->username=userName_;
  		bridgeList->push_back(&newBridge);
		*/
		session_->addBridge(bridgeList->back());
		
      return true;
    }

  }
	/* Note that We add the new Bridge to the front of the list because it's
	 * likely we may do something else with this Bridge shortly after addin
	 * g it.
	 */

	/* If we reach the else statement, there was a problem adding the Bridge
	 * (Either it could not be created or it could not be added to the
	 * bridgeList->.
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
	 * bridgeList->.
	 */
bool Bridge_Manager::deleteBridge(std::string name){
	int index=findBridge(name);//Initialize the Bridge

	//Try creating the Bridge and adding it to the bridgeList->
	if (findBridge(name)>=0) {
		Bridge* tBD=bridgeList->at(findBridge(name));
		bridgeList->erase(bridgeList->begin()+index);
		session_->deleteBridge(tBD);
		return true;}




	/* Note that We add the new Bridge to the front of the list because it's
	 * likely we may do something else with this Bridge shortly after addin
	 * g it.
	 */

	/* If we reach the else statement, there was a problem adding the Bridge
	 * (Either it could not be created or it could not be added to the
	 * bridgeList->.
	 */
	else return false;

}

bool Bridge_Manager::editBridge(std::string name, std::string location, std::string ipAddressOrHostname, std::string portNumber, std::string userName) {
	if (findBridge(name)>=0){
	Bridge* tBC=bridgeList->at(findBridge(name));
	tBC->setLocation(location);
	tBC->setIp(ipAddressOrHostname);
	tBC->setPort(portNumber);
	tBC->setUsername(userName);
	//DEBUG
	Wt::log("info") << tBC->getLocation();
	//DEBUG
	session_->editBridge(tBC);
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
        Wt::Http::Client *httpC = new Wt::Http::Client();
		/*
   		httpC->setMaximumResponseSize(0);
		*/
   		Wt::log("HANDLE")<<"BEFORE SET DONE";
        httpC->done().connect(boost::bind(&Bridge_Manager::handleHttpResponse,this,_1,_2));
        Wt::log("HANDLE")<<"AFTER SET DONE";

		std::string url;
        url = "http://" + ipOrHost + ':' + port + "/api/newdeveloper/lights/1";
        // Wt::log("austintest") << httpC->get(url);
		if(httpC->get("http://0.0.0.0:8000/api/newdeveloper/lights/1")){
				Wt::log("HANDLE")<<"WHAT";
				/*
				Wt::WApplication::instance()->deferRendering();
				*/
		}
		else{
			return false;
		}
		return true;
	}


void Bridge_Manager::handleHttpResponse(boost::system::error_code err,const Wt::Http::Message& response)
{
	/*
	Wt::WApplication::instance()->resumeRendering();
	*/
	Wt::log("HANDLE")<<"CALLED HANDLE";
	if (!err && response.status() == 200) {
	const std::string &input = response.body();
	Wt::log("HANDLE") << input;
	//Wt::Json::Value *jval = new Wt::Json::Value();
	//Wt::Json::Value &jvalref = jval; 
	Wt::Json::Object ob;
	Wt::Json::parse(input,ob,false);
	Wt::Json::Value val=ob.get("name");
	std::string s=val.toString().orIfNull("asdf34wafsda");
	std::cerr<<"TESTESTESTESTESTESTEST"<<s<<std::endl;
	}
}
std::vector<Bridge*>* Bridge_Manager::getBridgeList(){
	//DEBUGGING
	Wt::log("info") << ":::::::::::::::::BM CALLED";
	//DEBUGGING
	return bridgeList;
}
