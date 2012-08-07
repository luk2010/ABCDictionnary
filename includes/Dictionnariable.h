//
//  Dictionnariable.h
//  ABCDictionnary
//
//  Created by Jacques Tronconi on 05/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#ifndef ABCDictionnary_Dictionnariable_h
#define ABCDictionnary_Dictionnariable_h

#include <string>
#include <sstream>

namespace Abc 
{
    class Dictionnariable
    {
    public:
        
        Dictionnariable()
        {
            /* Do nothing. */
        }
        
        virtual ~Dictionnariable()
        {
            /* Do nothing. */
        }
        
        template <typename T> T& to()
        {
            return *(dynamic_cast<T*>(this));
        }
        
        virtual std::string toText() const
        {
            /* Do nothing. */
            return std::string();
        }
        
        virtual void fromText(const std::string& t)
        {
            /* Do nothing. */
        }
        
        virtual std::string getType() const
        {
            return "";
        }
        
    };
    
    template <typename T> 
    class GenericDictionnariable : public Dictionnariable
    {
    public:
        
        GenericDictionnariable()
        {
            
        }
        
        GenericDictionnariable(const GenericDictionnariable& g)
        : data(g.data)
        {
            
        }
        
        GenericDictionnariable(const T& value)
        : data(value)
        {
            
        }
        
        virtual ~GenericDictionnariable()
        {
            /* Do nothing. */
        }
        
        T& get()
        {
            return data;
        }
        
        const T& get() const
        {
            return data;
        }
        
        void set(const T& value)
        {
            data = value;
        }
        
        virtual std::string toText() const
        {
            return "";
        }
        
        virtual std::string getType() const
        {
            return "GenericDictionnariable";
        }
        
    protected:
        
        T data;
    };
    
    class DString : public GenericDictionnariable<std::string>
    {
    public:
        DString() 
        : GenericDictionnariable()
        {
            
        }
        
        DString(const DString & str)
        : GenericDictionnariable(str)
        {
            
        }
        
        DString(const std::string & str)
        : GenericDictionnariable(str)
        {
            
        }
        
        virtual ~DString()
        {
            
        }
        
        virtual std::string toText() const
        {
            return data;
        }
        
        virtual std::string getType() const
        {
            return "DString";
        }
    };
    
    typedef GenericDictionnariable<int>             DInt;
    typedef GenericDictionnariable<double>          DDouble;
    typedef GenericDictionnariable<char>            DChar;
    
    class NullDictionnariable : public Dictionnariable
    {
    public:
        
        NullDictionnariable() 
        {
            
        }
        
        ~NullDictionnariable()
        {
            
        }
        
        std::string toText() const
        {
            return "NullDictionnariable";
        }
        
        std::string getType() const
        {
            return "NullDictionnariable";
        }
    };
}

#endif
