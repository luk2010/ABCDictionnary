//
//  main.cpp
//  
//
//  Created by Jacques Tronconi on 05/08/12.
//  Copyright (c) 2012 ACorp. All rights reserved.
//

#include <ABCDictionnary.h>
#include <iostream>

using namespace Abc;

std::string itos(int a) {
    std::string sign = a<0?"-":"";
    std::string result = a>0?std::string(1,(a%10+'0')):std::string(1,((a=-a)%10+'0'));
	(a/=10)>0?result=itos(a)+result:result;
	return sign+result;
}

class MyDictionnariable : public GenericDictionnariable<std::vector<int> >
{
public:
    MyDictionnariable() {}
    
    virtual std::string toText() const
    {  
        std::string str =   "std::vector \n{\n";
        
        for(size_t i = 0; i < data.size(); i++)
        {
            str+= "\t";
            str+= itos(data.at(i));
            str+= ",\n";
        }
        
        str += "}\n";
        return str;
    }
};

int main(int argc, char** argv)
{
    Dictionnary dic;
    Dictionnary dic2;
    
    DString str("Hello World !");
    DString str2("This is another string !");
    DString str3("This is a cool string !");
    
    MyDictionnariable vector;
    vector.get().push_back(24);
    vector.get().push_back(39);
    
    dic.addEntry("hello_world", &str);
    dic.addEntry("MyVector", &vector);
    dic << std::make_pair("str2", &str2);
    dic << std::make_pair("dic2", &dic2);
    
    dic2 << &str3;
    
    std::cout << "---- Example Dictionnary Programm ----" << std::endl;
    std::cout << "Using the ABCDictionnary API v." << Abc::Dictionnary::version.MajorVersion << "." << Dictionnary::version.MinorVersion << " (build " << Dictionnary::version.CompleteVersion << ")." << std::endl;
    std::cout << "Showing current dictionnary..." << std::endl;
    
    std::cout << dic.toText() << std::endl; 
    
    std::string key = "";
    while (key != "exit" && key != "quit")
    {
        std::cout << "\n -- Wich key do you want to see ?";
        std::cin >> key;
        
        if(dic.getEntryPtr(key) != NULL)
        {
            std::cout << dic[key].toText();
        }
        else if(key != "exit" && key != "quit")
        {
            std::cout << "This key doesn't exist !!";
        }
    }
    
    return 0;
}