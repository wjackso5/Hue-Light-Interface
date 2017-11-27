//GroupView Headerfile
#ifndef GroupView_H_
#define GroupView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Light.h"
#include "LightGroup.h"
#include "Light_Manager.h"
#include "Bridge.h"
class GroupView : public Wt::WContainerWidget
{
public:
  GroupView(Light_Manager *lm);
private:
  Light_Manager *lm;
  //Light_Manager *lm;
  std::vector<LightGroup*> gl;
  Wt::WTable *group_list_;
  Wt::WText *group_msg_;
  Wt::WLineEdit *group_id_;
  Wt::WLineEdit *group_state_;
  Wt::WPushButton *group_button_;
  Wt::WPushButton *goto_bridgeview_button;
  void clearFields();
  void showGroupList();
  void UpdateGroup();
};
#endif