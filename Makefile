
CXX=g++
INCLUDES=-I include/

INCLUDEDIR=./include/
VPATH=$(INCLUDEDIR)

UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
FLAGS=-D__UNIX_JACK__ -c -g
LIBS=-lasound -lpthread -ljack -lstdc++ -lm \
	-lGL -lGLU -lglut -ldns_sd
endif
ifeq ($(UNAME), Darwin)
FLAGS=-D__MACOSX_CORE__ -c -g
LIBS=-framework CoreAudio -framework CoreMIDI -framework CoreFoundation \
	-framework IOKit -framework Carbon  -framework OpenGL \
	-framework GLUT -framework Foundation \
	-framework AppKit -lstdc++ -lm 
endif

HELLOBJS= mdns.o hello.o

SERVOBJS= mdns.o server.o

CLIENTOBJS = mdns.o client.o

all: hello server client

hello: $(HELLOBJS)
	$(CXX) -o hello $(HELLOBJS) $(LIBS) $(INCLUDE)

server: $(SERVOBJS)
	$(CXX) -o server $(SERVOBJS) $(LIBS) $(INCLUDE)

client: $(CLIENTOBJS)
	$(CXX) -o client $(CLIENTOBJS) $(LIBS) $(INCLUDE)

hello.o: hello.cpp
	$(CXX) $(FLAGS) $(INCLUDES) hello.cpp

server.o: server.cpp
	$(CXX) $(FLAGS) $(INCLUDES) server.cpp

client.o: client.cpp
	$(CXX) $(FLAGS) $(INCLUDES) client.cpp

mdns.o: mdns.h mdns.cpp
	$(CXX) $(FLAGS) $(INCLUDES) $(INCLUDEDIR)mdns.cpp


# OBJS=  RtAudio.o chuck_fft.o Thread.o Stk.o VoxeLib.o voxelMeter.o
# 
# voxelMeter: $(OBJS)
# 	$(CXX) -o voxelMeter $(OBJS) $(LIBS)
# 	
# voxelMeter.o: voxelMeter.cpp RtAudio.h
# 	$(CXX) $(FLAGS) voxelMeter.cpp
# 	
# VoxeLib.o: VoxeLib.h VoxeLib.cpp
# 	$(CXX) $(FLAGS) VoxeLib.cpp
# 
# chuck_fft.o: chuck_fft.h chuck_fft.c
# 	$(CXX) $(FLAGS) chuck_fft.c
# 	
# Thread.o: Thread.h Thread.cpp
# 	$(CXX) $(FLAGS) Thread.cpp
# 	
# Stk.o: Stk.h Stk.cpp
# 	$(CXX) $(FLAGS) Stk.cpp
# 	
# RtAudio.o: RtAudio.h RtAudio.cpp RtError.h
# 	$(CXX) $(FLAGS) RtAudio.cpp

clean:
	rm -f *~ *# *.o hello
	rm -f *~ *# *.o server
	rm -f *~ *# *.o client
