// #define BOOST_TEST_MODULE test_version
#define BOOST_TEST_MODULE test_ip_filter

#include "lib.h"

#include <boost/test/unit_test.hpp>

//  BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_SUITE(test_ip_filter)

 BOOST_AUTO_TEST_CASE(test_valid_version)
 {
    BOOST_CHECK(version() != 100);
 }

BOOST_AUTO_TEST_SUITE_END()
