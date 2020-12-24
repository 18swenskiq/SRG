#pragma once
#include <string>
#include <vector>

static class VMF_Utils
{
	struct planevertspos
	{
		float vert1pos[3];
		float vert2pos[3];
		float vert3pos[3];
	};

public:
	static std::vector<planevertspos> GetVertexFloatVectorFromPlaneString(std::string planestring)
	{

	}
};