//BridgeView
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
#include <string>
#include <vector>
#include "LightView.h"
#include "GroupView.h"
#include "ScheduleView.h"

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
LightView::LightView(Bridge *bridge)
  : WContainerWidget()
{ 
  lm = new Light_Manager(bridge);
  std::string bridgename = bridge->getName();
  WText *title = new WText("<h3>"+bridgename+" Bridge:</h3>");
  addWidget(title);

  light_msg_ = new WText("");
  addWidget(light_msg_);
  addWidget(new WBreak());

  addWidget(new WText("Light ID:"));
  light_id_ = new WLineEdit();                 // allow text input
  light_id_->setFocus();  
  addWidget(light_id_);
  addWidget(new WBreak());
                         
  addWidget(new WText("Light State:"));
  light_state_ = new WLineEdit();                 // allow text input
  addWidget(light_state_); 
  addWidget(new WBreak());
  

  light_button_ = new WPushButton("Confirm");
  addWidget(light_button_);
	goto_bridgeview_button = new WPushButton("Hide");
  addWidget(goto_bridgeview_button);
  WText *light_list_t= new WText("<h3><u>Light List for "+bridgename+":</u></h3>");
  addWidget(light_list_t);

  
  
  light_list_ = new WTable();
  showLightList();

  addWidget(new GroupView(lm));
  addWidget(new ScheduleView(lm));

  light_button_->clicked().connect(this, &LightView::UpdateLight);
  goto_bridgeview_button->clicked().connect(this, &LightView::clearView);
  
}

void LightView::clearFields(){
  light_id_->setText("");
  light_state_->setText("");
}
void LightView::UpdateLight(){
  //viv does work in here :D
}
void LightView::showLightList(){
  
  light_list_->setHeaderCount(1);
  light_list_->setWidth(WLength("100%"));
  //declare the table headers.
  light_list_->elementAt(0, 0)->addWidget(new WText("Id"));
  light_list_->elementAt(0, 1)->addWidget(new WText("Name"));
  light_list_->elementAt(0, 2)->addWidget(new WText("Switch "));
  light_list_->elementAt(0, 3)->addWidget(new WText("Color"));
  light_list_->elementAt(0, 4)->addWidget(new WText("Brightness"));
  //get the lightlist
  ll = lm->getLightList();
  //populate the table with the info from the lightlist.
  for(int i=0; i<ll.size(); i++){
      light_list_->elementAt(i+1, 0)->addWidget(new WText(llat(i)->getId()));
      light_list_->elementAt(i+1, 1)->addWidget(new WText(ll->at(i)->getName()));
      light_list_->elementAt(i+1, 2)->addWidget(new WText(ll->at(i)->getSwitch()));
      light_list_->elementAt(i+1, 3)->addWidget(new WText(ll->at(i)->getColor()));
      light_list_->elementAt(i+1, 4)->addWidget(new WText(ll->at(i)->getBrightness()));
  }
  addWidget(light_list_);
}
  void LightView::clearView(){
    this->hide();
  }
