
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>

#include "LightController.h"

using namespace Wt;

LightController::LightController(WContainerWidget *parent):
  WContainerWidget(parent)
{
  session_.login().changed().connect(this, &LightController::onAuthEvent);

  Auth::AuthModel *authModel = new Auth::AuthModel(Session::auth(),
						   session_.users(), this);
  authModel->addPasswordAuth(&Session::passwordAuth());
  authModel->addOAuth(Session::oAuth());

  Auth::AuthWidget *authWidget = new Auth::AuthWidget(session_.login());
  authWidget->setModel(authModel);
  authWidget->setRegistrationEnabled(true);

  WText *title = new WText("<h1>Light Controller</h1>");
  addWidget(title);

  addWidget(authWidget);

  mainStack_ = new WStackedWidget();
  addWidget(mainStack_);

  links_ = new WContainerWidget();
  links_->hide();
  addWidget(links_);

  testAnchor_ = new WAnchor("/test", "Testing", links_);
  testAnchor_->setLink(WLink(WLink::InternalPath, "/test"));

  testTwoAnchor_ = new WAnchor("/test2", "Test 2", links_);
  testTwoAnchor_->setLink(WLink(WLink::InternalPath, "/test2"));

  WApplication::instance()->internalPathChanged()
    .connect(this, &LightController::handleInternalPath);

  authWidget->processEnvironment();
}

void LightController::onAuthEvent()
{
  if (session_.login().loggedIn()) {
    links_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    mainStack_->clear();
    links_->hide();
  }
}

void LightController::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/test") {}
      //
    else if (internalPath == "/test2") {}
      //
    else
      WApplication::instance()->setInternalPath("/test",  true);
  }
}

void LightController::showGame()
{
  if (!game_) {
    //game_ = new HangmanWidget(session_.userName(), mainStack_);
    //game_->scoreUpdated().connect(&session_, &Session::addToScore);
  }

  //mainStack_->setCurrentWidget(game_);
}
