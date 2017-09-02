#include <iostream>
#include "LabyrinthLevel.hpp"
using namespace std;
using namespace Labyrinth;

int main() {
  Level level1(15,15,2);
  cout << level1 << endl << endl;
  Level level2("../test/level1_test_data.txt");
  cout << level2;
  return 0;
}
