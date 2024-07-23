#include<iostream>
#include<string>

unsigned int Hash(std::string& data)
{
    unsigned int result(0);

    for(unsigned int ch : data)
        result=ch + (result<<4) + (result<<10) - result;

    return result;
}

int main()
{
    std::string Name("i love you! :P");

    unsigned int hash
    {
        Hash(Name)
    };

    std::cout<<"The hash of "<<Name<<" is "<<hash<<std::endl;
    
    return 0;
}