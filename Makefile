# Makefile for libutils
# Copyright (C) 2014 Sergey Kolevatov

###################################################################

VER := 0

MODE ?= debug

###################################################################

BOOST_PATH := $(shell echo $$BOOST_PATH)

ifeq (,$(BOOST_PATH))
    $(error 'please define path to boost $$BOOST_PATH')
endif

###################################################################

BOOST_LIB_SYSTEM := libboost-system.a
BOOST_LIB_THREAD := libboost-thread.a


BOOST_INC=$(BOOST_PATH)/include
BOOST_LIB=$(BOOST_PATH)/lib

###################################################################

LIBNAME=libutils

###################################################################

ifeq "$(MODE)" "debug"
    OBJDIR=./DBG
    BINDIR=./DBG

    CFLAGS := -Wall -std=c++0x -ggdb -g3
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm -g
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -g -L. $(BINDIR)/$(LIBNAME).a -lm

    TARGET=example
else
    OBJDIR=./OPT
    BINDIR=./OPT

    CFLAGS := -Wall -std=c++0x
    LFLAGS := -Wall -lstdc++ -lrt -ldl -lm
#    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. $(BINDIR)/$(LIBNAME).a $(BINDIR)/libutils.a -lm
    LFLAGS_TEST := -Wall -lstdc++ -lrt -ldl -L. $(BINDIR)/$(LIBNAME).a -lm

    TARGET=example
endif

###################################################################

WARN = -W -Wall -Wshadow -Wreturn-type -Wcomment -Wtrigraphs -Wformat -Wparentheses -Wpointer-arith -Wuninitialized -O
CDBG = -g $(CWARN) -fno-inline

###################################################################

CC=gcc

LDSHARED=gcc
CPP=gcc -E
INCL = -I$(BOOST_INC)


STATICLIB=$(LIBNAME).a
SHAREDLIB=
SHAREDLIBV=
SHAREDLIBM=
LIBS=$(STATICLIB) $(SHAREDLIBV)

AR=ar rc
RANLIB=ranlib
LDCONFIG=ldconfig
LDSHAREDLIBC=-lc
TAR=tar
SHELL=/bin/sh
EXE=

#vpath %.cpp .

SRCC = dummy_logger.cpp sprintf.cpp number_format.cpp vformat.cpp gen_random_string.cpp HTTPDownloader.cpp \
		remove_extra_spaces.cpp \
		tune_wav.cpp
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRCC))

TYPES_H = types.h

all: static

static: $(TARGET)

check: test

test: all teststatic

teststatic: static
	@echo static test is not ready yet, dc10

$(BINDIR)/$(STATICLIB): $(OBJS)
	$(AR) $@ $(OBJS)
	-@ ($(RANLIB) $@ || true) >/dev/null 2>&1

$(OBJDIR)/%.o: %.cpp
	@echo compiling $<
	$(CC) $(CFLAGS) $(CDBG) -DPIC -c -o $@ $< $(INCL)

$(TYPES_H):
	@echo "generating $(TYPES_H)"
	$(CC) generate_types_h.c -o $(OBJDIR)/generate_types_h
	$(OBJDIR)/generate_types_h > $(TYPES_H)

$(TARGET): $(BINDIR) $(BINDIR)/$(TARGET)
	ln -sf $(BINDIR)/$(TARGET) $(TARGET)
	@echo "$@ uptodate - ${MODE}"

$(BINDIR)/$(TARGET): $(TYPES_H) $(OBJDIR)/$(TARGET).o $(OBJS) $(BINDIR)/$(STATICLIB)
	$(CC) $(CFLAGS) $(CDBG) -o $@ $(OBJDIR)/$(TARGET).o $(LFLAGS_TEST)
	
$(BINDIR):
	mkdir -p $(OBJDIR)
	mkdir -p $(BINDIR)

clean:
	#rm $(OBJDIR)/*.o *~ $(TARGET)
	- rm $(OBJDIR)/*.o $(TARGET) $(BINDIR)/$(TARGET) $(BINDIR)/$(STATICLIB)
	- rm $(OBJDIR)/generate_types_h
	- rm $(TYPES_H)
