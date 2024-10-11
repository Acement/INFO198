CXX = g++
CXXFLAGS = -Wall -std=c++17 -I./include

SRCS_PROG = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp INFO198_SO.cpp src/thread_operation.cpp src/env_setter.cpp 
SRCS_CONTAR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp contar_palabras.cpp
SRCS_PARALLEL = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/thread_operation.cpp src/env_setter.cpp contar_paralelo.cpp
SRCS_INVERTIR = src/file_operation.cpp src/func_cont.cpp src/func_math.cpp src/func_string.cpp src/user_operation.cpp src/invertido.cpp src/env_setter.cpp invertir_indice.cpp

OBJS_PROG = $(SRCS_PROG:src/%.cpp=obj/%.o)
OBJS_CONTAR = $(SRCS_CONTAR:src/%.cpp=obj/%.o)
OBJS_PARALLEL = $(SRCS_PARALLEL:src/%.cpp=obj/%.o)
OBJS_INVERTIR = $(SRCS_INVERTIR:src/%.cpp=obj/%.o)

TARGET_PROG = prog
TARGET_CONTAR = contar_palabras
TARGET_PARALLELO = contar_paralelo
TARGET_INVERTIR = invertir_indice

all: $(TARGET_PROG) $(TARGET_CONTAR) $(TARGET_PARALLELO) $(TARGET_INVERTIR)

$(TARGET_PROG): $(OBJS_PROG)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PROG)

$(TARGET_CONTAR): $(OBJS_CONTAR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_CONTAR)

$(TARGET_PARALLELO): $(OBJS_PARALLEL)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_PARALLEL)

$(TARGET_INVERTIR): $(OBJS_INVERTIR)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS_INVERTIR)

obj/%.o: src/%.cpp
	@mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f obj/*.o $(TARGET_PROG) $(TARGET_CONTAR) $(TARGET_PARALLELO) $(TARGET_INVERTIR)

.PHONY: all clean
