
O = 2
depth = 100000

CXX ?= g++
CXXFLAGS = -MMD -MP -ftemplate-depth=${depth} -Wall -Wextra -Wpedantic -Iinclude -std=c++20 -O$O
LDFLAGS = -O$O

SRC = ${wildcard tests/*.cpp}
DEP = ${SRC:.cpp=.d}
EXEC = ${SRC:.cpp=.out}

all: ${EXEC}

.PHONY: all clean

%.out: %.cpp
	${CXX} ${CXXFLAGS} -o $@ $< ${LDFLAGS}

clean:
	${RM} ${EXEC}

-include ${DEP}
