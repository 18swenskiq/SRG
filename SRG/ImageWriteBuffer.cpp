#include "ImageWriteBuffer.h"

ImageWriteBuffer::ImageWriteBuffer(int width, int height)
	:
	imagew(width),
	imageh(height)
{}

void ImageWriteBuffer::AddSolidToBuffer(VMF::Solid insolid, Utils::block_type bt)
{
	for (auto s : insolid.sides)
	{
		ImageWriteObject* imo = new ImageWriteObject(s, bt);
		AddToListSortZ(imo);
	}
}

void ImageWriteBuffer::AddToListSortZ(ImageWriteObject* imo)
{
	// Add object to obj_list, depending on z position
}