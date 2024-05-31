#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include "Utilities.h"
#include "Station.h"

namespace multiproj
{
    size_t Station::m_widthField = 0u;
    size_t Station::id_generator = 0u;

    Station::Station()
    {
        m_id = ++id_generator;
        m_name = "";
        m_desc = "";
        m_serial = 0;
        m_qty = 0;
    }

    Station::Station(const std::string &str)
    {
        Utilities util;
        size_t next_pos = 0;
        bool more = true;
        m_id = ++id_generator;
        m_name = util.extractToken(str, next_pos, more);
        Station::m_widthField = std::max(util.getFieldWidth(), Station::m_widthField);
        m_serial = std::stoi(util.extractToken(str, next_pos, more));
        m_qty = std::stoi(util.extractToken(str, next_pos, more));
        m_desc = util.extractToken(str, next_pos, more);
        
    }
    const std::string &Station::getItemName() const
    {
        return m_name;
    }
    unsigned Station::getNextSerialNumber()
    {
        return m_serial++;
    }
    unsigned Station::getQuantity() const
    {
        return m_qty;
    }
    void Station::updateQuantity()
    {
        if (m_qty > 0)
        {
            m_qty--;
        }
    }
    void Station::display(std::ostream &os, bool full) const
    {
        if (full)
        {
            os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | " << std::setw(6) << std::setfill('0') << std::right << m_serial << " | " << std::setfill(' ') << std::setw(4) << std::right << m_qty << " | " << m_desc << std::endl;
        }
        else
        {
            os << std::setw(3) << std::setfill('0') << std::right << m_id << " | " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_name << " | " << std::setw(6) << std::setfill('0') << std::right << m_serial << " | " << std::endl;
        }
    }
}