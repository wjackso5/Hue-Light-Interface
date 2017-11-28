/* Bridge Manager Class
 *
 * Controller Class for adding Bridges, editing Bridges, etc.
 *
 * FINISHED
 */

#ifndef BRIDGE_MANAGER_H
#define BRIDGE_MANAGER_H

/* FROM STL */
#include <string>
#include <vector>
#include <Wt/Http/Client>
#include <Wt/Http/Message>
#include <Wt/Http/Request>
#include <Wt/Http/Response>


/* LOCAL FILES */
#include "DBSession.h"
#include "Bridge.h"

class Bridge_Manager {
	private :
		//CLASS VARIABLES

		/*
		 * I chose to use a linked list instead of an array
		 * Since it's size needs to be dynamic and it's easy
		 * to work with. Might be a better data structure to
		 * implement here though.
		 */

		std::vector<Bridge *> *bridgeList;
		DBSession *session_;

		//PRIVATE METHODS
		


	public :
		//CONSTRUCTOR
		Bridge_Manager(DBSession *session_);
		~Bridge_Manager();
		Bridge* newBridge;
		//PUBLIC METHODS
		bool addBridge(std::string name, std::string location, std::string ipAddressOrHostname, std::string portNumber, std::string userName);

		int findBridge(std::string bridgeName);
		/* The "editBridge" method that follows was proposed in the UML
		 * Since we have to pass the bridgeManager some way to identify
		 * the Bridge we wish to edit (which it seems must be the name
		 * of the Bridge) this method seems untidy and propose that we
		 * create methods to change each of the fields individually.
		 *
		 * Also, it seems reasonable that one may wish to change the
		 * name of their bridge, such as if they move the physical
		 * brdige from one room to another.
		 */
		bool editBridge(std::string name, std::string location, std::string ipAddressOrHostname, std::string portNumber, std::string userName);
		bool deleteBridge(std::string name);
		bool validityCheck(std::string ipOrHost, std::string port, std::string user);
		bool validityCheck(std::string ipOrHost, std::string port);
		void handleHttpResponse(boost::system::error_code err,const Wt::Http::Message& response);
		std::vector<Bridge*> getBridgeList();
};

#endif
