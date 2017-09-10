#include "Event.hpp"
#include <set>

namespace Labyrinth {


/*

  GameEventServer

*/

struct GameEventServer::GESImpl {
  std::set<GameEventHandler*> event_handlers;
};

GameEventServer::GameEventServer() : pimpl(std::make_unique<GESImpl>()) {
}

GameEventServer::~GameEventServer() {
  for(auto iter : pimpl->event_handlers) {
    iter->remove_server(*this);
  }
}

void GameEventServer::add_handler(GameEventHandler& handler) {
  (pimpl->event_handlers).insert(&handler);
}

void GameEventServer::remove_handler(GameEventHandler& handler) {
  (pimpl->event_handlers).erase(&handler);
}

void GameEventServer::send_event_to_handlers(const GameEvent& event) {
  for(auto iter : pimpl->event_handlers) {
    (*iter)(event);
  }
}

/*

GameEventHandler

*/


struct GameEventHandler::GEHImpl {
  GEHImpl() {}
  std::set<GameEventServer*> event_servers;
};

GameEventHandler::GameEventHandler() : pimpl(std::make_unique<GEHImpl>()) {
}

GameEventHandler::~GameEventHandler() {
  for(auto iter : pimpl->event_servers) {
    iter->remove_handler(*this);
  }
}


void GameEventHandler::register_with_server(GameEventServer& server) {
  add_server(server);
  server.add_handler(*this);
}

void GameEventHandler::unregister_with_server(GameEventServer& server) {
  remove_server(server);
  server.remove_handler(*this);
}

void GameEventHandler::add_server(GameEventServer& server) {
  pimpl->event_servers.insert(&server);
}

void GameEventHandler::remove_server(GameEventServer& server) {
  pimpl->event_servers.erase(&server);
}



}
