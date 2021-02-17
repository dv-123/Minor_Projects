SRCS 		= constant.cpp delay.cpp padd.cpp register.cpp response.cpp \
		  sink.cpp stimulus.cpp add.cpp main.cpp

OBJS 		= $(SRCS:%.cpp=%.o)
DEPS		= $(SRCS:%.cpp=%.d)

SYSTEMC 	= /usr/local

CXX		= g++
CXXFLAGS	= -Wall -g -O0 -Di386 
INCLUDES 	= -I $(SYSTEMC)/include

LD		= $(CXX)
LDFLAGS 	= $(CXXFLAGS)

LIBS		= -L$(SYSTEMC)/lib-linux64 -lsystemc -Wl,-rpath,/usr/local/lib-linux64

PROGRAM 	= add

default:	$(PROGRAM)

$(PROGRAM):	$(OBJS) $(DEPS)
		$(LD) $(LDFLAGS) $(OBJS) $(LIBS) -o ./$@
		
test:		$(PROGRAM)
		./$<
		
clean:; 	rm -rf $(PROGRAM) *.o core* *.d *.vcd *.dump

# Cancel implicit rule
%.o:		%.cpp

%.o:		%.cpp %.d
		$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

%.d: 		%.cpp
		@ echo Making dependencies for $<
		@ g++ -MM $(INCLUDES) $< | sed 's#: # $*.d : #1' > $@

# Include dependency files .d
ifneq ("$(wildcard *.d)","")
  include $(wildcard *.d)
endif
