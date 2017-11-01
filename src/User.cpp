#include "User.h"

//Constructor
User::User(std::string fName, std::string lName) : firstName(fName), lastName(lName) {

}

//Getters
std::string User::getFirstName() {
	return firstName;
}

std::string User::getLastName() {
	return lastName;
}


//Setters
void User::setFirstName(std::string fName) {
	firstName = fName;
}

void User::setLastName(std::string lName) {
	lastName = lName;
}
