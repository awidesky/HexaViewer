
class FileReader {

private:
std::ifstream fs;
/** Length of the buffer */
int length;
int cnt;
int rowNumLength;
unsigned char* buf;
std::stringstream strStream;

public:
/** Set buffer size to the length of the file */
FileReader(std::string path);
/** Set buffer size to the given parameter */
FileReader(std::string path, int bufferSize);

/** Read all content of the file and returns it as string. */
std::string readAll();
/** Read the file once with the buffer(try filling it).
 * return true if there's something left to read, else false.
 */
bool readOnce();

/** Return the string . */
std::string copyResult();
/** Return the string, and deletes it.
  * Use this when you don't need any copy of the string in this object.
  * Metadata(e.g. position of file) will not be deleted
  */
std::string pollResult();
};