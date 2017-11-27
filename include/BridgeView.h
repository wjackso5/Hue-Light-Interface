//BridgeView Header
#ifndef BridgeView_H_
#define BridgeView_H_
#include <Wt/WContainerWidget>
#include <Wt/WTable>
#include "Bridge_Manager.h"
#include "Bridge.h"
class BridgeView : public Wt::WContainerWidget
{
public:
  BridgeView();
private:
  DBSession session_;
  Bridge_Manager *bm;
  Bridge *btv;
  std::string btv_name;
  std::vector<Bridge *> bl;
  Wt::WTable *bridge_list_;
  Wt::WText *bridge_msg_;
  Wt::WLineEdit *bridge_name_;
  Wt::WLineEdit *bridge_location_;
  Wt::WLineEdit *bridge_ip_;
  Wt::WLineEdit *bridge_port_;
  Wt::WLineEdit *bridge_username_;
  Wt::WPushButton *create_bridge_button_;
  Wt::WPushButton *delete_bridge_button_;
  Wt::WPushButton *edit_bridge_button_;
  Wt::WPushButton *show_bridge_list_;
  void clearBridgeFields();
  void addBridge();
  void editBridge();
  void deleteBridge();
  void showBridgeList();
  void createLightView();
};
#endif