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
#include <Wt/WComboBox>
#include <Wt/WStringListModel>
#include "SpotifyView.h"




//DEBUGGING
#include <Wt/WLogger>
//DEBUGGING

using namespace Wt;
LightView::LightView(Bridge *bridge)
  : WContainerWidget()
{ 
  
  lm = new Light_Manager(bridge);

  log("DEBUG") << "LM made";
  std::string bridgename = bridge->getName();
  log("DEBUG")<<"BRIDGENAMEIS";
  log("DEBUG")<<bridgename;
  WText *title = new WText("<h3>"+bridgename+" Bridge:</h3>");
  addWidget(title);

  light_msg_ = new WText("");
  addWidget(light_msg_);
  addWidget(new WBreak());

  log("DEBUG")<<"gotobridgeview button made";
  WText *light_list_t= new WText("<h3><u>Light List for "+bridgename+":</u></h3>");
  
  addWidget(light_list_t);
  log("DEBUG") << "table soon to be made";
  light_list_ = new WTable(); 
  addWidget(light_list_);
  log("DEBUG") << "table made";

  addWidget(new WText("Light ID:"));
  light_id_ = new WLineEdit();                 // allow text input
  light_id_->setFocus();  
  addWidget(light_id_);
  addWidget(new WBreak());
                         

  cb=new WComboBox();
  cb->addItem("on");
  cb->addItem("bri");
  cb->addItem("hue");
  cb->addItem("name");
  cb->setCurrentIndex(0);     // Show 'ID' initially.
  cb->setMargin(10, Wt::Side::Right);
  addWidget(cb);
  
  light_state_ = new WLineEdit();                 // allow text input
  light_state_->setFocus();  
  addWidget(light_state_);
  addWidget(new WBreak());
  addWidget(new WText("Transition Time:"));

  
  light_tt_ = new WSpinBox();                 // allow int input
  light_tt_->setFocus();
  light_tt_->setMinimum(0);  
  light_tt_->setValue(0);
  light_tt_->setSingleStep(1);
  addWidget(light_tt_);
  addWidget(new WBreak());
  log("DEBUG") << "cb made";

  light_button_ = new WPushButton("Update Light");
  addWidget(light_button_);
  log("DEBUG") << "light_button made";
  show_button_ = new WPushButton("Show Lights");
  addWidget(show_button_);
  log("DEBUG")<<"showbutton made";

  
  
  addWidget(new GroupView(lm));
  addWidget(new ScheduleView(lm));
  
  goto_bridgeview_button = new WPushButton("Hide");
  addWidget(goto_bridgeview_button);
 
  show_button_->clicked().connect(this,&LightView::showLightList);
  light_button_->clicked().connect(this, &LightView::UpdateLight);
  goto_bridgeview_button->clicked().connect(this, &LightView::clearView);

  //Create Music Mode Button
  addWidget(new WBreak());
  spotify_view_button = new WPushButton("Music Mode");
  addWidget(spotify_view_button);
  spotify_view_button->clicked().connect(this, &LightView::createSpotifyView);

}

void LightView::clearFields(){
  light_id_->setText("");
  light_state_->setText("");
  light_tt_->setValue(0);
}
void LightView::UpdateLight(){
  if (cb->currentText()=="name"){
    if (lm->setLightName(light_id_->text().toUTF8(), light_state_->text().toUTF8())){//first param should be light_id_->text()->toUTF8()
      light_msg_->setText("name successfully updated");
    }
    else {
      light_msg_->setText("name could not be updated");
    }

  }
  else{
  	//if setting "on" state
  	if(cb->currentText()=="on"){
  		bool b;
  		if(light_state_->text()=="true"){
        Wt::log("LIGHTSTATEBOOLEAN")<<"REACHED";
  			b=true;
  		}
  		else{
  			b=false;
  		}
      //if request sent successfully
  		if(lm->setLightState(light_id_->text().toUTF8(),cb->currentText().toUTF8(),b)){
  			light_msg_->setText("light successfully updated");
  		}
  		else{
  			light_msg_->setText("light could not be updated");
  		}
  	}else{
    //first param should be light_id_->text()->toUTF8()
    if(lm->setLightState(light_id_->text().toUTF8(), cb->currentText().toUTF8(), light_state_->text().toUTF8(), light_tt_->value())){
      light_msg_->setText("light successfully updated");
    }else{
      light_msg_->setText("light could not be updated");
    }
  }}
  lm->getLights();
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
  Json::Object ob;
  Json::parse(ll,ob,false);
  log("SHOWINGLIGHTLIST")<<"BEFORE OB";
  int size=ob.size();
  for (int i=0;i<size;i++){
    Json::Object val=ob.get(std::to_string(i+1));
    std::string light_name=val.get("name").toString().orIfNull("name:(((");
    Json::Object states=val.get("state"); 
    bool isOn=states.get("on").toBool().orIfNull(false);
    int light_brightness=states.get("bri").toNumber().orIfNull(-11111);
    int light_hue=states.get("hue").toNumber().orIfNull(-222222);
    log("SHOWINGLIGHTLIST")<<"BEFOREPOPULATING";
    light_list_->elementAt(i+1, 0)->addWidget(new WText(std::to_string(i+1)));
    light_list_->elementAt(i+1, 1)->addWidget(new WText(light_name));
    light_list_->elementAt(i+1, 2)->addWidget(new WText(std::to_string(isOn)));
    light_list_->elementAt(i+1, 3)->addWidget(new WText(std::to_string(light_hue)));
    light_list_->elementAt(i+1, 4)->addWidget(new WText(std::to_string(light_brightness)));
  
  }
  log("DEBUG") << "about to add tablewidget";
  log("DEBUG") << "added tablewidget";
}


  void LightView::clearView(){
    this->clear();
  }

  void LightView::createSpotifyView(){
    if (!spotifyActive){
      addWidget(new SpotifyView(lm));
      spotifyActive = true;
      log("SPOTIFY") << "music mode active";
      }
  }
