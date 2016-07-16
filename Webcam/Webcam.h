#ifndef S_WEBCAM_H
#define S_WEBCAM_H

#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <ctime>

#include "opencv2\opencv.hpp"


class webcam
{
public:
	webcam() : webcam(0) { }
	webcam(int device) : capture(nullptr), device(device), caption("Webcam Source"), imgFiletype(".bmp") {}
	~webcam() { capture.~VideoCapture(); }

	bool isOpen() const { return capture.isOpened(); }

	void start();
	void stop();

	void setCaption(std::string cap)  { this->caption = cap; }
	void setDevice(int device) { this->device = device; }
	void setCaptureSize(int width, int height);

	void setImageNamePattern(std::string (*f)()) { this->getImageName = f; }
	void setSaveFolder(std::string path) { this->saveFolder = path; }
	void setSaveImageFileType(std::string type) { this->imgFiletype = type; }
	

private:
	cv::VideoCapture capture;
	cv::Mat *currentFrame;
	std::string caption;
	std::string imgFiletype;
	std::string saveFolder;
	bool running;
	int device;	
	
	void saveImage();
	void run();
	static std::string (*getImageName)();

	/*
	This maps from characters to (pointers to) methods in this class.
	This is used to execute a method of this class on a key press.
	For example: the mapping 'q' -> &webcam::stop will call this->stop() whenever 'q' is pressed with the webcam open.

	This doesn't have an advantage over using switch / if, but this looks cooler.  Also, I wanted to practice using function pointers.
	*/
	std::map<char, void(webcam::*)()> keyBinds; // = { {'q', &webcam::stop} }; This way of initializing doesn't appear to work in VS 2013 :(.  It is now set in run.

}; // webcam

#endif //S_WEBCAM_H