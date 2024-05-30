#ifndef PORT_H
#define PORT_H


#include "field.h"
#include "string.h"

class Port : public Field {
	int low;
	int high;
	bool src = false;
protected:
	bool match_value(String value) const;
public:
	Port(String pattern);
	~Port();
	bool set_value(String val);
};
#endif