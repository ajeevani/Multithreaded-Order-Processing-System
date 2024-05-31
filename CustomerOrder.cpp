#define CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip>
#include "CustomerOrder.h"

namespace multiproj
{
    size_t CustomerOrder::m_widthField = 0u;

    CustomerOrder::CustomerOrder(const std::string str)
    {
        Utilities util;
        size_t next_pos = 0u;
        bool more = true;
        setEmpty();
        m_name = util.extractToken(str, next_pos, more);
        m_product = util.extractToken(str, next_pos, more);
        m_cntItem = std::count(str.begin(), str.end(), util.getDelimiter()) - 1;
        m_lstItem = new Item*[m_cntItem];
        for (size_t i = 0; i < m_cntItem; i++)
        {
            m_lstItem[i] = new Item(util.extractToken(str, next_pos, more));
        }
        if (m_widthField < util.getFieldWidth())
        {
            m_widthField = util.getFieldWidth();
        }
    }

    CustomerOrder::CustomerOrder(const CustomerOrder& co)
    {
        throw "ERROR: Cannot make copies.";
    }

    CustomerOrder::CustomerOrder(CustomerOrder&& co) noexcept
    {
        *this = std::move(co);
    }

    CustomerOrder& CustomerOrder::operator=(CustomerOrder&& co) noexcept
    {
        if (this != &co)
        {
            setEmpty();
            m_name = co.m_name;
            m_product = co.m_product;
            m_cntItem = co.m_cntItem;
            m_lstItem = co.m_lstItem;
            co.m_name = "";
            co.m_product = "";
            co.m_cntItem = 0u;
            co.m_lstItem = nullptr;
        }
        return *this;
    }

    void CustomerOrder::setEmpty()
    {
        if(m_lstItem)
        {
            for(size_t i = 0u; i < m_cntItem; i++)
            {
                delete m_lstItem[i];
                m_lstItem[i] = nullptr;
            }
            delete[] m_lstItem;
        }
        m_lstItem = nullptr;
        m_name = "";
        m_product = "";
        m_cntItem = 0u;
    }

    CustomerOrder::~CustomerOrder()
    {
        setEmpty();
    }

    bool CustomerOrder::isOrderFilled() const
    {
       bool fill = 1;

       for (size_t i = 0u; i < m_cntItem; i++)
       {
            if(m_lstItem[i]->m_isFilled == false)
            {
                fill = 0;
            }
       }

       return fill;

    }

    bool CustomerOrder::isItemFilled(const std::string& itemName) const
    {
        bool pass = true;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if (m_lstItem[i]->m_itemName == itemName)
				pass = m_lstItem[i]->m_isFilled;
		}

		return pass;

    }

    void CustomerOrder::fillItem(Station& station, std::ostream& os)
    {
        bool pass = false;
		for (size_t i = 0; i < m_cntItem; i++)
		{
			if ((m_lstItem[i]->m_itemName == station.getItemName()) && (station.getQuantity() >= 1) && (m_lstItem[i]->m_isFilled == pass))
			{
				pass = true;
				m_lstItem[i]->m_isFilled = true;
				station.updateQuantity(); // takes -1 from inventory
				m_lstItem[i]->m_serialNumber = station.getNextSerialNumber();

				os << "    Filled " << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else if ((m_lstItem[i]->m_itemName == station.getItemName()) && (station.getQuantity() == 0) /* && !m_lstItem[i]->m_isFilled */)
			{
				os << "    Unable to fill " << this->m_name << ", " << this->m_product << " [" << m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
    }

    void CustomerOrder::display(std::ostream& os) const
    {
        os << m_name << " - " << m_product << std::endl;
        for (size_t i = 0u; i < m_cntItem; i++)
        {
            os << "[" << std::setw(6) << std::setfill('0') << std::right << m_lstItem[i]->m_serialNumber << "] " << std::setw(m_widthField) << std::setfill(' ') << std::left << m_lstItem[i]->m_itemName << " - ";
            if (m_lstItem[i]->m_isFilled)
            {
                os << "FILLED" << std::endl;
            }
            else
            {
                os << "TO BE FILLED" << std::endl;
            }
        }
    }
}
