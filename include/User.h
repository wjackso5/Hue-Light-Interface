/* The User Class
 *
 * Model (MVC) Class
 *
 * Mostly just me getting a feel for how this is going to go down, nothing important here. 
 *
 * -Casey 11/1/17
 */

#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>

class User {
	private :
		std::string firstName;
		std::string lastName;
	
	public:
		/*Constructor(s)*/
		User(std::string fName, std::string lName);

		/*Getters and Setters */
		void setFirstName(std::string fName);
		void setLastName(std::string lName);
		std::string getFirstName();
		std::string getLastName();

};

#endif
