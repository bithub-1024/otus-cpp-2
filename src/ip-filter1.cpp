#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct ip_t
{
    short ip[4];
};

void print_ip(const ip_t &v)
{
    std::cout << v.ip[0] << '.' << v.ip[1] << '.' << v.ip[2] << '.' << v.ip[3] << '\n';
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

void sort_pool_ip(std::vector<ip_t> &pool)
{
    std::sort(pool.begin(), pool.end(),
              [](const ip_t &a, const ip_t &b)
              {
                  for (int i = 0; i < 4; i++)
                      if (a.ip[i] != b.ip[i])
                          return a.ip[i] > b.ip[i];
                  return false;
              });
}

template <typename... Args>
void print_pool_ip(std::vector<ip_t> &pool, bool for_any = false, Args... args)
{
    std::vector<int> filters{args...};

    int i_filters = sizeof(filters);

    if (i_filters == 0)
    {
        for (auto ip : pool)
            print_ip(ip);
    }
    else if (i_filters == 1)
    {
        if !(for_any)
        {
            for (auto ip : pool)
                if (ip.ip[0] == filters[0])
                    print_ip(ip);
        }
        else
        {
            for (auto ip : pool)
            {
                bool found = false;
                for (int i = 0; i < 4; i++)
                    if (ip.ip[i] == filters[0])
                    {
                        found = true;
                        break;
                    }

                if (found)
                    print_ip(ip);
            }
        }
    }
    else if (i_filters == 2) {

     for (auto ip : pool)
        if (ip.ip[0] == filters[0] && ip.ip[1] == filters[1])
            print_ip(ip);       
    }
}

int main()
{
    std::vector<ip_t> pool;

    load_pool_ip(pool);

    sort_pool_ip(pool);

    print_pool_ip(pool);
    print_pool_ip(pool, false, 1);
    print_pool_ip(pool, false, 46, 70);
    print_pool_ip(pool, true, 46);

    /*for (auto ip : pool)
        print_ip(ip);

    for (auto ip : pool)
        if (ip.ip[0] == 1)
            print_ip(ip);

    for (auto ip : pool)
        if (ip.ip[0] == 46 && ip.ip[1] == 70)
            print_ip(ip);

    for (auto ip : pool)
    {
        bool found = false;
        for (int i = 0; i < 4; i++)
            if (ip.ip[i] == 46)
            {
                found = true;
                break;
            }

        if (found)
            print_ip(ip);
    }*/
}
