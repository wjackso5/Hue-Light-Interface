//Light View Headerfile
#ifndef LightView_H_
#define LightView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "Light_Manager.h"
#include "Bridge.h"
class LightView : public Wt::WContainerWidget
{
public:
  LightView(Bridge *bridge);
private:
  std::string ll;
  Bridge bridge;
  Light_Manager *lm;
  // std::vector<Light*> *ll;
  Wt::WTable *light_list_;
  Wt::WText *light_msg_;
  Wt::WLineEdit *light_id_;
  Wt::WLineEdit *light_state_;
  Wt::WPushButton *light_button_;
  Wt::WPushButton *show_button_;
  Wt::WPushButton *goto_bridgeview_button;
  void clearFields();
  void showLightList();
  void UpdateLight();
  void clearView();
};
#endif