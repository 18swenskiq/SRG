#include <iostream>
#include <fstream>
#include "KeyValues.h"
#include "VMF.h"
#include "ImageWriteBuffer.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"

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
    //std::string VMFPATH = "C:\\Users\\Quinton\\Google Drive\\Desktop\\de_analog_005.vmf";
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


    // Load background
    std::cout << "Loading background..." << std::endl;
    const char* backgroundpath = "C:\\Users\\Quinton\\source\\repos\\SRG\\grid.png";
    //const char* backgroundpath = "C:\\Users\\Quinton\\source\\repos\\18swenskiq\\SRG\\grid.png";
    int bgwidth;
    int bgheight;
    int bgchannels;
    unsigned char* data = stbi_load(backgroundpath, &bgwidth, &bgheight, &bgchannels, 0);
    ImageWriteBuffer* imb = new ImageWriteBuffer();

    // TODO: check for errors

    
    // Put brushes on image
    // get visgroup IDs
    int vg_layoutid = 0;
    int vg_coverid = 0;
    int vg_maskid = 0;
    int vg_overlapid = 0;
    for (int i = 0; i < vmf->visgroups.size(); i++)
    {
        std::map<std::string, std::string> itermap = vmf->visgroups.at(i).data;
        std::string visgroupname = itermap.find("name")->second;
        if (visgroupname.compare("tar_layout") == 0)
        {
            vg_layoutid = std::stoi(itermap.find("visgroupid")->second);
        }
        else if (visgroupname.compare("tar_cover") == 0)
        {
            vg_coverid = std::stoi(itermap.find("visgroupid")->second);
        }
        else if (visgroupname.compare("tar_mask") == 0)
        {
            vg_maskid = std::stoi(itermap.find("visgroupid")->second);
        }
        else if (visgroupname.compare("tar_overlap") == 0)
        {
            vg_overlapid = std::stoi(itermap.find("visgroupid")->second);
        }
    }

    // iterate over each world brush and prepare each brush for writing
    for (VMF::Solid j : vmf->world.solids)
    {
        auto it = j.editor.data.find("visgroupid");
        if (it == j.editor.data.end()) continue; // If the brush isn't part of a visgroup, don't need it

        if(std::stoi(it->second) == vg_layoutid) 

    }





    // Write out image
    std::cout << "Writing png..." << std::endl;
    const char* savepath = "C:\\Users\\Quinton\\source\\repos\\SRG\\grid_new.png";
    stbi_write_png(savepath, bgwidth, bgheight, bgchannels, data, 0);




}
