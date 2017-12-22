**********************************************************************
*** Note this is just a copy of the main directory which exists on *** 
*** uwos bit bucket server. This application uses WT to implement  ***
*** an interface for remotely controlling philip hue lights using  ***
*** a web page.                                                    ***
**********************************************************************


If you put your header files in the include directory and your implementation files in the src directory they're automatically included in the build for this new Makefile. 

To Clean, Build and Run:
	1. run the command "make clean"
	2. run the command "make"
	3. run the command "./Main.exe --docroot /usr/local/share/Wt --http-address 0.0.0.0 --http-port 10026
"

On cs3307-pub ports 10000-20000 are open. If running from cs3307-pub go to cs3307-pub.gaul.csd.uwo.ca:10026, if running from local host go to 0.0.0.0:10026

Be sure to clean the project (i.e. just run "make clean") before you push to keep the repo tidy.

Requirements:
- gcc with c++11 suppoort. 
- Wt version 3.8 or greater.
- Internet connection (Pulls jquery binary from the web), see Main.cpp
- sqlite3
- Resources directory from Wt 3.8 in /usr/local/share/Wt

Note that for data base persistant, you'll want to just run the command make, there should be no reason to clean it unless building it for the first time. Clean removes the database which gets created in the working directory, "light.db". 


-Casey
--Austin
