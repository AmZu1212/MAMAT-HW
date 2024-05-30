#include "field.h"
#include "string.h"

Field::Field(String pattern) {
	this->pattern=pattern;
}

Field::~Field(){}

bool Field::match(String packet) {
	return this->match_value(packet);
}
