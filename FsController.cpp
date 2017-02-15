#include "FsController.h"

FsController::FsController()
{
	SPIFFS.begin();
}

std::vector<FileInfo> FsController::list()
{
	std::vector<FileInfo> fileInfos;
	Dir dir = SPIFFS.openDir("");
	while (dir.next()) {
		fileInfos.push_back(FileInfo(dir.fileName(), dir.fileSize()));
	}
	return fileInfos;
}

File FsController::read(const String name)
{
	return SPIFFS.open(name, "r");
}

bool FsController::exists(const String name)
{
	return SPIFFS.exists(name);
}

void FsController::remove(const String name)
{
	if (!SPIFFS.remove(name))
		logger::debug(String("remove ") + name + " failed");
}

void FsController::rename(const String nameFrom, const String nameTo)
{
	SPIFFS.rename(nameFrom, nameTo);
}

void FsController::uploadStart()
{
	tempFileName = "";
}

void FsController::uploadWrite(const uint8_t * buf, size_t size)
{
	if (size > 0) {
		if (tempFileName.length() == 0) {
			tempFileName = String(micros()) + ".tmp";
			tempFile = SPIFFS.open(tempFileName, "w");
		}

		tempFile.write(buf, size);
	}
}

void FsController::uploadEnd()
{
	tempFile.close();
}

void FsController::uploadSave(const String name)
{
	SPIFFS.rename(tempFileName, name);
	tempFileName = "";
}

