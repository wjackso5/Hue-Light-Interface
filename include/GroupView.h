/**
*Header File from GroupView
*/
#ifndef GroupView_H_
#define GroupView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "LightGroup.h"
#include "Light_Manager.h"
#include "Bridge.h"
#include <Wt/WComboBox>
#include <Wt/WSpinBox>
class GroupView : public Wt::WContainerWidget
{
public:
  GroupView(Light_Manager *lightm);
private:
  int maxid;
  Wt::WComboBox *cb;
  Wt::WSpinBox *group_tt_;
  Light_Manager *lm;
  Wt::WTable *group_list_;
  Wt::WText *group_msg_;
  Wt::WLineEdit *group_id_;
  Wt::WLineEdit *group_state_;
  Wt::WLineEdit *group_name_;
  Wt::WLineEdit *group_light_list_;
  Wt::WPushButton *show_group_list;
  Wt::WPushButton *rm_group_button_;
  Wt::WPushButton *add_group_button_;
  Wt::WPushButton *group_button_;
  Wt::WPushButton *goto_bridgeview_button;
  std::string grouplist;
  void clearFields();
  void addGroup();
  void removeGroup();
  void showGroupList();
  void updateGroup();

};
#endif