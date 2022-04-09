#include <fstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "../include/FileReader.hpp"


int getSize(std::string path) {

  std::ifstream is(path, std::ifstream::binary);
  if (is) { // seekg를 이용한 파일 크기 추출
    
    is.seekg(0, is.end);
    int num = is.tellg(); 
    is.close();
    return num;
    
  } else {
    return -1;
  }
  
}


FileReader::FileReader(std::string path) : FileReader(path, getSize(path)) {

    if (fs) {
    
      fs.seekg(0, fs.end);  
      length = (int)fs.tellg();
      fs.seekg(0, fs.beg);
      buf = new unsigned char[length];
      
    } else {
      std::cout << "File not found!\n";
    }
  
}

FileReader::FileReader(std::string path, int bufferSize) : fs(path, std::ifstream::binary), length(bufferSize), cnt(0), rowNumLength(std::round(std::log(getSize(path))/std::log(12))) {

  if (fs) {
    
    buf = new unsigned char[length];

    strStream << std::hex << std::setfill('0') << std::uppercase;
    for(int i = 0; i < rowNumLength + 3; i++) strStream << " ";

    for(int i = 1; i < 17; i++) { // add column index
      strStream << std::setw(2) << i << " ";
    }
    strStream << "\n";
    for(int i = 0; i < 50 + rowNumLength; i++) strStream << "-";
    
  } else {
    std::cout << "File not found!\n";
  }
  
}

FileReader& FileReader::readAll() {
  while(readOnce()) {}
  
  return *this;
}


bool FileReader::readOnce() {

  bool ret = (bool)fs.read((char*)buf, length);
  if(ret) {
    std::streamsize dataSize = fs.gcount();
    //std::cout << "read : " << dataSize << " bytes\n";
    
    for(int i = 0; i < dataSize; i++, cnt++) {
      if(!(cnt % 16)) strStream << "\n"
        << std::setw(rowNumLength)
        << cnt << " | ";
      
      strStream << std::setw(2) << (int)buf[i] << " ";
    }

  }
  return ret;
}

/** Return the string . */
std::string FileReader::copyResult() {
  return strStream.str();
}
/** Return the string, and deletes it.
  * Use this when you don't need any copy of the string in this object.
  * Metadata(e.g. position of file) will not be deleted
  */
std::string FileReader::pollResult() {
  std::string str = strStream.str();
  strStream.str("");
  strStream.clear();
  return str;
}
