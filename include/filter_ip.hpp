#pragma once

#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

struct ip_t
{
    short ip[4];
};

std::ostream& operator<<(std::ostream& st,const ip_t& ip)
{
    st<<static_cast<int>(ip.ip[0]) << "." << static_cast<int>(ip.ip[1]) << "." << static_cast<int>(ip.ip[2]) << "." << static_cast<int>(ip.ip[3]);

    return st;
}

void load_pool_ip(std::vector<ip_t> &pool)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        std::stringstream ss(line);
        std::string ip_str;
        std::getline(ss, ip_str, '\t');
        std::stringstream ipss(ip_str);
        ip_t value{};
        for (int i = 0; i < 4; i++)
        {
            std::string part;
            std::getline(ipss, part, '.');
            value.ip[i] = static_cast<short>(std::stoi(part));
        }
        pool.push_back(value);
    }
}

inline void sort_pool_ip(std::vector<ip_t>& pool)
{
    std::sort(pool.begin(), pool.end(),
        [](const ip_t& a, const ip_t& b)
        {
            for (int i = 0; i < 4; ++i)
            {
                if (a.ip[i] != b.ip[i])
                    return a.ip[i] > b.ip[i];
            }
            return false;
        });
}

/**
 * filter_ip(pool)              -> все IP
 * filter_ip(pool, 1)           -> ip[0] == 1
 * filter_ip(pool, 46, 70)      -> ip[0]==46 && ip[1]==70
 */
template <typename... Args>
std::vector<ip_t> filter_ip(const std::vector<ip_t>& pool, Args... args)
{
    std::vector<int> filters{args...};
    std::vector<ip_t> result;

    for (const auto& ip : pool)
    {
        bool match = true;
        for (size_t i = 0; i < filters.size(); ++i)
        {
            if (ip.ip[i] != filters[i])
            {
                match = false;
                break;
            }
        }

        if (match)
            result.push_back(ip);
    }

    return result;
}

/**
 * filter_any(pool, 46) -> любой октет == 46
 */
inline std::vector<ip_t> filter_any(const std::vector<ip_t>& pool, int value)
{
    std::vector<ip_t> result;

    for (const auto& ip : pool)
    {
        for (int i = 0; i < 4; ++i)
        {
            if (ip.ip[i] == value)
            {
                result.push_back(ip);
                break;
            }
        }
    }

    return result;
}
