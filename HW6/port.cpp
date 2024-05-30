#include "field.h"
#include "string.h"
#include "port.h"


Port::Port(String pattern) : Field(pattern) {
	this->low = 0;
	this->high = 0;
}

Port::~Port() {}

//gets rule
 bool Port::set_value(String val) {
	 String* output;
	 size_t size;
	 
	 val.split("=-",&output,&size);
	 if (size == 0) { return false; }
	 for (size_t i = 0; i < size; i++) {
		 output[i].trim();
	 }

	 String is_src = output[0];
	 this->low = output[2].to_integer();
	 this->high = output[3].to_integer();
	 delete[] output;

	 if (is_src.equals("src")) {
		 this->src = true;
		 return true;
	 }

	 return true;
}

 bool Port::match_value(String packet) const {
	 int found = 0;
	 int current_port;
	 String* packet_arr;
	 size_t size;
	 packet.split("=,", &packet_arr, &size);
	 if (this->src) {
		 for (size_t i = 0; i < size; i++) {
			 packet_arr[i].trim();
			 if (packet_arr[i].equals("src-port")) {
				 current_port = packet_arr[i + 1].trim().to_integer();
				 found++;
				 break;
			 }
		 }
		 delete[] packet_arr;//
		 if (!found) { return false; }
	 }
	 else {
		 for (size_t i = 0; i < size; i++) {
			 packet_arr[i].trim();
			 if (packet_arr[i].equals("dst-port")) {
				 current_port = packet_arr[i + 1].trim().to_integer();
				 found++;
				 break;
			 }
		 }
		 delete[] packet_arr;//
		 if (!found) { return false; }
	 }
	 
	 if (current_port <= (this->high) &&
		 current_port >= (this->low)) {

		 return true;
	 }
	 else {
	 return false;
	 }
 }