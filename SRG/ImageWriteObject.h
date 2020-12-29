#pragma once
#include "VMF.h"
#include "Utils.h"

class ImageWriteObject
{
public:
	int lowestZ;
	int highestZ;
	ImageWriteObject(VMF::Side s, Utils::block_type bt);

private:
	unsigned char* draw_data;
};