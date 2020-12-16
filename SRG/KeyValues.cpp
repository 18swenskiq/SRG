#include "KeyValues.h"
#include <iostream>

KeyValuesQueue::KeyValuesQueue(std::vector<std::string> filestrings)
{
    for (int i = 0; i < filestrings.size(); i++)
    {
        std::string currentstring = "";
        std::pair<enum KVToken, std::string>* temppair;

        std::string thisline = filestrings.at(i);
        if (thisline == "")
        {
            temppair = new std::pair<enum KVToken, std::string>;
            temppair->first = KVToken::T_EmptyLine;
            temppair->second = "";
            PushTokenQueue(temppair);
            continue;
        }

        bool hitfirstinfo = false;
        bool inside_quotes = false;
        bool addedkey = false;
        bool commentmode = false;

        if (thisline.at(0) == '/' && thisline.at(1) == '/')
        {
            commentmode = true;
        }

        for (int j = 0; j < thisline.size(); j++)
        {
            if (commentmode) goto skipswitch;
            switch (thisline.at(j))
            {
                // If there's a quote then we'll just swap the quote state
            case '\"':
                if (!inside_quotes) inside_quotes = true;
                else inside_quotes = false;
                if (j + 1 == thisline.size())
                {
                    if (currentstring == "") break;
                    temppair = new std::pair<enum KVToken, std::string>;
                    if (addedkey) temppair->first = KVToken::T_KeyValue;
                    else          temppair->first = KVToken::T_ObjectHeader;
                    temppair->second = currentstring;
                    PushTokenQueue(temppair);
                    currentstring = "";
                    break;
                }
                if (thisline.at(j + 1) == ' ' || thisline.at(j + 1) == '\t')
                {
                    temppair = new std::pair<enum KVToken, std::string>;
                    temppair->first = KVToken::T_KeyName;
                    temppair->second = currentstring;
                    PushTokenQueue(temppair);
                    currentstring = "";
                    addedkey = true;
                    break;
                }
                break;

                // If we have whitespace, either ignore it, or make sure our objects are split properly
            case ' ':
            case '\t':
                if (inside_quotes)
                {
                    currentstring.push_back(thisline.at(j));
                    break;
                }
                if (j + 1 == thisline.size())
                {
                    if (currentstring == "") break;
                    temppair = new std::pair<enum KVToken, std::string>;
                    if (addedkey) temppair->first = KVToken::T_KeyValue;
                    else          temppair->first = KVToken::T_ObjectHeader;
                    temppair->second = currentstring;
                    PushTokenQueue(temppair);
                }
                if (!hitfirstinfo) break;
                if (inside_quotes) break;
                if (currentstring == "") break;
                temppair = new std::pair<enum KVToken, std::string>;
                if (!addedkey) temppair->first = KVToken::T_KeyName;
                else temppair->first = KVToken::T_KeyValue;
                temppair->second = currentstring;
                PushTokenQueue(temppair);
                addedkey = true;
                currentstring = "";
                break;

                // Take note of { and }
            case '{':
                hitfirstinfo = true;
                temppair = new std::pair<enum KVToken, std::string>;
                temppair->first = KVToken::T_ObjectStart;
                temppair->second = "{";
                PushTokenQueue(temppair);
                break;
            case '}':
                hitfirstinfo = true;
                temppair = new std::pair<enum KVToken, std::string>;
                temppair->first = KVToken::T_ObjectEnd;
                temppair->second = "}";
                PushTokenQueue(temppair);
                break;

            case '/':
                hitfirstinfo = true;
                if (thisline.at(j + 1) == '/')
                {
                    commentmode = true;
                    j++;
                    currentstring.append("//");
                }
                else
                {
                    currentstring.push_back(thisline.at(j));
                    if (j + 1 == thisline.size())
                    {
                        if (currentstring == "") break;
                        temppair = new std::pair<enum KVToken, std::string>;
                        if (addedkey) temppair->first = KVToken::T_CommentInline;
                        else temppair->first = KVToken::T_CommentOwnline;
                        temppair->second = currentstring;
                        PushTokenQueue(temppair);
                    }
                    break;
                }
                break;

                // If it's not a special character, just add it to the current string
            default:
            skipswitch:
                hitfirstinfo = true;
                currentstring.push_back(thisline.at(j));
                if (j + 1 == thisline.size())
                {
                    temppair = new std::pair<enum KVToken, std::string>;
                    if (addedkey)
                    {
                        if (commentmode) temppair->first = KVToken::T_CommentInline;
                        else temppair->first = KVToken::T_KeyValue;
                    }
                    else
                    {
                        if (commentmode) temppair->first = KVToken::T_CommentOwnline;
                        else temppair->first = KVToken::T_ObjectHeader;
                    }
                    temppair->second = currentstring;
                    PushTokenQueue(temppair);
                }
                break;
            }
        }
    }
}

std::ostream& operator<<(std::ostream& os, const KeyValuesQueue& obj)
{
    auto localq = obj.tokenqueue;
    int queuesize = localq.size();
    int indentationlevel = 0;
    for (int x = 0; x < queuesize; x++)
    {
        std::pair<enum KeyValuesQueue::KVToken, std::string>* tpair = localq.front();

        switch (tpair->first)
        {
        case KeyValuesQueue::KVToken::T_CommentInline:
            os << " " << tpair->second;
            break;
        case KeyValuesQueue::KVToken::T_CommentOwnline:
            for (int i = 0; i < indentationlevel; i++) os << "\t";
            os << tpair->second;
            break;
        case KeyValuesQueue::KVToken::T_ObjectStart:
            for (int i = 0; i < indentationlevel; i++) os << "\t";
            os << "{";
            indentationlevel++;
            break;
        case KeyValuesQueue::KVToken::T_ObjectEnd:
            indentationlevel--;
            for (int i = 0; i < indentationlevel; i++) os << "\t";
            os << "}";
            break;
        case KeyValuesQueue::KVToken::T_ObjectHeader:
        case KeyValuesQueue::KVToken::T_KeyName:
            for (int i = 0; i < indentationlevel; i++) os << "\t";
            os << tpair->second;
            break;
        case KeyValuesQueue::KVToken::T_KeyValue:
            os << "  " << tpair->second;
            break;
        }

        localq.pop();
        if (x + 1 == queuesize) break;
        if (localq.front()->first == KeyValuesQueue::KVToken::T_CommentInline) continue;
        if (localq.front()->first == KeyValuesQueue::KVToken::T_KeyValue) continue;
        os << std::endl;
    }
    return os;
}

void KeyValuesQueue::PushTokenQueue(std::pair<KVToken, std::string>* newtokenpair)
{
    tokenqueue.push(newtokenpair);
}

int KeyValuesQueue::GetQueueSize()
{
    return tokenqueue.size();
}

std::pair<enum KeyValuesQueue::KVToken, std::string>* KeyValuesQueue::GetFrontValueOfQueue()
{
    return tokenqueue.front();
}

void KeyValuesQueue::PopQueue()
{
    tokenqueue.pop();
}