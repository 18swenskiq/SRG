#include <iostream>
#include <fstream>
#include "SRG_Image.h"
#include "KeyValues.h"
#include "VMF.h"

#define PROGVERSION "beta .1"

// argv[0] - "srg.exe"
// argv[1] - "-g"
// argv[2] - "game directory"
// argv[3] - "vmf directory"


int main()
{
    std::cout << "Squidski's Radar Generator; Version " << PROGVERSION << std::endl;

    std::fstream myfile;
    std::string VMFPATH = "H:\\DriveBackup\\Maps\\analog\\de_analog_005.vmf";
    //std::string VMFPATH = "H:\\OneDrive\\Frostbite\\VMF\\ski_160.vmf";
    //std::string VMFPATH = "C:\\Users\\Quinton\\Google Drive\\Desktop\\ski_160.vmf";
    std::cout << "Opening VMF..." << std::endl;
    myfile.open(VMFPATH, std::ios::in);
    if (!myfile.is_open())
    {
        std::cout << "Error: file could not be opened" << std::endl;
        return 1;
    } 
    std::cout << "VMF Successfully opened" << std::endl;
    std::cout << "Storing VMF info in memory..." << std::endl;
    char buf[512];
    std::vector<std::string> filestrings;
    while (myfile.getline(buf,512))
    {
        filestrings.push_back(buf);
    }
    myfile.close();
    std::cout << "VMF successfully stored in memory" << std::endl;

    std::cout << "Tokenizing VMF..." << std::endl;
    KeyValuesQueue* kv = new KeyValuesQueue(filestrings);

    std::cout << "Parsing tokens..." << std::endl;
    VMF *vmf = new VMF(kv, false);
    std::cout << "VMF successfully parsed into objects" << std::endl;

    // TODO: Load models


    std::cout << "Loading background..." << std::endl;
    const char* backgroundpath = "C:\\Users\\Quinton\\source\\repos\\SRG\\grid.png";
    SRG_Image *background = new SRG_Image(backgroundpath);


}
