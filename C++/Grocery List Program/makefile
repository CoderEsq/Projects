#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 1/30/2015
#   Last Modification Date:       2/1/2015
#   Filename:                     makefile
#
#   Overview:
#       This file instructs the compiler on how to compile a program (assign2).
#	This file can also clean the directory of object files.
#
#   Input:
#       This input consists of .cpp files, headers, and object files.
#
#   Output:
#       The output of this program will be an executable program.
#
#***************************************************************************************/

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS1 = assign2.o item.o
#OBJS2 =

SRCS1 = assign2.cpp item.cpp
#SRCS2 =

HEADERS = item.h

all: assign2

assign2: ${OBJS1} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS1} -o assign2

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

.PHONY: clean
clean :
	-rm edit ${OBJS1}
