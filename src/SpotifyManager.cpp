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
#include "Bridge.h"
#include <string>
#include "Light_Manager.h"
#include "Light.h"
#include "LightGroup.h"
#include "Schedule.h"
#include "SpotifyManager.h"

using namespace Wt;

SpotifyManager::SpotifyManager(Light_Manager* manager){
    lm = manager;
  };

void SpotifyManager::musicMode(int bpm, std::string lightid){
  int secondperpulse = ((60/bpm)*4);
  musicStopped = false;
  while (musicStopped == false){
    lm->setLightState(lightid, "hue", std::to_string(200), secondperpulse);
    lm->setLightState(lightid, "hue", std::to_string(300),secondperpulse);
    lm->setLightState(lightid, "hue", std::to_string(100),secondperpulse);
    lm->setLightState(lightid, "hue", std::to_string(50),secondperpulse);
    std::cerr << "Music Mode Active" << std::endl;
  }std::cerr << "Music Mode Stopped" << std::endl;
}

void SpotifyManager::stopMusic(){
  musicStopped = true;
}

  
  