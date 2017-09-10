#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>
#include <string>
#include "EventFwd.hpp"


namespace Labyrinth {


enum class GameEventType : char {
  test
};

/*

  GameEvent class
  to potentially be used polymorphically
  if more detailed events are needed
  exception safe (derived class constructor may only be exception neutral)

*/

class GameEvent {
public:
  GameEvent(GameEventType type) : type(type) {}
  virtual ~GameEvent()=default;
  GameEventType getType() const noexcept {
    return type;
  }
private:
  GameEventType type;
};


/*
  GameEventHandler
  interface for event handler
  uses pimpl idiom
  derived class needs to instantiate operator()
  make sure copy/move's work okay for derived class

  class invariants:
  pimpl is non-null

*/
class GameEventHandler {
  friend GameEventServer;
public:
  // exception neutral
  GameEventHandler();
  // never throws
  virtual ~GameEventHandler();
  // delete copy, move and assignment
  // as these may lead to confusing behavior for client
  // e.g. should the copy also be registered?
  GameEventHandler(GameEventHandler&& other)=delete;
  GameEventHandler& operator=(GameEventHandler&& other)=delete;
  GameEventHandler(const GameEventHandler& other)=delete;
  GameEventHandler& operator=(const GameEventHandler& other)=delete;
  
  virtual void operator()(const GameEvent& event)=0;
  
  void register_with_server(GameEventServer& server);
  void unregister_with_server(GameEventServer& server);

private:
  void add_server(GameEventServer& server);
  void remove_server(GameEventServer& server);
  struct GEHImpl;
  std::unique_ptr<GEHImpl> pimpl;
};






/*

  GameEventServer
  uses pimpl idiom

*/
class GameEventServer {
  friend void GameEventHandler::register_with_server(GameEventServer& server);
  friend void GameEventHandler::unregister_with_server(GameEventServer& server);
  friend GameEventHandler::~GameEventHandler();
public:
  GameEventServer();
  ~GameEventServer();
  GameEventServer(GameEventServer&)=delete;
  GameEventServer& operator=(const GameEventServer&)=delete;

  void send_event_to_handlers(const GameEvent& event);


private:
  void add_handler(GameEventHandler& handler);
  void remove_handler(GameEventHandler& handler);

  struct GESImpl;
  std::unique_ptr<GESImpl> pimpl;
};












}


#endif
