#define BOOST_TEST_MODULE test_ip_filter

#include "lib.h"


#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>


#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(test_ip_filter)

BOOST_AUTO_TEST_CASE(test_test)
{
  BOOST_CHECK(true == true);
}

BOOST_AUTO_TEST_CASE(test_valid_version)
{
  std::cout <<"test_valid_version" << std::endl;
  BOOST_CHECK(version() != 100);
}
BOOST_AUTO_TEST_CASE(ip_filter_md5sum)
{
  std::cout << "START ip_filter_md5sum" <<std::endl;
  system("cat ip_filter.tsv | ./ip_filter | md5sum > 1.txt");

  std::string line_test;
  std::ifstream in("1.txt"); 
  if (in.is_open())
  {
      std::string line;
      while (std::getline(in, line))
      {
          std::istringstream iss{line};
          iss >> std::ws >> line_test;
      }
  }else{
    std::cout<<"file not open" << "\n";
  }
  
  in.close(); 

  std::string true_line = "24e7a7b2270daee89c64d3ca5fb3da1a";

  BOOST_CHECK(line_test == true_line);
  system("rm 1.txt");
}

BOOST_AUTO_TEST_SUITE_END()
