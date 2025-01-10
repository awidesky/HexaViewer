#ifndef HEXAVIEWER_HPP
#define HEXAVIEWER_HPP

#include <fstream>
#include <iomanip>
#include <sstream>

#include <filesystem>

namespace hexa_fast {
/* https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */
static inline int getSize(const char* path) {
  // std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
  // return in.tellg();
  return std::filesystem::file_size({path});
}

class hexaViewer {

private:
  std::ifstream fs;
  /** Length of the buffer */
  int length;
  int cnt = 0;
  const int rowNumLength;
  unsigned char* buf;
  std::stringstream strStream;

  //static constexpr char* ROWHEXTABLE[] = {"01", "02", "03", "04", "05", "06", "07", "08", "09", "0A", "0B", "0C", "0D", "0E", "0F", "10"};
  
public:
  static constexpr int DEFAULTBUFFERSIZE = 64 * 1024;

  /** Set buffer size to the length to DEFAULTBUFFERSIZE */
  hexaViewer(std::string path) : hexaViewer(path.c_str(), DEFAULTBUFFERSIZE) {}
  /** Set buffer size to the length to DEFAULTBUFFERSIZE */
  hexaViewer(const char* path) : hexaViewer(path, DEFAULTBUFFERSIZE) {}
  /** Set buffer size to the given parameter */
  hexaViewer(const char* path, int bufferSize) : fs(path, std::ifstream::binary), length(bufferSize), rowNumLength((int)(std::log(getSize(path)) / std::log(16)) + 1) {
    if (fs) {
      buf = new unsigned char[length];

      for (int i = 0; i < rowNumLength + 3; i++)
        strStream << ' ';

      strStream << "01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F 10\n";

      for (int i = 0; i < 50 + rowNumLength; i++)
        strStream << '-';
        
      strStream << std::hex << std::setfill('0') << std::uppercase;
    }
  }

  ~hexaViewer() {
    delete buf;
  }

  operator bool() const {
    return (bool)fs;
  }

  /** Read all content of the file */
  hexaViewer& readAll() {
    while (readOnce() > 0) {
    }

    return *this;
  }
  /** Read the file once with the buffer(try filling it).
   * return number of characters. Or 0 if EOF, else -1 on error.
   */
  int readOnce() {
    fs.read((char*)buf, length);
    std::streamsize dataSize = fs.gcount();
    if (dataSize != 0) {
      // std::cout << "read : " << dataSize << " bytes\n";
      for (int i = 0; i < dataSize; i++, cnt++) {
        if (!(cnt % 16))
          strStream << '\n'
                    << std::setw(rowNumLength)
                    << cnt << " | ";

        strStream << std::setw(2) << (int)buf[i] << ' ';
      }
      return dataSize;
    } else if (fs.eof()) {
      return 0;
    } else {
      return -1;
    }
  }

  /** Return the string . */
  std::string copyResult() const {
    return strStream.str();
  }
  /** Return the string, and deletes it.
   * Use this when you don't need any copy of the string in this object.
   * Metadata(e.g. position of file) will not be deleted
   */
  std::string pollResult() {
    std::string str = strStream.str();
    strStream.str("");
    strStream.clear();
    return str;
  }
};

} // namespace hexa
#endif