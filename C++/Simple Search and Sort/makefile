#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 2/15/2015
#   Last Modification Date:       2/15/2015
#   Filename:                     makefile
#
#   Overview:
#       This file instructs the compiler on how to compile a program (lab6).
#	This file can also clean the directory of object files.
#
#   Input:
#       This input consists of a .cpp file an object file.
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

OBJS1 = lab6.o
#OBJS2 =

SRCS1 = lab6.cpp
#SRCS2 =

HEADERS =

all: lab6

lab6: ${OBJS1} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS1} -o lab6

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

.PHONY: clean
clean :
	-rm edit ${OBJS1}
