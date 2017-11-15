#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_
#include <Wt/WContainerWidget>
#include "Session.h"
#include "Bridge_Manager.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
  class WContainerWidget;
}


class Session;

class LightController : public Wt::WContainerWidget
{
public:
  LightController(Wt::WContainerWidget *parent = 0);



private:
  Wt::WContainerWidget *bridge_container_;
  Wt::WStackedWidget *mainStack_;
  
  
  Wt::WContainerWidget *links_;
  Wt::WAnchor *testAnchor_;
  Wt::WAnchor *testTwoAnchor_;
  Session session_;
  Bridge_Manager *bm;



  Wt::WLineEdit *bridge_name_;
  Wt::WLineEdit *bridge_location_;
  Wt::WLineEdit *bridge_ip_;
  Wt::WLineEdit *bridge_port_;
  Wt::WLineEdit *bridge_username_;
  Wt::WPushButton *create_bridge_button_;
  Wt::WPushButton *delete_bridge_button_;
  Wt::WPushButton *edit_bridge_button_;

void onAuthEvent();
void addBridge();
void editBridge();
void deleteBridge();
void handleInternalPath(const std::string &internalPath);
};

#endif //LIGHTCONTROLLER_H_
