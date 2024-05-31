#ifndef MULTIPROJ_STATION_H
#define MULTIPROJ_STATION_H
#include <iostream>

namespace multiproj
{
    class Station
    {
        size_t m_id;
        std::string m_name;
        std::string m_desc;
        unsigned m_serial;
        unsigned m_qty;
        static size_t m_widthField;
        static size_t id_generator;
    public:
        Station();
        Station(const std::string& str);
        const std::string& getItemName() const;
        unsigned getNextSerialNumber();
        unsigned getQuantity() const;
        void updateQuantity();
        void display(std::ostream& os, bool full) const;
    };
}
#endif