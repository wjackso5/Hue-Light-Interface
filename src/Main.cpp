#include <Wt/WApplication>
#include <Wt/WServer>
#include "Bridge.h"
#include "LoginView.h"
#include "Session.h"

Wt::WApplication *createApplication(const Wt::WEnvironment& env)
{
  Wt::WApplication *app = new Wt::WApplication(env);
  bool somebool;
  somebool = app->requireJQuery("https://code.jquery.com/jquery-1.12.3.min.js");

  app->setTitle("Log-in");

  new LoginView(app->root());

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
