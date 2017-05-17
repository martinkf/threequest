#include "FrameCounter.h"



FrameCounter::FrameCounter()
{
}

FrameCounter::~FrameCounter()
{
}

void FrameCounter::inicializar()
{
	counter = 1;
}

void FrameCounter::tick()
{
	if (counter + 1 > 720)
	{
		counter = 1;
	}
	else
	{
		counter++;
	}
}

int FrameCounter::getFrameNumber()
{
	return counter;
}
