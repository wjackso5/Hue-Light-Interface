#ifndef SpotifyView_H_
#define SpotifyView_H_
#include "DBSession.h"

namespace Wt {
  class WStackedWidget;
  class WAnchor;
  class WContainerWidget;
}


class SpotifyView : public Wt::WContainerWidget
{
public:
  SpotifyView(Wt::WContainerWidget *parent = 0);