#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

constexpr int BUFFERSIZELIMIT = 2 * 1024 * 1024;
unsigned char* buffer;
int bufferSize;

int main() {

  std::string filePath = "testBinary/tt.txt";

  std::ifstream fs(filePath, std::ifstream::binary);
  fs.close();
  std::cout << fs.tellg();
}