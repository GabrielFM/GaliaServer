#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
//galiasystem.herokuapp.com/infoUpdate?temp=200&username=Rasperna&password=GaliaRules
int main()
{
    std::string terminal = "curl --data \"username=Rasperna&password=GaliaRules& ";
    std::string url = "https://galiasystem.herokuapp.com/infoUpdate";
    std::string temp = "10";
    std::string pump = "false";
    std::string umidity = "2";
    std::string lum = "255";
    std::string water_level = "7";
    std::string e = "&";
    std::string post = terminal+"temp="+temp+e+"pump="+pump+e+"umidity="+umidity+e+"lum="+lum
        +e+"water_level="+water_level+"\" " + url;

    system(post.c_str());


    return 0;
}
