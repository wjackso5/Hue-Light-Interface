//ScheduleView Headerfile
#ifndef ScheduleView_H_
#define ScheduleView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
//#include "Light_Manager.h"
#include "Bridge.h"
class ScheduleView : public Wt::WContainerWidget
{
public:
  ScheduleView(Light_Manager *lm);
private:
  Light_Manager *lm;
  //Light_Manager *lm;
  std::vector<LightSchedule*> gl;
  Wt::WTable *schedule_list_;
  Wt::WText *schedule_msg_;
  Wt::WLineEdit *schedule_id_;
  Wt::WLineEdit *schedule_state_;
  Wt::WPushButton *schedule_button_;
  Wt::WPushButton *goto_bridgeview_button;
  void clearFields();
  void showScheduleList();
  void UpdateSchedule();
};
#endif