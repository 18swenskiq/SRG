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

	class Cordon : public GenericMap
	{
	public:
		GenericMap box;
	};

	class Cordons : public GenericMap
	{
	public:
		std::vector<Cordon> cordon;
	};

	class DispRowInfo : public GenericMap
	{
	public:
		std::string name;
	};

	class DispInfo : public GenericMap
	{
	public:
		std::vector<DispRowInfo> disprowinfo;
	};

	class Side : public GenericMap
	{
	public:
		DispInfo dispinfo;
	};

	class Solid : public GenericMap
	{
	public:
		std::vector<Side> sides;
		GenericMap editor;
	};

	class Entity : public GenericMap
	{
	public:
		GenericMap connections;
		std::vector<Solid> solids;
		GenericMap editor;
	};

	class Group : public GenericMap
	{
	public:
		GenericMap editor;
	};

	class World : public GenericMap
	{
	public:
		std::vector<Solid> solids;
		std::vector<Group> groups;
	};

	class Visgroup : public GenericMap
	{
	public:
		std::vector<Visgroup> child_visgroups;
		void PrintVisgroup(int indentation_level = 0)
		{
			std::map<std::string, std::string>::iterator it;
			for (it = data.begin(); it != data.end(); it++)
			{
				for (int x = 0; x < indentation_level; x++) std::cout << "--";
				std::cout << '"' << it->first << '"' << "    " << '"' << it->second << '"' << std::endl;
			}
			if (child_visgroups.size() > 0)
			{
				for (int x = 0; x < indentation_level; x++) std::cout << "--";
				std::cout << "Children: " << std::endl;
				for (int i = 0; i < child_visgroups.size(); i++)
				{
					child_visgroups.at(i).PrintVisgroup(indentation_level + 1);
				}
			}
		}
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

private:
	Visgroup GetVisgroupFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qcopy);
};
