#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 3/15/2015
#   Last Modification Date:       3/15/2015
#   Filename:                     makefile
#
#   Overview:
#       This file instructs the compiler on how to compile a program (final).
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
CXXFLAGS += -foptimize-sibling-calls
#CXXFLAGS += -O3
LDFLAGS = -lboost_date_time

OBJS1 = final.o Room.o Quarter.o Rock.o Dice.o Player.o
#OBJS2 =

SRCS1 = final.cpp Room.cpp Quarter.cpp Rock.cpp Dice.cpp Player.cpp
#SRCS2 =

HEADERS = Room.h Quarter.h Rock.h Dice.h Player.h

all: final

final: ${OBJS1} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS1} -o final

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

.PHONY: clean
clean :
	rm -f ${PROGS} *.o *~
