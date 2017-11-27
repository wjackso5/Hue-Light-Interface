//GroupView
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
#include "GroupView.h"

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
GroupView::GroupView(Light_Manager *lm)
  : WContainerWidget()
{ 
  
  std::string bridgename = lm->getBridge()->getName();

  group_msg_ = new WText("");
  addWidget(group_msg_);
  addWidget(new WBreak());

  addWidget(new WText("Group ID:"));
  group_id_ = new WLineEdit();                 // allow text input
  group_id_->setFocus();  
  addWidget(group_id_);
  addWidget(new WBreak());
                         
  addWidget(new WText("Group State:"));
  group_state_ = new WLineEdit();                 // allow text input
  addWidget(group_state_); 
  addWidget(new WBreak());
  

  group_button_ = new WPushButton("Confirm");
	goto_bridgeview_button = new WPushButton("Hide");
  WText *group_list_t= new WText("<h3><u>Group List for "+bridgename+":</u></h3>");
  addWidget(group_list_t);
  
  group_list_ = new WTable();
  showGroupList();



  group_button_->clicked().connect(this, &GroupView::UpdateLight);
  
}

void GroupView::clearFields(){
  group_id_->setText("");
  group_state_->setText("");
}
void GroupView::UpdateGroup(){
  //viv does work in here :D
  clearFields();
}
void GroupView::showGroupList(){
  
  group_list_->setHeaderCount(1);
  group_list_->setWidth(WLength("100%"));
  //declare the table headers.
  group_list_->elementAt(0, 0)->addWidget(new WText("Id"));
  group_list_->elementAt(0, 1)->addWidget(new WText("Name"));
  group_list_->elementAt(0, 2)->addWidget(new WText("Switch "));
  group_list_->elementAt(0, 3)->addWidget(new WText("Color"));
  group_list_->elementAt(0, 4)->addWidget(new WText("Brightness"));
  //get the lightlist
 /* ll = lm->getlightList();
  //populate the table with the info from the lightlist.
  for(int i=0; i<ll.size(); i++){
      group_list_->elementAt(i+1, 0)->addWidget(new WText(ll->at(i)->getName()));
      group_list_->elementAt(i+1, 1)->addWidget(new WText(ll->at(i)->getLocation()));
      group_list_->elementAt(i+1, 2)->addWidget(new WText(ll->at(i)->getIp()));
      group_list_->elementAt(i+1, 3)->addWidget(new WText(ll->at(i)->getPort()));
      group_list_->elementAt(i+1, 4)->addWidget(new WText(ll->at(i)->getUsername()));
  }*/
  addWidget(group_list_);
}

