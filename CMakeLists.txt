project(my_compiler)

set(CMAKE_CXX_STANDARD 11)

add_executable(my_compiler main.cpp alphabet.cpp alphabet.h tokenlizer.h tokenlizer.cpp expression_analyzer.h expression_analyzer.cpp expression_calculator.cpp expression_calculator.h)