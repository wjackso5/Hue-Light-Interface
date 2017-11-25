#ifndef LoginView_H_
#define LoginView_H_
#include <Wt/WContainerWidget>
#include "DBSession.h"
#include "Bridge_Manager.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
  class WContainerWidget;
}




class LoginView : public Wt::WContainerWidget
{
public:
  LoginView(Wt::WContainerWidget *parent = 0);



private:
  Wt::WContainerWidget *bridge_container_;
  Wt::WStackedWidget *mainStack_;
  
  
  Wt::WContainerWidget *links_;
  Wt::WAnchor *testAnchor_;
  Wt::WAnchor *testTwoAnchor_;
  DBSession session_;
  Bridge_Manager *bm;
  std::vector<Bridge> *bl;
  Wt::WText *bridge_list_;
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
void onAuthEvent();
void addBridge();
void editBridge();
void deleteBridge();
void showBridgeList();
void handleInternalPath(const std::string &internalPath);
};

#endif //LoginView_H_
