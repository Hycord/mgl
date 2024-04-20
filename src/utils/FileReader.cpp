/*
  FileReader.cpp
  Created: April 14, 2024
*/

#include "FileReader.h"
#include <fstream>



std::string ReadFile(std::string location)
{
    std::ifstream file(location);
    std::string data;

    if (file.is_open())
    {
        // Read file contents line by line
        std::string line;
        while (std::getline(file, line))
        {
            data += line;
            data += '\n'; // Add newline character since std::getline strips it
        }
        file.close(); // Close the file after reading
    }

    return data;
}

bool Exists (const std::string name) {
    if (FILE *file = fopen(name.c_str(), "r")) {
        fclose(file);
        return true;
    } else {
        return false;
    }   
}