
#ifndef DBSESSION_H_
#define DBSESSION_H_

#include <vector>

#include <Wt/Auth/Login>

#include <Wt/Dbo/Session>
#include <Wt/Dbo/ptr>
#include <Wt/Dbo/backend/Sqlite3>

#include "User.h"
#include "Bridge.h"

//using the Wt::Auth::Dbo::UserDatabase implementation using AuthInfo, 
//for which we declared a type alias earlier on in User.h
typedef Wt::Auth::Dbo::UserDatabase<AuthInfo> UserDatabase;

class DBSession
{
public:
  DBSession();
  ~DBSession();

  static void configureAuth();

  Wt::Auth::AbstractUserDatabase& users();
  //return the current login information,manipulated by login/logout widgets
  Wt::Auth::Login& login() { return login_; }

  /*
   * These methods deal with the currently logged in user
   */
  std::string userName() const;

  static const Wt::Auth::AuthService& auth();
  static const Wt::Auth::AbstractPasswordService& passwordAuth();
  static const std::vector<const Wt::Auth::OAuthService *>& oAuth();

  void initBM(std::vector<Bridge> *bridgeList);
  void addBridge(Bridge *b);
  void editBridge(Bridge *b);
  void deleteBridge(Bridge *b);

private:
  Wt::Dbo::backend::Sqlite3 sqlite3_;
  mutable Wt::Dbo::Session session_;
  UserDatabase *users_;
  Wt::Auth::Login login_;

  Wt::Dbo::ptr<User> user() const;
};

#endif //DBSESSION_H_
