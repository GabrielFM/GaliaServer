#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
//galiasystem.herokuapp.com/infoUpdate?temp=200&username=Rasperna&password=GaliaRules
int main()
{
    std::string terminal = "curl --data \"username=Rasperna&password=GaliaRules& ";
    std::string url = "https://galiasystem.herokuapp.com/infoUpdate";
    std::string temp = "21110";
    std::string pump = "false";
    std::string umidity = "5";
    std::string lum = "255";
    std::string water_level = "7";
    std::string ground_umi = "33"; 
	std::string e = "&";
	std::string response = ">> output.txt";
	
    std::string post = terminal+"temp="+temp+e+"pump="+pump+e+"ground_umi="+ground_umi+e+"umidity="+umidity+e+"lum="+lum+e+"water_level="+water_level+"\" " + url + response;

    system(post.c_str());
    //std::cout<<std::endl<<post<<std::endl;


    return 0;
}
