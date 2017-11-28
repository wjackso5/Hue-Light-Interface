#ifndef SpotifyView_H_
#define SpotifyView_H_
#include "DBSession.h"
#include <Wt/WContainerWidget>


class SpotifyView : public Wt::WContainerWidget
{
public:
  SpotifyView();
private:
  void handleHttpResponse();
};

#endif//SpotifyView_H_