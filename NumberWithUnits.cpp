
#include <string>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

#include "NumberWithUnits.hpp"
using namespace std;
#define EPSILON 0.01


namespace ariel {
    
   map<std::string, nu_cell> NumberWithUnits::_units_map; //map to save all units from the text file

    //this function update the unit dimension according to the units map !
    int NumberWithUnits::checks_dimension(string unit_name){
        map<string, nu_cell>::iterator it;

        for (it = _units_map.begin(); it != _units_map.end(); it++)
        {
            if ((it->first) == unit_name|| (it->second._to) == unit_name)
            {
                if(it->second._dimension != 0){
                    return it->second._dimension;
                }
                    
            }
        }
        return -1; //wont get here because we assuming the input is valid
        
    }

    //this function reading from the given file the units and number and fill in the units map
    ifstream& NumberWithUnits::read_units(ifstream& file){

        string line;

        while (getline(file, line))
        {
            int new_line = 0;
            double number = 0;
            string from;
            string to;
            string eq;

            stringstream ss(line);
            ss >> new_line >> from >> eq >> number >> to;

            nu_cell nu;
            nu._from = from;
            nu._to = to;
            nu._number = number;
            nu._dimension = 0;

            map<string, nu_cell>::iterator it;
        
            for (it = _units_map.begin(); it != _units_map.end(); it++)
            {
                if (it->first == from || it->second._to == from || it->first == to || it->second._to == to)
                {
                    nu._dimension = it->second._dimension;
                }
            }
            
            if (nu._dimension == 0) //if its new type - all dimension ==0 in the beggining
            {
                _dim = _dim+1; // new type - new dimension
                nu._dimension = _dim;

            }

            _units_map[from] = nu;

            cout << "from: " << from << " to: " << to;
            cout << "" << endl;
        }
        return file;
    }
    

    //function to search key by value in map
    string key_by_value(string const &value){
        
        map<string, nu_cell>::iterator it;
        for (it = NumberWithUnits::_units_map.begin(); it != NumberWithUnits::_units_map.end(); it++){
            if (it->second._to == value)
            {
                return it->first;
            }
                
        }
        return "";

    }

    //converting the unit=> a + b => a=to , b=from.  respectively the rules we got
    double NumberWithUnits::convert(const NumberWithUnits &to, const NumberWithUnits &from){

        if (NumberWithUnits::_units_map[from._unit_name]._to == to._unit_name)
        {
            return NumberWithUnits::_units_map[from._unit_name]._number;
        }

        if (NumberWithUnits::_units_map[to._unit_name]._to == from._unit_name)
        {
            return (1/(NumberWithUnits::_units_map[to._unit_name]._number));
        }
        
        string src1 = from._unit_name;
        double ans = 1;
        while (src1!=to._unit_name)
        {
            ans = ans*(NumberWithUnits::_units_map[src1]._number);
            src1 = NumberWithUnits::_units_map[src1]._to;

            if (src1.empty())
            {
                break;
            }
            
        }
        if (src1 == to._unit_name)
        {
            return ans;
        }
        ans = 1;
        string src2 = from._unit_name;
        while (src2 != to._unit_name)
        {
            src2 = key_by_value(src2);
            ans = ans/(NumberWithUnits::_units_map[src2]._number);

            if (src2.empty())
            {
                break;
            }
            
        }

        if (src2 == to._unit_name)
        {
            return ans;
        }
        return ans;
        

    }

    //implementation of operator+ friend func
    NumberWithUnits operator+(const NumberWithUnits& n1, const NumberWithUnits &n2){
        
        if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        if (n1._unit_name == n2._unit_name)
        {
            return NumberWithUnits{n1._unit_num+n2._unit_num, n1._unit_name};
        }
        
        double ratio = NumberWithUnits::convert(n1, n2);
        double new_num = n1._unit_num + (ratio*n2._unit_num);

        NumberWithUnits temp(new_num, n1._unit_name);
        return temp;

    }

    //implementation of operator- friend func
    NumberWithUnits operator-(const NumberWithUnits& n1, const NumberWithUnits &n2){
     
        if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }

        if (n1._unit_name == n2._unit_name)
        {
            return NumberWithUnits{n1._unit_num-n2._unit_num, n1._unit_name};
        }
        double ratio = NumberWithUnits::convert(NumberWithUnits(n1._unit_num,n1._unit_name), n2);


        double new_num = n1._unit_num - (ratio*n2._unit_num);

        NumberWithUnits temp(new_num, n1._unit_name);
        return temp;

    }
    
    //implementation of operator<< friend func
    ostream& operator<< (ostream& os, const NumberWithUnits& n) {
        return (os << n._unit_num << "[" << n._unit_name << "]");

    }

    /*
        took this function from erel`s github - https://github.com/erelsgl-at-ariel/cpp-5781/blob/master/04-operator-overloading/1-arithmetic-operators/Complex.cpp
        checks if we get from input the excepted char - in the input we get we expect "[" , " ]" 
    */
    static istream& getAndCheckNextCharIs(istream& input, char expectedChar) {
        char actualChar=0;
        input >> actualChar;
        if (!input){ return input;}

        if (actualChar!=expectedChar) {
            // failbit is for format error
            input.setstate(ios::failbit);}
        return input;
}

    /*
        took part from this function from erel`s github - https://github.com/erelsgl-at-ariel/cpp-5781/blob/master/04-operator-overloading/1-arithmetic-operators/Complex.cpp
        put the input into a NumberWithUnits object 
    */
    istream& operator>> (istream& input, NumberWithUnits& n) {

        double num=0;
        char bracket;
        string name;

        // remember place for rewinding (back to this point)
        ios::pos_type startPosition = input.tellg();

        input >> num;
        input >> bracket;
        bool flag = false;
        if (bracket != '[')
        {
            flag=true;
        }
        input >> name;
        if(name[name.length()-1] == ']'){
            name = name.substr(0,name.length()-1);
        }           
        
        n._unit_dim = NumberWithUnits::checks_dimension(name);
        if (flag == true || n._unit_dim <= 0)
        {
            //if an error ocuured -  rewind the input pointer
            auto errorState = input.rdstate(); // remember error state
            input.clear(); // clear error so seekg will work
            input.seekg(startPosition); // rewind
            input.clear(errorState); // set back the error flag
            throw invalid_argument("not valid");
        }
        
        n._unit_name= name;
        n._unit_num = num;

        return input;

    }

    //multiple double in NumberWithUnits operator implementation
    NumberWithUnits operator*(const double to_mult, const NumberWithUnits &n1){
        NumberWithUnits temp = NumberWithUnits((n1._unit_num)*to_mult, n1._unit_name);
        return temp;
    }
    //multiple double in NumberWithUnits operator implementation
    NumberWithUnits operator*(const NumberWithUnits &n1, const double to_mult){
        NumberWithUnits temp = NumberWithUnits((n1._unit_num)*to_mult, n1._unit_name);
        return temp;
    }

    //implementation of operator== friend func 
    bool operator ==(const NumberWithUnits &n1, const NumberWithUnits &n2){
        
        if (n1._unit_dim != n2._unit_dim)
        {
           
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        
        if ((n1._unit_name) == (n2._unit_name) && abs(n1._unit_num - n2._unit_num) < EPSILON)
        {
          
            return true;
        }
        if ((n1._unit_name) == (n2._unit_name) && abs(n1._unit_num - n2._unit_num) > EPSILON)
        {
            
            return false;
        }


        double ratio = NumberWithUnits::convert(n1, n2);
        double a =abs(n1._unit_num - (n2._unit_num*ratio));
        if (a < EPSILON)
        {
            
            return true;
        }
        
        return false;

    }
    
    //implementation of operator!= friend func
    bool operator!=(const NumberWithUnits& n1, const NumberWithUnits& n2) {

        return !(n1==n2); // using operator == that already has been written 
    }
    
    //implementation of operator< friend func
    bool operator <(const NumberWithUnits& n1, const NumberWithUnits& n2){
        if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num < n2._unit_num)
        {
            return true;
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num > n2._unit_num)
        {
            return false;
        }

        double ratio = NumberWithUnits::convert(n1, n2);
    
        if (n1._unit_num < (n2._unit_num*ratio))
        {
            return true;
        }
        return false;

    }
    
    //implementation of operator> friend func
    bool operator >(const NumberWithUnits& n1, const NumberWithUnits& n2){
       
        if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num > n2._unit_num)
        {
            return true;
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num < n2._unit_num)
        {
            return false;
        }

        double ratio = NumberWithUnits::convert(n1, n2);
    
        if (n1._unit_num > (n2._unit_num*ratio))
        {
            return true;
        }
        return false;

    }

    //implementation of operator<= friend func
    bool operator <=(const NumberWithUnits& n1, const NumberWithUnits& n2){
        if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num <= n2._unit_num )
        {
            return true;
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num > n2._unit_num)
        {
            return false;
        }

        double ratio = NumberWithUnits::convert(n1, n2);
        int a = abs(n1._unit_num - (n2._unit_num*ratio)); 
        if (a < EPSILON || n1._unit_num < n2._unit_num*ratio)
        {
            return true;
        }
        return false;

    }

    //implementation of operator>= friend func
    bool operator >=(const NumberWithUnits& n1, const NumberWithUnits& n2){

       if (n1._unit_dim != n2._unit_dim)
        {
            //units arent in the same dimension
            throw std::logic_error(std::string("Units do not match - [" + n2._unit_name + "] cannot be converted to [" + n1._unit_name+"] "));
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num >= n2._unit_num)
        {
            return true;
        }
        if (n1._unit_name == n2._unit_name && n1._unit_num < n2._unit_num)
        {
            return false;
        }

        double ratio = NumberWithUnits::convert(n1, n2);
        if (n1._unit_num >= (n2._unit_num*ratio))
        {
            return true;
        }
        return false;

    }


};