#include <Wt/WApplication>
#include <Wt/WServer>
#include "Bridge.h"
#include "LightController.h"
#include "Session.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  Wt::WApplication *app = new Wt::WApplication(env);

  /* 
   * Wt comes in with a built in jquery binary that doesn't support
   * for example tr in my distribution. This work arround compiles fine
   * on the server (If you can press register on the home page then it 
   * should be working fine)
   *
   * Casey
   */
  bool somebool;
  somebool = app->requireJQuery("https://code.jquery.com/jquery-1.12.3.min.js");

  app->setTitle("Light Controller");

  new LightController(app->root());

  return app;
}


int main(int argc, char **argv)
{
  try {
    Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

    server.addEntryPoint(Wt::Application, createApplication);

    Session::configureAuth();


    server.run();
  } catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }
}
