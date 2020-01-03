src = $(wildcard ./*.cpp)
hed = $(wildcard ./*.h)
notsrc = $(notdir $(src))
nothed = $(notdir $(hed))
bassrc = $(basename $(notsrc))

act = -Wall -g -lpthread -std=c++11

#obj = $(patsubst %.cpp, $(bassrc), $(notsrc))

#all:$(obj)

client:$(notsrc)
	g++ $^ -o $@ $(act)
