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

	std::cout << "VersionInfo: " << std::endl;
	std::map<std::string, std::string>::iterator it;
	for (it = versioninfo.data.begin(); it != versioninfo.data.end(); it++)
	{
		std::cout << '"' << it->first << '"' << "    " << '"' << it->second << '"' << std::endl;
	}

}