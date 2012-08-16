//
//  AutoReleaseDictionnariable.h
//  ABCDictionnary
//
//  Created by Jacques Tronconi on 07/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#ifndef ABCDictionnary_AutoReleaseDictionnariable_h
#define ABCDictionnary_AutoReleaseDictionnariable_h

#include <vector>
#include <map>
#include <iostream>
#include "Dictionnariable.h"

namespace Abc 
{
    template <typename T>
    class AutoReleaseDictionnariable : public Dictionnariable
    {
    protected:
        
        typedef typename std::map<GenericDictionnariable<T>*, int> DicablesMap;
        
    public:
        
        static DLL_CONFIG DicablesMap dicables;
        
    protected:
        
        static bool isAllocated(GenericDictionnariable<T>* ptr)
        {
            for(typename DicablesMap::const_iterator it = dicables.begin(); it != dicables.end(); it ++)
            {
                if(it->first == ptr)
                    return true;
            }
            
          return false;
        }
        
        static void pushDicable(GenericDictionnariable<T>* dicable) 
        {
            if(!isAllocated(dicable))
            {
                dicables[dicable] = 1;
                std::cout << "\nDicable " << dicable << " created !";
            }
            else
            {
                dicables[dicable] += 1;
                std::cout << "\nDicable " << dicable << " pushed !";
            }
        }
        
        static void popDicable(GenericDictionnariable<T>* dicable)
        {
            if(isAllocated(dicable))
            {
                if(dicables[dicable] <= 1)
                {
                    destroyDicable(dicable);
                    std::cout << "\nDicable " << dicable << " destroyed !";
                }
                else
                {
                    dicables[dicable] -= 1;
                    std::cout << "\nDicable " << dicable << " popped !";
                }
            }
        }
        
        static void destroyDicable(GenericDictionnariable<T>* dicable)
        {
            for(typename DicablesMap::iterator it = dicables.begin(); it != dicables.end(); it++)
            {
                if(it->first == dicable)
                {
                    std::cout << "\nDestroying dicable  " << dicable << "...";
                    dicables.erase(it);
                    delete dicable;
                    std::cout << "Ok.";
                }
            }
        }
        
    public:
        
        static void clean()
        {
            while(dicables.size() > 0)
            {
                destroyDicable(dicables.begin()->first);
            }
        }
        
    protected:
        
        GenericDictionnariable<T>* dicable;
        
    public:
        
        AutoReleaseDictionnariable()
        {
            dicable = new GenericDictionnariable<T>();
            pushDicable(dicable);
        }
        
        AutoReleaseDictionnariable(const T& data)
        {
            dicable = new GenericDictionnariable<T>(data);
            pushDicable(dicable);
        }
        
        AutoReleaseDictionnariable(const AutoReleaseDictionnariable<T>& obj)
        {
            dicable = obj.dicable;
            pushDicable(dicable);
        }
        
        virtual ~AutoReleaseDictionnariable()
        {
            popDicable(dicable);
        }
        
        virtual std::string getType() const
        {
            return "AutoReleaseDictionnariable";
        }
    };

    template <typename T> typename AutoReleaseDictionnariable<T>::DicablesMap AutoReleaseDictionnariable<T>::dicables;
}

#endif
