# Makefile

CXXFLAGS = -O3 -std=c++17

all : fibonacci-tmp fibonacci-rt fibonacci-c++11 fibonacci-c++14 fibonacci-c++17 

%: %.cc
	${CXX} ${CXXFLAGS} -o $@ $< ${LIB}

clean:
	rm -f fibonacci-tmp fibonacci-rt fibonacci-c++11 fibonacci-c++14 fibonacci-c++17 static_if1 static_if2 static_if3

