// DFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Stack.h"

static bool checkSurrounding(Maze m,Stack s,bool **visted,Cell **predecessor,Cell v);
static bool isCellEqual(Cell c1,Cell c2);
static void markPath(Maze m,Cell **predecessor,Cell end);

bool solve(Maze m) {
    if(MazeVisit(m,MazeGetStart(m))){
        return true;
    }
    bool **visted = createBoolMatrix(MazeHeight(m),MazeWidth(m));
    Cell **predecessor = createCellMatrix(MazeHeight(m),MazeWidth(m));
    Stack stack = StackNew();
    StackPush(stack,MazeGetStart(m));
    bool solved = false;
    while(!StackIsEmpty(stack)){
        Cell v = StackPop(stack);
        visted[v.row][v.col] = true;
        if(checkSurrounding(m,stack,visted,predecessor,v)){
            solved = true;
            break;
        }

    }
    freeBoolMatrix(visted);
    freeCellMatrix(predecessor);
    StackFree(stack);
    return solved;
}


/*
add all the surrounding path around v to the stack
and update the visted and predecessor matrix
return true if the exit is reached.
If exit is reached call MazeMarkPath() to mark the path to the exit.
*/
static bool checkSurrounding(Maze m,Stack s,bool **visted,Cell **predecessor,Cell v){
    //check the downwards
    Cell down;
    down.row = v.row + 1;
    down.col = v.col;
    if(down.row < MazeHeight(m) && !visted[down.row][down.col] && ! MazeIsWall(m,down)){
        StackPush(s,down);
        predecessor[down.row][down.col] = v;
        if(MazeVisit(m,down)){
            markPath(m,predecessor,down);
            return true;
        }
    }
    // check right
    Cell right;
    right.row = v.row;
    right.col = v.col + 1;
    if(right.col < MazeWidth(m) && !visted[right.row][right.col] && ! MazeIsWall(m,right)){
        StackPush(s,right);
        predecessor[right.row][right.col] = v;
        if(MazeVisit(m,right)){
            markPath(m,predecessor,right);
            return true;
        }
    }

    //check upwards
    Cell up;
    up.row = v.row - 1;
    up.col = v.col;
    if(up.row >= 0 && !visted[up.row][up.col] && !MazeIsWall(m,up)){
        StackPush(s,up);
        predecessor[up.row][up.col] = v;
        if(MazeVisit(m,up)){
            markPath(m,predecessor,up);
            return true;
        }
    }
    //check left
    Cell left;
    left.row = v.row;
    left.col = v.col -1;
    if(left.col >= 0 && !visted[left.row][left.col] && !MazeIsWall(m,left)){
        StackPush(s,left);
        predecessor[left.row][left.col] = v;
        if(MazeVisit(m,left)){
            markPath(m,predecessor,left);
            return true;
        }
    }
    return false;
}

static void markPath(Maze m,Cell **predecessor,Cell end){
    int row = end.row;
    int col = end.col;
    MazeMarkPath(m,end);
    while(!isCellEqual(predecessor[row][col],MazeGetStart(m))){
        MazeMarkPath(m,predecessor[row][col]);
        int temp = predecessor[row][col].row;
        col = predecessor[row][col].col;
        row = temp;
    }
    MazeMarkPath(m,MazeGetStart(m));
}

static bool isCellEqual(Cell c1,Cell c2){
    return (c1.row == c2.row && c1.col == c2.col);
}

