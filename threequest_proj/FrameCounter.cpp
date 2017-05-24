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
	isFrozen = false;
}

void FrameCounter::tick()
{
	if (!isFrozen) 
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
}

void FrameCounter::freeze()
{
	isFrozen = true;
	counter = 1;
}

void FrameCounter::unfreeze()
{
	isFrozen = false;
}

int FrameCounter::getFrameNumber()
{
	return counter;
}
