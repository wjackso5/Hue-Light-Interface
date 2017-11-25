#ifndef USER_H_
#define USER_H_

#include <Wt/WDateTime>
#include <Wt/Dbo/Types>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Auth/Dbo/AuthInfo>

#include <string>

class User;
//Linking the authentication information persistence class to the custom User information persistence class
typedef Wt::Auth::Dbo::AuthInfo<User> AuthInfo;
typedef Wt::Dbo::collection< Wt::Dbo::ptr<User> > Users;

class User
{
public:
  User();

  std::string name; /* a copy of auth info's user name */
  Wt::Dbo::collection< Wt::Dbo::ptr<AuthInfo> > authInfos;
  //Using the default persistence class from Wt::Auth::Dbo::AuthInfo
  template<class Action>
  void persist(Action& a)
  {

    Wt::Dbo::hasMany(a, authInfos, Wt::Dbo::ManyToOne, "user");
  }
};

DBO_EXTERN_TEMPLATES(User);

#endif // USER_H_
