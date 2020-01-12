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

int least_sur_enemy_to_explode(Board board,char color,int i,int j)
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
    return least_ene_to_exlpode;
}

int sur_orb(Board board,char color,int i,int j)
{
    int enemy=0;
    if(i-1>=0)
    {
        if(board.get_cell_color(i-1,j)!=color&&board.get_cell_color(i-1,j)!='w')//if enemy in up row
        {
            enemy+=board.get_orbs_num(i-1,j);
        }
    }
    if(i+1<5)
    {
        if(board.get_cell_color(i+1,j)!=color&&board.get_cell_color(i+1,j)!='w')
        {
            enemy+=board.get_orbs_num(i+1,j);
        }
    }
    if(j-1>=0)
    {
        if(board.get_cell_color(i,j-1)!=color&&board.get_cell_color(i,j-1)!='w')
        {
            enemy+=board.get_orbs_num(i,j-1);
        }
    }
    if(j+1<6)
    {
        if(board.get_cell_color(i,j+1)!=color&&board.get_cell_color(i,j+1)!='w')
        {
            enemy+=board.get_orbs_num(i,j+1);
        }
    }
    return enemy;
}

void need_to_explode(Board tmp_board,char color,int*row,int*col)
{
    int most_sur_enemy=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(tmp_board.get_cell_color(i,j)==color)
            {
                int sur_least=least_sur_enemy_to_explode(tmp_board,color,i,j);
                int cur_to_explode=tmp_board.get_capacity(i,j)-tmp_board.get_orbs_num(i,j);
                if(cur_to_explode==sur_least&&cur_to_explode==1)
                {
                    int cur_sur_enemy=sur_orb(tmp_board,color,i,j);
                    if(cur_sur_enemy>most_sur_enemy)
                    {
                        most_sur_enemy=cur_sur_enemy;
                        *row=i;
                        *col=j;
                    }
                }
            }
        }
    }
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
                int sur_least=least_sur_enemy_to_explode(tmp_board,color,i,j);
                int cur_to_explode=tmp_board.get_capacity(i,j)-tmp_board.get_orbs_num(i,j);
                if(tmp_board.get_orbs_num(i,j)!=1)
                {
                    if(cur_to_explode==sur_least-1)
                    {
                        sc+=6+tmp_board.get_orbs_num(i,j)+sur_orb(tmp_board,color,i,j);
                    }
                    else if(cur_to_explode<sur_least-1)
                        sc+=2;
                }
                else
                {
                    if(tmp_board.get_capacity(i,j)-tmp_board.get_orbs_num(i,j)<least_sur_enemy_to_explode(tmp_board,color,i,j))
                    {
                        if(tmp_board.get_capacity(i,j)==2)
                            sc+=5;
                        else if(tmp_board.get_capacity(i,j)==3)
                            sc+=4;
                        else
                            sc+=3;
                    }
                }
                //if(cur_to_explode==1&&cur_to_explode==sur_least-1)sc+=20;
            }
            if(tmp_board.get_cell_color(i,j)!=color&&tmp_board.get_cell_color(i,j)!='w')
                enemy_orb+=tmp_board.get_orbs_num(i,j);
        }
    }
    sc+=my_orb-enemy_orb;
    return sc;
}

bool iswin(Board tmp_board,char color)
{
    int my_orb=0,enemy_orb=0;
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(tmp_board.get_cell_color(i,j)==color)
                my_orb+=tmp_board.get_orbs_num(i,j);
            else if(tmp_board.get_cell_color(i,j)!=color&&tmp_board.get_cell_color(i,j)!='w')
                enemy_orb+=tmp_board.get_orbs_num(i,j);
        }
    }
    if(enemy_orb==0&&my_orb>1)
        return true;
    else
        return false;
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
    Board tmp_board=board;
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
                if(iswin(tmp_board,color))
                {
                    index[0]=i;
                    index[1]=j;
                    return;
                }
            }
        }
    }
    tmp_board=board;
    need_to_explode(tmp_board,color,&row,&col);
    if(row!=-1&&col!=-1)
    {
        index[0] = row;
        index[1] = col;
        return;
    }
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
