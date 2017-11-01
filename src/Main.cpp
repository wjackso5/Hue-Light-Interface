#include <iostream>
#include <string>
#include "User.h"

int main() {
	printf("Hello World\n");

	std::string firstName = "Joe";
	std::string lastName = "Smith";

	User u1(firstName, lastName);

	return 0;
}
