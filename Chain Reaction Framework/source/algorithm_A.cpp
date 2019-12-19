#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions
 * 1. ~ 4. are listed in next block)
 *
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 *
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

int corner[4][2]= {{0,0},{0,5},{4,0},{4,5}};
int edge[14][2]= {{0,1},{0,2},{0,3},{0,4},
    {1,0},{2,0},{3,0},
    {1,5},{2,5},{3,5},
    {4,1},{4,2},{4,3},{4,4}
};
int usual[12][2]= {{1,1},{1,2},{1,3},{1,4},
    {2,1},{2,2},{2,3},{2,4},
    {3,1},{3,2},{3,3},{3,4},
};
int continue_critial=0;
int DFS_search[5][6];
int dangerous_critical;
void DFS(Board tmp_board,char color,int i,int j)
{
    continue_critial++;
    DFS_search[i][j]=1;
    if(i-1>=0)
    {
        if(tmp_board.get_cell_color(i-1,j)==color)
        {
            if(tmp_board.get_capacity(i-1,j)-tmp_board.get_orbs_num(i-1,j)==1&&DFS_search[i-1][j]==0)
            {
                DFS(tmp_board,color,i-1,j);
            }
        }
        else if(tmp_board.get_cell_color(i-1,j)!='w'&&tmp_board.get_cell_color(i-1,j)!=color)
        {
            if(tmp_board.get_capacity(i-1,j)-tmp_board.get_orbs_num(i-1,j)==1)
            {
                dangerous_critical=1;
            }
        }
    }
    if(i+1<5)
    {
        if(tmp_board.get_cell_color(i+1,j)==color)
        {
            if(tmp_board.get_capacity(i+1,j)-tmp_board.get_orbs_num(i+1,j)==1&&DFS_search[i+1][j]==0)
            {
                DFS(tmp_board,color,i+1,j);
            }
        }
        else if(tmp_board.get_cell_color(i+1,j)!='w'&&tmp_board.get_cell_color(i+1,j)!=color)
        {
            if(tmp_board.get_capacity(i+1,j)-tmp_board.get_orbs_num(i+1,j)==1)
            {
                dangerous_critical=1;
            }
        }
    }
    if(j-1>=0)
    {
        if(tmp_board.get_cell_color(i,j-1)==color)
        {
            if(tmp_board.get_capacity(i,j-1)-tmp_board.get_orbs_num(i,j-1)==1&&DFS_search[i][j-1]==0)
            {
                DFS(tmp_board,color,i,j-1);
            }
        }
        else if(tmp_board.get_cell_color(i,j-1)!='w'&&tmp_board.get_cell_color(i,j-1)!=color)
        {
            if(tmp_board.get_capacity(i,j-1)-tmp_board.get_orbs_num(i,j-1)==1)
            {
                dangerous_critical=1;
            }
        }
    }
    if(j+1<6)
    {
        if(tmp_board.get_cell_color(i,j+1)==color)
        {
            if(tmp_board.get_capacity(i,j+1)-tmp_board.get_orbs_num(i,j+1)==1&&DFS_search[i][j+1]==0)
            {
                DFS(tmp_board,color,i,j+1);
            }
        }
        else if(tmp_board.get_cell_color(i,j+1)!='w'&&tmp_board.get_cell_color(i,j+1)!=color)
        {
            if(tmp_board.get_capacity(i,j+1)-tmp_board.get_orbs_num(i,j+1)==1)
            {
                dangerous_critical=1;
            }
        }
    }
}

int find_dangerous_critical(Board tmp_board,char color)
{
    int add=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            DFS_search[i][j]=0;
        }
    }
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(tmp_board.get_capacity(i,j)-tmp_board.get_orbs_num(i,j)==1&&DFS_search[i][j]==0&&tmp_board.get_cell_color(i,j)==color)
            {
                continue_critial=0;
                dangerous_critical=0;
                DFS(tmp_board,color,i,j);
                if(continue_critial>=1)
                {
                    if(dangerous_critical==1)add+=continue_critial;
                }
            }
        }
    }
    return add;
}

int score(Board tmp_board,char color)
{
    int sc=0;
    int my_orb=0,enemy_orb=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(tmp_board.get_cell_color(i,j)==color)
            {
                my_orb+=tmp_board.get_orbs_num(i,j);
                int flag=1;
                int sur_least_to_explode=3;
                int cur_to_explode=tmp_board.get_capacity(i,j)-tmp_board.get_orbs_num(i,j);
                if(i-1>=0)
                {
                    if(tmp_board.get_cell_color(i-1,j)!='w'&&tmp_board.get_cell_color(i-1,j)!=color)
                    {
                        if(tmp_board.get_capacity(i-1,j)-tmp_board.get_orbs_num(i-1,j)<sur_least_to_explode)
                        {
                            sur_least_to_explode=tmp_board.get_capacity(i-1,j)-tmp_board.get_orbs_num(i-1,j);
                        }

                    }
                }
                if(i+1<5)
                {
                    if(tmp_board.get_cell_color(i+1,j)!='w'&&tmp_board.get_cell_color(i+1,j)!=color)
                    {
                        if(tmp_board.get_capacity(i+1,j)-tmp_board.get_orbs_num(i+1,j)<sur_least_to_explode)
                        {
                            sur_least_to_explode=tmp_board.get_capacity(i+1,j)-tmp_board.get_orbs_num(i+1,j);
                        }
                    }
                }
                if(j-1>=0)
                {
                    if(tmp_board.get_cell_color(i,j-1)!='w'&&tmp_board.get_cell_color(i,j-1)!=color)
                    {
                        if(tmp_board.get_capacity(i,j-1)-tmp_board.get_orbs_num(i,j-1)<sur_least_to_explode)
                        {
                            sur_least_to_explode=tmp_board.get_capacity(i,j-1)-tmp_board.get_orbs_num(i,j-1);
                        }
                    }
                }
                if(j+1<6)
                {
                    if(tmp_board.get_cell_color(i,j+1)!='w'&&tmp_board.get_cell_color(i,j+1)!=color)
                    {
                        if(tmp_board.get_capacity(i,j+1)-tmp_board.get_orbs_num(i,j+1)<sur_least_to_explode)
                        {
                            sur_least_to_explode=tmp_board.get_capacity(i,j+1)-tmp_board.get_orbs_num(i,j+1);
                        }
                    }
                }
                if(cur_to_explode>=sur_least_to_explode&&sur_least_to_explode==1)
                    sc=sc-3-tmp_board.get_orbs_num(i,j);
                else if(cur_to_explode>=sur_least_to_explode&&sur_least_to_explode==2)
                    sc=sc-2-tmp_board.get_orbs_num(i,j);
                else if(cur_to_explode>=sur_least_to_explode&&sur_least_to_explode==3)
                    sc=sc-1-tmp_board.get_orbs_num(i,j);
                if(cur_to_explode>=sur_least_to_explode)
                {
                    flag=0;
                }
                if(flag)
                {
                    if(tmp_board.get_capacity(i,j)==2)
                        sc+=3;
                    else if(tmp_board.get_capacity(i,j)==3)
                        sc+=2;
                }

            }
            if(tmp_board.get_cell_color(i,j)!='w'&&tmp_board.get_cell_color(i,j)!=color)
            {
                enemy_orb+=tmp_board.get_orbs_num(i,j);
            }
        }
    }
    sc+=my_orb;
    if(enemy_orb==0&&my_orb>1)
        return 10000;
    if(my_orb==0&&enemy_orb>1)
        return -10000;
    sc=sc-3*find_dangerous_critical(tmp_board,color);
    return sc;
}

void algorithm_A(Board board, Player player, int index[])
{

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.
    int row, col;
    char color = player.get_color();
    Board tmp_board;
    int largest_score=-10000;
    int cur_score;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            tmp_board=board;
            if(tmp_board.get_cell_color(i,j)==color||tmp_board.get_cell_color(i,j)=='w')
            {
                tmp_board.place_orb(i,j,&player);
                cur_score=score(tmp_board,color);
                if(cur_score>largest_score)
                {
                    largest_score=cur_score;
                    row=i;
                    col=j;
                }
            }
        }
    }
    index[0] = row;
    index[1] = col;
}
