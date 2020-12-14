#pragma once
#include <ostream>
#include <queue>
#include <string>

class KeyValuesQueue
{
public:
	enum KVToken
    {
        T_ObjectHeader, T_ObjectStart, T_KeyName, T_KeyValue,
        T_ObjectEnd, T_CommentInline, T_CommentOwnline, T_EmptyLine
    };

public:
    KeyValuesQueue(std::vector<std::string> filestrings);
    friend std::ostream& operator<<(std::ostream& os, const KeyValuesQueue& obj);
    void PushTokenQueue(std::pair<KVToken, std::string>* newtokenpair);
    int GetQueueSize();
    std::pair<enum KeyValuesQueue::KVToken, std::string>* GetFrontValueOfQueue();
    void PopQueue();

public:
    std::queue<std::pair<KVToken, std::string>*> tokenqueue;

};