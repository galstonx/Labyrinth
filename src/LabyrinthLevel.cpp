#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include "LabyrinthLevel.hpp"

namespace Labyrinth {

// helpers

std::ostream& operator<<(std::ostream& os,const Level& level) {
  for(coord i=0;i<level.getRows();++i) {
    for(coord j=0;j<level.getCols();++j) {
      os << level.getCell(i,j) << " ";
    }
    os << std::endl;
  }
  return os;
}

std::ostream& operator<<(std::ostream& os,const Cell& cell) {
  os << cell_type_to_char(cell.getCellType());
  return os;
}


CellType random_wall(int seed) {
  static std::uniform_int_distribution<unsigned> u(0,1);
  static std::default_random_engine e(seed);
  if(u(e)==0) return CellType::empty;
  return CellType::wall;
}

char cell_type_to_char(CellType cell_type) {
  if(cell_type==CellType::wall) return '#';
  return ' '; //default is return empty
}

// Cell



// Level

Level::Level(std::string data_file) {
  std::ifstream input(data_file);
  input >> rows >> cols;
  cells=std::vector<std::vector<Cell>>(rows,std::vector<Cell>(cols));
  // getline to get to end of current line
  std::string line;
  std::getline(input,line);
  CellType cell_type;
  for(coord i=0;i<rows;++i) {
    getline(input,line);
    for(coord j=0;j<cols;++j) {
      if(line[j]==' ') cell_type=CellType::empty;
      else if(line[j]=='#') cell_type=CellType::wall;
      cells[i][j]=Cell(Position(i,j),cell_type);
    }
  }
}

Level::Level(coord rows,coord cols,int seed) : rows(rows), cols(cols) {
  cells.reserve(rows);
  for(coord i=0;i<rows;++i) {
    cells[i].reserve(cols);
    for(coord j=0;j<cols;++j) {
      cells[i].push_back(Cell(Position(i,j),random_wall(seed)));
    }
  }
}


};
