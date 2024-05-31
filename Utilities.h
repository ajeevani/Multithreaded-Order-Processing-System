#ifndef MULTIPROJ_UTILITIES_H
#define MULTIPROJ_UTILITIES_H
#include <iostream>

namespace multiproj
{
   class Utilities
   {
       size_t m_widthField = 1;
       static char m_delimiter;
    public:
        void setFieldWidth(size_t newWidth);
        size_t getFieldWidth() const;
        const std::string extractToken(const std::string& str, size_t& next_pos, bool& more);
        static void setDelimiter(char newDelimiter);
        static char getDelimiter();
        std::string trim(const std::string& str);
   };
}
#endif