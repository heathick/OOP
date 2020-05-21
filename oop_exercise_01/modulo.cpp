#include <iostream>
#include <cassert>

#include "modulo.hpp"

int ExtendedEuclid(int a, int b, int& x, int& y) {
    if(a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int gcd = ExtendedEuclid(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return gcd;
}

Modulo Modulo::Add(const Modulo& addend) const {
    assert(mod == addend.mod);
    Modulo result;
    result.number = (number % mod + addend.number % mod + mod) % mod;
    result.mod = mod;
    return result;
}

Modulo Modulo::Multiply(const Modulo& multiplier) const {
    assert(mod == multiplier.mod);
    Modulo result;
    result.number = ((number % mod) * (multiplier.number % mod) + mod) % mod;
    result.mod = mod;
    return result;
}

Modulo Modulo::Subtract(const Modulo& subtrahend) const {
    assert(mod == subtrahend.mod);
    Modulo result;
    result.number = (number % mod - subtrahend.number % mod + mod) % mod;
    result.mod = mod;
    return result;
}

Modulo Modulo::Divide(const Modulo& divisor) const {
    assert(mod == divisor.mod);
    int x, y;
    if(ExtendedEuclid(divisor.number, mod, x, y) != 1) {
        std::cerr << "Divisor and aren't coprime, therefore division can't be made" << std::endl;
        return {number, 0};
    }
    Modulo result;
    int ModInverse = (x % mod + mod) % mod;
    result.number = (number * ModInverse) % mod;
    result.mod = mod;
    return result;
}

void Modulo::Read(std::istream& is) {
    is >> number >> mod;
    if(number % mod >= 0) {
        number %= mod;
    } else {
        number = mod + (number % mod);
    }
}

void Modulo::Print(std::ostream& os) const {
    os << number << " mod " << mod << std::endl;
}

void Modulo::SetNumber(int number) {
    this->number = number;
}

void Modulo::SetMod(int mod) {
    this->mod = mod;
}

int Modulo::GetNumber() const {
    return number;
}

int Modulo::GetMod() const {
    return mod;
}

bool Modulo::IsEqual(const Modulo& to_compare) const {
    assert(mod == to_compare.mod);
    return number == to_compare.number;
}

bool Modulo::IsGreater(const Modulo& to_compare) const {
    assert(mod == to_compare.mod);
    return number > to_compare.number;
}

bool Modulo::IsLess(const Modulo& to_compare) const {
    assert(mod == to_compare.mod);
    return number < to_compare.number;
}
