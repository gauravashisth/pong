# PONG

A 2-Dimensional video game that stimulates table tennis.

## Command to run the program:

1. cmake -B build -S . -DCMAKE_EXPORT_COMPILE_COMMANDS=YES?
2. ln -s build/compile_commands.json .

- (not necessary)

3. cmake -B build -S .
4. cmake --build build
5. ./build/pong
