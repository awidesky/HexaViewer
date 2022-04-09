#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include "../include/FileReader.hpp"


int main() {

  std::string filePath = "testBinary/tt.txt";

  FileReader fr{filePath, 10};
  fr.readOnce(); std::cout << fr.pollResult();
  fr.readOnce(); std::cout << fr.pollResult();
  fr.readOnce(); std::cout << fr.pollResult();
  std::cout << fr.readAll().copyResult() << std::endl;
}