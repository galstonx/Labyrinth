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


/*

GameEventHandler

*/


struct GameEventHandler::GEHImpl {

  std::set<GameEventServer*> event_servers;
};

GameEventHandler::GameEventHandler() : pimpl(std::make_unique<GEHImpl>()) {
}

GameEventHandler::~GameEventHandler() {
  for(auto iter : pimpl->event_servers) {
    iter->remove_handler(*this);
  }
}



GameEventHandler::GameEventHandler(GameEventHandler&& other) noexcept=default;

GameEventHandler& GameEventHandler::operator=(GameEventHandler&& other) noexcept=default;

GameEventHandler::GameEventHandler(const GameEventHandler& other) : pimpl(nullptr) {
  if(other.pimpl) pimpl=std::make_unique<GEHImpl>(*other.pimpl);
}

GameEventHandler& GameEventHandler::operator=(const GameEventHandler& other) {
  if(! other.pimpl) pimpl.reset();
  else if (! pimpl) pimpl = std::make_unique<GEHImpl>(*other.pimpl);
  else *pimpl=*other.pimpl;
  return *this;
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
