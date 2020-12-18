#include "SRG_Image.h"
#include <iostream>
#include <string>


// Loads a PNG image from path
SRG_Image::SRG_Image(const char* background_path)
{
	std::fstream myfile;
	myfile.open(background_path, std::ios::in | std::ios::binary);

	// read png signature
	myfile.read(HeaderSignature, 8);
	
	// start reading chunks
	while (true)
	{
		Chunk* resultchunk = ReadChunk(myfile);
		datachunks.push_back(resultchunk);
		if (CompareCharArrayAndLiteral(resultchunk->type, "IEND", 4)) break;
	}
}

SRG_Image::Chunk* SRG_Image::ReadChunk(std::fstream& inputstream)
{
	Chunk* newchunk = new Chunk();
	char holder1[1];
	char holder4[4];
	inputstream.read(holder4, 4);
	newchunk->length = CharArrayToInt(holder4);
	inputstream.read(newchunk->type, 4);

	if (CompareCharArrayAndLiteral(newchunk->type, "IHDR", 4))
	{
		// Header chunk
		inputstream.read(holder4, 4);
		this->width = CharArrayToInt(holder4);
		newchunk->data.push_back((std::byte)this->width);
		newchunk->data.

		inputstream.read(holder4, 4);
		this->height = CharArrayToInt(holder4);

		inputstream.read(holder1, 1);
		this->bitdepth = CharArrayToByte(holder1);

		inputstream.read(holder1, 1);
		this->colortype = CharArrayToByte(holder1);

		inputstream.read(holder1, 1);
		this->compressionmethod = CharArrayToByte(holder1);

		inputstream.read(holder1, 1);
		this->filtermethod = CharArrayToByte(holder1);

		inputstream.read(holder1, 1);
		this->interlacemethod = CharArrayToByte(holder1);
	}
	else
	{
		// Data chunk
	}
	inputstream.read(holder4, 4); // read CRC
	newchunk->crc = CharArrayToInt(holder4);
	return newchunk;
}

bool SRG_Image::CompareCharArrayAndLiteral(char* ca, const char* li, size_t cmpsize)
{
	if (std::strncmp(ca, li, 4) == 0) return true;
	return false;
}

std::byte SRG_Image::CharArrayToByte(char ca[1])
{
	std::byte newbyte = (std::byte)0;
	return (std::byte)((char)newbyte | ca[0]);
}

int SRG_Image::CharArrayToInt(char ca[4])
{
	int newint = 0;
	for (int i = 3; i >= 0; i--)
	{
		newint = (newint | ca[i]);
	}
	return newint;
}


