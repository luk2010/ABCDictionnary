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
    //! \class Dictionnariable
    /**
     *  Base class for every object wich can be stored in a dictionnary. Every object must inherit this class if they want to be storable 
     *  in the Dictionnary.
     * 
     *  This is the minimal code for a class to be storable.
     *  \code
     *  class MyStorableClass : public Dictionnariable
     *  {
     *      public:
     *      MyStorableClass() : Dictionnariable() { // Do whatever you want in initialization. 
                                                  }
     *      ~MyStorableClass() {}
     *      
     *      std::string getType() { return "MyStorableClass"; }
     *  };
     *  \endcode
     *
     *  For basic type or other class see \ref GenericDictionnariable .
     */
    class Dictionnariable
    {
    public:
        
        //! Constructor
        Dictionnariable()
        {
            /* Do nothing. */
        }
        
        //! Destructor
        virtual ~Dictionnariable()
        {
            /* Do nothing. */
        }
        
        //! Convert this object to his original type.
        /**
         *  The user must know what type is the object to convert it to his original type. It use pointer cast so you can convert it to any type
         *  but it might result to undefined results.
         *  \return This object
         */
        template <typename T> T& to()
        {
            return *(dynamic_cast<T*>(this));
        }
        
        //! Describe the object.
        /**
         *  \return A description of the object wich is almost everytime the values of the object.
         *  \see Dictionnary::toText() for example.
         */
        virtual std::string toText() const
        {
            /* Do nothing. */
            return std::string();
        }
        
        //! Return the type of the object.
        /** 
         *  \return the type of the object.
         *  \warning When implementing it, you MUST return the Exact type of the object.
         */
        virtual std::string getType() const
        {
            return "Dictionnariable";
        }
        
        //! Tell if this object is an instance of NullDictionnariable, i.e. a Null object.
        bool isNull() const
        {
            return getType() == "NullDictionnariable";
        }
        
    };
    
    //! \class GenericDictionnariable
    /**
     *  Generic template class to implement almost every type as Dictionnariable.
     *  You can get every object with this class to Storable object :
     *
     *  \code
     *  class MyClass { }
     *  
     *  int main()
     *  {
     *      GenericDictionnariable<MyClass> myClassStorable();
     *      MyClass & myClass = myClassStorable.get();
     *
     *      [... Do whatever you want with your class ...]
     *
     *      Dictionnary dic;
     *      dic << myClassStorable; // Your object has been stored
     *
     *      return 0;
     *  }
     *  \endcode
     */
    template <typename T> 
    class GenericDictionnariable : public Dictionnariable
    {
    public:
        
        //! Constructor
        GenericDictionnariable()
        {
            
        }
        
        //! Copy constructor
        /**
         *  \warning Copy constructor must be available in template class.
         */
        GenericDictionnariable(const GenericDictionnariable& g)
        : data(g.data)
        {
            
        }
        
        //! Constructor with value
        /**
         *  \warning Copy constructor must be available in template class.
         */
        GenericDictionnariable(const T& value)
        : data(value)
        {
            
        }
        
        //! Destructor
        virtual ~GenericDictionnariable()
        {
            /* Do nothing. */
        }
        
        //! Return the object.
        T& get()
        {
            return data;
        }
        
        //! Return the object.
        const T& get() const
        {
            return data;
        }
        
        //! Change current object.
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
    
    //! Specialization for std::string compatibility
    /** 
     *  It enhances user usability.
     */
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
    
    //! \class NullDictionnariable
    /**
     *  Represents a Null object.
     */
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
