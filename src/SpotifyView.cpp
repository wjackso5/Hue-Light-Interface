using namespace Wt;

SpotifyView::SpotifyView(WContainerWidget *parent):WContainerWidget(parent)
{

}

char client_id[] = '9bc9cc02a0824d7eaed59d5e652c3bab'; // Our Spotify Client id
char client_secret[] = '131449d1316e4ceaa38b655787d9591c'; // Our Spotify Client secret
char redirect_uri[] = 'REDIRECT_URI'; // Our redirect uri, should bring us back to main view, to be done in future

//char state[] = Generate a random string containing numbers and letters

char stateKey[] = 'spotify_auth_state';
/*
WApplication::setCookie(statekey, state, 1800)

//const std::string & 	domain = "",
//const std::string & 	path = "",
//bool 	secure = false 
//name is statekey, value is state

char scope[] = 'user-read-private user-read-email'; //the application requests authorization

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