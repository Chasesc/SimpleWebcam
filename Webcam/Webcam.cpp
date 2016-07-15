#include "Webcam.h"


void webcam::start()
{
	this->running = true;
	this->capture = cv::VideoCapture(this->device);

	if (!isOpen())
	{
		std::cerr << "Error: Device " << this->device << " was unable to open." << std::endl;
		return;
	}

	try
	{
		std::thread webcam_thread(std::mem_fn(&webcam::run), this);
		webcam_thread.detach();
	}
	catch (...) // gotta catch em all
	{
		std::cerr << "Error: Unable to initialze the webcam thread!" << std::endl;
	}
	
}

void webcam::stop()
{
	this->running = false;
	capture.~VideoCapture();
}

void webcam::setCaptureSize(int width, int height)
{
	this->capture.set(cv::CAP_PROP_FRAME_WIDTH, width);
	this->capture.set(cv::CAP_PROP_FRAME_HEIGHT, height);
}

void webcam::run()
{
	this->keyBinds['q'] = &webcam::stop;

	while (this->running)
	{
		cv::Mat frame;
		this->capture >> frame;
		cv::imshow(this->caption, frame);

		char key = cv::waitKey(1);

		auto iterator = keyBinds.find(key); //See if we do anything with this key.
		if (iterator != keyBinds.end())
		{
			(this->*(iterator->second))(); // Dereference the pointer to the function and call it using our 'this' pointer
		}
	}	
}