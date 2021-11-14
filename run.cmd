@echo off
g++ src/Sources/main.cpp -o bin/snake.exe -I include -I src/Headers -L lib -lsfml-graphics -lsfml-window -lsfml-system
echo Your game has been build.
pause