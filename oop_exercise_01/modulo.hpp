#ifndef _MODULO_H_
#define _MODULO_H_


#include <iostream>


class Modulo {
    public:
        Modulo() : number(0), mod(0) {}
        Modulo(int number, int mod) : number(number < 0 ? mod + (number % mod) : number % mod), mod(mod) {}
        Modulo Add(const Modulo& addend) const;
        Modulo Multiply(const Modulo& multiplier) const;
        Modulo Subtract(const Modulo& subtracthend) const;
        Modulo Divide(const Modulo& divisor) const;
        void Read(std::istream& is);
        void Print(std::ostream& os) const;
        void SetNumber(int number);
        void SetMod(int mod);
        int GetNumber() const;
        int GetMod() const;
        bool IsEqual(const Modulo& to_compare) const;
        bool IsGreater(const Modulo& to_compare) const;
        bool IsLess(const Modulo& to_compare) const;
    private:
        int number;
        int mod;
};

#endif
