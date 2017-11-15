#include "Session.h"
#include "Bridge.h"

#include "Wt/Auth/AuthService"
#include "Wt/Auth/HashFunction"
#include "Wt/Auth/PasswordService"
#include "Wt/Auth/PasswordStrengthValidator"
#include "Wt/Auth/PasswordVerifier"
#include "Wt/Auth/GoogleService"
#include "Wt/Auth/Dbo/AuthInfo"
#include "Wt/Auth/Dbo/UserDatabase"

#include <Wt/WApplication>
#include <Wt/WLogger>

#ifndef WT_WIN32
#include <unistd.h>
#endif

using namespace Wt;
namespace dbo = Wt::Dbo;

namespace {

  class MyOAuth : public std::vector<const Auth::OAuthService *>
  {
  public:
    ~MyOAuth()  
    {
      for (unsigned i = 0; i < size(); ++i)
  delete (*this)[i];
    }
  };

  Auth::AuthService myAuthService;
  Auth::PasswordService myPasswordService(myAuthService);
  MyOAuth myOAuthServices;
}

void Session::configureAuth()
{
  myAuthService.setAuthTokensEnabled(true, "lightcookie");
  myAuthService.setEmailVerificationEnabled(true);

  Auth::PasswordVerifier *verifier = new Auth::PasswordVerifier();
  verifier->addHashFunction(new Auth::BCryptHashFunction(7));

  myPasswordService.setVerifier(verifier);
  myPasswordService.setStrengthValidator(new Auth::PasswordStrengthValidator());
  myPasswordService.setAttemptThrottlingEnabled(true);

  if (Auth::GoogleService::configured())
    myOAuthServices.push_back(new Auth::GoogleService(myAuthService));
}

Session::Session()
  : sqlite3_(WApplication::instance()->appRoot() + "light.db")
{
  session_.setConnection(sqlite3_);
  sqlite3_.setProperty("show-queries", "true");
	session_.mapClass<Bridge>("_bridge");
	session_.mapClass<User>("_user");
	 session_.mapClass<AuthInfo>("_auth_info");
	session_.mapClass<AuthInfo::AuthIdentityType>("_auth_identity");
	session_.mapClass<AuthInfo::AuthTokenType>("_auth_token");

 	 //session_.mapClass<Bridge>("bridge");


  users_ = new UserDatabase(session_);

  dbo::Transaction transaction(session_);
  try {
    session_.createTables();

    /*
     * Add a default guest/guest account
     */
    Auth::User guestUser = users_->registerNew();
    guestUser.addIdentity(Auth::Identity::LoginName, "guest");
    myPasswordService.updatePassword(guestUser, "guest");

    /*
     * Add a bridge
     */
  

  transaction.commit();
}catch (...) {
    Wt::log("info") << "User:::::::::Using existing database";
  }
}




Session::~Session()
{
  delete users_;
}

void Session::addBridge(Bridge *b){

  dbo::Transaction transaction(session_);
  Wt::log("info")<<b;
  try{
  dbo::ptr<Bridge> br=session_.add(std::move(b));
  transaction.commit();
}catch(...)
{
  Wt::log("info")<<"can't add";
}
}

void Session::initBM(std::vector<Bridge> *bridgeList){
  typedef dbo::collection< dbo::ptr<Bridge> > Bridges;
   dbo::Transaction transaction(session_);

  Bridges bridges=session_.find<Bridge>();
  Wt::log("info")<<"# of bridges"+bridges.size();
  try{
  for (const dbo::ptr<Bridge> &bridge: bridges)
  { 
    Bridge *next=new Bridge();
    next->name=bridge->name;
    next->location=bridge->location;
    next->ip=bridge->ip;
    next->bridgeNum=bridge->bridgeNum;
    next->userName=bridge->userName;
    bridgeList->push_back(*next);

  }}catch(...)
  {
    Wt::log("info")<<"Populating failed";
  }
}

dbo::ptr<User> Session::user() const
{
  if (login_.loggedIn()) {
    dbo::ptr<AuthInfo> authInfo = users_->find(login_.user());
    dbo::ptr<User> user = authInfo->user();

    if (!user) {
      user = session_.add(new User());
      authInfo.modify()->setUser(user);
    }

    return user;
  } else
    return dbo::ptr<User>();
}

std::string Session::userName() const
{
  if (login_.loggedIn())
    return login_.user().identity(Auth::Identity::LoginName).toUTF8();
  else
    return std::string();
}

// *Session Session::getSession(){
//   return &this;
// }

Auth::AbstractUserDatabase& Session::users()
{
  return *users_;
}

const Auth::AuthService& Session::auth()
{
  return myAuthService;
}

const Auth::AbstractPasswordService& Session::passwordAuth()
{
  return myPasswordService;
}

const std::vector<const Auth::OAuthService *>& Session::oAuth()
{
  return myOAuthServices;
}


