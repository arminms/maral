#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.135                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

INC = 
CFLAGS =  -std=c++11 -Wall -fexceptions -DNDEBUG
RESINC = 
LIBDIR = 
LIB = 
LDFLAGS = 

INC_DEBUG =  $(INC)
CFLAGS_DEBUG =  $(CFLAGS) -Wall -g
RESINC_DEBUG =  $(RESINC)
RCFLAGS_DEBUG =  $(RCFLAGS)
LIBDIR_DEBUG =  $(LIBDIR)
LIB_DEBUG = $(LIB)
LDFLAGS_DEBUG =  $(LDFLAGS)
OBJDIR_DEBUG = obj/debug
DEP_DEBUG = 
OUT_DEBUG = bin/debug/Maral.so

INC_RELEASE =  $(INC)
CFLAGS_RELEASE =  $(CFLAGS) -O2 -Wall
RESINC_RELEASE =  $(RESINC)
RCFLAGS_RELEASE =  $(RCFLAGS)
LIBDIR_RELEASE =  $(LIBDIR)
LIB_RELEASE = $(LIB)
LDFLAGS_RELEASE =  $(LDFLAGS) -s
OBJDIR_RELEASE = obj/release
DEP_RELEASE = 
OUT_RELEASE = bin/release/Maral.so

INC_DOXYGEN = 
CFLAGS_DOXYGEN = 
RESINC_DOXYGEN = 
RCFLAGS_DOXYGEN =  $(RCFLAGS)
LIBDIR_DOXYGEN = 
LIB_DOXYGEN = $(LIB)
LDFLAGS_DOXYGEN = 
OBJDIR_DOXYGEN = .objs
DEP_DOXYGEN = 

INC_MAKEFILE = 
CFLAGS_MAKEFILE = 
RESINC_MAKEFILE = 
RCFLAGS_MAKEFILE =  $(RCFLAGS)
LIBDIR_MAKEFILE = 
LIB_MAKEFILE = $(LIB)
LDFLAGS_MAKEFILE = 
OBJDIR_MAKEFILE = .objs
DEP_MAKEFILE = 

OBJ_DEBUG = 

OBJ_RELEASE = 

all: debug release doxygen makefile

clean: clean_debug clean_release

before_debug: 
	test -d bin/debug || mkdir -p bin/debug

after_debug: 
	bin/debug/test --result_code=no --report_level=no

debug: before_debug out_debug after_debug

out_debug: $(OBJ_DEBUG) $(DEP_DEBUG)
	$(LD) -shared $(LDFLAGS_DEBUG) $(LIBDIR_DEBUG) $(OBJ_DEBUG) $(LIB_DEBUG) -o $(OUT_DEBUG)

clean_debug: 
	rm -f $(OBJ_DEBUG) $(OUT_DEBUG)
	rm -rf bin/debug

before_release: 
	test -d bin/release || mkdir -p bin/release

after_release: 

release: before_release out_release after_release

out_release: $(OBJ_RELEASE) $(DEP_RELEASE)
	$(LD) -shared $(LDFLAGS_RELEASE) $(LIBDIR_RELEASE) $(OBJ_RELEASE) $(LIB_RELEASE) -o $(OUT_RELEASE)

clean_release: 
	rm -f $(OBJ_RELEASE) $(OUT_RELEASE)
	rm -rf bin/release

before_doxygen: 
	rm -rf doc/html doc/latex
	doxygen Doxyfile

after_doxygen: 

doxygen: before_doxygen after_doxygen

before_makefile: 
	cbp2make --local -in Maral.cbp -out Makefile --wrap-objects --with-deps

after_makefile: 

makefile: before_makefile after_makefile

.PHONY: before_debug after_debug clean_debug before_release after_release clean_release before_doxygen after_doxygen before_makefile after_makefile
