/**
*GroupView Implementation file.
*/
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
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/Json/Parser>
#include <Wt/Json/Array>


//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
/**
*constructor for the GroupView widget
*adds all widgets required for the GroupView
*@param bridge that we will be showing/modifying lights for.
*@return none
*/
GroupView::GroupView(Light_Manager *lightm)
  : WContainerWidget()
{ 
  lm=lightm;
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
  show_group_list=new WPushButton("Show Groups");
  addWidget(show_group_list);
  group_button_ = new WPushButton("Confirm");

  addWidget(new WText("Group Name:"));
  group_name_ = new WLineEdit();
  addWidget(group_name_);
  addWidget(new WBreak());

  addWidget(new WText("List the Lights (by id):"));
  group_light_list_ = new WLineEdit();
  addWidget(group_light_list_ );
  addWidget(new WBreak());

  add_group_button_ = new WPushButton("Add Group");
  rm_group_button_ = new WPushButton("Remove Group");
  WText *group_list_t= new WText("<h3><u>Group List for "+bridgename+":</u></h3>");
  addWidget(group_list_t);
  addWidget(add_group_button_);
  addWidget(rm_group_button_);
  
  group_list_ = new WTable();
  
  group_button_->clicked().connect(this, &GroupView::updateGroup);
  show_group_list->clicked().connect(this,&GroupView::showGroupList);
  rm_group_button_->clicked().connect(this, &GroupView::removeGroup);
  add_group_button_->clicked().connect(this, &GroupView::addGroup);
}
/**
*clearFields clears the existing text from this widget
*@param none
*@return none
*/
void GroupView::clearFields(){
  group_id_->setText("");
  group_state_->setText("");
  group_light_list_->setText("");
  group_name_->setText("");
}
/**
*UpdateGroup takes the info from the form in this widget and decides which Light_Manager method it should call to update the group
*@param   none
*@return none
*/
void GroupView::updateGroup(){
  //viv does work in here :D
  clearFields();
}
/**
*addGroup calls the light manager to add a group
*@param none
*@return none
*/
void GroupView::addGroup(){
  if (lm->createGroup(group_light_list_->text().toUTF8(), group_name_->text().toUTF8())){
    group_msg_->setText(group_name_->text().toUTF8()+" added to groups");
  }
  else{
    group_msg_->setText(group_name_->text().toUTF8()+"could not be added to groups");
  }
}
/**
*removeGroup calls the light manager to remove a group
*@param none
*@return none
*/
void GroupView::removeGroup(){
  //call lm to remove group
  if (lm->deleteGroup(group_id_->text().toUTF8())){
    group_msg_->setText(group_name_->text().toUTF8()+" was deleted from groups");
  }
  else{
    group_msg_->setText(group_name_->text().toUTF8()+"could not be deleted from groups");
  }
}

/**
*showGroupList renders a WTable object to show the user the light groups that are connected to the given bridge. 
*@param none
*@return none
*/
void GroupView::showGroupList(){
  group_list_->clear();
  grouplist=lm->getGroupList();
  group_list_->setHeaderCount(1);
  group_list_->setWidth(WLength("100%"));
  //declare the table headers.
  group_list_->elementAt(0, 0)->addWidget(new WText("Id"));
  group_list_->elementAt(0, 1)->addWidget(new WText("Name"));
  group_list_->elementAt(0, 2)->addWidget(new WText("Switch "));
  group_list_->elementAt(0, 3)->addWidget(new WText("Color"));
  group_list_->elementAt(0, 4)->addWidget(new WText("Brightness"));
  group_list_->elementAt(0, 5)->addWidget(new WText("Lights"));
  log("SHOWGROUOPLIST")<<"BEFORE OB";
  Json::Object ob;
  Json::parse(grouplist,ob,false);
  int size=ob.size();
  for (int i=0;i<size;i++){
    Json::Object val=ob.get(std::to_string(i+1));
    std::string group_name=val.get("name").toString().orIfNull("name:(((");
    Json::Object states=val.get("action"); 
    bool isOn=states.get("on").toBool().orIfNull(false);
    int light_brightness=states.get("bri").toNumber().orIfNull(-11111);
    int light_hue=states.get("hue").toNumber().orIfNull(-222222);
    Json::Array ls=val.get("lights");
    std::string lls;
    log("SHOWGROUOPLIST")<<"BEFORE 2ND FOR LOOP";
    for(int i=0;i<ls.size();i++){
      lls=lls+ls.at(i).toString().orIfNull("no lights");
    }
    group_list_->elementAt(i+1, 0)->addWidget(new WText(std::to_string(i+1)));
    group_list_->elementAt(i+1, 1)->addWidget(new WText(group_name));
    group_list_->elementAt(i+1, 2)->addWidget(new WText(std::to_string(isOn)));
    group_list_->elementAt(i+1, 3)->addWidget(new WText(std::to_string(light_hue)));
    group_list_->elementAt(i+1, 4)->addWidget(new WText(std::to_string(light_brightness)));
    group_list_->elementAt(i+1, 5)->addWidget(new WText(lls));
  
  }
  addWidget(group_list_);
}

