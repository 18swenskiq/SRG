#pragma once
#include "VMF.h"
#include "ImageWriteObject.h"
#include "Utils.h"

class ImageWriteBuffer
{
public:
	ImageWriteBuffer(int width, int height);
	void AddSolidToBuffer(VMF::Solid insolid, enum Utils::block_type bt);
	std::vector<ImageWriteObject> obj_list;

private:
	void AddToListSortZ(ImageWriteObject* imo);
	int imagew;
	int imageh;
};