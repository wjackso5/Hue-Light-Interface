//Light View Headerfile
#ifndef LightView_H_
#define LightView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "Light_Manager.h"
#include "Bridge.h"
#include <Wt/WComboBox>
#include <Wt/WSpinBox>
class LightView : public Wt::WContainerWidget
{
public:
  LightView(Bridge *bridge);
private:
  std::string ll;
  Bridge bridge;
  Light_Manager *lm;
  Wt::WComboBox *cb;
  Wt::WTable *light_list_;
  Wt::WText *light_msg_;
  Wt::WLineEdit *light_id_;
  Wt::WLineEdit *light_state_;
  Wt::WSpinBox *light_tt_;
  Wt::WPushButton *light_button_;
  Wt::WPushButton *show_button_;
  Wt::WPushButton *goto_bridgeview_button;
  Wt::WPushButton *spotify_view_button;
  void clearFields();
  void showLightList();
  void UpdateLight();
  void clearView();
  void createSpotifyView();
  bool spotifyActive;
};
#endif