#pragma once
class FrameCounter
{
public:
	FrameCounter();
	~FrameCounter();
	void inicializar();
	void tick();

	int getFrameNumber();

private:
	int counter;
};

