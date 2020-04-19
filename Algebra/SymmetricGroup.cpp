#include "SymmetricGroup.h"
#include <iostream>

std::ostream& operator<<(std::ostream& ost, const SymmetricGroup& s) {
    for (int i = 0; i < s.m_size; ++i) {
        std::cout << s.m_data[i] << " ";
    }
    return ost;
}

std::istream& operator>>(std::istream& ist, SymmetricGroup& s) {
    int size = 0;
    ist >> size;
    s.m_size = size;
    delete[] s.m_data;
    s.m_data = new int[s.m_size];
    int obj = 0;
    for (int i = 0; i < s.m_size; ++i) {
        ist >> obj;
        s.m_data[i] = obj;
    }
    return ist;
}

SymmetricGroup::SymmetricGroup(const int n)
    : m_data(0)
    , m_size(n)
{
    m_data = new int[m_size];
    for (int i = 1; i <= n; ++i) {
        m_data[i - 1] = i;
    }
}

SymmetricGroup::SymmetricGroup(const SymmetricGroup& s)
    : m_data(0)
    , m_size(s.m_size)
{
    m_data = new int[m_size];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = s.m_data[i];
    }
}

SymmetricGroup& SymmetricGroup::operator=(const SymmetricGroup& s) {
    if (this != &s) {
        int* tmp = new int[s.m_size];
        for (int i = 0; i < s.m_size; ++i) {
            tmp[i] = s.m_data[i];
        }
        delete[] m_data;
        m_data = tmp;
    }
    return *this;
}

SymmetricGroup::SymmetricGroup(const int* data, const int size)
    : m_data(0)
    , m_size(size)
{
    m_data = new int[size];
    for (int i = 0; i < m_size; ++i) {
        m_data[i] = data[i];
    }
}

SymmetricGroup::~SymmetricGroup() {
    delete[] m_data;
}

bool SymmetricGroup::operator==(const SymmetricGroup& s) const {
    if (m_size == s.m_size) {
        for (int i = 0; i < m_size; ++i) {
            if (s.m_data[i] != m_data[i]) {
                return false;
            }
        }
        return true;
    }
    return false;
}

SymmetricGroup& SymmetricGroup::operator*=(const SymmetricGroup& s) {
    if (m_size == s.m_size) {
        for (int i = 0; i < m_size; ++i) {
            m_data[i] = s.m_data[m_data[i] - 1];
        }
    }
    return *this;
}

SymmetricGroup& SymmetricGroup::inverse() {
    int* tmp = new int[m_size];
    for (int i = 0; i < m_size; ++i) {
        tmp[m_data[i] - 1] = i + 1;
    }
    delete[] m_data;
    m_data = tmp;
    return *this;
}

bool SymmetricGroup::isNeutral() const {
    for (int i = 0; i < m_size; ++i) {
        if (m_data[i] != i + 1) {
            return false;
        }
    }
    return true;
}

bool operator!=(const SymmetricGroup& s1, const SymmetricGroup& s2) {
    return !(s1 == s2);
}

SymmetricGroup operator*(SymmetricGroup s1, const SymmetricGroup& s2) {
    return s1 *= s2;
}

SymmetricGroup pow(SymmetricGroup& s, int n) {
    for (int i = 0; i < n; ++i) {
        s *= s;
    }
    return s;
}

int ord(const SymmetricGroup& s) {
    SymmetricGroup s1 = s;
    int n = 1;
    while (!s1.isNeutral()) {
        s1 *= s;
        ++n;
    }
    return n;
}