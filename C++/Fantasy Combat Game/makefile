#****************************************************************************************
#   Author:                       Alex Samuel
#   Date Created:                 2/15/2015
#   Last Modification Date:       2/15/2015
#   Filename:                     makefile
#
#   Overview:
#       This file instructs the compiler on how to compile a program (assign3).
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

OBJS1 = assign3.o Barbarian.o BlueMen.o Creature.o Goblin.o ReptilePeople.o TheShadow.o
#OBJS2 =

SRCS1 = assign3.cpp Barbarian.cpp BlueMen.cpp Creature.cpp Goblin.cpp ReptilePeople.cpp TheShadow.cpp
#SRCS2 =

HEADERS = Barbarian.h BlueMen.h Creature.h Goblin.h ReptilePeople.h TheShadow.h

all: assign3

assign3: ${OBJS1} ${HEADERS}
	${CXX} ${LDFLAGS} ${OBJS1} -o assign3

${OBJS1}: ${SRCS1}
	${CXX} ${CXXFLAGS} -c $(@:.o=.cpp)

.PHONY: clean
clean :
	-rm edit ${OBJS1}
