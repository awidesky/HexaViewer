#include <fstream>
#include <sstream>
#include <iomanip>

#include <cmath>

#include <filesystem>

/* https://stackoverflow.com/questions/5840148/how-can-i-get-a-files-size-in-c */
static inline int getSize(const char *path) {
  // std::ifstream in(path, std::ifstream::ate | std::ifstream::binary);
  // return in.tellg();
  return std::filesystem::file_size({path});
}

class FileReader {

private:
  std::ifstream fs;
  /** Length of the buffer */
  int length;
  int cnt = 0;
  int rowNumLength;
  unsigned char *buf;
  std::stringstream strStream;

public:
  static constexpr int DEFAULTBUFFERSIZE = 64 * 1024;

  /** Set buffer size to the length to DEFAULTBUFFERSIZE */
  FileReader(std::string path) : FileReader(path.c_str(), DEFAULTBUFFERSIZE) {}
  /** Set buffer size to the length to DEFAULTBUFFERSIZE */
  FileReader(const char *path) : FileReader(path, DEFAULTBUFFERSIZE) {}
  /** Set buffer size to the given parameter */
  FileReader(const char *path, int bufferSize) : fs(path, std::ifstream::binary), length(bufferSize), rowNumLength(std::round(std::log(getSize(path)) / std::log(12))) {
    if (fs) {
      buf = new unsigned char[length];

      strStream << std::hex << std::setfill('0') << std::uppercase;
      for (int i = 0; i < rowNumLength + 3; i++)
        strStream << " ";

      for (int i = 1; i < 17; i++) { // add column index
        strStream << std::setw(2) << i << " ";
      }
      strStream << "\n";
      for (int i = 0; i < 50 + rowNumLength; i++)
        strStream << "-";
    }
  }

  ~FileReader() {
    delete buf;
  }

  operator bool() const {
    return (bool)fs;
  }

  /** Read all content of the file */
  FileReader &readAll() {
    while (readOnce() > 0) {
    }

    return *this;
  }
  /** Read the file once with the buffer(try filling it).
   * return number of characters. Or 0 if EOF, else -1 on error.
   */
  int readOnce() {
    fs.read((char *)buf, length);
    if (fs.good()) {
      std::streamsize dataSize = fs.gcount();
      // std::cout << "read : " << dataSize << " bytes\n";

      for (int i = 0; i < dataSize; i++, cnt++) {
        if (!(cnt % 16))
          strStream << "\n"
                    << std::setw(rowNumLength)
                    << cnt << " | ";

        strStream << std::setw(2) << (int)buf[i] << " ";
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