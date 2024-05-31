#ifndef MULTIPROJ_WORKSTATION_H
#define MULTIPROJ_WORKSTATION_H
#include <iostream>
#include <deque>
#include "Station.h"
#include "CustomerOrder.h"

namespace multiproj
{
    extern std::deque<CustomerOrder> g_pending;    
    extern std::deque<CustomerOrder> g_completed;   
    extern std::deque<CustomerOrder> g_incomplete;

    class Workstation : public Station
    {
        std::deque<CustomerOrder> m_orders{};
        Workstation *m_pNextStation{};

    public:
        Workstation(const std::string &str);
        void fill(std::ostream &os);
        bool attemptToMoveOrder();
        void setNextStation(Workstation *station = nullptr);
        Workstation *getNextStation() const;
        void display(std::ostream &os) const;
        Workstation &operator+=(CustomerOrder &&newOrder);

        // deleted copy and move operations
        Workstation(const Workstation &ws) = delete;
        Workstation &operator=(const Workstation &ws) = delete;
        Workstation(Workstation &&ws) = delete;
        Workstation &operator=(Workstation &&ws) = delete;
    };
}

#endif