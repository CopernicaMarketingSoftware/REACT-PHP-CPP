CPP			    = g++
RM			    = rm -f
CPPFLAGS		= -Wall -c -I. -O2 -flto -std=c++11 -g
LD			    = g++
LD_FLAGS		= -Wall -shared -O2 
LIB				= react.so
SOURCES			= $(wildcard *.cpp */*.cpp)
OBJECTS			= $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${LIB}

${LIB}: ${OBJECTS}
	${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lev -lcares -lreactcpp -lphpcpp `mysql_config --libs`

clean:
	${RM} *.obj *~* ${OBJECTS} ${LIB}

${OBJECTS}:
	${CPP} ${CPPFLAGS} -fpic -o $@ ${@:%.o=%.cpp}
