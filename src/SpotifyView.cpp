#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/Json/Parser>
#include <Wt/Json/Value>
#include <Wt/Json/Object>
#include <Wt/WText>
#include "SpotifyView.h"

using namespace Wt;

SpotifyView::SpotifyView(WContainerWidget *parent):WContainerWidget(parent)
{

WText *title = new WText("<h1>Spotify Music Sync:</h1>");
addWidget(title);
addWidget(new WBreak());

char client_id[37] = {"9bc9cc02a0824d7eaed59d5e652c3bab"}; // Our Spotify Client id
char client_secret[37] = {"131449d1316e4ceaa38b655787d9591c"}; // Our Spotify Client secret
char redirect_uri[15] = {"REDIRECT_URI"}; // Our redirect uri, should bring us back to main view, to be done in future

char state[37] = {""}; //Generate a random string containing numbers and letters

char stateKey[20] = {"spotify_auth_state"};

//WApplication.setCookie(stateKey, state, 1800);

//const std::string & 	domain = "",
//const std::string & 	path = "",
//bool 	secure = false 
//name is statekey, value is state

char scope[37] = {"user-read-private user-read-email"}; //the application requests authorization
}
/*

  res.redirect('https://accounts.spotify.com/authorize?' +
    querystring.stringify({
      response_type: 'code',
      client_id: client_id,
      scope: scope,
      redirect_uri: redirect_uri,
      state: state
    }));
});
*/