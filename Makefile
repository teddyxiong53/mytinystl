SRC_DIR=./

csrc = $(wildcard $(SRC_DIR)/*.c)


ccsrc = $(wildcard $(SRC_DIR)/*.cpp)

obj = $(csrc:.c=.o) $(ccsrc:.cpp=.o)
dep = $(obj:.o=.d)

CXX=g++
CC=gcc
CPP=g++
CFLAGS := -I./include
CXXFLAGS := $(CFLAGS) -std=c++11

LDFLAGS = -lpthread

TARGET = test

$(TARGET): $(obj)
	$(CXX) -o $@ $^ $(LDFLAGS)

-include $(dep)

%.d:%.c
	@$(CPP) $(CFLAGS) $< -MM -MT $(@:.d=.o) >$@

%.d:%.cpp
	@$(CPP) $(CXXFLAGS) $< -MM -MT $(@:.d=.o) >$@


.PHONY: clean cleandep distclean

distclean:clean cleandep

clean:
	rm -f $(obj) $(TARGET)

cleandep:
	rm -rf $(dep)

