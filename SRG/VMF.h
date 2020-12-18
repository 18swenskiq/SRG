#pragma once
#include <map>
#include <string>
#include <vector>
#include "KeyValues.h"

class VMF
{
public:
	VMF(KeyValuesQueue *kv, bool IsCollapseInstances);
public:
	class GenericMap
	{
	public:
		std::map<std::string, std::string> data;
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

	class Solid
	{
	public:
		std::string id;
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
		void PrintVisgroup(int indentation_level);
	};
public:
	GenericMap versioninfo;
	std::vector<Visgroup> visgroups;
	GenericMap viewsettings;
	World world;
	std::vector<Entity> entities;
	// We can skip hidden items. if its hidden we don't care about it
	// we can skip cameras
	// we can skip cordons
	// we can skip quickhide

private:
	Visgroup GetVisgroupFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qcopy);
	Solid GetSolidFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref);
	Side GetSideFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref);
	void AddTokenPairsToMapFromQueueUntilString(std::map<std::string, std::string>& inputmap, std::string hitstring, std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref);
	void AddTokenPairsToMapFromQueueUntilKVType(std::map<std::string, std::string>& inputmap, KeyValuesQueue::KVToken kvtoken, std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref);
};
