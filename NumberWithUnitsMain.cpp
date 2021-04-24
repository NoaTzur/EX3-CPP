/**
 * 
 * My Main for showing my exrecise
 * Noa Tzur
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "NumberWithUnits.hpp"
using namespace ariel;


void check_operator1() {
    NumberWithUnits n1(5, "USD");
    NumberWithUnits n2(6.66, "ILS");
    NumberWithUnits n3(6, "km");
    NumberWithUnits n4(4000, "m");
    cout << n1 << " + " << n2 << " = " << n1+n2 << endl; //should print 7 USD
    cout << n3 << " + " << n4 << " = " << n3+n4 << endl; //should print 6.4km
    cout << n2 << " + " << n1 << " = " << n2+n1 << endl; //should print

    try {
        cout << n1 << " + " << n3 << " = " << endl;
        n1+n3; // should print error
    } catch (const std::exception& ex) {
    cout << ex.what() << endl; 
    }
    try {
        cout << n2 << " + " << n4 << " = " << endl;
        n2+n4; // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator2() {
    NumberWithUnits n1(5, "USD");
    NumberWithUnits n2(6.66, "ILS");
    NumberWithUnits n3(6, "km");
    NumberWithUnits n4(400, "cm");
    cout << n1 << " - " << n2 << " = " << n1-n2 << endl; //should print 3 USD
    cout << n3 << " - " << n4 << " = " << n3-n4 << endl; //should print 5.6km
    cout << n2 << " - " << n1 << " = " << n2-n1 << endl; //should print
    try {
        cout << n1 << " - " << n3 << " = " << endl;
        n1-n3; // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
    try {
        cout << n2 << " - " << n4 << " = " << endl;
        n2-n4; // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator3() {
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(6.66, "ILS");
    NumberWithUnits n3(30, "min");
    cout << "60*" << n1 << " = " <<  60*n1 << endl; //should print 3 USD
    //cout << n3*9.4 << endl; //should print 5.6km
    cout << "5.3*" << n2 << " = " << 5.3*n2 << endl; //should print 3 USD
    cout << "7.5*" << n3 << " = " <<  7.5*n3 << endl; //should print 3 USD
    
}

void check_operator4() {
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(5000, "m");
    NumberWithUnits n3(30, "min");
    NumberWithUnits n4(4, "hour");
    cout << n1 << " -= " << n2 <<  " = "; //should print 3 USD
    n1-=n2;
    cout << n1 << endl;

    cout << n4 << " -= " << n3 <<  " = "; //should print 3 USD
    n4-=n3;
    cout << n4 << endl;

    try {
        cout << n3 << " -= " << n1 <<  " = " << endl;
        n3-=n1;  
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator5() {
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(1000, "m");
    NumberWithUnits n3(30, "ton");
    NumberWithUnits n4(4, "kg");
    cout << n1 << " += " << n2 <<  " = "; //should print 3 USD
    n1+=n2;
    cout << n1 << endl;

    cout << n4 << " += " << n3 <<  " = "; //should print 3 USD
    n4+=n3;
    cout << n4 << endl;

    try {
        cout << n3 << " += " << n1 <<  " = " << endl;
        n3+=n1;  
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
    
    try {
        cout << n1 << " += " << n3 <<  " = " << endl;
        n1+=n3;  
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
    
}

void check_operator6(){
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(5000, "m");
    NumberWithUnits n3(300, "min");
    NumberWithUnits n4(5, "hour");
    NumberWithUnits n5(78, "hour");
    cout << n1 << " == " << n2 <<  " is " << (n1==n2) << endl; //should print true
    cout << n4 << " == " << n3 <<  " is " << (n3==n4) << endl; //should print true
    cout << n5 << " == " << n4 <<  " is " << (n4==n5) << endl; // should print false

    try {
        cout << n1 << " == " << n4 <<  endl;
        bool a = (n1==n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }

}

void check_operator7() {
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(5000, "m");
    NumberWithUnits n3(300, "min");
    NumberWithUnits n4(5, "hour");
    NumberWithUnits n5(78, "hour");
    cout << n1 << " != " << n2 <<  " is " << (n1==n2) << endl; //should print false
    cout << n4 << " != " << n3 <<  " is " << (n3==n4) << endl; //should print false
    cout << n5 << " != " << n4 <<  " is " << (n4==n5) << endl; // should print true

    try {
        cout << n1 << " != " << n4 <<  endl;
        bool a = (n1!=n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator8() {
    NumberWithUnits n1(5, "km");
    NumberWithUnits n2(5543, "m");
    NumberWithUnits n3(300, "min");
    NumberWithUnits n4(7, "hour");
    NumberWithUnits n5(78, "hour");
    cout << n1 << " < " << n2 <<  " is " << (n1<n2) << endl; //should print true
    cout << n4 << " < " << n3 <<  " is " << (n4<n3) << endl; //should print false
    cout << n5 << " < " << n4 <<  " is " << (n4<n5) << endl; // should print true

    try {
        cout << n1 << " < " << n4 <<  endl;
        bool a = (n1<n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator9(){
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n2(5543, "ILS");
    NumberWithUnits n3(3, "ton");
    NumberWithUnits n4(5000, "kg");
    cout << n1 << " > " << n2 <<  " is " << (n1>n2) << endl; //should print true
    cout << n3 << " > " << n4 <<  " is " << (n3>n4) << endl; //should print false
    cout << n4 << " > " << n3 <<  " is " << (n4>n3) << endl; // should print true

    try {
        cout << n1 << " > " << n4 <<  endl;
        bool a = (n1>n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
    
}

void check_operator10(){
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n2(5543, "ILS");
    NumberWithUnits n3(3, "hour");
    NumberWithUnits n4(5000, "min");
    cout << n2 << " >= " << n1 <<  " is " << (n2>=n1) << endl; //should print false
    cout << n3 << " >= " << n4 <<  " is " << (n3>=n4) << endl; //should print true
    cout << n4 << " >= " << n3 <<  " is " << (n4>=n3) << endl; // should print true

    try {
        cout << n1 << " >= " << n4 <<  endl;
        bool a = (n1>=n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator11(){
    
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n2(5543, "ILS");
    NumberWithUnits n3(3, "ton");
    NumberWithUnits n4(5000, "g");
    cout << n1 << " <= " << n2 <<  " is " << (n1<=n2) << endl; //should print false
    cout << n3 << " <= " << n4 <<  " is " << (n3<=n4) << endl; //should print false
    cout << n4 << " <= " << n3 <<  " is " << (n4<=n3) << endl; // should print true

    try {
        cout << n1 << " <= " << n4 <<  endl;
        bool a = (n1<=n4); // should print error
    } catch (const std::exception& ex) {
        cout << ex.what() << endl; 
    }
}

void check_operator12(){
    istringstream sample_input1{"193 [ ILS ]"};
    NumberWithUnits n1(500, "USD");
    sample_input1 >> n1;
    cout << n1 << endl;

    istringstream sample_input2{"455 [ ton ]"};
    NumberWithUnits n2(500, "USD");
    sample_input2 >> n2;
    cout << n2 << endl;

}

void check_operator13(){
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n2(5543, "hour");
    
    cout << n1 << "- " << " = " << -n1 << endl;
    cout << n2 << "- " << " = " << -n2 << endl;
}

void check_operator14(){
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n2(5543, "hour");
    
    cout << n1 << "+ " << " = " << +n1 << endl;
    cout << n2 << "+ " << " = " << +n2 << endl;
}

void check_operator15(){
    NumberWithUnits n1(500, "USD");
    NumberWithUnits n3(3, "ton");

    cout << "++" << n1 << " = " << ++n1 << endl;
    cout << "++++++" << n3 << " = " << ++++++n3 << endl;

}

void check_operator16(){
    NumberWithUnits n1(524, "hour");
    NumberWithUnits n3(10, "km");

    cout << "in the same line=> " << "--" << n1 << " = " << --n1 << endl;
    cout << "in the same line=> " << "------" << n3 << " = " << ------n3 << endl;
}

void check_operator17(){
    NumberWithUnits n1(56, "ton");
    NumberWithUnits n3(1342, "cm");

    cout << "in the same line=> " << n1 << "++" << " = " << n1++ << endl;
    cout << n1 << endl;
    cout << "in the same line=> " << n3 << "++" << " = " <<  n3++ << endl;
    cout << n3 << endl;
}

void check_operator18(){
    NumberWithUnits n1(56, "ton");
    NumberWithUnits n3(1342, "cm");

    cout << "in the same line=> " << n1 << "--" << " = " << n1-- << endl;
    cout << n1 << endl;
    cout << "in the same line=> " << n3 << "--" << " = " <<  n3-- << endl;
    cout << n3 << endl;
}

int main() {
  
    ifstream units_file{"units.txt"};
    NumberWithUnits::read_units(units_file);

    cout << "This is my MAIN for exercise 3 PART B" << endl ;
    cout << "Lets get started !! " << endl;
    cout << "" << endl;

    cout << "~~~ checking operator+ ~~~\n" << endl;
    

    check_operator1();
    cout << "" << endl;
    
    cout << "~~~ checking operator- ~~~\n" << endl;

    check_operator2();
    cout << "" << endl;

    cout << "~~~ checking operator* ~~~\n" << endl;

    check_operator3();
    cout << "" << endl;

    cout << "~~~ checking operator-= ~~~\n" << endl;

    check_operator4();
    cout << "" << endl;
    
    cout << "~~~ checking operator+= ~~~\n" << endl;

    check_operator5();
    cout << "" << endl;

    cout << "~~~ checking operator== ~~~\n" << endl;

    check_operator6();
    cout << "" << endl;

    cout << "~~~ checking operator!= ~~~\n" << endl;

    check_operator7();
    cout << "" << endl;

    cout << "~~~ checking operator< ~~~\n" << endl;

    check_operator8();
    cout << "" << endl;

    cout << "~~~ checking operator> ~~~\n" << endl;

    check_operator9();
    cout << "" << endl;

    cout << "~~~ checking operator>= ~~~\n" << endl;

    check_operator10();
    cout << "" << endl;

    cout << "~~~ checking operator<= ~~~\n" << endl;

    check_operator11();
    cout << "" << endl;

    cout << "~~~ checking operator>> ~~~\n" << endl;

    check_operator12();
    cout << "" << endl;

    cout << "~~~ checking operator-(unary) ~~~\n" << endl;

    check_operator13();
    cout << "" << endl;

    cout << "~~~ checking operator+(unary) ~~~\n" << endl;

    check_operator14();
    cout << "" << endl;

    cout << "~~~ checking operator++(prefix)~~~\n" << endl;

    check_operator15();
    cout << "" << endl;

    cout << "~~~ checking operator--(prefix) ~~~\n" << endl;

    check_operator16();
    cout << "" << endl;

    cout << "~~~ checking operator++(postfix) ~~~\n" << endl;

    check_operator17();
    cout << "" << endl;

    cout << "~~~ checking operator--(postfix) ~~~\n" << endl;

    check_operator18();
    cout << "" << endl;


  return 0;
}










