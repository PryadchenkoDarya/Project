#ifndef __Base_H_
#define __Base_H_

#include <string>
#include <iostream>

class Printable {
public:
	virtual ~Printable() {}
	virtual void Print() const = 0;
};

class Named: virtual public Printable {
public:
	explicit Named( std::string iName ) {
		m_name = iName;
	}
	std::string m_name;

	void Print() const {
		std::cout << m_name << std::endl;
	}
};

#endif // __Base_H_
