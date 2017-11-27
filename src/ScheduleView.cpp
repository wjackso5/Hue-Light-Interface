//scheduleView
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

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
ScheduleView::ScheduleView(Light_Manager *lm)
  : WContainerWidget()
{ 
  
  std::string bridgename = lm->getBridge()->getName();

  schedule_msg_ = new WText("");
  addWidget(schedule_msg_);
  addWidget(new WBreak());

  addWidget(new WText("Schedule ID:"));
  schedule_id_ = new WLineEdit();                 // allow text input
  schedule_id_->setFocus();  
  addWidget(schedule_id_);
  addWidget(new WBreak());
                         
  addWidget(new WText("Schedule State:"));
  schedule_state_ = new WLineEdit();                 // allow text input
  addWidget(schedule_state_); 
  addWidget(new WBreak());
  

  schedule_button_ = new WPushButton("Confirm");
  goto_bridgeview_button = new WPushButton("Hide");
  WText *schedule_list_t= new WText("<h3><u>Schedule List for "+bridgename+":</u></h3>");
  addWidget(schedule_list_t);
  
  schedule_list_ = new WTable();
  showscheduleList();


  light_button_->clicked().connect(this, &scheduleView::UpdateLight);
  goto_bridgeview_button->clicked().connect(this, &scheduleView::clearView);
  
}

void ScheduleView::clearFields(){
  schedule_id_->setText("");
  schedule_state_->setText("");
}
void ScheduleView::Updateschedule(){
  //viv does work in here :D
  clearFields();
}
void ScheduleView::showscheduleList(){
  
  schedule_list_->setHeaderCount(1);
  schedule_list_->setWidth(WLength("100%"));
  //declare the table headers.
  schedule_list_->elementAt(0, 0)->addWidget(new WText("Id"));
  schedule_list_->elementAt(0, 1)->addWidget(new WText("Name"));
  schedule_list_->elementAt(0, 2)->addWidget(new WText("Switch "));
  schedule_list_->elementAt(0, 3)->addWidget(new WText("Brightness"));
  schedule_list_->elementAt(0, 4)->addWidget(new WText("Time"));
  //get the lightlist
 /* ll = lm->getlightList();
  //populate the table with the info from the lightlist.
  for(int i=0; i<ll.size(); i++){
      schedule_list_->elementAt(i+1, 0)->addWidget(new WText(ll->at(i)->getName()));
      schedule_list_->elementAt(i+1, 1)->addWidget(new WText(ll->at(i)->getLocation()));
      schedule_list_->elementAt(i+1, 2)->addWidget(new WText(ll->at(i)->getIp()));
      schedule_list_->elementAt(i+1, 3)->addWidget(new WText(ll->at(i)->getPort()));
      schedule_list_->elementAt(i+1, 4)->addWidget(new WText(ll->at(i)->getUsername()));
  }*/
  addWidget(schedule_list_);
}
  void ScheduleView::clearView(){
    this->hide();
  }
