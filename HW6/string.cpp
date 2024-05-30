#include "string.h"
#include <string.h>



//
String::String() {

	this->data = new char[2];
	strcpy(this->data , "");
	this->length = 1;
}
//
String::String(const String& str) {
	
	this->data = strcpy(new char[strlen(str.data) + 1], str.data);
	this->length = str.length;
}
//
String::String(const char* str) {

	this->data = strcpy(new char[strlen(str) + 1], str);
	this->length = strlen(str);
}
//
String::~String() {
	delete[] this->data;
}

//=======================================================
//
String& String::operator=(const String& str) {
	if (this == &str) {
		return *this;
	}
	delete[] this->data;
	this->data = strcpy(new char[strlen(str.data)+1],str.data);
	length = str.length;
	return *this;
}
//
String& String::operator=(const char* str) {
	if (!strcmp(this->data,str)) {
		return *this;
	}
	delete[] this->data;
	this->data = strcpy(new char[strlen(str) + 1], str);
	length = strlen(str);
	return *this;
}
//
bool String::equals(const String& rhs) const {
	if (!strcmp(rhs.data, this->data)) {
		return true;
	}

	return false;
}
//
bool String::equals(const char* rhs) const {
	if (!strcmp(rhs, this->data)) {
		return true;
	}

	return false;
}
//
void String::split(const char* delimiters, String** output, size_t* size) const {
	size_t count = 0, offset = 0, h = 0;
	size_t output_size = 0;
	for (size_t j = 0; j < strlen(this->data); j++) {
		for (size_t i = 0; i < strlen(delimiters); i++) {
			if ((this->data)[j] == delimiters[i]) {
				output_size++;
			}
		}
	}
	if(output_size==0){return;}
	if(output==NULL) {return;}
	*output = new String[output_size];

	for (size_t j = 0; j < strlen(this->data); j++) {
		for (size_t i = 0; i < strlen(delimiters); i++) {
			if ((this->data)[j] == delimiters[i]) {
				size_t len = 0;
				char* temp = new char[1+j-offset];
				for ( h = offset; h < j; h++) {
					temp[len] = (this->data)[h];
					len++;
				}
				String* str = new String(temp);
				str->length = len;
				output[count] = str;
				count++;
				offset = j+1;
				delete[] temp;
				delete(str);
			}
		}
	}
	*size = /*(size_t*)*/count;

	if (!count) {output[0] = NULL;}
}
//
int String::to_integer() const {
	return atoi(this->data);
}
//
String String::trim() const {
	int size = this->length, start = 0, end = size,j=0;
	while (start < size && this->data[start] == ' ')
		start++;
	while (end > 0 && this->data[end] == ' ')
		end--;
	char* temp = new char[2+end-start];
	for (int i = start; i < end; i++) {
		temp[j] = this->data[i];
		j++;
	}
	String* str = new String(temp);
	str->length = 1 + end - start;
	delete[] temp;
	return *str;
}

