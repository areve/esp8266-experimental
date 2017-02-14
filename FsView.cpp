#include "FsView.h"

FsView::FsView(FsController* fsController)
{
	this->fsController = fsController;
	this->errorView = new ErrorView();
}

String FsView::getContentType(String filename) {
	if (filename.endsWith(".htm")) return "text/html";
	else if (filename.endsWith(".html")) return "text/html";
	else if (filename.endsWith(".css")) return "text/css";
	else if (filename.endsWith(".json")) return "application/json";
	else if (filename.endsWith(".js")) return "application/javascript";
	else if (filename.endsWith(".png")) return "image/png";
	else if (filename.endsWith(".gif")) return "image/gif";
	else if (filename.endsWith(".jpg")) return "image/jpeg";
	else if (filename.endsWith(".ico")) return "image/x-icon";
	else if (filename.endsWith(".xml")) return "text/xml";
	else if (filename.endsWith(".pdf")) return "application/x-pdf";
	else if (filename.endsWith(".zip")) return "application/x-zip";
	else if (filename.endsWith(".gz")) return "application/x-gzip";
	else if (filename.endsWith(".txt")) return "text/plain";
	return "application/octet-stream";
}

void FsView::handleUpload() {
	HTTPUpload& upload = webServer->upload();
	if (upload.status == UPLOAD_FILE_START) {
		fsController->uploadStart();
	}
	else if (upload.status == UPLOAD_FILE_WRITE) {
		fsController->uploadWrite(upload.buf, upload.currentSize);
	}
	else if (upload.status == UPLOAD_FILE_END) {
		fsController->uploadEnd();
	}
	yield();
}

void FsView::handleRemove(const String remove)
{
	fsController->remove(remove);
	webServer->sendHeader("Location", "/fs?saved=OK", false);
	webServer->send(302, "text/plain", "OK");
	etag = String(random(0xffffffff));
}

void FsView::handleRename(const String rename)
{
	String name = webServer->getArg("name");
	fsController->rename(rename, name);
	webServer->sendHeader("Location", "/fs?saved=OK", false);
	webServer->send(302, "text/plain", "OK");
	etag = String(random(0xffffffff));
}

void FsView::handleUpload(HTTPUpload & upload)
{
	String name = webServer->getArg("name");
	fsController->uploadSave(name.length() ? name : upload.filename);
	webServer->sendHeader("Location", "/fs?saved=OK", false);
	webServer->send(302, "text/plain", "OK");
	etag = String(random(0xffffffff));
}

void FsView::handleRead(const String read)
{
	String fileName = read.substring(read.lastIndexOf("/") + 1);
	String contentType = getContentType(read);
	String ifNoneMatch = webServer->getHeader(String("If-None-Match"));
	String fileEtag = "\"" + etag + fileName + "\"";
	if (ifNoneMatch.length()) {
		if (ifNoneMatch == fileEtag) {
			webServer->send(304, "text/plain", "Not modified");
			return;
		}
	}

	if (fsController->exists(read)) {
		webServer->sendHeader("Content-Disposition", String("inline; filename=\"") + fileName + "\"", false);
		webServer->sendHeader("ETag", fileEtag, false);
		File file = fsController->read(read);
		size_t sent = webServer->streamFile(file, contentType);
		file.close();
		return;
	}

	errorView->webServer = webServer;
	this->errorView->handleNotFound();
}

void FsView::handleList()
{
	std::vector<FileInfo> fileInfos = fsController->list();
	String fileList = "<ul>";
	for (FileInfo fileInfo : fileInfos) {
		fileList += "<li data-name=\"" + htmlEncode(fileInfo.name) + "\">"
			"<a href=\"?read=" + htmlEncode(fileInfo.name) + "\">" +
			htmlEncode(fileInfo.name) +
			"</a>"
			" "
			"<em>" + String(fileInfo.size) + "b</em>"
			" <button onclick=\"remove(this)\">Remove</button>"
			" <button onclick=\"rename(this)\">Rename</button>"
			"</li>";
	}
	fileList += "</ul>";

	String html =
		htmlHeader("File System < Moth") +
		"<section class=\"file-system\">"
		"<h1>MOTH File System</h1>"
		"<p>A File System browser.</p>" +
		fileList +
		"<form method=\"POST\" enctype=\"multipart/form-data\">" +
		"<input name=\"remove\" type=\"hidden\" />"
		"<div><label id=\"upload\">Upload <input type=\"file\" name=\"upload\" onchange=\"uploadChange()\" /></label></div>"
		"<div><label id=\"rename\">Rename <input name=\"rename\" value=\"\" /></label></div>"
		"<div><label id=\"name\">To <input name=\"name\" value=\"\" /></label></div>"
		"<button>Save</button>"
		"</form>" +
		"<script>"
		"function uploadChange(button) {"
		"document.forms[0].rename.value='';"
		"document.forms[0].name.value=document.forms[0].upload.value.replace(/^.*[\\\\\\/]/g, '');"
		"document.forms[0].name.focus();"
		"}"
		"function remove(button) {"
		"document.forms[0].rename.value='';"
		"document.forms[0].remove.value=button.parentNode.getAttributeNode('data-name').value;"
		"document.forms[0].submit();"
		"}"
		"function rename(button) {"
		"document.forms[0].rename.value=button.parentNode.getAttributeNode('data-name').value;"
		"document.forms[0].name.value=button.parentNode.getAttributeNode('data-name').value;"
		"document.forms[0].name.focus();"
		"}"
		"</script>" +
		"</section>" +
		htmlFooter();

	webServer->send(200, "text/html", html);
}


void FsView::handleRequest()
{
	if (webServer->method() == HTTP_POST) {
		String remove = webServer->getArg("remove");
		if (remove.length()) return handleRemove(remove);

		String rename = webServer->getArg("rename");
		if (rename.length()) return handleRename(rename);

		HTTPUpload& upload = webServer->upload();
		if (upload.filename.length()) return handleUpload(upload);

		webServer->sendHeader("Location", "/fs", false);
		webServer->send(200, "text/plain", "What?");
		return;
	}

	String read = webServer->getArg("read");
	if (read.length()) return handleRead(read);

	if (webServer->uri().startsWith("/fs")) return handleList();

	handleRead(webServer->uri().substring(1));
}
