#ifndef _FSCONTROLLER_h
#define _FSCONTROLLER_h
	
#include "arduino.h"
#include "arduino.h"
#include "logger.h"
#include "FileInfo.h"
#include <FS.h>
#include <vector>

class FsController {
public:
	FsController();
	std::vector<FileInfo> list();
	File read(const String name);
	void remove(const String name);
	void rename(const String nameFrom, const String nameTo);
	void uploadStart();
	void uploadWrite(const uint8_t* buf, size_t size);
	void uploadEnd();
	void uploadSave(const String name);
private:
	String tempFileName;
	File tempFile;
};

#endif

