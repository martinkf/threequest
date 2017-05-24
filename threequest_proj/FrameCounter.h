#pragma once
class FrameCounter
{
public:
	FrameCounter();
	~FrameCounter();

	void inicializar();
	void tick();
	
	void freeze();
	void unfreeze();

	int getFrameNumber();

private:
	int counter;
	bool isFrozen;
};

