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
#include <string>
#include <vector>

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;

BridgeView::BridgeView()
  : WContainerWidget()
{ 
  addWidget(new WText("hello there"));
  bm = new Bridge_Manager(&session_);
  //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH29";
  //DEBUGGING
  WText *title = new WText("<h1>Manage your Bridges:</h1>");
  addWidget(title);
  //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH34";
  //DEBUGGING
  bridge_msg_ = new WText("");
  addWidget(bridge_msg_);
  //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH39";
  //DEBUGGING
  bridge_name_ = new WLineEdit();                 // allow text input
  bridge_name_->setFocus();  
  addWidget(bridge_name_);   
    //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH45";
  //DEBUGGING                            // give focus

  bridge_location_ = new WLineEdit();                 // allow text input
  bridge_location_->setFocus();                                // give focus
  addWidget(bridge_location_); 
    //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH52";
  //DEBUGGING

  bridge_ip_ = new WLineEdit();                 // allow text input
  bridge_ip_->setFocus();
  addWidget(bridge_ip_); 
    //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH59";
  //DEBUGGING
 
  bridge_port_ = new WLineEdit();                 // allow text input
  bridge_port_->setFocus();                                 // give focus
  addWidget(bridge_port_); 
    //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH66";
  //DEBUGGING

  bridge_username_ = new WLineEdit();                 // allow text input
  bridge_username_->setFocus();
  addWidget(bridge_username_);
  //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH73";
  //DEBUGGING
  
  // bridge_list_->hide();
    //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH79";
  //DEBUGGING

  create_bridge_button_ = new WPushButton("Create Bridge");
  addWidget(create_bridge_button_);
  delete_bridge_button_ = new WPushButton("Delete Bridge");
  addWidget(delete_bridge_button_);
  edit_bridge_button_ = new WPushButton("Edit Bridge");
  addWidget(edit_bridge_button_);
  show_bridge_list_=new WPushButton("Show Bridge Lists");
  addWidget(show_bridge_list_);
  //DEBUGGING
  Wt::log("info") << ":::::::::::::::::REACH91";
  //DEBUGGING
  create_bridge_button_->clicked().connect(this, &BridgeView::addBridge);
  edit_bridge_button_->clicked().connect(this, &BridgeView::editBridge);
  delete_bridge_button_->clicked().connect(this, &BridgeView::deleteBridge);
  show_bridge_list_->clicked().connect(this,&BridgeView::showBridgeList);
	
  WText *bridge_list_t= new WText("<h1>Bridge List:</h1>");
  addWidget(bridge_list_);
}

void BridgeView::clearBridgeFields(){
  bridge_name_->setText("");
  bridge_location_->setText("");
  bridge_ip_->setText("");
  bridge_port_->setText("");
  bridge_username_->setText("");

}
void BridgeView::addBridge()
{
  //calls BM to add the bridge to the db
  Wt::log("info") << bridge_name_->text().toUTF8();
  bool response;
  response = bm->addBridge(bridge_name_->text().toUTF8(),bridge_location_->text().toUTF8(), bridge_ip_->text().toUTF8(), bridge_port_->text().toUTF8(), bridge_username_->text().toUTF8());
  if (response==true){
    Wt::log("info") << bridge_name_->text().toUTF8();
    bridge_msg_->setText(bridge_name_->text()+" was sucessfully added.");
  }else{
    bridge_msg_->setText(bridge_name_->text()+" could not be added.");
  }
  BridgeView::clearBridgeFields();
  BridgeView::showBridgeList();

}
void BridgeView::editBridge()
{
  //calls BM to add the bridge to the db
  bool response;
  response = bm->editBridge(bridge_name_->text().toUTF8(),bridge_location_->text().toUTF8(), bridge_port_->text().toUTF8(), bridge_port_->text().toUTF8(), bridge_username_->text().toUTF8());
  if (response==true){
    bridge_msg_->setText(bridge_name_->text()+" was sucessfully edited.");
  }else{
    bridge_msg_->setText(bridge_name_->text()+" could not be edited.");
  }
  BridgeView::clearBridgeFields(); 
  BridgeView::showBridgeList();

}
void BridgeView::deleteBridge()
{
  //calls BM to add the bridge to the db
  bool response;
  response = bm->deleteBridge(bridge_name_->text().toUTF8());
  if (response==true){
    bridge_msg_->setText(bridge_name_->text()+" was sucessfully removed.");
  }else{
    bridge_msg_->setText(bridge_name_->text()+" could not be removed.");
  }
  BridgeView::clearBridgeFields();
  BridgeView::showBridgeList();
}
void BridgeView::showBridgeList(){
  bridge_list_ = new WTable();
  bridge_list_->setHeaderCount(1);
  bridge_list_->setWidth(WLength("100%"));
  //declare the table headers.
  bridge_list_->elementAt(0, 0)->addWidget(new WText("Bridge"));
  bridge_list_->elementAt(0, 1)->addWidget(new WText("Location"));
  bridge_list_->elementAt(0, 2)->addWidget(new WText("IP address"));
  bridge_list_->elementAt(0, 3)->addWidget(new WText("Port Number"));
  bridge_list_->elementAt(0, 4)->addWidget(new WText("Username"));
  //get the bridgelist
  std::vector<Bridge*> bl = bm->getBridgeList();
  //populate the table with the info from the bridgelist.
  for(int i=0; i<bl.size(); i++){
      bridge_list_->elementAt(i, 0)->addWidget(new WText(bl.at(i)->getName()));
      bridge_list_->elementAt(i, 1)->addWidget(new WText(bl.at(i)->getLocation()));
      bridge_list_->elementAt(i, 2)->addWidget(new WText(bl.at(i)->getIp()));
      bridge_list_->elementAt(i, 3)->addWidget(new WText(bl.at(i)->getPort()));
      bridge_list_->elementAt(i, 4)->addWidget(new WText(bl.at(i)->getUsername()));
  }
  bridge_list_->addStyleClass("table-hover");
  bridge_list_->addStyleClass("table-bordered");
  addWidget(bridge_list_);
}

