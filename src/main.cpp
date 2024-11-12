#include <FileReader.hpp>

#include <iostream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage : " << argv[0] << " <filenames>" << std::endl;
    return 0;
  }
  std::cout << "fileSize : " << getSize(argv[1]) << std::endl;

  for (int i = 1; i < argc; i++) {
    std::cout << argv[i] << " :" << std::endl;
    FileReader fr{argv[i]};
    while(fr) {
      fr.readOnce();
      std::cout << fr.pollResult();
    }

    std::cout << std::endl << fr.readOnce() << "asdf\"" << fr.pollResult() << "\"" << std::endl;
  }
}