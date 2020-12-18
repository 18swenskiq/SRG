#pragma once
#include <fstream>
#include <vector>

class SRG_Image
{
public:
	class Chunk
	{
	public:
		int length;
		char type[4];
		std::vector<std::byte> data;
		int crc;
	};

public:
	SRG_Image(const char* background_path);

public:
	std::vector<Chunk*> datachunks;
	char HeaderSignature[8];
	int width;
	int height;
	std::byte bitdepth;
	std::byte colortype;
	std::byte compressionmethod;
	std::byte filtermethod;
	std::byte interlacemethod;

private:
	Chunk* ReadChunk(std::fstream &inputstream);
	int CharArrayToInt(char ca[4]);
	std::byte CharArrayToByte(char ca[1]);
	bool CompareCharArrayAndLiteral(char* ca, const char* li, size_t cmpsize);
};