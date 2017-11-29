#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/Http/Client>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/WLineEdit>
#include <Wt/Json/Object>
#include <Wt/WText>
#include <Wt/WVBoxLayout>
#include <Wt/WHBoxLayout>
#include <Wt/WPushButton>
#include <Wt/WAnchor>
#include <Wt/WStackedWidget>
#include <Wt/WLink>
#include "SpotifyView.h"
#include "SpotifyManager.h"
#include <string>

using namespace Wt;

SpotifyView::SpotifyView(Light_Manager* lights):WContainerWidget(){

  //Print the "Spotify" title
  WText *title = new WText("<h1>Spotify Music Sync:</h1>");
  addWidget(title);
  addWidget(new WBreak());

  client = new Http::Client(this);
  client->setTimeout(15);
  client->setMaximumResponseSize(10 * 1024);
  client->done().connect(boost::bind(&SpotifyView::handleHttpResponse, this, _1, _2));
  client->setFollowRedirect(true); 

/*
  //Info for HTTP responses
  char client_id[37] = {"9bc9cc02a0824d7eaed59d5e652c3bab"}; // Our Spotify Client id
  char client_secret[37] = {"131449d1316e4ceaa38b655787d9591c"}; // Our Spotify Client secret
  char redirect_uri[15] = {"localhost:10026"}; // Our redirect uri, should bring us back to main view, to be done in future
  char stateKey[20] = {"spotify_auth_state"};
  char scope[37] = {"user-read-private user-read-email"}; //the application requests authorization

  //Adding Button
  Wt::log("SPOTIFY")<<"Ready to Create Button";
  spotify_login_button = new WPushButton("Log In");
  Wt::log("SPOTIFY")<<"Button Created";
  addWidget(spotify_login_button);
  Wt::log("SPOTIFY")<<"Button Added, Ready to Link Function";
  spotify_login_button->clicked().connect(this, &SpotifyView::spotifyLogIn);
  Wt::log("SPOTIFY")<<"Function Added";
  */

  addWidget(new WText("BPM of the song you are currently listening to:"));
  bpmline = new WLineEdit();                 // allow text input
  addWidget(bpmline); 
  addWidget(new WBreak());

  addWidget(new WText("Light Id for light on which you would like music sync:"));
  lightid = new WLineEdit();                 // allow text input
  addWidget(lightid); 
  addWidget(new WBreak());
  Wt::log("SPOTIFY")<<"Buttons Created";

  startMusicModeButton = new WPushButton("Start Music Mode");
  addWidget(startMusicModeButton);
  startMusicModeButton->clicked().connect(this, &SpotifyView::startMusicMode);

  stopMusicModeButton = new WPushButton("Stop Music Mode");
  addWidget(stopMusicModeButton);
  stopMusicModeButton->clicked().connect(this, &SpotifyView::stopMusicMode);

  sm = new SpotifyManager(lights);

}
void SpotifyView::spotifyLogIn(){
  
  //BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! 
  //BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! 
  //BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! BUG TO BE FIXED!! 

  //Not sure which method to use to login! I'm supposed to get an auth code from it, so "get" make sense, 
  //but get doesn't redirect the user to the login page.
  //the WAnchor method causes an error on login, and doesnt allow the auth code to be sent back.

  //Method 1: Make get call to the Spotify Authorization. Result: nothing happens?
  /*
  if (client->get("https://accounts.spotify.com/en/authorize?%20&response_type=code&client_id=9bc9cc02a0824d7eaed59d5e652c3bab&scope=user-read-private%20user-read-email&redirect_uri=localhost:10026&state=state")){
       //WApplication::instance()->deferRendering();
       std::cerr << "No error." << std::endl;
  }else {
       std::cerr << "URL Error!" << std::endl;
  }

  //Method 2 (Open new tab with login info. Result: user can input information, but then gets Spotify error upon login.
    WAnchor *login;
  login = new WAnchor("https://accounts.spotify.com/en/authorize?%20&response_type=code&client_id=9bc9cc02a0824d7eaed59d5e652c3bab&scope=user-read-private%20user-read-email&redirect_uri=localhost:10026&state=state", "Spotify Log In", this);
  login -> setTarget(TargetNewWindow);
*/
}

void SpotifyView::handleHttpResponse(boost::system::error_code err, const Http::Message& response)
  {
   WApplication::instance()->resumeRendering();
   if (!err && response.status() == 200) {
      //parse the response information
    }
  }

void SpotifyView::startMusicMode(){
  int bpm = std::stoi(bpmline->text());
  sm->musicMode(bpm, lightid->text().toUTF8());
}

void SpotifyView::stopMusicMode(){
  sm->stopMusic();
}



