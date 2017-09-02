#ifndef LABYRINTH_LEVEL_HPP
#define LABYRINTH_LEVEL_HPP

#include <vector>
#include <string>
#include "Event.hpp"

namespace Labyrinth {

typedef size_t coord;

struct Position {
  coord row;
  coord col;
  Position(coord row,coord col) : row(row), col(col) {}
};

enum class CellType : char {
  empty=' ',
    wall='#',
    water,
    grass,
    door,
    stairs_up,
    stairs_down,
    hole
};

char cell_type_to_char(CellType cell_type);

class Cell {
public:
  //constructors
  Cell(Position position,CellType cell_type) : position(position), cell_type(cell_type) {}
  Cell() : position(0,0), cell_type(CellType::empty) {}
  //getters
  Position getPosition() const {return position;}
  CellType getCellType() const {return cell_type;}
protected:
private:
  Position position;
  CellType cell_type;
};


class Level {
public:
  //constructors
  Level(coord rows,coord cols,int seed); // randomly generate
  Level(std::string data_file); // generate from data_file
  //getters
  coord getRows() const {return rows;}
  coord getCols() const {return cols;}
  const Cell& getCell(coord row,coord col) const {
    return cells[row][col];
  }
protected:
private:
  coord rows;
  coord cols;
  std::vector<std::vector<Cell>> cells;
  std::vector<GameEventHandler*> event_handlers;
};


//display
std::ostream& operator<<(std::ostream& os,const Level& level);
std::ostream& operator<<(std::ostream& os,const Cell& cell);

//other helpers
CellType random_wall(int seed);



}




#endif
