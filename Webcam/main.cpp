#include "Webcam.h"

#include <iostream>
#include <chrono>


int main(int argc, char **argv)
{
	webcam cam;
	cam.setCaption("my Webcam");

	assert(!cam.isOpen());

	cam.start();

	assert(cam.isOpen());

	const int LIMIT = 10;
	int count = 0;

	while (true)
	{
		std::cout << "hi " << count << std::endl;

		if (++count == LIMIT)
		{
			cam.stop();
			assert(!cam.isOpen());
		}			

		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0;
}