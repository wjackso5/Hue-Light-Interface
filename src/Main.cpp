#include <Wt/WApplication>
#include <Wt/WServer>
#include "Bridge.h"
#include "LightController.h"
#include "Session.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  Wt::WApplication *app = new Wt::WApplication(env);

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
