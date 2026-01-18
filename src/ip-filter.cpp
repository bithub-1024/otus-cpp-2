#include <iostream>
#include "filter_ip.hpp"

int main()
{
    std::vector<ip_t> pool;

    load_pool_ip(pool); /*← как было, оставляешь*/

    sort_pool_ip(pool);

    for (const auto& ip : filter_ip(pool))
        std::cout << to_string(ip) << '\n';

    for (const auto& ip : filter_ip(pool, 1))
        std::cout << to_string(ip) << '\n';

    for (const auto& ip : filter_ip(pool, 46, 70))
        std::cout << to_string(ip) << '\n';

    for (const auto& ip : filter_any(pool, 46))
        std::cout << to_string(ip) << '\n';
}

