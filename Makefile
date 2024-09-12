CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include

SRCS_PROG = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp INFO198_SO.cpp
SRCS_CONTAR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp contar_palabras.cpp


OBJS_PROG = $(SRCS_PROG:src/%.cpp=obj/%.o)
OBJS_CONTAR = $(SRCS_CONTAR:src/%.cpp=obj/%.o)


TARGET_PROG = prog
TARGET_CONTAR = contar_palabras


all: $(TARGET_PROG) $(TARGET_CONTAR)


$(TARGET_PROG): $(OBJS_PROG)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PROG)


$(TARGET_CONTAR): $(OBJS_CONTAR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_CONTAR)


obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@


clean:
	rm -f obj/*.o $(TARGET_PROG) $(TARGET_CONTAR)

.PHONY: all clean
