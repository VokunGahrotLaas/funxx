
O = 2
depth = 10000

CXX ?= g++
CXXFLAGS = -ftemplate-depth=${depth} -Wall -Wextra -Wpedantic -Iinclude -std=c++20 -O$O
LDFLAGS = -O$O

EXEC = tests/main.out

all: ${EXEC}

.PHONY: all clean

%.out: %.cpp
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}

clean:
	${RM} ${EXEC}
