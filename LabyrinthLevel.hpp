#ifndef LABYRINTH_LEVEL_HPP
#define LABYRINTH_LEVEL_HPP

#include <vector>
#include <string>

namespace Labyrinth {

typedef size_t coord;
typedef char code_type;

struct Position {
  coord row;
  coord col;
  Position(coord row,coord col) : row(row), col(col) {}
};


class Cell {
public:
  //constructors
  Cell(Position position,code_type code) : position(position), code(code) {}
  Cell() : position(0,0), code(' ') {}
  //getters
  Position getPosition() const {return position;}
  char getChar() const {return (char) code;}
protected:
private:
  Position position;
  code_type code;
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
};


//display
std::ostream& operator<<(std::ostream& os,const Level& level);
std::ostream& operator<<(std::ostream& os,const Cell& cell);

//other helpers
code_type random_wall(int seed);



}




#endif
