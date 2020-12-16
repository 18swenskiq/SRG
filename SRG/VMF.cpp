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
	std::string holder1;
	std::string holder2;

	while ((temppair = localq.front())->first != KeyValuesQueue::KVToken::T_ObjectEnd)
	{
		if (temppair->first == KeyValuesQueue::KVToken::T_KeyName)
		{
			holder1 = temppair->second;
			localq.pop();
			continue;
		}
		if (temppair->first == KeyValuesQueue::KVToken::T_KeyValue)
		{
			holder2 = temppair->second;

			versioninfo.data.emplace(holder1, holder2);
			localq.pop();
			continue;
		}

		// if here something is wrong
		std::cout << "MALFORMED VMF" << std::endl;
		return;
	}
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
	localq.pop(); // bsnaptogrid
	viewsettings.data.emplace("bSnapToGrid", localq.front()->second);
	localq.pop(); // bsnaptogrid value
	localq.pop(); // bshowgrid
	viewsettings.data.emplace("bShowGrid", localq.front()->second);
	localq.pop(); // bshowgrid value
	localq.pop(); // bshowlogicalgrid
	viewsettings.data.emplace("bShowLogicalGrid", localq.front()->second);
	localq.pop(); // bshowlogicalgrid value
	localq.pop(); // ngridspacing
	viewsettings.data.emplace("nGridSpacing", localq.front()->second);
	localq.pop(); // ngridspacing value
	localq.pop(); // bshow3dgrid
	viewsettings.data.emplace("bShow3DGrid", localq.front()->second);
	localq.pop(); // bshow3dgrid value
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
	localq.pop(); // id
	world.


	// Debug print
	// print versioninfo
	std::cout << "VersionInfo: " << std::endl;
	std::map<std::string, std::string>::iterator it;
	for (it = versioninfo.data.begin(); it != versioninfo.data.end(); it++)
	{
		std::cout << '"' << it->first << '"' << "    " << '"' << it->second << '"' << std::endl;
	}
	std::cout << std::endl;

	// print visgroups
	std::cout << "Visgroups:" << std::endl;
	for (int i = 0; i < visgroups.size(); i++)
	{
		visgroups.at(i).PrintVisgroup();
		std::cout << std::endl;
	}
	std::cout << std::endl;

	// print settings
	std::cout << "View Settings:" << std::endl;
	for (it = viewsettings.data.begin(); it != viewsettings.data.end(); it++)
	{
		std::cout << '"' << it->first << '"' << "    " << '"' << it->second << '"' << std::endl;
	}
	std::cout << std::endl;
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