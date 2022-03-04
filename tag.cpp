/***
 * Created Date: 2022/02/24
 * Yelanika Gunasekara
 * GNSSEN002
 * 
 * tag.cpp
 * 
 * ***/

#include "tag.h"
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>

/***
 * 
 * getTag -  
 * 
 * 
 * **/

std::string GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
    
    std::vector<std::string> tags;
    std::vector<std::string> text; 

    for (int i = 0; i < tagInfo.size(); ++i) {

        std::string temp = tagInfo[i];

        bool found_endTag = false; //to check if the end tag is found first

        //variables to help identify if the line has any values or is empty 
        std::string temp2 = temp;
        int spaces_temp2 = 0;
        for (int j = 0; j < temp2.length(); ++j) {
            if (temp2.at(j) == ' ')
                spaces_temp2++;
        }       

        //if the no. of spaces in the line = length of the line-1, then iterate again and go to next line
        if (spaces_temp2 == (temp2.length()-1))
            continue;
        else {              //else capture the data in the line

            //std::cout << "1: " << temp << std::endl;

            //Getting the tag
            std::size_t StagPos = temp.find("<");

            //if there is a tag in the current line
            if (StagPos!=std::string::npos) {
                std::size_t EtagPos = temp.find(">");
                std::string tag = temp.substr(StagPos,EtagPos-StagPos+1);

                std::size_t EndTagPos = tag.find("/");

                if (EndTagPos!=std::string::npos)  //if an endtag is found
                    found_endTag = true;
                else {
                    tags.push_back(tag);

                    //current line without the tag
                    temp = temp.substr(EtagPos+1);
                    //std::cout << temp.length() << std::endl;

                    //Check for text once the tag is removed 
                    if (temp.length() == 0)
                        found_endTag = true;

                    // std::string temp3 = temp;
                    // int spaces_temp3 = 0;
                    // for (int j = 0; j < temp3.length(); ++j) {
                    //     if (temp3.at(j) == ' ')
                    //         spaces_temp3++;
                    // }

                    // if (spaces_temp3 == (temp3.length()-1))
                    //     found_endTag = true;
                }
                      
                
            }

            //std::cout << "2: " << found_endTag << std::endl;
            //if the end tag is found first - then skip this section of pushing back text
            if (found_endTag == false) {    
                //Getting the text - looking for end tag
                std::size_t StextPos = temp.find("<");

                //if end tag is found & we are getting the text
                if (StextPos!=std::string::npos) {
                    std::size_t EtextPos = temp.find(">");
                    std::string tText = temp.substr(0,StextPos);
                    text.push_back(tText);
                }
                else    //else there must only be string left in the current line 
                    text.push_back(temp);
            }
        }        
    }

    std::vector<GNSSEN002::TagStruct> Tag;  
    Tag.push_back({tags[0], 1, text[0]});

    if (tags.size() > 1) {
        for (int i = 1; i < tags.size(); ++i) {
            
            bool found = false;
            int k_tag;

            //std::cout << i << " " << tags[i] << " " << text[i] << std::endl;

            //search for the same tag
            for (k_tag = 1; k_tag < i+1; ++k_tag) { //k_tag = position of the tag in vector

                //condition: to not check same tag against each other
                if ((k_tag-1) != i) {
                    if (tags[i] == tags[k_tag-1]) {
                        found = true;
                        break;      //break out of loop
                    }
                }
            }
            
            if (found)  {       //if found is true
                Tag[k_tag-1].noTagPairs++;
                Tag[k_tag-1].tagText += " : " + text[i];
            }
            else                //if a new tag name is found
                Tag.push_back({tags[i], 1, text[i]});  

        }

    }

    //std::cout << "Testing 4" << std::endl;
    for (int j = 0; j < Tag.size(); ++j) {
        std::cout << Tag[j].tagName << std::endl;
        std::cout << Tag[j].noTagPairs << std::endl;
        std::cout << Tag[j].tagText << std::endl;
    }

    //std::cout << "Testing Passed" << std::endl;
    return "";
    
}
    