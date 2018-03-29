#pragma once

typedef struct Point{
    int row;
    int col;
}Point;

#define ROW 6
#define COL 6

typedef struct Maze{
    int map[ROW][COL];
}Maze;

void MazeInit(Maze* maze);

void HasPath(Maze* maze,Point entry);

void HasPathiByLoop(Maze* maze,Point entry);

void MazeInitMulExit(Maze* maze);

void GetShrtPath(Maze* maze,Point entry);

void MazeInitHasCycle(Maze* maze);

void GetShortPathWithCycle(Maze* maze,Point entry);
