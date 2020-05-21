#ifndef _MODULO_H_
#define _MODULO_H_


#include <iostream>
#include <cassert>

class Modulo {
    public:
        Modulo() : number(0), mod(0) {}
        Modulo(int number, int mod);
        Modulo& operator+=(const Modulo& rhs);
        Modulo& operator*=(const Modulo& rhs);
        Modulo& operator-=(const Modulo& rhs);
        Modulo& operator/=(const Modulo& rhs);
        friend std::istream& operator>>(std::istream& is, Modulo& mod);
        friend std::ostream& operator<<(std::ostream& os, const Modulo& mod);
        void SetNumber(int number);
        void SetMod(int mod);
        int GetNumber() const;
        int GetMod() const;
        friend bool operator==(const Modulo& lhs, const Modulo& rhs);
        friend bool operator>(const Modulo& lhs, const Modulo& rhs);
        friend bool operator<(const Modulo& lhs, const Modulo& rhs);
    private:
        int number;
        int mod;
};

Modulo operator+(Modulo lhs, const Modulo& rhs);
Modulo operator-(Modulo lhs, const Modulo& rhs);
Modulo operator*(Modulo lhs, const Modulo& rhs);
Modulo operator/(Modulo lhs, const Modulo& rhs);
Modulo operator"" _mod(const char* str, std::size_t);

#endif
