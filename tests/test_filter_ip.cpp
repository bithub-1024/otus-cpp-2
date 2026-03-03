#define BOOST_TEST_MODULE IPFilterTests
#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include "filter_ip.hpp"

static std::string to_str(const ip_t& ip)
{
    std::ostringstream os;
    os << ip;
    return os.str();
}

BOOST_AUTO_TEST_CASE(SortDescending)
{
    std::vector<ip_t> pool = {
        {{1,2,3,4}},
        {{46,70,1,1}},
        {{46,71,0,0}},
        {{1,1,1,1}}
    };

    sort_pool_ip(pool);

    BOOST_TEST(to_str(pool[0]) == "46.71.0.0");
    BOOST_TEST(to_str(pool[1]) == "46.70.1.1");
    BOOST_TEST(to_str(pool[2]) == "1.2.3.4");
    BOOST_TEST(to_str(pool[3]) == "1.1.1.1");
}

BOOST_AUTO_TEST_CASE(FilterByFirstOctet)
{
    std::vector<ip_t> pool = {
        {{1,2,3,4}},
        {{1,5,6,7}},
        {{46,70,1,1}}
    };

    auto res = filter_ip(pool, 1);

    BOOST_TEST(res.size() == 2);
    BOOST_TEST(to_str(res[0]) == "1.2.3.4");
    BOOST_TEST(to_str(res[1]) == "1.5.6.7");
}

BOOST_AUTO_TEST_CASE(FilterByTwoOctets)
{
    std::vector<ip_t> pool = {
        {{46,70,1,1}},
        {{46,70,2,2}},
        {{46,71,1,1}}
    };

    auto res = filter_ip(pool, 46, 70);

    BOOST_TEST(res.size() == 2);
    BOOST_TEST(to_str(res[0]) == "46.70.1.1");
    BOOST_TEST(to_str(res[1]) == "46.70.2.2");
}

BOOST_AUTO_TEST_CASE(FilterAny)
{
    std::vector<ip_t> pool = {
        {{1,2,3,4}},
        {{46,0,0,0}},
        {{1,46,1,1}},
        {{2,3,4,5}}
    };

    auto res = filter_any(pool, 46);

    BOOST_TEST(res.size() == 2);
    BOOST_TEST(to_str(res[0]) == "46.0.0.0");
    BOOST_TEST(to_str(res[1]) == "1.46.1.1");
}

BOOST_AUTO_TEST_CASE(EmptyResult)
{
    std::vector<ip_t> pool = {
        {{1,1,1,1}}
    };

    auto res = filter_ip(pool, 99);

    BOOST_TEST(res.empty());
}
