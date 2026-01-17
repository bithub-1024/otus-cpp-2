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

int main()
{
    std::vector<ip_t> pool;
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

    std::sort(pool.begin(), pool.end(),
              [](const ip_t &a, const ip_t &b)
              {
                  for (int i = 0; i < 4; i++) if (a.ip[i] != b.ip[i]) return a.ip[i] > b.ip[i];
                  return false;
              });

    for (auto ip : pool) print_ip(ip);

    for (auto ip : pool) if (ip.ip[0] == 1) print_ip(ip);

    for (auto ip : pool) if (ip.ip[0] == 46 && ip.ip[1] == 70) print_ip(ip);

    for (auto ip : pool)
    {
        bool found = false;
        for (int i = 0; i < 4; i++)
            if (ip.ip[i] == 46)
            {
                found = true;
                break;
            }

        if (found) print_ip(ip);
    }

}
