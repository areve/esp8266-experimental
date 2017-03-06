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
	void handleRequest(IServer* server) override;
	void handleUpload(IServer* server) override;
	virtual void handleRemove(IServer* server, const String remove);
	virtual void handleRename(IServer* server, const String rename);
	virtual void handleUpload(IServer* server, HTTPUpload& upload);
	virtual void handleRead(IServer* server, const String read);
	virtual void handleList(IServer* server);

private:
	FsController* fsController;
	ErrorView* errorView;
	String getContentType(String filename);
	String etag = String(random(0xFFFFFFFF));
};

#endif

