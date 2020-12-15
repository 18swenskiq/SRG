#include <iostream>
#include <fstream>
#include "KeyValues.h"
#include "VMF.h"

// argv[0] - "srg.exe"
// argv[1] - "-g"
// argv[2] - "game directory"
// argv[3] - "vmf directory"


int main()
{
    std::fstream myfile;
    //std::string VMFPATH = "H:\\DriveBackup\\Maps\\analog\\de_analog_005.vmf";
    //std::string VMFPATH = "H:\\OneDrive\\Frostbite\\VMF\\ski_160.vmf";
    std::string VMFPATH = "C:\\Users\\Quinton\\Google Drive\\Desktop\\ski_160.vmf";
    myfile.open(VMFPATH, std::ios::in);
    if (!myfile.is_open())
    {
        std::cout << "Error: file could not be opened" << std::endl;
        return 1;
    } 
    char buf[256];
    std::vector<std::string> filestrings;
    while (myfile.getline(buf, 256))
    {
        filestrings.push_back(buf);
    }
    myfile.close();

    KeyValuesQueue* kv = new KeyValuesQueue(filestrings);
    VMF *vmf = new VMF(kv);
}
