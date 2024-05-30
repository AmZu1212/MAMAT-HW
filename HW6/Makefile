CXX=g++
CXXFLAGS=-g -Wall -std=c++11
OBJS=string.o field.o ip.o port.o
EXEC=firewall.exe
LIBS=libfirewall.so libinput.so
RM= $(OBJS) $(EXEC) libfirewall.so main.o

#exe compile&link
firewall.exe: main.o $(LIBS)
	$(CXX) $(CXXFLAGS) main.o -lfirewall -linput -L. -o firewall.exe


#binary file rules
main.o: main.cpp input.h string.h field.h ip.h port.h 
	$(CXX) $(CXXFLAGS) -c -fpic main.cpp
	

libfirewall.so: $(OBJS)
	$(CXX) $(CXXFLAGS) -shared $(OBJS) -o libfirewall.so
	
string.o: string.cpp string.h
	$(CXX) $(CXXFLAGS) -c -fpic string.cpp
	
field.o: field.cpp field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic field.cpp

ip.o: ip.cpp ip.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic ip.cpp

port.o: port.cpp port.h field.h string.h
	$(CXX) $(CXXFLAGS) -c -fpic port.cpp


#cleans directory
clean:
	rm -rf $(RM)



