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

Modulo::Modulo(int number, int mod) {
    assert(mod != 0);
    this->mod = mod;
    if(number > 0) {
        this->number = number % mod;
    } else {
        this->number = (number % mod) + mod;
    }
}

Modulo& Modulo::operator+=(const Modulo& rhs) {
    assert(this->mod == rhs.mod);
    number = (number % mod + rhs.number % mod + mod) % mod;
    return *this;
}

Modulo& Modulo::operator*=( const Modulo& rhs) {
    assert(this->mod == rhs.mod);
    this->number = ((this->number % this->mod) * (rhs.number % this->mod) + this->mod) % this->mod;
    return *this;
}

Modulo& Modulo::operator-=(const Modulo& rhs) {
    assert(this->mod == rhs.mod);
    this->number = (this->number % this->mod - rhs.number % this->mod + this->mod) % this->mod;
    return *this;
}

Modulo& Modulo::operator/=(const Modulo& rhs) {
    assert(this->mod == rhs.mod);
    int x, y;
    if(ExtendedEuclid(rhs.number, this->mod, x, y) != 1) {
        throw std::invalid_argument("Divisor and aren't coprime, therefore division can't be made");
    }
    int ModInverse = (x % this->mod + this->mod) % this->mod;
    this->number = (this->number * ModInverse) % this->mod;
    return *this;
}

Modulo operator+(Modulo lhs, const Modulo& rhs) {
    lhs += rhs;
    return lhs;
}

Modulo operator*(Modulo lhs, const Modulo& rhs) {
    lhs *= rhs;
    return lhs;    
}

Modulo operator-(Modulo lhs, const Modulo& rhs) {
    lhs -= rhs;
    return lhs;
}

Modulo operator/(Modulo lhs, const Modulo& rhs) {
    lhs /= rhs;
    return lhs;
}

std::istream& operator>>(std::istream& is, Modulo& m) {
    is >> m.number >> m.mod;
    assert(m.mod != 0);
    if(m.number % m.mod >= 0) {
        m.number %= m.mod;
    } else {
        m.number = m.mod + (m.number % m.mod);
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Modulo& m) {
    os << m.number << " mod " << m.mod;
    return os;
}

void Modulo::SetNumber(int number) {
    if(number >= 0) {
        this->number = number % this->mod;
    } else {
        this->number = (number % this->mod) + this->mod;
    }
}

void Modulo::SetMod(int mod) {
    assert(mod != 0);
    this->mod = mod;
    this->number %= mod;
}

int Modulo::GetNumber() const {
    return number;
}

int Modulo::GetMod() const {
    return mod;
}

bool operator==(const Modulo& lhs, const Modulo& rhs) {
    assert(lhs.mod == rhs.mod);
    return lhs.number == rhs.number;
}

bool operator>(const Modulo& lhs, const Modulo& rhs) {
    assert(lhs.mod == rhs.mod);
    return lhs.number > rhs.number;
}

bool operator<(const Modulo& lhs, const Modulo& rhs) {
    assert(lhs.mod == rhs.mod);
    return lhs.number < rhs.number;
}

Modulo operator"" _mod(const char* str, std::size_t) {
     std::string number, mod;
     int i = 0;
     while(str[i] != '%') {
         number += str[i];
       i++;
     }
     i++;
     while(str[i] != '\0') {
         mod = str[i];
         i++;
     }
     return Modulo(std::stoi(number), std::stoi(mod));
}
