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
#include <Wt/WTable>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>
#include "BridgeView.h"
#include "Bridge.h"
#include "LightView.h"
#include <string>
#include <vector>

//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;

BridgeView::BridgeView()
  : WContainerWidget()
{ 
  //adds BridgeUI widgets
  bm = new Bridge_Manager(&session_);

  WText *title = new WText("<h1>Manage your Bridges:</h1>");
  addWidget(title);
  addWidget(new WBreak());

  bridge_msg_ = new WText("");
  addWidget(bridge_msg_);
  addWidget(new WBreak());

  addWidget(new WText("Name:"));
  bridge_name_ = new WLineEdit();                 // allow text input
  bridge_name_->setFocus();  
  addWidget(bridge_name_);   
  addWidget(new WBreak());
                         
  addWidget(new WText("Location:"));
  bridge_location_ = new WLineEdit();                 // allow text input
  addWidget(bridge_location_); 
  addWidget(new WBreak());

  addWidget(new WText("IP:"));
  bridge_ip_ = new WLineEdit();                 // allow text input
  addWidget(bridge_ip_); 
  addWidget(new WBreak());

  addWidget(new WText("Port:"));
  bridge_port_ = new WLineEdit();                 // allow text input
  addWidget(bridge_port_); 
  addWidget(new WBreak());

  addWidget(new WText("Username (optional):"));
  bridge_username_ = new WLineEdit();                 // allow text input
  addWidget(bridge_username_);
  addWidget(new WBreak());
  

  create_bridge_button_ = new WPushButton("Create Bridge");
  addWidget(create_bridge_button_);
  delete_bridge_button_ = new WPushButton("Delete Bridge");
  addWidget(delete_bridge_button_);
  edit_bridge_button_ = new WPushButton("Edit Bridge");
  addWidget(edit_bridge_button_);
  show_bridge_list_=new WPushButton("Show Bridge Lists");
  addWidget(show_bridge_list_);


	
  WText *bridge_list_t= new WText("<h2><u>Bridge List:</u></h2>");
  addWidget(bridge_list_t);
  addWidget(new WText("Bridge to view: (by name)"));
  btv_name = new WLineEdit();
  addWidget(btv_name);
  addWidget(new WBreak());

  goto_lightview_button = new WPushButton("View Bridge");
  addWidget(goto_lightview_button);

  bridge_list_ = new WTable();

  create_bridge_button_->clicked().connect(this, &BridgeView::addBridge);
  edit_bridge_button_->clicked().connect(this, &BridgeView::editBridge);
  delete_bridge_button_->clicked().connect(this, &BridgeView::deleteBridge);
  show_bridge_list_->clicked().connect(this,&BridgeView::showBridgeList);
  goto_lightview_button->clicked().connect(this, &BridgeView::createLightView);


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
  bridge_list_->clear();
  bridge_list_->setHeaderCount(1);
  bridge_list_->setWidth(WLength("100%"));
  //declare the tabl-> headers.
  bridge_list_->elementAt(0, 0)->addWidget(new WText("Bridge"));
  bridge_list_->elementAt(0, 1)->addWidget(new WText("Location"));
  bridge_list_->elementAt(0, 2)->addWidget(new WText("IP address"));
  bridge_list_->elementAt(0, 3)->addWidget(new WText("Port Number"));
  bridge_list_->elementAt(0, 4)->addWidget(new WText("Username"));
  //get the bridgelist
  bm = new Bridge_Manager(&session_);
  bl = bm->getBridgeList();

  /*
  for (std::vector<Bridge*>::iterator it = bl->begin(); it != bl->end(); ++it) {
	Wt::log("Bridge Name") << (*it)->getName(); 
  }
  */
  


  //populate the tabl-> with the info from the bridgelist.
  for(int i=0; i<bl->size(); i++){
      bridge_list_->elementAt(i+1, 0)->addWidget(new WText(bl->at(i)->getName()));
      bridge_list_->elementAt(i+1, 1)->addWidget(new WText(bl->at(i)->getLocation()));
      bridge_list_->elementAt(i+1, 2)->addWidget(new WText(bl->at(i)->getIp()));
      bridge_list_->elementAt(i+1, 3)->addWidget(new WText(bl->at(i)->getPort()));
      bridge_list_->elementAt(i+1, 4)->addWidget(new WText(bl->at(i)->getUsername()));
  }
  addWidget(bridge_list_);

}

  void BridgeView::createLightView(){
    int index = bm->findBridge(btv_name->text().toUTF8());
    Bridge btv = new Bridge();
    btv = *bl->at(index);
    Wt::log("info") << btv->getName();
    //addWidget(new LightView(btv));
    //this->hide();
    //this->clear();
  }
