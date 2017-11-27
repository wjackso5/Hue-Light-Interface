//Light View Headerfile
#ifndef LightView_H_
#define LightView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "Light_Manager.h"
#include "Bridge.h"
class lightView : public Wt::WContainerWidget
{
public:
  lightView();
private:
  Bridge bridge;
  Light_Manager *lm;
  std::vector<light*> ll;
  Wt::WTable *light_list_;
  Wt::WText *light_msg_;
  Wt::WLineEdit *light_id_;
  Wt::WLineEdit *light_state_;
  Wt::WPushButton *light_button_;
  Wt::WPushButton *goto_bridgeview_button;
  void clearFields();
  void showLightList();
  void createBridgeView();
};
#endif