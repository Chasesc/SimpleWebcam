#include "Webcam.h"

#include <iostream>
#include <string>
#include <chrono>


std::string newPatternExample()
{
	static int counter = 0;
	return "example-" + std::to_string(++counter);
}

int main(int argc, char **argv)
{
	webcam cam;
	cam.setCaption("My Webcam");
	cam.setSaveFolder("C:/Users/Public/Pictures");

	/*
	This sets the function that will name all saved images.
	In this case, each image will be named 'example-n' where n is the nth image saved.

	The default function for this is based on the current time.
	*/
	cam.setImageNamePattern(&newPatternExample);

	assert(!cam.isOpen());

	cam.start();

	assert(cam.isOpen());

	const int LIMIT = 50;
	int count = 0;

	while (cam.isOpen())
	{
		std::cout << "hi " << count << std::endl;

		if (++count == LIMIT)
			cam.stop();				

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}