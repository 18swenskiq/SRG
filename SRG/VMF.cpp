#include <queue>
#include <iostream>
#include "VMF.h"

VMF::VMF(KeyValuesQueue *kv)
{
	// Start traversing through the queue
	std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*> localq = kv->tokenqueue;
	std::pair<KeyValuesQueue::KVToken, std::string>* temppair;

	// Read versioninfo
	localq.pop();
	localq.pop();

	AddTokenPairsToMapFromQueueUntilString(versioninfo.data, "}", localq);

	// End read versioninfo

	// Read visgroups
	localq.pop();	// }
	localq.pop();	// visgroups
	localq.pop();	// {

	while ((temppair = localq.front())->first != KeyValuesQueue::KVToken::T_ObjectEnd)
	{
		if (temppair->second == "visgroup")
		{
			Visgroup newgroup = GetVisgroupFromQueue(localq);
			visgroups.push_back(newgroup);
			if (localq.front()->second == "}") localq.pop();
		}
		else if (temppair->second == "viewsettings")
		{
			break;
		}
		else
		{
			std::cout << "MALFORMED VMF" << std::endl;
			std::cout << localq.size() << std::endl;
			return;
		}
	}

	// End read visgroups

	// Read viewsettings
	if (localq.front()->second != "viewsettings")
	{
		std::cout << "MALFORMED VMF" << std::endl;
		return;
	}

	localq.pop(); // viewsettings
	localq.pop(); // {
	AddTokenPairsToMapFromQueueUntilString(viewsettings.data, "}", localq);
	localq.pop(); // }

	// end viewsettings read

	// read world
	if (localq.front()->second != "world")
	{
		std::cout << "MALFORMED VMF" << std::endl;
		return;
	}
	localq.pop(); // world
	localq.pop(); // {
	AddTokenPairsToMapFromQueueUntilString(world.data, "solid", localq);
	// next in queue should be solid, but we have to iterate through
	while (localq.front()->second != "}")
	{
		if (localq.front()->second == "solid")
		{
			world.solids.emplace_back(GetSolidFromQueue(localq));
		}
		else if (localq.front()->second == "group")
		{
			Group newgroup;
			localq.pop(); // group
			localq.pop(); // {
			AddTokenPairsToMapFromQueueUntilString(newgroup.data, "editor", localq);
			localq.pop(); // editor
			localq.pop(); // {
			AddTokenPairsToMapFromQueueUntilString(newgroup.editor.data, "}", localq);
			localq.pop(); // }
			localq.pop();
			world.groups.emplace_back(newgroup);
		}
		else if (localq.front()->second == "hidden")
		{
			// we can skip anything hidden so let's do a little hack
			int cil = 1; // current indentation level
			localq.pop(); // hidden
			localq.pop(); // {
			while (cil != 0)
			{
				if (localq.front()->second == "{") cil++;
				if (localq.front()->second == "}") cil--;
				localq.pop();
			}
		}
		else
		{
			if (localq.front()->second == "entity")
			{
				break;
			}
			std::cout << "UNKNOWN TOKEN IN VMF" << localq.front()->second << std::endl;
			localq.pop();
		}
	}
	localq.pop();
	// end read world

	// read entities
	while (localq.front()->second != "cameras")
	{
		if (localq.front()->second == "entity")
		{
			std::cout << "ADDING ENT" << std::endl;
			Entity newent;
			localq.pop(); // entity
			localq.pop(); // {
			while (true)
			{
				if (localq.front()->second == "connections")
				{
					std::cout << "ADDING CONNECTION" << std::endl;
					localq.pop(); // connections
					localq.pop(); // {
					AddTokenPairsToMapFromQueueUntilString(newent.connections.data, "}", localq);
					localq.pop();
				}
				if (localq.front()->second == "solid")
				{
					std::cout << "ADDING SOLID" << std::endl;
					newent.solids.emplace_back(GetSolidFromQueue(localq));
				}
				if (localq.front()->second == "editor")
				{
					std::cout << "ADDING EDITOR" << std::endl;
					localq.pop(); // editor
					localq.pop(); // {
					AddTokenPairsToMapFromQueueUntilString(newent.editor.data, "}", localq);
					// This should always be the last item in an entity
					localq.pop(); // }
					localq.pop(); // }
					break;
				}
				AddTokenPairsToMapFromQueueUntilKVType(newent.data, KeyValuesQueue::KVToken::T_ObjectHeader, localq);
			}
			entities.emplace_back(newent);
		}
		else if (localq.front()->second == "hidden")
		{
			int cil = 1; // current indentation level
			localq.pop(); // hidden
			localq.pop(); // {
			while (cil != 0)
			{
				if (localq.front()->second == "{") cil++;
				if (localq.front()->second == "}") cil--;
				localq.pop();
			}
		}
		else
		{
			std::cout << "UNKNOWN TOKEN IN VMF" << localq.front()->second << std::endl;
			localq.pop();
		}
	}

	// read cameras
	localq.pop();
	localq.pop();

}

VMF::Solid VMF::GetSolidFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref)
{
	// read solid
	qref.pop(); // solid
	qref.pop(); // {
	qref.pop(); // id
	Solid newsolid;
	newsolid.id = qref.front()->second;
	qref.pop(); // id value

	// read sides iteratively
	while (qref.front()->second == "side")
	{
		newsolid.sides.emplace_back(GetSideFromQueue(qref));
		if (qref.front()->second == "editor")
		{
			qref.pop(); // editor
			qref.pop(); // {
			AddTokenPairsToMapFromQueueUntilString(newsolid.editor.data, "}", qref);
		}
	}
	qref.pop();
	qref.pop();
	return newsolid;
}

VMF::Side VMF::GetSideFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref)
{
	Side newside;
	qref.pop(); // side
	qref.pop(); // {
	AddTokenPairsToMapFromQueueUntilString(newside.data, "smoothing_groups", qref);
	qref.pop(); // smoothing groups
	newside.data.emplace("smoothing_groups", qref.front()->second);
	qref.pop(); // smoothing group value
	if (qref.front()->second == "dispinfo")
	{
		// read dispinfo here
		qref.pop(); // dispinfo
		qref.pop(); // {
		AddTokenPairsToMapFromQueueUntilString(newside.dispinfo.data, "normals", qref);
		// read disp info rows
		while (qref.front()->second != "}")
		{
			DispRowInfo dri;
			dri.name = qref.front()->second;
			qref.pop();
			qref.pop();
			AddTokenPairsToMapFromQueueUntilString(dri.data, "}", qref);
			qref.pop(); // }
			newside.dispinfo.disprowinfo.push_back(dri);
		}
		qref.pop(); // }
		qref.pop(); // }
		return newside;
	}
	else
	{
		// if we're here, this isn't a displacement face
		qref.pop(); // }
		return newside;
	}
}

void VMF::AddTokenPairsToMapFromQueueUntilKVType(std::map<std::string, std::string>& inputmap, KeyValuesQueue::KVToken kvtoken, std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref)
{
	std::string holder1;
	std::string holder2;
	while (qref.front()->first != kvtoken)
	{
		holder1 = qref.front()->second;
		qref.pop();
		holder2 = qref.front()->second;
		qref.pop();
		inputmap.emplace(holder1, holder2);
	}
}

void VMF::AddTokenPairsToMapFromQueueUntilString(std::map<std::string, std::string>& inputmap, std::string hitstring, std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref)
{
	std::string holder1;
	std::string holder2;
	while (qref.front()->second != hitstring)
	{
		holder1 = qref.front()->second;
		qref.pop();
		holder2 = qref.front()->second;
		qref.pop();
		inputmap.emplace(holder1, holder2);
	}
}

VMF::Visgroup VMF::GetVisgroupFromQueue(std::queue<std::pair<KeyValuesQueue::KVToken, std::string>*>& qref)
{
	Visgroup thisgroup;
	qref.pop();	// visgroup
	qref.pop();	// {
	qref.pop(); // name
	thisgroup.data.emplace("name", qref.front()->second);
	qref.pop();	// name value
	qref.pop(); // visgroupid
	thisgroup.data.emplace("visgroupid", qref.front()->second);
	qref.pop();	// visgroupid value
	qref.pop();	// color
	thisgroup.data.emplace("color", qref.front()->second);
	qref.pop(); // color value
	if (qref.front()->second != "visgroup") qref.pop(); // }
	else {
		while (qref.front()->second == "visgroup")
		{
			thisgroup.child_visgroups.push_back(GetVisgroupFromQueue(qref));
		}
	}
	return thisgroup;
}

void VMF::Visgroup::PrintVisgroup(int indentation_level = 0)
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
