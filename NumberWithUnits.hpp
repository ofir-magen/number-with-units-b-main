#pragma ones
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <utility>
#include <stdbool.h>


namespace ariel
{

    class NumberWithUnits
    {
    private:
        static std::map<std::string, std::pair<std::string, double>> unit_list;

        std::string unit_type;
        double num_size;

    public:
        static void read_units(std::ifstream &file);
        static double changeUnit(const std::string &unit_from, const std::string &unit_to, double to_change);

        NumberWithUnits(double number, const std::string &unit);

        ~NumberWithUnits() {}

        friend std::ostream &operator<<(std::ostream &out, const NumberWithUnits &element);
        friend std::istream &operator>>(std::istream &in, NumberWithUnits &element);

        NumberWithUnits operator+(const NumberWithUnits &element2);
        NumberWithUnits operator+(); 
        NumberWithUnits &operator+=(const NumberWithUnits &element2);
        NumberWithUnits operator-(const NumberWithUnits &element2);
        NumberWithUnits operator-();
        NumberWithUnits &operator-=(const NumberWithUnits &element2);

        NumberWithUnits &operator++();  
        NumberWithUnits operator++(int); 
        NumberWithUnits &operator--();   
        NumberWithUnits operator--(int); 

        friend NumberWithUnits operator*(const NumberWithUnits &element, double num);
        friend NumberWithUnits operator*(double num, const NumberWithUnits &element);
        NumberWithUnits &operator*=(double num);

        bool operator>(const NumberWithUnits &element2) const;
        bool operator>=(const NumberWithUnits &element2) const;
        bool operator<(const NumberWithUnits &element2) const;
        bool operator<=(const NumberWithUnits &element2) const;
        bool operator==(const NumberWithUnits &element2) const;
        bool operator!=(const NumberWithUnits &element2) const;
    };
}