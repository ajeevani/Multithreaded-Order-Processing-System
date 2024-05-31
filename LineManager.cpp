#define CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <algorithm>
#include <string>
#include "LineManager.h"

namespace multiproj
{
    LineManager::LineManager(const std::string &file, const std::vector<Workstation *> &stations)
    {
        std::ifstream ifs(file);
        if (!ifs)
        {
            throw "Error opening file";
        }

        std::string line{};
        while (std::getline(ifs, line))
        {
            if (line.find('|') != std::string::npos)
            {
                std::string fline = line.substr(0, line.find('|')); 
                std::string lline = line.substr((line.find('|') + 1));

                auto firstWorkStation = std::find_if(stations.begin(), stations.end(), [fline](Workstation *ws)
                 { return (ws->getItemName() == fline); });

                if (firstWorkStation != stations.end())
                    m_activeLine.push_back(*firstWorkStation);

                auto nextWorkStation = std::find_if(stations.begin(), stations.end(), [lline](Workstation *ws)
                 { return (ws->getItemName() == lline); });

                if (nextWorkStation != stations.end())
                    m_activeLine.back()->setNextStation(*nextWorkStation);
            }
            else
            {
                auto onlyWorkStation = std::find_if(stations.begin(), stations.end(), [line](Workstation *ws)
                 { return (ws->getItemName() == line); });

                if (onlyWorkStation != stations.end())
                {
                    m_activeLine.push_back(*onlyWorkStation);
                    m_activeLine.back()->setNextStation(); // default to nullptr
                }
            }
        }

        auto firstWorkStation = std::find_if(m_activeLine.begin(), m_activeLine.end(), [this](const Workstation *ws)
        { 
            bool result = true; 
            std::for_each(m_activeLine.begin(), m_activeLine.end(), [ws, &result](const Workstation *ws2)
            {
                if((ws != ws2) && (ws2->getNextStation() != nullptr) && (ws == ws2->getNextStation()))
                    result = false;
            });
            return result; 
        });

        if (firstWorkStation != m_activeLine.end())
            m_firstStation = *(firstWorkStation);
        m_cntCustomerOrder = g_pending.size();
    }

    void LineManager::reorderStations()
    {
        std::vector<Workstation *> reordered;
        for (Workstation *station = m_firstStation; station != nullptr; station = station->getNextStation())
        {
            reordered.push_back(station);
        }
        m_activeLine = std::move(reordered);
    }

    bool LineManager::run(std::ostream &os)
    {
        static int counter = 0;
        counter++;

        os << "Line Manager Iteration: " << counter << std::endl;

        if (!g_pending.empty())
        {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto &station : m_activeLine)
        {
            station->fill(os);
        }

        for (auto &station : m_activeLine)
        {
            station->attemptToMoveOrder();
        }

        return (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size()));
    }

    void LineManager::display(std::ostream &os) const
    {
        std::for_each(m_activeLine.begin(), m_activeLine.end(), [&os](const Workstation *ws)
         { ws->display(os); });
    }
}