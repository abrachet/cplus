TARGET = current_test
WARNING = -Wall -Wshadow --pedantic -Wvla -Werror
# we need to optimize tail calls because apple 
# freaks about a recursive function 
OPTIMIZATIONS = 
GCC = clang++ -std=c++17 -g $(OPTIMIZATIONS) $(WARNING)
DEFINES = -DLAZY -DDEBUG


LEXFUNCDIR = ./Lexer/LexFuncs/
LEXER_SRCS = ./Lexer/lexer.cpp $(LEXFUNCDIR)ObjectHandle.cpp \
			$(LEXFUNCDIR)VariousHandle.cpp $(LEXFUNCDIR)TypeDefHandle.cpp \
			$(LEXFUNCDIR)UserTypeHandle.cpp ./lexer/KnownTypes.cpp

SCANNER_SRCS = ./Scanner/scanner.cpp 

LOGGER_SRCS = ./Logger/Logger.cpp

SRCS = $(LEXER_SRCS) $(SCANNER_SRCS) $(LOGGER_SRCS) main.cpp

OBJS = $(SRCS:%.cpp=%.o)

.cpp.o:
	$(GCC) $(DEFINES) -c $< -o $@

$(TARGET): $(OBJS)
	$(GCC) $(CXXFLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@


VALGRIND = valgrind --tool=memcheck --verbose --log-file=memcheck.txt ./$(TARGET)

testmemory: $(TARGET)
	$(VALGRIND) ./$(TARGET)

test1: $(TARGET)
	./$(TARGET) easy_to_scan.txt

debug: $(TARGET)
	lldb ./$(TARGET) easy_to_scan.txt

clean:
	-rm -f $(OBJS)