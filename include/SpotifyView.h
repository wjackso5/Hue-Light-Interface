#ifndef SpotifyView_H_
#define SpotifyView_H_
#include "DBSession.h"
#include "Light_Manager.h"
#include "SpotifyManager.h"
#include <Wt/WContainerWidget>
#include <Wt/Http/Client>


class SpotifyView : public Wt::WContainerWidget
{
public:
  SpotifyView(Light_Manager* lights);
  Wt::Http::Client *client;
private:
  Wt::WPushButton *spotify_login_button;
  void handleHttpResponse(boost::system::error_code err,const Wt::Http::Message& response);
  void spotifyLogIn();
  void startMusicMode();
  void stopMusicMode();
  Wt::WLineEdit *bpmline;
  Wt::WLineEdit *lightid;
  Wt::WPushButton *startMusicModeButton;
  Wt::WPushButton *stopMusicModeButton;
  SpotifyManager* sm;
};

#endif//SpotifyView_H_