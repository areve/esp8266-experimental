#ifndef _FSVIEW_h
#define _FSVIEW_h

#include "arduino.h"
#include "logger.h"
#include "AppView.h"
#include "WebServer.h"
#include "FileInfo.h"
#include "FsController.h"
#include "ErrorView.h"

class FsView : public AppView {
public:
	FsView(FsController* fsController);
	virtual void handleRequest();
	virtual void handleUpload();
	virtual void handleRemove(const String remove);
	virtual void handleRename(const String rename);
	virtual void handleUpload(HTTPUpload& upload);
	virtual void handleRead(const String read);
	virtual void handleList();

private:
	FsController* fsController;
	ErrorView* errorView;
	String getContentType(String filename);
	String etag = String(random(0xFFFFFFFF));
};

#endif

