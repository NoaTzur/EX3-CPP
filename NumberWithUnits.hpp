#pragma once
#include <string>
#include <map>
#include <fstream>
#include <sstream>

namespace ariel {

    // class that represent one number unit, each unit has : "from" = number "to".
    // and dimension that represent the unit "group" its in
    class nu_cell{

        public:
            std:: string _from;
            std:: string _to;
            double _number;
            int _dimension;
    };

    static int _dim = 0;

    class NumberWithUnits{

        public:
            static std::map<std::string, nu_cell> _units_map; //map to save all units from the text file

            double _unit_num;
            std::string _unit_name;
            int _unit_dim;

            //constructor with initialization list, for each unit_number we check in what "units group" its belong to.
            NumberWithUnits(double unit_num = 0, std::string unit_name = "n"): _unit_num(unit_num), _unit_name(unit_name){
                this->_unit_dim = checks_dimension(unit_name);
                if (this->_unit_dim <= 0){
                    throw std::logic_error(std::string("not valid"));
                }

            }

            ~NumberWithUnits() {}
            /*

                           Static functions for building the "units_map" and the converting algo.
           
            */
            static int checks_dimension(std::string unit_name);
            static double convert(const NumberWithUnits &to, const NumberWithUnits &from);
            static std::ifstream& read_units(std::ifstream& file); 
          
            /*

                           Member class operators that i implemented in hpp class

            */

            //a = a+b . a in "this" in this example
            NumberWithUnits& operator+=(const NumberWithUnits& other) {
                if (this->_unit_dim != other._unit_dim)
                {
                    //units arent in the same dimension
                    throw std::logic_error(std::string("Units do not match - [" + other._unit_name + "] cannot be converted to [" + this->_unit_name+"] "));
                }
                double ratio = convert(*this, other);
                this->_unit_num = (this->_unit_num) + (other._unit_num)*ratio;
                return *this; // for call chaining

            }

            //a = a-b . a in "this" in this example
            NumberWithUnits& operator-=(const NumberWithUnits& other) {
                if (this->_unit_dim != other._unit_dim)
                {
                    //units arent in the same dimension
                    throw std::logic_error(std::string("Units do not match - [" + other._unit_name + "] cannot be converted to [" + this->_unit_name+"] "));
                }
                double ratio = convert(NumberWithUnits(_unit_num,_unit_name), other);
                this->_unit_num = (this->_unit_num) - (other._unit_num)*ratio;
                return *this; // for call chaining
            }

            //unary minus , from a to -a . example : from 2km to -2km
            const NumberWithUnits operator-() const {
                
                double to_minus = (this->_unit_num) * -1;
                NumberWithUnits temp{to_minus, this->_unit_name};
                return temp;
                
            }
            
            //unary plus - does nothing
            const NumberWithUnits operator+() const {
                
                NumberWithUnits temp{this->_unit_num, this->_unit_name};
                return temp;
                
            }
            
            // postfix increment
            const NumberWithUnits operator++(int dummy_flag_for_postfix_increment) {
                NumberWithUnits temp = *this;
                this->_unit_num++;
                return temp;
            }
            
            // postfix dicrement
            const NumberWithUnits operator--(int dummy_flag_for_postfix_increment) {

                NumberWithUnits temp = *this;
                this->_unit_num--;
                return temp;
            }
            
            // prefix increment
            NumberWithUnits& operator++() {
                this->_unit_num++;
                return *this;
                
            }
            
            // prefix increment
            NumberWithUnits& operator--() {
               this->_unit_num--;
                return *this;
            }

            /*
            
                            Friend operators i have implemented in CPP file
            
            */
            friend NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits &n2);
            friend NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits &n2);
            friend NumberWithUnits operator*(const double to_mult, const NumberWithUnits &n1);
            friend NumberWithUnits operator*(const NumberWithUnits &n1, const double to_mult);
            friend std::ostream& operator<< (std::ostream& os, const NumberWithUnits& n);
            friend std::istream& operator>> (std::istream& input, NumberWithUnits& n);
            friend bool operator ==(const NumberWithUnits &n1, const NumberWithUnits &n2);
            friend bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2);
            friend bool operator <(const NumberWithUnits& n1, const NumberWithUnits& n2);
            friend bool operator >(const NumberWithUnits& n1, const NumberWithUnits& n2);
            friend bool operator <=(const NumberWithUnits& n1, const NumberWithUnits& n2);
            friend bool operator >=(const NumberWithUnits& n1, const NumberWithUnits& n2);
   

    };
};