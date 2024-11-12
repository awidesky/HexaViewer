#include <FileReader.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage : " << argv[0] << " <filenames>" << std::endl;
    return 0;
  }
  
  for (int i = 1; i < argc; i++) {
    std::cout << argv[i] << " :" << std::endl;
    FileReader fr{argv[i]};
    while (fr.readOnce())
      std::cout << fr.pollResult();

    std::cout << std::endl;
  }
}