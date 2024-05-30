#ifndef IP_H
#define IP_H

#include "string.h"
#include "field.h"

class Ip: public Field {
	int ip;
	int mask;
	bool src = false;
protected:
	bool match_value(String val) const;
public:
	Ip(String pattern);
	~Ip();
	bool set_value(String val);
};
#endif