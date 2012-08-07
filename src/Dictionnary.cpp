//
//  Dictionnary.cpp
//  ABCDictionnary
//
//  Created by Jacques Tronconi on 05/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#include "ABCDictionnary.h"

namespace Abc 
{
    std::string itos(int a) {
        std::string sign = a<0?"-":"";
        std::string result = a>0?std::string(1,(a%10+'0')):std::string(1,((a=-a)%10+'0'));
        (a/=10)>0?result=itos(a)+result:result;
        return sign+result;
    }
    
    NullDictionnariable nullinstance;
    
    Dictionnary::Version Dictionnary::version = {
        itos(VERSION_MAJOR),
        itos(VERSION_MINOR),
        itos(VERSION_BUILD)
    };
    
    Dictionnary::Dictionnary()
    {
        /* Do nothing. */
    }
    
    Dictionnary::Dictionnary(const Dictionnary& other)
    {
        if(other.entries.size() > 0)
        {
            for (size_t i = 0; i < other.entries.size(); i++) 
            {
                entries.push_back(other.entries.at(i));
            }
        }
    }
    
#if defined (cplusplus0x)
    Dictionnary::Dictionnary(std::initializer_list<Dictionnariable*> list)
    {
        for(auto it = list.begin(); it != list.end(); it++)
            addEntry(*it);
    }
#endif
    
    Dictionnary::~Dictionnary()
    {
        while(!entries.empty())
        {
            entries.erase(entries.begin());
        }
    }
    
    void Dictionnary::addEntry(Abc::Dictionnariable *obj)
    {
        char buffer[1024];
        sprintf(buffer, "%lu", entries.size());
        this->addEntry(std::string(buffer), obj);
    }
    
    void Dictionnary::addEntry(const std::string &entryName, Abc::Dictionnariable *obj)
    {
        if(getEntryPtr(entryName) == NULL)
        {
            entries.push_back(std::make_pair(entryName, obj));
        }
    }
    
    Dictionnariable& Dictionnary::getEntry(const std::string &key)
    {
        for (size_t i = 0; i < entries.size(); i++) 
        {
            if(entries.at(i).first == key)
                return *(entries.at(i).second);
        }
        
        return nullinstance;
    }
    
    Dictionnariable& Dictionnary::getEntry(int index)
    {
        if (index >= 0 && index < entries.size())
            return *(entries.at(index).second);
        return nullinstance;
    }
    
    const Dictionnariable& Dictionnary::getEntry(const std::string &key) const
    {
        for (size_t i = 0; i < entries.size(); i++) 
        {
            if(entries.at(i).first == key)
                return *(entries.at(i).second);
        }
        
        return nullinstance;
    }
    
    const Dictionnariable& Dictionnary::getEntry(int index) const
    {
        if (index >= 0 && index < entries.size())
            return *(entries.at(index).second);
        return nullinstance;
    }
    
    Dictionnariable* Dictionnary::getEntryPtr(const std::string &key)
    {
        for (size_t i = 0; i < entries.size(); i++) 
        {
            if(entries.at(i).first == key)
                return entries.at(i).second;
        }
        
        return NULL;
    }
    
    Dictionnariable* Dictionnary::getEntryPtr(int index)
    {
        if (index >= 0 && index < entries.size())
            return entries.at(index).second;
        return NULL;
    }
    
    const std::pair<std::string, Dictionnariable*>& Dictionnary::getPair(int index) const
    {
        return entries.at(index);
    }
    
    std::pair<std::string, Dictionnariable*>& Dictionnary::getPair(int index)
    {
        return entries.at(index);
    }
    
    void Dictionnary::removeEntry(int index)
    {
        entries.erase(entries.begin() + index);
    }
    
    void Dictionnary::removeEntry(const std::string &key)
    {
        int index = getIndex(key);
        if(index >= 0)
            entries.erase(entries.begin() + index);
    }
    
    int Dictionnary::getIndex(const std::string &key) const
    {
        for(size_t i = 0; i < entries.size(); i++)
        {
            if(entries.at(i).first == key)
                return (int) i;
        }
        
        return -1;
    }
    
    size_t Dictionnary::size() const
    {
        return entries.size();
    }
    
    Dictionnary& Dictionnary::operator<<(std::pair<std::string, Dictionnariable *> pair)
    {
        addEntry(pair.first, pair.second);
        return *this;
    }
    
    Dictionnary& Dictionnary::operator<<(Abc::Dictionnariable *obj)
    {
        addEntry(obj);
        return *this;
    }
    
    std::string Dictionnary::toText() const
    {
        std::string str;
        
        str += "Dictionnary\n{\n\tSize = ";
        str += itos(size());
        str += ",\n";
        
        for(int i = 0; i < (int) size(); i++)
        {
            Dictionnariable* dic = getPair(i).second;
            std::string key = getPair(i).first;
            
            str += "\t";
            str += "Key : ";
            str += key;
            str += " | ";
            
            str += dic->getType();
            str += " : ";
            str += dic->toText() + ",\n";
        }
        
        str += "}\n";
        
        return str;
    }
    
    std::string Dictionnary::getType() const
    {
        return "Dictionnary";
    }
    
    Dictionnariable& Dictionnary::operator[](const std::string &index)
    {
        return getEntry(index);
    }
    
    const Dictionnariable& Dictionnary::operator[](const std::string &index) const
    {
        return getEntry(index);
    }
    
}