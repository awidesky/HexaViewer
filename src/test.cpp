#include <hexaviewer.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage : " << argv[0] << " <filenames>" << std::endl;
    return 0;
  }

  //if()

  for (int i = 1; i < argc; i++) {
    std::cout << argv[i] << " (size : " << hexa::getSize(argv[i]) << "bytes)" << std::endl;
    hexa::hexaViewer fr{argv[i]};
    while(fr) {
      fr.readOnce();
      std::cout << fr.pollResult();
    }
    std::cout << std::endl;
  }
}