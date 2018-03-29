#include "maze.h"
#include <stdio.h>
#include "StackQueue.h"

void MazeInit(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int arr[ROW][COL] = { 
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,0,0},
        {0,1,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };
    int i = 0;
    for(; i < ROW; ++i)
    {
        int j = 0;
        for(; j < COL; ++j)
        {
            maze->map[i][j] = arr[i][j];
        }
    }
}

int CanStay(Maze* maze,Point cur)
{
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)
    {
        return 0;
    }
    if(maze->map[cur.row][cur.col] != 1)
    {
        return 0;
    }return 1;
}

void Mark(Maze* maze,Point cur)
{
    maze->map[cur.row][cur.col] = 2;
}

int IsExit(Point cur,Point entry)
{
    if(cur.row == 0 || cur.row == ROW - 1 || cur.col == 0 || cur.col == COL - 1)
    {
        if(cur.col == entry.col && cur.row == entry.row)
        {
            return 0;
        }
        return 1;
    }
    return 0;
}

void _HasPath(Maze* maze,Point cur,Point entry)
{
    //1.判断当前点是否可以落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //2.标记当前点
    Mark(maze,cur);
    //3.判断当前点是否是出口(边缘点，不是入口点)
    if(IsExit(cur,entry))
    {
        printf("找到了!!!\n");
    }
    //4.按一定顺序判断当前点的四周点(递归)
    Point up;
    up.row = cur.row - 1;
    up.col = cur.col;
    _HasPath(maze,up,entry);

    Point left;
    left.row = cur.row;
    left.col = cur.col - 1;
    _HasPath(maze,left,entry);

    Point down;
    down.row = cur.row + 1;
    down.col = cur.col;
    _HasPath(maze,down,entry);

    Point right;
    right.row = cur.row;
    right.col = cur.col + 1;
    _HasPath(maze,right,entry);

    //5.四周判定完后 返回
    return;
}

void HasPath(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    _HasPath(maze,entry,entry);
}

void HasPathByLoop(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    //1.判定入口是否可以落脚
    if(!CanStay(maze,entry))
    {
        return;
    }
    //2.标记入口点，并将该点入栈
    Mark(maze,entry);
    SeqStack stack;
    SeqStackInit(&stack);
    SeqStackPush(&stack,entry);
    //3.进入循环
    //    a)取栈顶元素
    Point cur;
    while(SeqStackTop(&stack,&cur))
    {
        //    b)判定当前点是不是出口，如果是，就退出
        if(IsExit(cur,entry))
        {
            printf("找到了...\n");
            return;
        }
        //    c)按一定顺序判断当前点的四周点
        //      若可以落脚，则标记，入栈，进入下一次循环
        Point up = cur;
        up.row -= 1;
        if(CanStay(maze,up))
        {
            Mark(maze,up);
            SeqStackPush(&stack,up);
            continue;
        }
        Point left = cur;
        left.col -= 1;
        if(CanStay(maze,left))
        {
            Mark(maze,left);
            SeqStackPush(&stack,left);
            continue;
        }
        Point down = cur;
        down.row += 1;
        if(CanStay(maze,down))
        {
            Mark(maze,down);
            SeqStackPush(&stack,down);
            continue;
        }
        Point right = cur;
        right.col += 1;
        if(CanStay(maze,right))
        {
            Mark(maze,right);
            SeqStackPush(&stack,right);
            continue;
        }
        //    d)若四周都不可以的话，就出栈(回溯)
        SeqStackPop(&stack);
    }
    return;
}

void MazeInitMulExit(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int arr[ROW][COL] = { 
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,0,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };
    int i = 0;
    for(; i < ROW; ++i)
    {
        int j = 0;
        for(; j < COL; ++j)
        {
            maze->map[i][j] = arr[i][j];
        }
    }
}

void _GetShortPath(Maze* maze,Point cur,Point entry,SeqStack* short_path,SeqStack* cur_path)
{
    //1.判定当前点是否可以落脚
    if(!CanStay(maze,cur))
    {
        return;
    }
    //2.标记当前点，把它push到cur_path中
    Mark(maze,cur);
    SeqStackPush(cur_path,cur);
    //3.判定当前点是不是出口 
    if(IsExit(cur,entry))
    {
        //如果是出口
        //a)比较当前cur_path和short_path的长短
        //b)如果cur_path小于short_path(或者short_path为空)，那就用cur_path替换short_path
        if(SeqStackSize(cur_path) < SeqStackSize(short_path) || SeqStackSize(short_path) == 0)
        {
            SeqStackAssign(short_path,cur_path);
        }
        printf("找到了一条当前比较短的路径...\n");
        SeqStackDebugPrint(short_path);
        //c)让 cur_path 出栈，同时返回到上一层栈桢
        SeqStackPop(cur_path);
        return;
    }
    //4.如果当前点不是出口，那就按照一定顺序递归的判定四周的元素(递归)
    Point up = cur;
    up.row -= 1;
    _GetShortPath(maze,up,entry,short_path,cur_path);
    Point right = cur;
    right.col += 1;
    _GetShortPath(maze,right,entry,short_path,cur_path);
    Point down = cur;
    down.row += 1;
    _GetShortPath(maze,down,entry,short_path,cur_path);
    Point left = cur;
    left.col -= 1;
    _GetShortPath(maze,left,entry,short_path,cur_path);
    //5.四周元素都判定完应该回溯到上一个位置，先将cur_path出栈，再return
    SeqStackPop(cur_path);
    return;
}

void GetShrtPath(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    SeqStack short_path;
    SeqStackInit(&short_path);
    SeqStack cur_path;
    SeqStackInit(&cur_path);
    _GetShortPath(maze,entry,entry,&short_path,&cur_path);
    SeqStackDebugPrint(&short_path);
}

void MazeInitHasCycle(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int arr[ROW][COL] = { 
        {0,1,0,0,0,0},
        {0,1,1,1,0,0},
        {0,1,0,1,1,1},
        {1,1,1,1,0,0},
        {0,0,1,0,0,0},
        {0,0,1,0,0,0}
    };
    int i = 0;
    for(; i < ROW; ++i)
    {
        int j = 0;
        for(; j < COL; ++j)
        {
            maze->map[i][j] = arr[i][j];
        }
    }
}

int IsValidPoint(Point cur)
{
    if(cur.row < 0 || cur.row >= ROW || cur.col < 0 || cur.col >= COL)
    {
        return 0;
    }
    return 1;
}

//cur_value 10 pre_value 10 不能走
//cur_value 10 pre_value 9  没有必要走
//cur_value 10 pre_value 8  必须走
//所以 当 cur_value - 1 > pre_value 就必须走
int CanStayWithCycle(Maze* maze,Point cur,Point pre)
{
    //1.当前点在不在地图上
    //2.当前点的值是 1，可以落脚
    if(maze->map[cur.row][cur.col] == 1)
    {
        return 1;
    }
    if(IsValidPoint(cur))
    {
        //3.满足 cur_value - 1 > pre_value
        if(pre.row != -1 && pre.col != -1)
        {
            int pre_value = maze->map[pre.row][pre.col];
            int cur_value = maze->map[cur.row][cur.col];
            if(cur_value - pre_value > 1)
            {
                return 1;
            }

        }
        else
        {
            if(maze->map[cur.row][cur.col] == 1)
            {
                return 1;
            }
        }
    }
    return 0;
}

void MarkWithCycle(Maze* maze,Point pre, Point cur)
{
    if(IsValidPoint(pre) == 1)
    {
        maze->map[cur.row][cur.col] = maze->map[pre.row][pre.col] + 1;
    }
    else if(IsValidPoint(pre) == 0)
    {
        maze->map[cur.row][cur.col] = 2;
    }
}

void _GetShortPathWithCycle(Maze* maze,Point cur,Point pre, Point entry,SeqStack* cur_path,SeqStack* short_path)
{
    //1.判定当前点是否可以落脚(方式变化)
    if(CanStayWithCycle(maze,cur,pre) == 0)
    {
        return;
    }
    //2.如果可以落脚就标记当前点(方式变化),并且入栈
    MarkWithCycle(maze,pre,cur);
    SeqStackPush(cur_path,cur);
    //3.判定是否是出口
    if(IsExit(cur,entry))
    {
        //a) 判定cur_path 和short_path的大小
        //b) 如果cur_path小，就替换short_path
        if(SeqStackSize(cur_path) < SeqStackSize(short_path) || SeqStackSize(short_path) == 0)
        {
            SeqStackAssign(short_path,cur_path);
        }
        printf("找到一条较短的路径...\n");
        SeqStackDebugPrint(short_path);
        //c) 出栈，回溯
        SeqStackPop(cur_path);
        return;
    }
    //4.如果不是出口，递归判定四个方向
    Point up = cur;
    up.row -= 1;
    _GetShortPathWithCycle(maze,up,cur,entry,cur_path,short_path);

    Point right = cur;
    right.col += 1;
    _GetShortPathWithCycle(maze,right,cur,entry,cur_path,short_path);

    Point down = cur;
    down.row += 1;
    _GetShortPathWithCycle(maze,down,cur,entry,cur_path,short_path);

    Point left = cur;
    left.col -= 1;
    _GetShortPathWithCycle(maze,left,cur,entry,cur_path,short_path);
    //5.四个方向都判定完成，出栈，回溯
    SeqStackPop(cur_path);
    return;
}

void GetShortPathWithCycle(Maze* maze,Point entry)
{
    if(maze == NULL)
    {
        return;
    }
    SeqStack short_path;
    SeqStackInit(&short_path);
    SeqStack cur_path;
    SeqStackInit(&cur_path);
    Point pre = {-1,-1};
    _GetShortPathWithCycle(maze,entry,pre,entry,&cur_path,&short_path);
}

////////////////////////////////////////////////////
//测试代码
////////////////////////////////////////////////////

#if 1

#define TEST_HEADER printf("\n----------------%s--------------\n",__FUNCTION__)

void PrintMap(Maze* maze)
{
    if(maze == NULL)
    {
        return;
    }
    int i = 0;
    for(; i < ROW; ++i)
    {
        int j = 0;
        for(; j < COL; ++j)
        {
            printf("%2d ",maze->map[i][j]);
        }
        printf("\n");
    }
}

void Test()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    PrintMap(&maze);
}

void TestHasPath()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry;
    entry.row = 0;
    entry.col = 1;
    HasPath(&maze,entry);
    PrintMap(&maze);
}

void TestHasPathByLoop()
{
    TEST_HEADER;
    Maze maze;
    MazeInit(&maze);
    Point entry;
    entry.row = 0;
    entry.col = 1;
    HasPathByLoop(&maze,entry);
    PrintMap(&maze);
}

void TestMulExit()
{
    TEST_HEADER;
    Maze maze;
    MazeInitMulExit(&maze);
    Point entry = {0,1};
    GetShrtPath(&maze,entry);
    PrintMap(&maze);
}

void TestHasCycleMaze()
{
    TEST_HEADER;
    Maze maze;
    MazeInitHasCycle(&maze);
    Point entry = {0,1};
    GetShortPathWithCycle(&maze,entry);
    PrintMap(&maze);
}

int main()
{
    Test();
    TestHasPath();
    TestHasPathByLoop();
    TestMulExit();
    TestHasCycleMaze();
    return 0;
}
#endif
