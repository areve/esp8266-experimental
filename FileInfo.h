#ifndef _FILEINFO_h
#define _FILEINFO_h

class FileInfo {
public:
	FileInfo(String name, size_t size) {
		this->name = name;
		this->size = size;
	}
	String name;
	size_t size;
};

#endif

