#include <iostream>

#ifndef SYMMETRICGROUP_H
#define SYMMETRICGROUP_H

class SymmetricGroup {
    friend std::ostream& operator<<(std::ostream&, const SymmetricGroup&);
    friend std::istream& operator>>(std::istream&, SymmetricGroup&);
public:
    SymmetricGroup(const int);
    SymmetricGroup(const SymmetricGroup&);
    SymmetricGroup& operator=(const SymmetricGroup&);
    SymmetricGroup(const int*, const int);
    ~SymmetricGroup();

    int operator[](const int  i) { return m_data[i]; }
    const int operator[](const int i) const { return m_data[i]; }
    int getSize() const { return m_size; }
    bool operator==(const SymmetricGroup&) const;
    SymmetricGroup& operator*=(const SymmetricGroup&);						// composition
    SymmetricGroup& inverse();												// calculate the inverse element
    bool isNeutral() const;
private:
    int* m_data;
    int m_size;
};

bool operator!=(const SymmetricGroup&, const SymmetricGroup&);
SymmetricGroup operator*(SymmetricGroup, const SymmetricGroup&);			// composition
SymmetricGroup pow(SymmetricGroup&, int);			    // the n-th power of element
int ord(const SymmetricGroup&);											    // the order of element
#endif // SYMMETRICGROUP_H