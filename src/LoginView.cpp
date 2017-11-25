
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>
#include "LoginView.h"
#include "Bridge.h"
#include <string>
#include <vector>

using namespace Wt;

LoginView::LoginView(WContainerWidget *parent): WContainerWidget(parent)
{


  session_.login().changed().connect(this, &LoginView::onAuthEvent);

  Auth::AuthModel *authModel = new Auth::AuthModel(DBSession::auth(),
						   session_.users(), this);
  authModel->addPasswordAuth(&DBSession::passwordAuth());
  authModel->addOAuth(DBSession::oAuth());

  Auth::AuthWidget *authWidget = new Auth::AuthWidget(session_.login());
  authWidget->setModel(authModel);
  authWidget->setRegistrationEnabled(true);

  bm=new Bridge_Manager(&session_);
  WText *title = new WText("<h1>Manage your Bridges:</h1>");
  addWidget(title);
  addWidget(new WText("Logged in as: "));
  addWidget(authWidget);

  mainStack_ = new WStackedWidget();
  addWidget(mainStack_);

  //Bridge UI
  bridge_msg_ = new WText("");
  bridge_container_ = new WContainerWidget();

  bridge_name_ = new WLineEdit();                 // allow text input
  bridge_name_->setFocus();                                 // give focus

  bridge_location_ = new WLineEdit();                 // allow text input
  bridge_location_->setFocus();                                // give focus

  bridge_ip_ = new WLineEdit();                 // allow text input
  bridge_ip_->setFocus();

  bridge_port_ = new WLineEdit();                 // allow text input
  bridge_port_->setFocus();                                 // give focus

  bridge_list_= new WText("<h1>Bridge List:</h1>");

  bridge_username_ = new WLineEdit();                 // allow text input
  bridge_username_->setFocus();
  create_bridge_button_ = new WPushButton("Create Bridge");
  delete_bridge_button_ = new WPushButton("Delete Bridge");
  edit_bridge_button_ = new WPushButton("Edit Bridge");
  show_bridge_list_=new WPushButton("Show Bridge Lists");
  bridge_container_->addWidget(new WText("Bridge Name: "));
  bridge_container_->addWidget(bridge_name_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(new WText("Bridge Location: "));
  bridge_container_->addWidget(bridge_location_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(new WText("Bridge IP Address or Hostname: "));
  bridge_container_->addWidget(bridge_ip_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(new WText("Bridge Port Number: "));
  bridge_container_->addWidget(bridge_port_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(new WText("Optional Username: "));
  bridge_container_->addWidget(bridge_username_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(create_bridge_button_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(delete_bridge_button_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(edit_bridge_button_);
  bridge_container_->addWidget(new WBreak());
  bridge_container_->addWidget(show_bridge_list_);
  bridge_container_->addWidget(bridge_msg_);
  bridge_container_->addWidget(bridge_list_);
  bridge_container_->hide();

  create_bridge_button_->clicked().connect(this, &LoginView::addBridge);
  edit_bridge_button_->clicked().connect(this, &LoginView::editBridge);
  delete_bridge_button_->clicked().connect(this, &LoginView::deleteBridge);
  show_bridge_list_->clicked().connect(this,&LoginView::showBridgeList);
  //  //update the view list


  links_ = new WContainerWidget();
  links_->hide();
  addWidget(bridge_container_);
  addWidget(links_);

  // testAnchor_ = new WAnchor("/test", "Testing", links_);
  // testAnchor_->setLink(WLink(WLink::InternalPath, "/test"));

  // testTwoAnchor_ = new WAnchor("/test2", "Test 2", links_);
  // testTwoAnchor_->setLink(WLink(WLink::InternalPath, "/test2"));

  WApplication::instance()->internalPathChanged()
    .connect(this, &LoginView::handleInternalPath);

  authWidget->processEnvironment();
};

void LoginView::onAuthEvent()
{
  if (session_.login().loggedIn()) {
    links_->show();
    bridge_container_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    bridge_container_->hide();
    mainStack_->clear();
    links_->hide();
  }
}
void LoginView::clearBridgeFields(){
  bridge_name_->setText("");
  bridge_location_->setText("");
  bridge_ip_->setText("");
  bridge_port_->setText("");
  bridge_username_->setText("");

}
void LoginView::addBridge()
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
  LoginView::clearBridgeFields();

}
void LoginView::editBridge()
{
  //calls BM to add the bridge to the db
  bool response;
  response = bm->editBridge(bridge_name_->text().toUTF8(),bridge_location_->text().toUTF8(), bridge_port_->text().toUTF8(), bridge_port_->text().toUTF8().c_str(), bridge_username_->text().toUTF8());
  if (response==true){
    bridge_msg_->setText(bridge_name_->text()+" was sucessfully edited.");
  }else{
    bridge_msg_->setText(bridge_name_->text()+" could not be edited.");
  }
  LoginView::clearBridgeFields();

}
void LoginView::deleteBridge()
{
  //calls BM to add the bridge to the db
  bool response;
  response = bm->deleteBridge(bridge_name_->text().toUTF8());
  if (response==true){
    bridge_msg_->setText(bridge_name_->text()+" was sucessfully removed.");
  }else{
    bridge_msg_->setText(bridge_name_->text()+" could not be removed.");
  }
  LoginView::clearBridgeFields();
  LoginView::showBridgeList();
}
void LoginView::showBridgeList(){
  //call bm bridgelist and display.
  std::string text = "<h1>Bridge List:</h1>"
  "<table>";
  text+=
    "<tr>"
    "<th> |Bridge Name| </th>"
    "<th> |Bridge Location| </th>"
    "<th> |Bridge IP| </th>"
    "<th> |Bridge Port Number| </th>"
    "</tr>";
  std::vector<Bridge> bl = bm->getBridgeList();
  for(int i=0;i<bl.size();i++){
  text += "<tr>";
  text += "<th>"+bl.at(i).getName()+"</th>";
  text += "<th>"+bl.at(i).getLocation()+"</th>";
  text += "<th>"+bl.at(i).getIp()+"</th>";
  text += "<th>"+bl.at(i).getPort()+"</th>";
  text += "</tr>";
  }
  text += "</table>";
  bridge_list_->setText(text);
}
void LoginView::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/test") {}
      //
    else if (internalPath == "/test2") {}
      //
    else
      WApplication::instance()->setInternalPath("/test",  true);
  }
}


  //mainStack_->setCurrentWidget(game_);
