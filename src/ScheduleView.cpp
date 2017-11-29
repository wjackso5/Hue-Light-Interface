//scheduleView
#include <iostream>
#include <string>
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WTable>
#include <Wt/WTableCell>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>
#include "BridgeView.h"
#include "Bridge.h"
#include "Light.h"
#include "Light_Manager.h"
#include <string>
#include <vector>
#include "ScheduleView.h"
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/WSignal>

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
ScheduleView::ScheduleView(std::string bridgeName, std::string bridgeIP, std::string bridgePORT)
  : WContainerWidget()
{ 
  std::string bridgename = bridgeName;
  ip = bridgeIP;
  port = bridgePORT;

  Wt::log("INFO") << "ScheduleView made";

  schedule_msg_ = new WText("");
  addWidget(schedule_msg_);
  addWidget(new WBreak());

  addWidget(new WText("Time:"));
  schedule_time_ = new WLineEdit();                 // allow text input
  schedule_time_->setFocus(); 
  schedule_time_->setInputMask("0000-00-00T00:00:00;_"); 
  addWidget(schedule_time_);
  addWidget(new WBreak());
                         
  addWidget(new WText("Name:"));
  schedule_name_ = new WLineEdit();                 // allow text input
  addWidget(schedule_name_); 
  addWidget(new WBreak());

  addWidget(new WText("On/Off:"));
  schedule_on_ = new WLineEdit();                 // allow text input
  addWidget(schedule_on_); 
  addWidget(new WBreak());

  addWidget(new WText("Brightness:"));
  schedule_bri_ = new WLineEdit();                 // allow text input
  addWidget(schedule_bri_); 
  addWidget(new WBreak());

  addWidget(new WText("Address:"));
  schedule_address_ = new WLineEdit();                 // allow text input
  addWidget(schedule_address_); 
  addWidget(new WBreak());


  schedule_add_button_ = new WPushButton("Add");
  schedule_del_button_ = new WPushButton("Delete");
  addWidget(schedule_add_button_);
  addWidget(schedule_del_button_);


  WText *schedule_list_t= new WText("<h3><u>Schedule List for "+bridgename+":</u></h3>");
  addWidget(schedule_list_t);

  //SHOW SCHEDULES
  
  /**
   * Initialize the Wtable
   */
  schedule_list_ = new WTable();
  Wt::log("INFO") << "Yabadabadoo x2";

  /**
   * Enable push button and connect it
   */
  showSchedulesButton = new Wt::WPushButton("Show Schedules");
  addWidget(showSchedulesButton);
  showSchedulesButton->clicked().connect(this, &ScheduleView::initializeSchedule);
  schedule_add_button_->clicked().connect(this, &ScheduleView::addSchedule);
  schedule_del_button_->clicked().connect(this, &ScheduleView::deleteSchedule);
  doneScheduleList.connect(this, &ScheduleView::printSchedule);

}

void ScheduleView::clearFields(){
  schedule_id_->setText("");
  schedule_state_->setText("");
}


void ScheduleView::addSchedule(){
	std::string name, address, method, on, bri, localtime;

	name = schedule_name_->text().toUTF8();
	address = schedule_address_->text().toUTF8();
	method = "PUT";
	on = schedule_on_->text().toUTF8();
	bri = schedule_bri_->text().toUTF8();
	localtime = schedule_time_->text().toUTF8();

	std::string response;

	response = assembleJsonForPutRequest(name, address, method, on, bri, localtime);
	std::cout << response;
}


void ScheduleView::deleteSchedule(){

}


void ScheduleView::UpdateSchedule(){
  clearFields();

}


/**
 * METHODS FOR FETCHING THE SCHEDULE
 *
 * NOTE THAT THEY'RE IN ORDER OF CALLING
 */
void ScheduleView::initializeSchedule() {
	handleSShasBeenCalled = false;
	handleIVShasBeenCalled = false;
	if (sl) {
		delete sl;
	}
	sl = new std::vector<Schedule>();
	getSchedule();

}

void ScheduleView::getSchedule() {
	Wt::Http::Client *httpC = new Wt::Http::Client(this);
	httpC->done().connect(boost::bind(&ScheduleView::handleShowScheduleHttpResponse, this, _1, _2)); 
	if (!httpC->get("http://" + ip + ":" + port + "/api/newdeveloper/schedules")) {
		Wt::log("ERROR") << "Malformed URL";
	}
}


void ScheduleView::handleShowScheduleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response) {
        Wt::log("INFO") << "Yabadabadoo x6";
	if (handleSShasBeenCalled == false) {
		handleSShasBeenCalled = true;
		if (!err && response.status() == 200) {
			const std::string &input = response.body();
			parseGottenSchedule(input);
		}
	}
	
}

/**
 * The command for getting the schedules 'ip/api/username/schedules' doesn't 
 * return the core properties of each schedule (i.e. scene, on, xy, etc).
 * So unfortunatley, we have to make another get request for each schedule.
 */
void ScheduleView::parseGottenSchedule(const std::string &scheduleList) {
	int size, i;
	std::string scheduleNumber;
	Json::Object jScheduleList;

	Json::parse(scheduleList, jScheduleList, false);
	size = jScheduleList.size();
	for (i=0; i<size; i++) {
		scheduleNumber = std::to_string(i+1);
		getIndividualSchedule(scheduleNumber);
	}

	numSchedules = size;

}

void ScheduleView::getIndividualSchedule(std::string scheduleNumber) {
	Wt::Http::Client *httpC = new Wt::Http::Client(this);
	httpC->done().connect(boost::bind(&ScheduleView::handleIVShttpResponse, this, _1, _2)); 
	if (!httpC->get("http://" + ip + ":" + port + "/api/newdeveloper/schedules/" + scheduleNumber)) {
		Wt::log("ERROR") << "Malformed URL";
	}

}

void ScheduleView::handleIVShttpResponse(boost::system::error_code err, const Wt::Http::Message& response) {
	if (handleIVShasBeenCalled == false) {
		handleIVShasBeenCalled = true;
		if (!err && response.status() == 200) {
			const std::string &input = response.body();
			parseIVS(input);
		}
	}
}

void ScheduleView::parseIVS(const std::string &input) {
	std::string time, name, address, method, on, bri;
	Json::Object jSchedule, jCommand, jBody;

	Json::parse(input, jSchedule, false);
	time = jSchedule.get("time").toString().orIfNull("N/A");
	name = jSchedule.get("name").toString().orIfNull("N/A");
	jCommand = jSchedule.get("command");
	jBody = jCommand.get("body");
	on = jBody.get("on").toString().orIfNull("N/A");
	bri = jBody.get("bri").toString().orIfNull("N/A");
	address = jCommand.get("address").toString().orIfNull("N/A");
	method = jCommand.get("method").toString().orIfNull("N/A");

	sl->push_back(Schedule(time, name, on, bri, address, method));
	
	schedNum++;

	if (schedNum == numSchedules) {
		Wt::log("INFO") << "Signal about to be emitted";
		doneScheduleList.emit();
	}
}	

void ScheduleView::printSchedule() {
  /**
   * Erase the current contents of the table
   */

  /**
   * Initialize headers
   */
  schedule_list_->setHeaderCount(1);
  schedule_list_->setWidth(WLength("100%"));
  schedule_list_->elementAt(0, 0)->addWidget(new WText("Time"));
  schedule_list_->elementAt(0, 1)->addWidget(new WText("Name"));
  schedule_list_->elementAt(0, 2)->addWidget(new WText("On/Off"));
  schedule_list_->elementAt(0, 3)->addWidget(new WText("Brightness"));
  schedule_list_->elementAt(0, 4)->addWidget(new WText("Address"));
  schedule_list_->elementAt(0, 5)->addWidget(new WText("method"));
  /**
   * For each schedule, add a row to the table.
   */
  for(int i=0; i<numSchedules; i++){
      schedule_list_->elementAt(i+1, 0)->addWidget(new WText(sl->at(i).time));
      schedule_list_->elementAt(i+1, 1)->addWidget(new WText(sl->at(i).name));
      schedule_list_->elementAt(i+1, 2)->addWidget(new WText(sl->at(i).on));
      schedule_list_->elementAt(i+1, 3)->addWidget(new WText(sl->at(i).bri));
      schedule_list_->elementAt(i+1, 4)->addWidget(new WText(sl->at(i).address));
      schedule_list_->elementAt(i+1, 5)->addWidget(new WText(sl->at(i).method));
  }
  this->addWidget(schedule_list_);
}

std::string ScheduleView::assembleJsonForPutRequest(std::string name, std::string address, std::string method, std::string on, std::string bri, std::string localtime ) {
	std::string jsonObj;
	jsonObj = "{ \"name\":\"" + name + "\",";
	jsonObj += "\"description\": \"\",";
	jsonObj += "\"command\": {";
	jsonObj += "\"address\": \"" + address + "\",";
	jsonObj += "\"method\" : \"" + method + "\",";
	jsonObj += "\"body\": {";
	jsonObj += "\"on\": "+on+",";
	jsonObj += "\"bri\":"+bri+",";
	jsonObj += "}";
	jsonObj += "},";
	jsonObj += "\"localtime\": \"" + localtime + "\"";
	jsonObj += "}";
	
	return jsonObj;
}

