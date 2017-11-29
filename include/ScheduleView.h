//ScheduleView Headerfile
#ifndef ScheduleView_H_
#define ScheduleView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "Light_Manager.h"
#include "Schedule.h"
#include "Bridge.h"
class ScheduleView : public Wt::WContainerWidget
{
public:
  ScheduleView(std::string bridgeName, std::string bridgeIP, std::string bridgePORT);
private:
  int numSchedules;
  int schedNum;
  bool slHasBeenInit;
  bool handleSShasBeenCalled;
  bool handleIVShasBeenCalled;

  Wt::Signal<> doneScheduleList;
 
  std::string ip;
  std::string port;

  Light_Manager *lm;
  std::vector<Schedule> *sl;

  Wt::WTable *schedule_list_;
  Wt::WTable **schedule_list_p;
  Wt::WText *schedule_msg_;
  Wt::WLineEdit *schedule_time_;
  Wt::WLineEdit *schedule_name_;
  Wt::WLineEdit *schedule_on_;
  Wt::WLineEdit *schedule_brightness_;
  Wt::WLineEdit *schedule_address_;
  Wt::WPushButton *schedule_button_;
  Wt::WPushButton *goto_bridgeview_button;
  Wt::WPushButton *showSchedulesButton;
  Wt::WContainerWidget *this2_;
  void initializeSchedule();
  void clearFields();
  void showScheduleList();
  void addSchedule();
  void deleteSchedule();
  void UpdateSchedule();
  void getSchedule();
  void handleShowScheduleHttpResponse(boost::system::error_code err, const Wt::Http::Message& response);
  void parseGottenSchedule(const std::string &scheduleList);
  void getIndividualSchedule(std::string scheduleNumber);
  void handleIVShttpResponse(boost::system::error_code err, const Wt::Http::Message& response);
  void parseIVS(const std::string &input);
  void printSchedule();


};
#endif
