#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 1/17/2015
#   Last Modification Date:       1/17/2015
#   Filename:                     makefile
#
#   Overview:
#       This file instructs the compiler on how to compile 1 program (assignment 1).
#	This file can also clean the directory of object files.
#
#   Input:
#       This input consists of .cpp files, headers, and object files.
#
#   Output:
#       The output of this program will be 1 executable programs.
#
#***************************************************************************************/

CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS1 = assign1.o
#OBJS2 =

SRCS1 = assign1.cpp
#SRCS2 =

#HEADERS =

all: assign1

assign1: ${OBJS1} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS1} -o assign1

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

${OBJS2}: ${SRCS2}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

.PHONY : clean
clean :
	-rm ${OBJS1}
