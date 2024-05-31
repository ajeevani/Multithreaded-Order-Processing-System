#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <algorithm>
#include "Utilities.h"

namespace multiproj
{
    char Utilities::m_delimiter{};
    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }
    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }
    const std::string Utilities::extractToken(const std::string &str, size_t &next_pos, bool &more)
    {
        std::string result = ""; 
        size_t first_pos = next_pos;
    
        next_pos = str.find(m_delimiter, first_pos); 

        if (first_pos == next_pos)
        {
            more = false;
            throw "   ERROR: No token.\n";
        }  
        else if (next_pos == std::string::npos)
        {
            result = str.substr(first_pos); 
            more = false;
        }
        else
        {
            result = str.substr(first_pos, next_pos - first_pos);
            more = true;
        }
        result = trim(result);
        if(result.size() > m_widthField)
        {
            m_widthField = result.length();
        }    
        next_pos++;

        return result;
    }
    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }
    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
    std::string Utilities::trim(const std::string& str) 
    {
        size_t first = str.find_first_not_of(' ');
        if (first == std::string::npos) 
        {
            return "";
        }
        
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, last-first + 1);
    }
}