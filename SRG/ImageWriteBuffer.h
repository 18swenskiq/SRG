#pragma once
#include "VMF.h"

class ImageWriteBuffer
{
public:
	ImageWriteBuffer(int width, int height);
	void AddSolidToBuffer(VMF::Solid insolid);

private:
	int imagew;
	int imageh;
};