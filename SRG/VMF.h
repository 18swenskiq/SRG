#pragma once
#include <map>
#include <string>
#include <vector>
#include "KeyValues.h"

class VMF
{
public:
	VMF(KeyValuesQueue *kv);
public:
	class GenericMap
	{
	public:
		std::map<std::string, std::string> data;
	};

	class Cordon : GenericMap
	{
	public:
		GenericMap box;
	};

	class Cordons : GenericMap
	{
	public:
		std::vector<Cordon> cordon;
	};

	class DispRowInfo : GenericMap
	{
	public:
		std::string name;
	};

	class DispInfo : GenericMap
	{
	public:
		std::vector<DispRowInfo> disprowinfo;
	};

	class Side : GenericMap
	{
	public:
		DispInfo dispinfo;
	};

	class Solid : GenericMap
	{
	public:
		std::vector<Side> sides;
		GenericMap editor;
	};

	class Entity : GenericMap
	{
	public:
		GenericMap connections;
		std::vector<Solid> solids;
		GenericMap editor;
	};

	class Group : GenericMap
	{
	public:
		GenericMap editor;
	};

	class World : GenericMap
	{
	public:
		std::vector<Solid> solids;
		std::vector<Group> groups;
	};

	class Visgroup : GenericMap
	{
	public:
		std::vector<Visgroup> child_visgroups;
	};
public:
	GenericMap versioninfo;
	std::vector<Visgroup> visgroups;
	GenericMap viewsettings;
	World world;
	std::vector<Entity> entity;
	// We can skip hidden items. if its hidden we don't care about it
	GenericMap cameras;
	Cordons cordons;
};
