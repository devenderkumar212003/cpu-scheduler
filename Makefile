# Makefile for CPU Scheduling Simulator

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SRCS = main.cpp process.cpp scheduler.cpp fcfs_scheduler.cpp sjf_scheduler.cpp \
       rr_scheduler.cpp priority_scheduler.cpp ljf_scheduler.cpp hrrn_scheduler.cpp \
       process_loader.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = cpu_scheduler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean