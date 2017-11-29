
#ifndef SPOTIFY_MANAGER_H
#define SPOTIFY_MANAGER_H


#include "Light.h"
#include "LightGroup.h"
#include "Bridge.h"
#include "SpotifyView.h"
#include "Light_Manager.h"
#include <Wt/Http/Client>
#include <string>

class SpotifyManager{

private:
	bool musicStopped;

public:
	SpotifyManager(Light_Manager* manager);
	void musicMode(int bpm, std::string lightid);
	Light_Manager* lm;
	void stopMusic();
};

#endif //SPOTIFY_MANAGER_H