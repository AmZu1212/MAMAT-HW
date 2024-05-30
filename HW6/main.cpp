#include "input.h"
#include "string.h"
#include <string.h>
#include <iostream>
#include "field.h"
#include "port.h"
#include "ip.h"
using namespace std;

int main(int argc, char** argv) {

	if (check_args(argc, argv)) {
		cout << ("check arg failed(1)\n");
		return 1;
	}

	String *output;
	size_t size;
	String rule(argv[1]);
	rule.split("-=",&output,&size);
	String ip_rule("ip");
	String port_rule("port");

	if (output[1].equals(ip_rule)) {
		Ip rule_ip(rule);
		if (!rule_ip.set_value(rule)) {
			cout << ("ip set value failed\n");
			return 1;
		}
		parse_input(rule_ip);
	}
	if (output[1].equals(port_rule)) {
		Port rule_port(rule);
		if (!rule_port.set_value(rule)) {
			cout << ("port set value failed\n");
			return 1;
		}
		parse_input(rule_port);
	}
	delete[] output;
	//only delete pointer/ "new strings"
	return 0;
}
 