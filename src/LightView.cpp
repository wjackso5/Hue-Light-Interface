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
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/WAny>
#include <Wt/WComboBox>
#include <Wt/WStringListModel>



//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
LightView::LightView(Bridge *bridge)
  : WContainerWidget()
{ 

  Wt::log("LIGHT")<<"about to make LM";
  lm = new Light_Manager(bridge);
  Wt::log("INITIALIZINGLIGHTLIST")<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";

  Wt::log("DEBUG")<<"!!!!!!33!!!!!!";
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
                         



  addWidget(light_state_); 
  addWidget(new WBreak());
  
  show_button_ = new WPushButton("Show list");

  light_button_ = new WPushButton("Confirm");
	goto_bridgeview_button = new WPushButton("Hide");
  WText *light_list_t= new WText("<h3><u>Light List for "+bridgename+":</u></h3>");
  addWidget(light_list_t);

  light_list_ = new WTable();
  Wt::log("DEBUG")<<"!!!!!!58!!!!!! B4 showLightList";
  // LightView::showLightList();
  Wt::log("DEBUG")<<"!!!!!!60!!!!!! aft showLightList";
  addWidget(goto_bridgeview_button);
  addWidget(light_list_);
  addWidget(show_button_);

  Wt::log("DEBUG")<<"!!!!!!60!!!!!! b4 add group and schedule views";

  addWidget(new GroupView(lm));
  addWidget(new ScheduleView(lm));

  Wt::log("DEBUG")<<"!!!!!!60!!!!!! aft add group and sched views";
  show_button_->clicked().connect(this,&LightView::showLightList);
  light_button_->clicked().connect(this, &LightView::UpdateLight);
  goto_bridgeview_button->clicked().connect(this, &LightView::clearView);
 
  
}

void LightView::clearFields(){
  light_id_->setText("");
  light_state_->setText("");
}
void LightView::UpdateLight(){
  
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
  Wt::log("DEBUG")<<"about to get the lightlist from lm";
 

  log("FRONTEND") << ll;
  Json::Object ob;
  Json::parse(ll,ob,false);
  int size=ob.size();
  for (int i=0;i<size;i++){
    Json::Object val=ob.get(std::to_string(i+1));
    std::string light_name=val.get("name").toString().orIfNull("name:(((");
    Json::Object states=val.get("state"); 
    bool isOn=states.get("on").toBool().orIfNull(false);
    int light_brightness=states.get("bri").toNumber().orIfNull(-11111);
    int light_hue=states.get("hue").toNumber().orIfNull(-222222);
    light_list_->elementAt(i+1, 0)->addWidget(new WText(std::to_string(i+1)));
    light_list_->elementAt(i+1, 1)->addWidget(new WText(light_name));
    light_list_->elementAt(i+1, 2)->addWidget(new WText(std::to_string(isOn)));
    light_list_->elementAt(i+1, 3)->addWidget(new WText(std::to_string(light_hue)));
    light_list_->elementAt(i+1, 4)->addWidget(new WText(std::to_string(light_brightness)));
  
  }
}


  void LightView::clearView(){
    this->clear();
  }
