#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/Http/Client>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/WText>
#include "SpotifyView.h"

using namespace Wt;

SpotifyView::SpotifyView():WContainerWidget(){

  //Print the "Spotify" title
  WText *title = new WText("<h1>Spotify Music Sync:</h1>");
  addWidget(title);
  addWidget(new WBreak());

  //Set up info for HTTP responses
  char client_id[37] = {"9bc9cc02a0824d7eaed59d5e652c3bab"}; // Our Spotify Client id
  char client_secret[37] = {"131449d1316e4ceaa38b655787d9591c"}; // Our Spotify Client secret
  char redirect_uri[15] = {"REDIRECT_URI"}; // Our redirect uri, should bring us back to main view, to be done in future
  char state[37] = {""}; //Generate a random string containing numbers and letters
  char stateKey[20] = {"spotify_auth_state"};
  char scope[37] = {"user-read-private user-read-email"}; //the application requests authorization

  //Set up HTTP client
  Http::Client *client = new Http::Client(this);
  client->setTimeout(15);
  client->setMaximumResponseSize(10 * 1024);
  client->done().connect(boost::bind(&SpotifyView::handleHttpResponse, this, _1, _2));
  
  //Make get call to the Spotify Authorization
  if (client->get("https://accounts.spotify.com/en/authorize?%20&response_type=code&client_id=9bc9cc02a0824d7eaed59d5e652c3bab&scope=user-read-private%20user-read-email&redirect_uri=cs3307-pub.gaul.csd.uwo.ca:10026&state=state"))
       WApplication::instance()->deferRendering();
  else {
      // in case of an error in the %URL
  }

  //WApplication.setCookie(stateKey, state, 1800);

  void handleHttpResponse(boost::system::error_code err, const Http::Message& response)
  {
   WApplication::instance()->resumeRendering();
   if (!err && response.status() == 200) {
      //parse the response information
   }
}
