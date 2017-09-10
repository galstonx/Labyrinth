#include <iostream>
#include "Event.hpp"
using namespace Labyrinth;
using std::cout;
using std::endl;

class MyGameEventHandler : public GameEventHandler {
public:
  void operator() (const GameEvent& event) {
    cout << "MyGameEventHandler::operator()" << endl;
  }
};

class MyGameEventHandler2 : public GameEventHandler {
public:
  void operator() (const GameEvent& event) {
    cout << "MyGameEventHandler2::operator()" << endl;
  }
};


int main() {
  // testing basic operation
  cout << "Testing basic operation" << endl;
  GameEvent event(GameEventType::test);
  GameEventServer& server=*(new GameEventServer);
  MyGameEventHandler handler1;
  MyGameEventHandler2 handler2;
  MyGameEventHandler& handler3=*(new MyGameEventHandler);
  handler1.register_with_server(server);
  handler2.register_with_server(server);
  handler3.register_with_server(server);
  server.send_event_to_handlers(event);
  cout << endl;
  handler2.unregister_with_server(server);
  server.send_event_to_handlers(event);
  cout << endl;
  delete &handler3;
  server.send_event_to_handlers(event);
  cout << endl;
  delete &server;
  GameEventServer server1;
  GameEventServer server2;
  handler1.register_with_server(server1);
  handler1.register_with_server(server2);
  server1.send_event_to_handlers(event);
  cout << endl;
  server2.send_event_to_handlers(event);

  // test implicit conversion

}
