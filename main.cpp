#include "lib.h"

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <vector>
#include <iterator>
#include <sstream>
#include <array>

using namespace std;

template <typename T = int>
struct Tstring_ip_addres { 
    std::array<T,4> ip_numbers{};    
    bool before (const Tstring_ip_addres& other) const{
    return !std::lexicographical_compare(ip_numbers.begin(),ip_numbers.end(),
                                        other.ip_numbers.begin(),other.ip_numbers.end(),
                                        [&](const T&a,const T&b){
                                            return a < b;
                                            }
                                        );            
    }
    bool any(T number){
        return std::find(ip_numbers.begin(),ip_numbers.end(),number) != ip_numbers.end();
    }
    void print()const{
        std::cout  << ip_numbers[0] << "." << ip_numbers[1] << "." << ip_numbers[2] << "." << ip_numbers[3] << "\n";
    }
};

std::istream& operator>>(std::istream &is, Tstring_ip_addres<> &ip)
{
    std::string ip_addres; 
    is >> std::ws >> ip_addres;
    
    std::istringstream iss{ip_addres};
    
    iss.setf(std::ios_base::dec, std::ios_base::floatfield);
    iss.setf(std::ios_base::skipws);
    iss >> ip.ip_numbers[0];iss.ignore(1);
    iss >> ip.ip_numbers[1];iss.ignore(1);
    iss >> ip.ip_numbers[2];iss.ignore(1);
    iss >> ip.ip_numbers[3];iss.ignore(1);   
    
    int a;   
    
    is >> std::ws >> a >> std::ws >> a;
    
    return is;
}


int main (int, char **) {

    string line{};
    string all_line{};
    while (getline(cin,line)){
        all_line+= line+"\n";
    }
    std::istringstream in{all_line};
    std::vector<Tstring_ip_addres<>> ip_address;
    copy(std::istream_iterator<Tstring_ip_addres<>>{in}, {},back_inserter(ip_address));
    std::sort(ip_address.begin(),ip_address.end(),[](const Tstring_ip_addres<>& a, const Tstring_ip_addres<>& b) {return a.before(b);});
    for (const auto &ip_addres:ip_address)ip_addres.print();    
    std::for_each(ip_address.begin(), ip_address.end(), [](auto &n) { if(n.ip_numbers[0]==1)n.print(); });    
    std::for_each(ip_address.begin(), ip_address.end(), [](auto &n) { if(n.ip_numbers[0]==46 && n.ip_numbers[1]==70)n.print(); });    
    std::for_each(ip_address.begin(), ip_address.end(), [](auto &n) { if(n.any(46))n.print(); });    
    return 0;
}
