//
//  ABCDictionnary.h
//  ABCDictionnary
//
//  Created by Jacques Tronconi on 05/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#ifndef ABCDictionnary_ABCDictionnary_h
#define ABCDictionnary_ABCDictionnary_h

/** \mainpage ABCDictionnary Documentation
 *
 *  \section Introduction
 *  The ABCDictionnary Library is a library that works on every STL-Compliant machine, using the CMake generator.
 *  This library try to reproduce the NSDictionnary class of the Foundation framework, but in C++. You need C++
 *  to use this library. 
 *
 *  Building the Library
 *
 *  \subsection a Using CMake
 *  Just run "cmake -G" in the ABCDictionnary directory with the generator of your choice and build the library !
 *
 *  \subsection a Using anything else
 *  You can build the source file in src directory as a shared or static library as you want.
 *
 *  \section a Using the library
 *  Just link the library to your project and include <Dictionnary.h> in your file. That's all !
 *
 */

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
    //! \class Dictionnary
    /**
     *  This class describes a dictionnary. It stores pair of key, value where key is a string and value is a \ref Dictionnariable.
     *  
     *  \warning 
     *  Destruction of object in the dictionnary is at the charge of the user. 
     *
     *  \brief
     *  Almost every object can be stored in the dictionnary thanks to the dictionnariable template class. 
     */
    class Dictionnary : public Dictionnariable
    {
    public:
        //! \struct Version
        /**
         *  Defines some Version constants.
         */
        struct Version
        {
            std::string MajorVersion;///< The Major Version (1.x).
            std::string MinorVersion;///< The Minor Version (x.4).
            std::string CompleteVersion;///< The build number (4).
        };
        
    protected:
        
        std::vector<std::pair<std::string, Dictionnariable*> > entries;///< Entries in the dictionnary.
        
    public:
        
        //! Default constructor
        Dictionnary();
        //! Copy constructor
        /** 
         *  \warning The copy constructor does not copy object in the dictionnary, but pointers to these objects.
         */
        Dictionnary(const Dictionnary& other);
        
#if defined (cplusplus0x)
        //! Constructs the dictionnary with an initializer list.
        Dictionnary(std::initializer_list<Dictionnariable*> list);
#endif
        
        ~Dictionnary();
        
        //! Add an entry to the dictionnary.
        /**
         *  \param entryName : Key
         *  \param obj : Pointer to the object to store.
         *  \note If the key already exists, entry will be ecrased by the new one.
         */
        void addEntry(const std::string& entryName, Dictionnariable* obj);
        //! Add an entry to the dictionnary.
        /**
         *  \note Key will be automaticly generated, as the current size of the dictionnary.
         *  \param obj : Pointer to the object to store.
         */
        void addEntry(Dictionnariable* obj);
        
        //! Returns the dictionnariable in given entry.
        /**
         *  \param key : Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a NullDictionnariable object.
         */
        Dictionnariable& getEntry(const std::string& key);
        //! Returns the dictionnariable in given entry.
        /**
         *  \param index : Index of the Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a NullDictionnariable object.
         */
        Dictionnariable& getEntry(int index);
        
        //! Returns the dictionnariable in given entry.
        /**
         *  \param key : Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a NullDictionnariable object.
         */
        const Dictionnariable& getEntry(const std::string& key) const;
        //! Returns the dictionnariable in given entry.
        /**
         *  \param index : Index of the Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a NullDictionnariable object.
         */
        const Dictionnariable& getEntry(int index) const;
        
        //! Returns a dictionnariable pointer from given entry.
        /**
         *  \param key : Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a Null pointer.
         */
        Dictionnariable* getEntryPtr(const std::string& key);
        //! Returns a dictionnariable pointer from given entry.
        /**
         *  \param index : Index of the Entry
         *  \return The Dictionnariable object.
         *  \note If entry is not found, it return a Null pointer.
         */
        Dictionnariable* getEntryPtr(int index);
        
        //! Return the pair at given index.
        /** 
         *  \param index : Index of the entry.
         *  \return The pair {Key, Entry}.
         */
        const std::pair<std::string, Dictionnariable*>& getPair(int index) const;
        //! Return the pair at given index.
        /** 
         *  \param index : Index of the entry.
         *  \return The pair {Key, Entry}.
         */
        std::pair<std::string, Dictionnariable*>& getPair(int index);
        
        //! Remove the entry at given index.
        /**
         *  \param index : Index of the Entry.
         */
        void removeEntry(int index);
        //! Remove the entry at given key.
        /**
         *  \param key : Key of the entry.
         */
        void removeEntry(const std::string & key);
        
        //! Return the index for a given key.
        /**
         *  \param key : Key of the Entry.
         *  \return Index of the entry.
         *  \note If key is not found index returned will be -1.
         */
        int getIndex(const std::string & key) const;
        
        //! Return the size of the dictionnary.
        /**
         *  \return Size of the dictionnary.
         */
        size_t size() const;
        
        //! Add an entry with a pair {Key, Entry}
        /**
         *  \param pair : A std::pair with Key and Entry.
         *  \return The dictionnary.
         */
        Dictionnary& operator << (std::pair<std::string, Dictionnariable*> pair);
        //! Add an entry with automatic key
        /**
         *  \param obj : The entry to add.
         *  \return The dictionnary.
         */
        Dictionnary& operator << (Dictionnariable* obj);
        
        //! Return a description of this object.
        virtual std::string toText() const;
        //! Return the type of this object.
        virtual std::string getType() const;
        
        //! Get an entry by his key.
        /**
         *  \param index : Key
         *  \return The dictionnariable in the entry. 
         *  \note Can be NullDictionnariable if not found.
         */
        Dictionnariable& operator [] (const std::string & index);
        //! Get an entry by his key.
        /**
         *  \param index : Key
         *  \return The dictionnariable in the entry. 
         *  \note Can be NullDictionnariable if not found.
         */
        const Dictionnariable& operator [] (const std::string & index) const;
        
    public:
        static Version version;///< Describes current Version
    };
}

#endif
