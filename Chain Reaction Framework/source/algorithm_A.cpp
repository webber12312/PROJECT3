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

void expand(Board board,int*row,int*col)
{
    for(int i=0; i<4; i++)
    {
        if(board.get_cell_color(corner[i][0],corner[i][1])=='w')
        {
            *row=corner[i][0];
            *col=corner[i][1];
            return;
        }
    }
    for(int i=0; i<14; i++)
    {
        if(board.get_cell_color(edge[i][0],edge[i][1])=='w')
        {
            *row=edge[i][0];
            *col=edge[i][1];
            return;
        }
    }
    for(int i=0; i<12; i++)
    {
        if(board.get_cell_color(usual[i][0],usual[i][1])=='w')
        {
            *row=usual[i][0];
            *col=usual[i][1];
            return;
        }
    }
}

void add_orb_up(Board board,char color,int*row,int*col)
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(board.get_cell_color(i,j)==color)
            {
                int least_ene_to_exlpode=10;
                int ene_ready_explode;
                if(i-1>=0)
                {
                    if(board.get_cell_color(i-1,j)!=color&&board.get_cell_color(i-1,j)!='w')//if enemy in up row
                    {
                        ene_ready_explode=board.get_capacity(i-1,j)-board.get_orbs_num(i-1,j);
                        if(ene_ready_explode<least_ene_to_exlpode)
                            least_ene_to_exlpode=ene_ready_explode;
                    }
                }
                if(i+1<5)
                {
                    if(board.get_cell_color(i+1,j)!=color&&board.get_cell_color(i+1,j)!='w')
                    {
                        ene_ready_explode=board.get_capacity(i+1,j)-board.get_orbs_num(i+1,j);
                        if(ene_ready_explode<least_ene_to_exlpode)
                            least_ene_to_exlpode=ene_ready_explode;
                    }
                }
                if(j-1>=0)
                {
                    if(board.get_cell_color(i,j-1)!=color&&board.get_cell_color(i,j-1)!='w')
                    {
                        ene_ready_explode=board.get_capacity(i,j-1)-board.get_orbs_num(i,j-1);
                        if(ene_ready_explode<least_ene_to_exlpode)
                            least_ene_to_exlpode=ene_ready_explode;
                    }
                }
                if(j+1<6)
                {
                    if(board.get_cell_color(i,j+1)!=color&&board.get_cell_color(i,j+1)!='w')
                    {
                        ene_ready_explode=board.get_capacity(i,j+1)-board.get_orbs_num(i,j+1);
                        if(ene_ready_explode<least_ene_to_exlpode)
                            least_ene_to_exlpode=ene_ready_explode;
                    }
                }
                int my_ready_explode=board.get_capacity(i,j)-board.get_orbs_num(i,j);
                if(my_ready_explode==least_ene_to_exlpode)
                {
                    *row=i;
                    *col=j;
                    return;
                }
            }
        }
    }
}

void random(Board board,char color,int*row,int*col)
{
    srand(time(NULL)*time(NULL));
    while(1){
        *row = rand() % 5;
        *col = rand() % 6;
        if(board.get_cell_color(*row, *col) == color || board.get_cell_color(*row, *col) == 'w') break;
    }
}

void algorithm_A(Board board, Player player, int index[])
{

    // cout << board.get_capacity(0, 0) << endl;
    // cout << board.get_orbs_num(0, 0) << endl;
    // cout << board.get_cell_color(0, 0) << endl;
    // board.print_current_board(0, 0, 0);

    //////////// Random Algorithm ////////////
    // Here is the random algorithm for your reference, you can delete or comment it.

    int row=-1, col=-1;
    char color = player.get_color();
    add_orb_up(board,color,&row,&col);
    if(row==-1&&col==-1)
    {
        expand(board,&row,&col);
    }
    if(row==-1&&col==-1)
    {
        random(board,color,&row,&col);
    }

    index[0] = row;
    index[1] = col;
}
