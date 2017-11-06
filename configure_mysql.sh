#Shell script for installing mysql server
#To run the script (NB from the directory containing the script) run the following
#chmod a+x configure_mysql.sh
#./configure_mysql.sh
#Leave the root password blank for mysql

sudo apt-get update #Update repositories
sudo apt-get install mysql-server #Get installer
mysql_secure_installation #Installs mysql
service --status-all | grep mysql #you should see " [ + ]  mysql"

