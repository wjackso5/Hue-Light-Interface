#ifndef LoginView_H_
#define LoginView_H_
#include <Wt/WContainerWidget>
#include "Session.h"
#include "Bridge_Manager.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
  class WContainerWidget;
}


class Session;

class LoginView : public Wt::WContainerWidget
{
public:
  LoginView(Wt::WContainerWidget *parent = 0);



private:
  Wt::WStackedWidget *mainStack_;
  
  
  Wt::WContainerWidget *links_;
  Wt::WAnchor *bridgeAnchor_;
  Wt::WAnchor *testTwoAnchor_;
  Session session_;   

void onAuthEvent();

void handleInternalPath(const std::string &internalPath);
};

#endif //LoginView_H_
