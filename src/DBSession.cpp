#include "DBSession.h"
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

  //Authentication services
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

/**
*Constructor
*Setting up the database session
*Mapping each model schema to the corresponding table
**/
DBSession::DBSession()
  : sqlite3_(WApplication::instance()->appRoot() + "light.db")
{

  session_.setConnection(sqlite3_);
  sqlite3_.setProperty("show-queries", "true");
  //Auth
  session_.mapClass<User>("user");
  session_.mapClass<AuthInfo>("auth_info");
  session_.mapClass<AuthInfo::AuthIdentityType>("auth_identity");
  session_.mapClass<AuthInfo::AuthTokenType>("auth_token");
  //Bridge
  session_.mapClass<Bridge>("bridge");


  
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

    //users_ the user class???
  

  transaction.commit();
}catch (...) {
    Wt::log("info") << "User:::::::::Using existing database";
  }
}




DBSession::~DBSession()
{
  delete users_;
}


void DBSession::configureAuth()
{
  //"Remember-me" functionality
  myAuthService.setAuthTokensEnabled(true, "lightcookie");
  //Email verification
  myAuthService.setEmailVerificationEnabled(true);

  Auth::PasswordVerifier *verifier = new Auth::PasswordVerifier();
  verifier->addHashFunction(new Auth::BCryptHashFunction(7));

  myPasswordService.setVerifier(verifier);
  myPasswordService.setStrengthValidator(new Auth::PasswordStrengthValidator());
  myPasswordService.setAttemptThrottlingEnabled(true);

  if (Auth::GoogleService::configured())
    myOAuthServices.push_back(new Auth::GoogleService(myAuthService));
}



/**
*Return the user name of the current logged in user
**/
dbo::ptr<User> DBSession::user() const
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

/**
*Return the user name of the current logged in user
**/
std::string DBSession::userName() const
{
  if (login_.loggedIn())
    return login_.user().identity(Auth::Identity::LoginName).toUTF8();
  else
    return std::string();
}

Auth::AbstractUserDatabase& DBSession::users()
{
  return *users_;
}

const Auth::AuthService& DBSession::auth()
{
  return myAuthService;
}

const Auth::AbstractPasswordService& DBSession::passwordAuth()
{
  return myPasswordService;
}

const std::vector<const Auth::OAuthService *>& DBSession::oAuth()
{
  return myOAuthServices;
}

/**
*Initialize the vector<Bridge> object in the bridge manager 
*by finding all existing bridges in the dabatase to the vector
*and pushing them to the vector.
*@param std::vector<Bridge> *bridgeList : the pointer to the 
*vector of Bridgesin the bridge manager class
**/

void DBSession::initBM(std::vector<Bridge*> *bridgeList){
  typedef dbo::collection< dbo::ptr<Bridge> > Bridges;
  dbo::Transaction transaction(session_);
  try{
    Bridges bridges=session_.find<Bridge>();
    Wt::log("HHHHHHHHHHHHHHHHHH")<< bridges.size();
      for (const dbo::ptr<Bridge> &bridge: bridges)
      { 
        Bridge *next=new Bridge();
        next->name=bridge->name;
        next->location=bridge->location;
        next->ip=bridge->ip;
        next->port=bridge->port;
        next->username=bridge->username;
        bridgeList->push_back(next);
      }
  }catch(...)
  {
    Wt::log("info")<<"Populating failed";
  }
}

/**
*add a new Bridge to the database
*@param Bridge *b : the pointer to the bridge to be added
**/
void DBSession::addBridge(Bridge *b){

  dbo::Transaction transaction(session_);
  Wt::log("info")<<"Adding";
  Wt::log("info")<<b;
  try{
    dbo::ptr<Bridge> br=session_.add(std::move(b));
    transaction.commit();
  }catch(...)
  {
    Wt::log("info")<<"can't add";
  }
}
/**
*add a new Bridge to the database
*@param Bridge *b : the pointer to the bridge to be added
**/
void DBSession::editBridge(Bridge *b){
  dbo::Transaction transaction(session_);
  Wt::log("info")<<"Editing";
  Wt::log("info")<<b->getName();
  try{
    dbo::ptr<Bridge> br=session_.find<Bridge>().where("name = ?").bind(b->getName());
    Wt::log("info")<<"Editing location:";
    Wt::log("info")<<b->getLocation();
    br.modify()->location=b->getLocation();
    br.modify()->ip=b->getIp();
    br.modify()->port=b->getPort();
    br.modify()->username=b->getUsername();
    transaction.commit();
  }catch(...)
  {
    Wt::log("info")<<"can't edit";
  }
}

/**
*remove a exisiting Bridge from the database
*@param Bridge *b : the pointer to the bridge to be removed
**/
void DBSession::deleteBridge(Bridge *b){
  dbo::Transaction transaction(session_);
  Wt::log("info")<<"Deleting";
  Wt::log("info")<<b;
  try{
    dbo::ptr<Bridge> br=session_.find<Bridge>().where("name = ?").bind(b->getName());
    br.remove();
  }catch(...)
  {
    Wt::log("info")<<"can't remove";
  }
}





