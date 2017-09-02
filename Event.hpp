#ifndef EVENT_HPP
#define EVENT_HPP

#include <memory>
#include <string>



namespace Labyrinth {

class GameEventHandler;
class GameEventServer;
class GameEvent;

enum class GameEventType : char {
  test
};

/*

  GameEvent class
  to be used polymorphically

*/

class GameEvent {
public:
  GameEvent(GameEventType type=GameEventType::test) : type(type) {}
  virtual ~GameEvent()=default;
  GameEventType getType() const {
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
  
*/
class GameEventHandler {
  friend GameEventServer;
public:
  GameEventHandler();
  virtual ~GameEventHandler();
  GameEventHandler(GameEventHandler&& other) noexcept;
  GameEventHandler& operator=(GameEventHandler&& other) noexcept;
  GameEventHandler(const GameEventHandler& other);
  GameEventHandler& operator=(const GameEventHandler& other);
  
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
