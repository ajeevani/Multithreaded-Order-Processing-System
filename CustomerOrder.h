#ifndef MULTIPROJ_CUSTOMERORDER_H
#define MULTIPROJ_CUSTOMERORDER_H
#include <iostream>
#include <string>
#include "Station.h"
#include "Utilities.h"
namespace multiproj
{
    struct Item
    {
        std::string m_itemName{""};
        unsigned int m_serialNumber{0};
        bool m_isFilled{false};

        Item(const std::string& str) : m_itemName(str) {};
    };

    class CustomerOrder
    {
        std::string m_name{};
        std::string m_product{};
        unsigned int m_cntItem{};
        Item** m_lstItem{};
        static size_t m_widthField;
    public:
        CustomerOrder() = default;
        CustomerOrder(const std::string str);
        CustomerOrder(const CustomerOrder& co);
        CustomerOrder& operator=(const CustomerOrder& co) = delete;
        CustomerOrder(CustomerOrder&& co) noexcept;
        CustomerOrder& operator=(CustomerOrder&& co) noexcept;
        void setEmpty();
        ~CustomerOrder();
        bool isOrderFilled() const;
        bool isItemFilled(const std::string& itemName) const;
        void fillItem(Station& station, std::ostream& os);
        void display(std::ostream& os) const;
    };
}

#endif