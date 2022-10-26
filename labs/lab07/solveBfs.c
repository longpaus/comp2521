// BFS maze solver

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Cell.h"
#include "matrix.h"
#include "Maze.h"
#include "Queue.h"

static bool checkSurrounding(Maze m,Queue q,bool **visted,Cell **predecessor,Cell v);
static bool isCellEqual(Cell c1,Cell c2);
static void markPath(Maze m,Cell **predecessor,Cell end);

bool solve(Maze m) {
    bool **visted = createBoolMatrix(MazeHeight(m),MazeWidth(m));
    Cell **predecessor = createCellMatrix(MazeHeight(m),MazeWidth(m));
    Queue queue = QueueNew();
    QueueEnqueue(queue,MazeGetStart(m));
    if(MazeVisit(m,MazeGetStart(m))){
        return true;
    }
    while(!QueueIsEmpty(queue)){
        Cell v = QueueDequeue(queue);
        if(visted[v.row][v.col]){
            continue;
        }
        visted[v.row][v.col] = true;
        if(checkSurrounding(m,queue,visted,predecessor,v)){
            return true;
        }
        
    }
    freeBoolMatrix(visted);
    freeCellMatrix(predecessor);
    QueueFree(queue);
    return false;
}
/*
add all the surrounding path around v to the queue
and update the visted and predecessor matrix
return true if the exit is reached.
If exit is reached call MazeMarkPath() to mark the path to the exit.
*/
static bool checkSurrounding(Maze m,Queue q,bool **visted,Cell **predecessor,Cell v){
    //check the downwards
    Cell down;
    down.row = v.row + 1;
    down.col = v.col;
    if(down.row < MazeHeight(m) && !visted[down.row][down.col] && ! MazeIsWall(m,down)){
        QueueEnqueue(q,down);
        predecessor[down.row][down.col] = v;
        if(MazeVisit(m,down)){
            markPath(m,predecessor,down);
            return true;
        }
    }
    //check upwards
    Cell up;
    up.row = v.row - 1;
    up.col = v.col;
    if(up.row >= 0 && !visted[up.row][up.col] && !MazeIsWall(m,up)){
        QueueEnqueue(q,up);
        predecessor[up.row][up.col] = v;
        if(MazeVisit(m,up)){
            markPath(m,predecessor,up);
            return true;
        }
    }
     // check right
    Cell right;
    right.row = v.row;
    right.col = v.col + 1;
    if(right.col < MazeWidth(m) && !visted[right.row][right.col] && ! MazeIsWall(m,right)){
        QueueEnqueue(q,right);
        predecessor[right.row][right.col] = v;
        if(MazeVisit(m,right)){
            markPath(m,predecessor,right);
            return true;
        }
    }
    return false;
    //check left
    Cell left;
    left.row = v.row;
    left.col = v.col -1;
    if(left.col >= 0 && !visted[left.row][left.col] && !MazeIsWall(m,left)){
        QueueEnqueue(q,left);
        predecessor[left.row][left.col] = v;
        if(MazeVisit(m,left)){
            markPath(m,predecessor,left);
            return true;
        }
    }
   
}

static void markPath(Maze m,Cell **predecessor,Cell end){
    int row = end.row;
    int col = end.col;
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