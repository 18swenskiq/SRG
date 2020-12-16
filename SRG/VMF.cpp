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
	world.data.emplace("id", localq.front()->second);
	localq.pop(); // id value
	localq.pop(); // mapversion
	world.data.emplace("mapversion", localq.front()->second);
	localq.pop(); // mapversion value
	localq.pop(); // classname
	world.data.emplace("classname", localq.front()->second);
	localq.pop(); // classname value
	localq.pop(); // detailmaterial
	world.data.emplace("detailmaterial", localq.front()->second);
	localq.pop(); // detailmaterial value
	localq.pop(); // detailvbsp
	world.data.emplace("detailvbsp", localq.front()->second);
	localq.pop(); // detailvbsp value
	localq.pop(); // maxpropscreenwidth
	world.data.emplace("maxpropscreenwidth", localq.front()->second);
	localq.pop(); // maxpropscreenwidth value
	localq.pop(); // skyname
	world.data.emplace("skyname", localq.front()->second);
	localq.pop(); // skyname value
	int iterator = 0;
	// next in queue should be solid, but we have to iterate through
	while (localq.front()->second != "}")
	{
		if (localq.front()->second == "solid")
		{
			std::cout << "Reading solid..." << std::endl;
			// read solid
			localq.pop(); // solid
			localq.pop(); // {
			localq.pop(); // id
			Solid newsolid;
			newsolid.id.first = "id";
			newsolid.id.second = localq.front()->second;
			std::cout << "Solid #" << newsolid.id.second << std::endl;
			localq.pop(); // id value

			// read sides iteratively
			while (localq.front()->second == "side")
			{
				Side newside;
				localq.pop(); // side
				localq.pop(); // {
				localq.pop(); // id
				newside.data.emplace("id", localq.front()->second);
				localq.pop(); // id value
				localq.pop(); // plane
				newside.data.emplace("plane", localq.front()->second);
				localq.pop(); // plane value
				localq.pop(); // material;
				newside.data.emplace("material", localq.front()->second);
				localq.pop(); // material value
				localq.pop(); // uaxis
				newside.data.emplace("uaxis", localq.front()->second);
				localq.pop(); // vuaxis value
				localq.pop(); // vaxis
				newside.data.emplace("vaxis", localq.front()->second);
				localq.pop(); // vaxis value
				localq.pop(); // rotation
				newside.data.emplace("rotation", localq.front()->second);
				localq.pop(); // rotation value
				localq.pop(); // lightmapscale
				newside.data.emplace("lightmapscale", localq.front()->second);
				localq.pop(); // lightmapscale value
				localq.pop(); // smoothing groups
				newside.data.emplace("smoothing_groups", localq.front()->second);
				localq.pop(); // smoothing group value
				if (localq.front()->second == "dispinfo")
				{
					// read dispinfo here
					localq.pop(); // dispinfo
					localq.pop(); // {
					while (localq.front()->second != "normals")
					{
						holder1 = localq.front()->second;
						localq.pop();
						holder2 = localq.front()->second;
						localq.pop();
						newside.dispinfo.data.emplace(holder1, holder2);
					}
					// read disp info rows
					while (localq.front()->second != "}")
					{
						DispRowInfo dri;
						dri.name = localq.front()->second;
						localq.pop();
						localq.pop();
						while (localq.front()->second != "}")
						{
							holder1 = localq.front()->second;
							localq.pop();
							holder2 = localq.front()->second;
							localq.pop();
							dri.data.emplace(holder1, holder2);
						}
						localq.pop(); // }
						newside.dispinfo.disprowinfo.push_back(dri);
					}
					localq.pop(); // }
					newsolid.sides.push_back(newside);
					localq.pop(); // }
					continue;
				}
				else
				{
					// if we're here, this isn't a displacement face
					localq.pop(); // }
					newsolid.sides.push_back(newside);
					if (localq.front()->second == "editor")
					{
						localq.pop(); // editor
						localq.pop(); // {
						while (localq.front()->second != "}")
						{
							holder1 = localq.front()->second;
							localq.pop();
							holder2 = localq.front()->second;
							localq.pop();
							newsolid.editor.data.emplace(holder1, holder2);
						}
						localq.pop(); // }
						localq.pop(); // }
						break;
					}
					continue;
				}
			}


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
			std::cout << "Matched none" << std::endl;
			std::cout << "Token: " << localq.front()->second << std::endl;
		}
	}

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

	// print viewsettings
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