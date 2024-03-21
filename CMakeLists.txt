cmake_minimum_required(VERSION 3.0)
project(X11Examples)

# C言語のプログラム用のビルド設定
add_executable(example_c src/example.c)
target_link_libraries(example_c X11)

# C++のプログラム用のビルド設定
add_executable(example_cpp src/example.cpp)
target_link_libraries(example_cpp X11)
