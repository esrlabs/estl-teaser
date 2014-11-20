
CPP=g++
CPPFLAGS=-Iinclude
AR=ar

LIBNAME=estd.a

SRC_DIR=src/estd
LIB_SRCS=$(SRC_DIR)/assert.cpp

LIB_OBJS=$(LIB_SRCS:.cpp=.obj)

EXAMPLE_DIR=examples/estd

EXAMPLES=vector1.exe vector2.exe vector3.exe

all: lib examples

lib: $(LIB_OBJS)
	$(AR) rvu $(LIBNAME) $(LIB_OBJS)

examples: lib $(EXAMPLES)

clean:
	rm -f $(EXAMPLES) $(LIBNAME) $(LIB_OBJS)

$(SRC_DIR)/%.obj: $(SRC_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

%.exe: $(EXAMPLE_DIR)/%.cpp
	$(CPP) $(CPPFLAGS) $< -o $@ $(LIBNAME)

