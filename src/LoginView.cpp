
#include <Wt/WAnchor>
#include <Wt/WText>
#include <Wt/WLineEdit>
#include <Wt/WContainerWidget>
#include <Wt/WStackedWidget>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WApplication>
#include <Wt/Auth/AuthWidget>
#include "LoginView.h"
#include "Bridge.h"
#include "BridgeView.h"
#include <string>
#include <vector>

using namespace Wt;

LoginView::LoginView(WContainerWidget *parent): WContainerWidget(parent)
{


  session_.login().changed().connect(this, &LoginView::onAuthEvent);

  Auth::AuthModel *authModel = new Auth::AuthModel(DBSession::auth(),
						   session_.users(), this);
  authModel->addPasswordAuth(&DBSession::passwordAuth());
  authModel->addOAuth(DBSession::oAuth());

  Auth::AuthWidget *authWidget = new Auth::AuthWidget(session_.login());
  authWidget->setModel(authModel);
  authWidget->setRegistrationEnabled(true);
  
  addWidget(new WText("Logged in as: "));
  addWidget(authWidget);

  mainStack_ = new WStackedWidget();
  addWidget(mainStack_);


  links_ = new WContainerWidget();
  links_->hide();
  addWidget(links_);

  //bridgeAnchor_ = new WAnchor("/bridge", "Bridge", links_);
  //bridgeAnchor_->setLink(WLink(WLink::InternalPath, "/bridge"));

  // testTwoAnchor_ = new WAnchor("/test2", "Test 2", links_);
  // testTwoAnchor_->setLink(WLink(WLink::InternalPath, "/test2"));

  WApplication::instance()->internalPathChanged()
    .connect(this, &LoginView::handleInternalPath);

  authWidget->processEnvironment();
};

void LoginView::onAuthEvent()
{
  if (session_.login().loggedIn()) {
    links_->show();
    //bridge_container_->show();
    handleInternalPath(WApplication::instance()->internalPath());
  } else {
    //bridge_container_->hide();
    mainStack_->clear();
    links_->hide();
  }
}

void LoginView::handleInternalPath(const std::string &internalPath)
{
  if (session_.login().loggedIn()) {
    if (internalPath == "/bridge") {
      mainStack_->addWidget(new BridgeView());
    }
    else if (internalPath == "/test2") {}
      //
    else
      WApplication::instance()->setInternalPath("/bridge",  true);
  }
}


  //mainStack_->setCurrentWidget(game_);
