#include <iostream>
#include <stdexcept>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string.h>
#include <map>
#include "NumberWithUnits.hpp"

const double Eps = 0.0001;

using namespace std;
namespace ariel
{
        std::map<std::string, std::pair<std::string, double>> NumberWithUnits::unit_list{};
        NumberWithUnits::NumberWithUnits(double number, const std::string &unit)
        {
                if (unit_list.count(unit) == 0)
                {
                        throw std::out_of_range("Invalid uniot: " + unit);
                }
                this->num_size = number;
                this->unit_type = unit;
        };

        void NumberWithUnits::read_units(ifstream &file)
        {
                double parameter = 0;
                double one = 0;
                std::string MainUnit;
                std::string sub_main_unit;
                std::string equals;
                while (file >> one >> MainUnit >> equals >> parameter >> sub_main_unit)
                {
                        int flag_case = -1;
                        if (unit_list.count(MainUnit) != 0)
                        {
                                if (unit_list.count(sub_main_unit) != 0)
                                {
                                        flag_case = 1;
                                }
                                else
                                {
                                        flag_case = 2;
                                }
                        }
                        else
                        {
                                if (unit_list.count(sub_main_unit) != 0)
                                {
                                        flag_case = 3;
                                }
                                else
                                {
                                        flag_case = 4;
                                }
                        }
                        switch (flag_case)
                        {
                        case (1):
                                if (unit_list[MainUnit].first == unit_list[sub_main_unit].first)
                                {
                                        break;
                                }
                                else
                                {
                                        double temp = unit_list[MainUnit].second * unit_list[sub_main_unit].second * parameter;
                                        unit_list[unit_list[MainUnit].first].second = temp;
                                        unit_list[unit_list[MainUnit].first].first = unit_list[unit_list[sub_main_unit].first].first;
                                        for (pair<string, pair<string, double>> element : unit_list)
                                        {
                                                if (element.second.first == unit_list[MainUnit].first)
                                                {
                                                        element.second.second = (1.0 / element.second.second) * temp;
                                                }
                                        }
                                }
                                break;
                        case (2):
                                unit_list[sub_main_unit].first = unit_list[MainUnit].first;
                                unit_list[sub_main_unit].second = (1 / parameter) * unit_list[MainUnit].second;

                                break;
                        case (3):
                                unit_list[MainUnit].first = unit_list[sub_main_unit].first;
                                unit_list[MainUnit].second = parameter * unit_list[sub_main_unit].second;

                                break;
                        case (4):
                                unit_list[MainUnit].first = MainUnit;
                                unit_list[MainUnit].second = 1;
                                unit_list[sub_main_unit].first = unit_list[MainUnit].first;
                                unit_list[sub_main_unit].second = (1 / parameter);
                                break;

                        default:
                                break;
                        }
                }
                file.close();
        }

        double NumberWithUnits::changeUnit(const std::string &unit_from, const std::string &unit_to, double to_change)
        {
                double ans = 0;
                if (unit_list[unit_from].first == unit_list[unit_to].first)
                {

                        ans = (to_change * unit_list[unit_from].second) * (1 / unit_list[unit_to].second);
                }
                else
                {
                        throw invalid_argument{"The units are not from the same category!!"};
                }
                return ans;
        }

        ostream &operator<<(std::ostream &out, const NumberWithUnits &element)
        {
                out << element.num_size << "[" << element.unit_type << "]";
                return out;
        }
        istream &operator>>(std::istream &in, NumberWithUnits &element)
        {
                double parameter = 0;
                string unit;
                char bracket_1;
                char bracket_2;
                in >> parameter >> bracket_1 >> unit;
                double bracket = unit.length() - 1;
                if ((unit.at(bracket)) == ']')
                {
                        unit = unit.substr(0, unit.size() - 1);
                        element = NumberWithUnits(parameter, unit);
                }
                else
                {
                        in >> bracket_2;
                        element = NumberWithUnits(parameter, unit);
                }
                return in;
        }

        NumberWithUnits NumberWithUnits::operator+(const NumberWithUnits &element2)
        {
                double newNumber = changeUnit(element2.unit_type, this->unit_type, element2.num_size);
                return NumberWithUnits((this->num_size + newNumber), this->unit_type);
        }
        NumberWithUnits NumberWithUnits::operator+()
        {
                return NumberWithUnits(+this->num_size, this->unit_type);
        }
        NumberWithUnits &NumberWithUnits::operator+=(const NumberWithUnits &element2)
        {
                double newNumber = changeUnit(element2.unit_type, this->unit_type, element2.num_size);
                this->num_size += newNumber;
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator-(const NumberWithUnits &element2)
        {
                double newNumber = changeUnit(element2.unit_type, this->unit_type, element2.num_size);
                return NumberWithUnits(this->num_size - newNumber, this->unit_type);
        }
        NumberWithUnits NumberWithUnits::operator-()
        {
                return NumberWithUnits(-this->num_size, this->unit_type);
        }
        NumberWithUnits &NumberWithUnits::operator-=(const NumberWithUnits &element2)
        {
                double newNumber = changeUnit(element2.unit_type, this->unit_type, element2.num_size);
                this->num_size -= newNumber;
                return *this;
        }
        NumberWithUnits &NumberWithUnits::operator++()
        {
                ++(this->num_size);
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator++(int)
        {
                return NumberWithUnits((this->num_size)++, this->unit_type);
        }
        NumberWithUnits &NumberWithUnits::operator--()
        {
                --(this->num_size);
                return *this;
        }
        NumberWithUnits NumberWithUnits::operator--(int)
        {
                return NumberWithUnits((this->num_size)--, this->unit_type);
        }
        NumberWithUnits operator*(const NumberWithUnits &element, double num)
        {
                return NumberWithUnits(element.num_size * num, element.unit_type);
        }
        NumberWithUnits operator*(double num, const NumberWithUnits &element)
        {
                return NumberWithUnits(element.num_size * num, element.unit_type);
        }
        NumberWithUnits &NumberWithUnits::operator*=(double num)
        {
                this->num_size *= num;
                return *this;
        }
        bool NumberWithUnits::operator>(const NumberWithUnits &element2) const
        {
                return ((this->num_size) - changeUnit(element2.unit_type, this->unit_type, element2.num_size) > Eps);
        }
        bool NumberWithUnits::operator>=(const NumberWithUnits &element2) const
        {
                return !(*this < element2);
        }
        bool NumberWithUnits::operator<(const NumberWithUnits &element2) const
        {
                return ((this->num_size) - changeUnit(element2.unit_type, this->unit_type, element2.num_size) < -Eps);
        }
        bool NumberWithUnits::operator<=(const NumberWithUnits &element2) const
        {
                return !(*this > element2);
        }
        bool NumberWithUnits::operator==(const NumberWithUnits &element2) const
        {
                double temp_num = changeUnit(element2.unit_type, this->unit_type, element2.num_size);
                return ((this->num_size <= (temp_num + Eps)) && (this->num_size >= (temp_num - Eps)));
        }
        bool NumberWithUnits::operator!=(const NumberWithUnits &element2) const
        {
                return !(*this == element2);
        }
};