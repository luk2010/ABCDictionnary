//
//  ABCDictionnary.h
//  ABCDictionnary
//
//  Created by Jacques Tronconi on 05/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#ifndef ABCDictionnary_ABCDictionnary_h
#define ABCDictionnary_ABCDictionnary_h

#include <vector>
#include <string>

#if __cplusplus >= 201103L
#define cplusplus0x 1
#endif

#include "Dictionnariable.h"

#if defined (cplusplus0x)
#include <initializer_list>
#endif

#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_BUILD 4

namespace Abc 
{
    class Dictionnary : public Dictionnariable
    {
    public:
        
        struct Version
        {
            std::string MajorVersion;
            std::string MinorVersion;
            std::string CompleteVersion;
        };
        
    protected:
        
        std::vector<std::pair<std::string, Dictionnariable*> > entries;
        
    public:
        
        Dictionnary();
        Dictionnary(const Dictionnary& other);
        
#if defined (cplusplus0x)
        Dictionnary(std::initializer_list<Dictionnariable*> list);
#endif
        
        ~Dictionnary();
        
        void addEntry(const std::string& entryName, Dictionnariable* obj);
        void addEntry(Dictionnariable* obj);
        
        Dictionnariable& getEntry(const std::string& key);
        Dictionnariable& getEntry(int index);
        
        const Dictionnariable& getEntry(const std::string& key) const;
        const Dictionnariable& getEntry(int index) const;
        
        Dictionnariable* getEntryPtr(const std::string& key);
        Dictionnariable* getEntryPtr(int index);
        
        const std::pair<std::string, Dictionnariable*>& getPair(int index) const;
        std::pair<std::string, Dictionnariable*>& getPair(int index);
        
        void removeEntry(int index);
        void removeEntry(const std::string & key);
        
        int getIndex(const std::string & key) const;
        
        size_t size() const;
        
        Dictionnary& operator << (std::pair<std::string, Dictionnariable*> pair);
        Dictionnary& operator << (Dictionnariable* obj);
        
        virtual std::string toText() const;
        virtual std::string getType() const;
        
        Dictionnariable& operator [] (const std::string & index);
        const Dictionnariable& operator [] (const std::string & index) const;
        
    public:
        static Version version;
    };
}

#endif
