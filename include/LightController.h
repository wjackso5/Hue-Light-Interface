

#ifndef LIGHTCONTROLLER_H_
#define LIGHTCONTROLLER_H_

#include <Wt/WContainerWidget>

#include "Session.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
}

class HangmanWidget;
class HighScoresWidget;
class Session;

class LightController : public Wt::WContainerWidget
{
public:
  LightController(Wt::WContainerWidget *parent = 0);

  void handleInternalPath(const std::string &internalPath);

private:
  Wt::WStackedWidget *mainStack_;
  HangmanWidget *game_;
  HighScoresWidget *scores_;
  Wt::WContainerWidget *links_;
  Wt::WAnchor *testAnchor_;
  Wt::WAnchor *testTwoAnchor_;

  Session session_;

  void onAuthEvent();
  void showGame();
};

#endif //LIGHTCONTROLLER_H_
