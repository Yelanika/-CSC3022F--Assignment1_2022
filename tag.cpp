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

//namespace GNSSEN002 {
    /***
     * * ExtractTagsandText():
     *      ` 
     * 
     * **/
    void GNSSEN002::ExtractTagsandText(std::vector<std::string> tagInfo) {
        
        std::vector<std::string> tags;
        std::vector<std::string> text; 
        int no_nestedTag = 0; 

        //int tags_size = tags.size();
        //int texts_size = text.size();
        //if (tags_size == texts_size) {

            //int counter = 0;
            //while ((tags_size != 0) and (texts_size != 0)) {
                

            //}
        //}
        //else 
        //std::cout << "Error: The no. of tags and assciated texts are unequal" << std::endl;

        for (int lineNo = 0; lineNo < tagInfo.size(); ++lineNo) {      //going through each line of the textfile

            std::string TagInfo_currentLine = tagInfo[lineNo];    
             
            
            //Testing
            //if (lineNo == 6)
              //  break;
            bool found_ClosingTag = false; //to check if the end tag is found first
            //std::string tag = " ";
            std::size_t TagPos_Start = -1;

            int tagCounter = 0;
            bool sameLine = false;

            if ((TagInfo_currentLine.length()) == 0)       //line is empty
                //ends this iteration and goes to the next iteration
                continue;
            else {              //else capture the data in the line

                char action = 'a';  //the action that will take place in the below switch statement
                
                bool notEmpty = true;
                bool tagInText = false;

                
                //for loop going through each line
                //nestedTag_no                
                while(notEmpty) {
                    switch(action) {
                        case 'a' : {    //option = assign
                            std::cout << lineNo << " Assign: " << TagInfo_currentLine << std::endl;
                            if (TagInfo_currentLine.length() == 0)  {       //if line is empty
                                notEmpty = false;
                                std::cout << " " <<std::endl;
                                break;
                                //continue;
                            }
                            else {
                                // std::size_t prev_TagPos_Start = TagPos_Start;
                                // std::string copy_TagInfo_currentLine = TagInfo_currentLine;       //copy_TagInfo_currentline is just for comparsion
                                // bool found = true;

                                // //Checking for the beginning of a tag
                                // while(found) {        //looking for <
                                TagPos_Start = TagInfo_currentLine.find("<");

                                    //if (TagPos_Start != std::string::npos) //can find < 
                                            //copy_TagInfo_currentLine = copy_TagInfo_currentLine.substr(TagPos_Start+1);
                                            //std::size_t TagPos_End = copy_TagInfo_currentLine.find(">");
                                            //if (TagPos_End != std::string::npos)      //if end tag exists
                                                //if (TagPos_End < TagPos_Start)    //end tag if before the open tag
                                                //TagPos_Start = prev_TagPos_Start;
                                                //break;
                                            //else
                                                //prev_TagPos_Start = TagPos_Start;
                                    //else      //no tag in the line or left in the line
                                            //if (prev_TagPos_Start != std::string::npos)
                                                //TagPos_Start = prev_TagPos_Start;
                                                //found = false
                                
                                //while(true)   //put this is case b
                                //get a tag, look for < sign inside it
                                //if found
                                    //new tag with inner < starting the tag
                                    //take what is left of that tag and add it to the text 
                                //else  
                                    //exception_OpenTag = true;
                                    //std::size_t exception_PosOpenTag_ = what ever the new tags starting postion is in the currentline thing- declare this outside switch statement
                                    //tagInText = true;
                                    //action = 'c';
                                    //break;

                                //in case c inside tagintext is true you have:
                                //if exception_OpenTag = true
                                

                                //if there is a tag in the current line
                                if (TagPos_Start != std::string::npos) {

                                    
                                        //TagPos_Start = copy_TagInfo_currentLine.find("<");
                                        
                                
                                
                                    if (TagPos_Start == 0) {    //if tag is in the first position
                                    //if (counter == 0)
                                        action = 'b';//option:tag
                                        break;
                                    }
                                    else {          // else text is before tag
                                        tagInText = true;
                                        action = 'c';   //option text
                                        break;
                                    }
                                }
                                else {  //there is no tag in the line, just text
                                    action ='c';
                                    break;
                                }
                            }
                            break;
                        }
                        case 'b' : {    //option = tag
                            std::cout << lineNo << " Tag: " << TagInfo_currentLine << std::endl;
                            //Checking for the beginning of a tag
                            //TagPos_Start = TagInfo_currentLine.find("<");

                            //if there is a tag in the current line
                            if (TagPos_Start != std::string::npos) {
                            //     action = 'b';//option:tag
                            // else
                            //     action = 'c';//option text
                                //comment following two lines
                                std::size_t TagPos_End = TagInfo_currentLine.find(">");   //finding the end of the tag 
                                std::string tag = TagInfo_currentLine.substr(TagPos_Start,TagPos_End-TagPos_Start+1); 

                                //put code here
                                bool inner_bracket = true;
                                std::size_t test_tag_open = -1;
                                std::string test_tag = tag.substr(1,tag.size());

                                while (inner_bracket) {
                                    

                                    test_tag_open = test_tag.find("<");
                                    if (test_tag_open != std::string::npos) {
                                        test_tag = test_tag.substr(test_tag_open+1,test_tag.size());
                                        tagInText = true;
                                        TagPos_Start = test_tag_open;
                                        action = 'c';
                                    }
                                    else {
                                        inner_bracket = false;
                                    }
                                }

                                if (tagInText == true) {
                                    
                                    break;
                                }

                                //if onlytage left in the current line
                                std::size_t find_ClosingTag = tag.find("/");    //check if tag is a closing tag
                                if (find_ClosingTag != std::string::npos) {
                                    no_nestedTag--;
                                    sameLine = false;
                                }
                                else {            //opening tag
                                    tags.push_back(tag);
                                    tagCounter++;
                                    no_nestedTag++;
                                }
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_End+1); 
                                std::cout << lineNo << " Tag: no_nestedTag: " << no_nestedTag << std::endl;
                            }
                            action = 'a';    //option = assign
                            break;
                        }
                        case 'c' : {    //option = text
                            std::cout << lineNo << " Text: " << TagInfo_currentLine << std::endl;
                            std::string tagInfo = " ";

                            if (tagInText == true) {     //there is a tag after the text
                                //std::size_t TagPos_Start = TagInfo_currentLine.find("<");       //comment out
                               // std::cout << lineNo << " Text: inside loop" << std::endl;
                                tagInfo = TagInfo_currentLine.substr(0,TagPos_Start);
                               // std::cout << lineNo << " Text: " << tagInfo << std::endl;
                                TagInfo_currentLine = TagInfo_currentLine.substr(TagPos_Start);
                                std::cout << lineNo << " Text: " << TagInfo_currentLine << std::endl;
                            }
                            else { //no tag in text
                                tagInfo = TagInfo_currentLine;
                                //std::cout << "Error 1" << std::endl;
                                TagInfo_currentLine = TagInfo_currentLine.substr(tagInfo.size());
                               // std::cout << "Error 2" << std::endl;
                            }

                            //check for tab spaces
                            bool tabFound = true;
                            

                            while (tabFound) {
                                if (tagInfo[0] == '\t') 
                                    tagInfo = tagInfo.substr(1, tagInfo.size());
                                else
                                    tabFound = false;
                            }
                           // std::cout << lineNo << " Text: no_nestedTag: " << no_nestedTag << " info: " << TagInfo_currentLine << std::endl;
                            if ((no_nestedTag == 1) and (sameLine == false))  {
                                text.push_back(tagInfo);
                                sameLine = true;
                            }
                            else if ((no_nestedTag == 1) and (sameLine == true)) {
                                text[tagCounter - 1] += tagInfo;
                            }
                            //no_nestedTag to current_nestedTagNo
                            //prev_no_nestedTag = no_nestedTag; //at the beginneing of lineno loop
                            //if (no_nestedTag == prev_nestedTagNo)
                            //text.push_back(tagInfo);
                            //if (no_nestedTag > 1) {       //nesting of tags is taking place
                            //if (prev_nestedTagNo > current_nestTagNo)        //tag has been added to nest
                            //text.push_back(tagInfo)
                            //else if (prev_nestedTagNo < current_nestTagNo)    //tag has been removed from the nest
                            //text[tags.size() - 2] = tagInfo      //HOW DO WE FIND THE TEXT_NO -> test[text_no]?????
                            //}
                            else {
                               // std::cout << "Error 3" << std::endl;
                                text[tagCounter - no_nestedTag - 1] += tagInfo;
                               // std::cout << "Error 4" << std::endl;
                            }
                            std::cout << lineNo << " Text: " << tagInfo << std::endl;
                            tagInText = false;
                            action = 'a';   //option = assign
                            break;
                        }
                        default:
                            break;
                    }
                }
            }
        }

        if (tags.size() == text.size()) {
            for (int i = 0; i < tags.size(); ++i) {
                std::cout << "Tag: " << tags[i] << " Text: " << text[i] << std::endl;
            }
        }
        else 
            std::cout << "Error: tags and text size doens't match" << std::endl;

    }
        
        // Tag.push_back({tags[0], 1, text[0]});

        // if (tags.size() > 1) {
        //     for (int i = 1; i < tags.size(); ++i) {     //need to change i to different variable name
                
        //         bool found = false;
        //         int k_tag;

        //         //search for the same tag
        //         for (k_tag = 1; k_tag < i+1; ++k_tag) { //k_tag = position of the tag in vector

        //             //condition: to not check same tag against each other
        //             if ((k_tag-1) != i) {
        //                 if (tags[i] == tags[k_tag-1]) {
        //                     found = true;
        //                     break;      //break out of loop
        //                 }
        //             }
        //         }
                
        //         if (found)  {       //if found is true
        //             Tag[k_tag-1].noTagPairs++;
        //             Tag[k_tag-1].tagText += " : " + text[i];
        //         }
        //         else                //if a new tag name is found
        //             Tag.push_back({tags[i], 1, text[i]});  

        //     }

        // }
        
   // }

    /**** 
     * printTag() -  printing only the tags
     * [option p]
     * **/
    void GNSSEN002::printTag() {

        for (int j = 0; j < Tag.size(); ++j) {
            std::cout << Tag[j].tagName << std::endl;
        }
    }

    /**** 
     * printTagInfo() - printing tag data for given tag
     * [option l]
     * **/
    void GNSSEN002::printTagInfo(std::string inputTagName) {
        
        bool found = false;
        //Looping through the stored tags searching for the tag input 
        for (int j = 0; j < Tag.size(); ++j) {
            if (Tag[j].tagName == inputTagName) {
                std::cout << "No. of Tag Pairs: " << Tag[j].noTagPairs << std::endl;
                std::cout << "Tag Text: " << Tag[j].tagText << std::endl;
                found = true;
            }
            if (found == true)
                break;
        }

        //if the tag input could not be found
        if (found == false)
            std::cout << "The tag '" << inputTagName << "' could not be found." << std::endl;
    }

    /**** 
     * writeTagInfoToFile() -  writing tag data to a file called tag.txt
     * [option d]
     * **/
    void writeTagInfoToFile() {
        
        // for (int j = 0; j < Tag.size(); ++j) {
        //     std::cout << Tag[j].tagName << std::endl;
        // }
    }
    
//}   