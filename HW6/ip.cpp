#include "ip.h"
#include "field.h"
#include "string.h"


Ip::Ip(String pattern) : Field(pattern) {
    this->ip = 0;
    this->mask= 0;
}

Ip::~Ip() {
}
 
//gets terminal rule
bool Ip::set_value(String val) {

    String* output;
    size_t size;
    val.split("=/", &output, &size);
    if (size == 0) { return false; }
    for (size_t i = 0; i < size; i++) {
        output[i].trim();
    }

    
    if (output[0].equals("src-ip")) {
        this->src = true;
    }

    String current_ip = output[1];
    this->mask = output[2].to_integer();
    
    
    String* numbers;
    size_t nums;
    current_ip.split(".", &numbers, &nums);
    this->ip =
          (numbers[0].to_integer()<<24)
        | (numbers[1].to_integer()<<16)
        | (numbers[2].to_integer()<<8)
        | (numbers[3].to_integer());
    delete[] &current_ip;
    delete[] numbers;
    delete[] output;
    return true;
}

//gets the entire packet
bool Ip::match_value(String packet) const {
    int found = 0;
	String current_ip;
	String* packet_arr;
	size_t size;
	packet.split("=,", &packet_arr, &size);
	if (this->src) {
		for (size_t i = 0; i < size; i++) {
			packet_arr[i].trim();
			if (packet_arr[i].equals("src-ip")) {
				current_ip = packet_arr[i + 1];
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
			if (packet_arr[i].equals("dst-ip")) {
				current_ip = packet_arr[i + 1];
                found++;
				break;
			}
		}
		delete[] packet_arr;//
        if (!found) { return false; }
	}
	

	current_ip.trim();
    String* numbers;
    size_t nums;
    current_ip.split(".", &numbers, &nums);

    int test_ip =
        (numbers[0].to_integer() << 24)
        | (numbers[1].to_integer() << 16)
        | (numbers[2].to_integer() << 8)
        | (numbers[3].to_integer());

    delete[] &current_ip;
    delete[] numbers;
    delete[] packet_arr;//

    int shift = 32 - (this->mask);
    test_ip = test_ip >> shift;
    int passer = (this->ip) >> shift; 


    if (passer == test_ip) {

        return true;
    }
    return false;
}
