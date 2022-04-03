#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

constexpr int BUFFERSIZELIMIT = 2 * 1024 * 1024;
unsigned char* buffer;
int bufferSize;

int main() {
  std::string filePath = "testBinary/tt.txt";
  //std::cout << "Hello World!\n";
  std::ifstream is(filePath, std::ifstream::binary);
  if (is) { // seekg를 이용한 파일 크기 추출
    
    is.seekg(0, is.end);
    int length = (int)is.tellg();
    is.seekg(0, is.beg);
    //bufferSize = (BUFFERSIZELIMIT > length) ? length : BUFFERSIZELIMIT;
    bufferSize = length;
    buffer = new unsigned char[bufferSize]; // read data as a block: 
    is.read((char*)buffer, bufferSize);
    is.close(); 

    //std::stringstream tempStrStream;
    std::stringstream strStream;//(tempStrStream << std::hex);
    strStream << std::hex << std::setfill('0') << std::uppercase << "     ";

    for(int i = 1; i < 17; i++) {
      strStream << std::setw(2) << i << " ";
    }
    strStream << "\n";
    for(int i = 0; i < 52; i++) strStream << "-";
    
    for(int i = 0; i < bufferSize; i++) {
      if(!(i % 16)) strStream << "\n"
        << std::setw(std::round(std::log(length)/std::log(12)))
        << i << " | ";
      strStream << std::setw(2) << (int)buffer[i] << " ";
    }

    std::cout << strStream.str() << std::endl;
    
  } else {
    std::cout << "File not found!\n";
  }

}