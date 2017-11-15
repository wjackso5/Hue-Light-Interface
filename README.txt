If you put your header files in the include directory and your implementation files in the src directory they're automatically included in the build for this new Makefile. 

To Clean, Build and Run:
	1. run the command "make clean"
	2. run the command "make"
	3. run the command "./Main.exe --docroot /usr/local/share/Wt --http-address 127.0.0.1 --http-port 8888
"

Be sure to clean the project (i.e. just run "make clean") before you push to keep the repo tidy.

Requirements:
- gcc with c++11 suppoort. 
- Wt version 3.8 or greater.
- Internet connection (Pulls jquery binary from the web), see Main.cpp
- sqlite3
- Resources directory from Wt 3.8 in /usr/local/share/Wt


-Casey
--Austin
