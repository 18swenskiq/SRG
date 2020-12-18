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
	int iterator = 0;
	while (true)
	{
		Chunk* resultchunk = ReadChunk(myfile);
		datachunks.push_back(resultchunk);
		iterator++;
		std::cout << "Read " << iterator << "chunks" << std::endl;
		if (iterator == 4)
		{
			std::cout << "aaaa" << std::endl;
		}
		if (CompareCharArrayAndLiteral(resultchunk->type, "IEND", 4)) break;
	}
	myfile.close();

	std::cout << datachunks.size() << std::endl;
}

SRG_Image::Chunk* SRG_Image::ReadChunk(std::fstream& inputstream)
{
	Chunk* newchunk = new Chunk();
	char holder1;
	char holder4[4];
	std::vector<std::byte> tempbytevec;
	inputstream.read(holder4, 4);
	int test2 = inputstream.tellg();
	newchunk->length = CharArrayToInt(holder4);
	inputstream.read(newchunk->type, 4);

	if (CompareCharArrayAndLiteral(newchunk->type, "IHDR", 4))
	{
		// Header chunk
		inputstream.read(holder4, 4);
		this->width = CharArrayToInt(holder4);
		tempbytevec = UIntToByteVector(this->width);
		newchunk->data.insert(newchunk->data.end(), tempbytevec.begin(), tempbytevec.end());

		inputstream.read(holder4, 4);
		this->height = CharArrayToInt(holder4);
		tempbytevec = UIntToByteVector(this->height);
		newchunk->data.insert(newchunk->data.end(), tempbytevec.begin(), tempbytevec.end());

		inputstream.read(&holder1, 1);
		this->bitdepth = CharToByte(holder1);
		newchunk->data.push_back(this->bitdepth);

		inputstream.read(&holder1, 1);
		this->colortype = CharToByte(holder1);
		newchunk->data.push_back(this->colortype);

		inputstream.read(&holder1, 1);
		this->compressionmethod = CharToByte(holder1);
		newchunk->data.push_back(this->compressionmethod);

		inputstream.read(&holder1, 1);
		this->filtermethod = CharToByte(holder1);
		newchunk->data.push_back(this->filtermethod);

		inputstream.read(&holder1, 1);
		this->interlacemethod = CharToByte(holder1);
		newchunk->data.push_back(this->interlacemethod);
	}
	else
	{
		// Data chunk (or something else)
		char *tempdataholder = (char*)malloc(sizeof(char) * newchunk->length);
		inputstream.read(tempdataholder, newchunk->length);
		tempbytevec = CharArrayToByteVector(tempdataholder, newchunk->length);
		newchunk->data.insert(newchunk->data.end(), tempbytevec.begin(), tempbytevec.end());
		free(tempdataholder);

	}
	inputstream.read(holder4, 4); // read CRC
	newchunk->crc = CharArrayToInt(holder4);
	return newchunk;
}

std::vector<std::byte> SRG_Image::UIntToByteVector(unsigned int input)
{
	std::vector<std::byte> retvec;
	for (unsigned int i = 4; i > 0; i--)
	{
		std::byte mask = std::byte(00);
		std::byte ms = std::byte(input >> ((i - 1) * 8));
		std::byte shifted = std::byte(ms);
		retvec.push_back(shifted | mask);
	}
	return retvec;
}

inline bool SRG_Image::CompareCharArrayAndLiteral(char* ca, const char* li, size_t cmpsize)
{
	if (std::strncmp(ca, li, 4) == 0) return true;
	else return false;
}

std::vector<std::byte> SRG_Image::CharArrayToByteVector(char* arr, size_t inpsize)
{
	std::vector<std::byte> retvec;
	for (int i = 0; i < inpsize; i++)
	{
		retvec.push_back(CharToByte(arr[i]));
	}
	return retvec;
}

inline std::byte SRG_Image::CharToByte(char ca)
{
	return (std::byte)((char)((std::byte)0) | ca);
}

int SRG_Image::CharArrayToInt(char ca[4])
{
	unsigned int newint = 0;
	newint = ((ca[0] << 24) | (ca[1] << 16) | (ca[2] << 8) | (ca[3] << 0));
	return newint;
}


