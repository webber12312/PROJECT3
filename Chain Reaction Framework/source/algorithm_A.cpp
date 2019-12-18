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
int one_step_to_explode[30][2];
int two_step_to_explode[30][2];
int three_step_to_explode[30][2];
int continue_critial=0;
int DFS_search[5][6];

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

void expand(Board board,char color,int*row,int*col)
{
    for(int i=0; i<4; i++)
    {
        if(board.get_cell_color(corner[i][0],corner[i][1])=='w')
        {
            int my_ready_explode=board.get_capacity(corner[i][0],corner[i][1])-board.get_orbs_num(corner[i][0],corner[i][1]);
            if(my_ready_explode<=least_sur_enemy_to_explode(board,color,corner[i][0],corner[i][1]))
            {
                *row=corner[i][0];
                *col=corner[i][1];
                return;
            }
        }
    }
    for(int i=0; i<14; i++)
    {
        if(board.get_cell_color(edge[i][0],edge[i][1])=='w')
        {
            int my_ready_explode=board.get_capacity(edge[i][0],edge[i][1])-board.get_orbs_num(edge[i][0],edge[i][1]);
            if(my_ready_explode<=least_sur_enemy_to_explode(board,color,edge[i][0],edge[i][1]))
            {
                *row=edge[i][0];
                *col=edge[i][1];
                return;
            }
        }
    }
    for(int i=0; i<12; i++)
    {
        if(board.get_cell_color(usual[i][0],usual[i][1])=='w')
        {
            int my_ready_explode=board.get_capacity(usual[i][0],usual[i][1])-board.get_orbs_num(usual[i][0],usual[i][1]);
            if(my_ready_explode<=least_sur_enemy_to_explode(board,color,usual[i][0],usual[i][1]))
            {
                *row=usual[i][0];
                *col=usual[i][1];
                return;
            }
        }
    }
}

void add_orb_up(Board board,char color,int*row,int*col,int record1,int record2,int record3)
{
    for(int r=0; r<record1; r++)
    {
        int i=one_step_to_explode[r][0];
        int j=one_step_to_explode[r][1];
        int my_ready_explode=board.get_capacity(i,j)-board.get_orbs_num(i,j);
        if(my_ready_explode==least_sur_enemy_to_explode(board,color,i,j))
        {
            *row=i;
            *col=j;
            return;
        }

    }
    for(int r=0; r<record2; r++)
    {
        int i=two_step_to_explode[r][0];
        int j=two_step_to_explode[r][1];
        int my_ready_explode=board.get_capacity(i,j)-board.get_orbs_num(i,j);
        if(my_ready_explode==least_sur_enemy_to_explode(board,color,i,j))
        {
            *row=i;
            *col=j;
            return;
        }

    }
    for(int r=0; r<record3; r++)
    {
        int i=three_step_to_explode[r][0];
        int j=three_step_to_explode[r][1];
        int my_ready_explode=board.get_capacity(i,j)-board.get_orbs_num(i,j);
        if(my_ready_explode==least_sur_enemy_to_explode(board,color,i,j))
        {
            *row=i;
            *col=j;
            return;
        }

    }
}


void random(Board board,char color,int*row,int*col)
{
    /*****************************/
    //srand(time(NULL)*time(NULL));
    /*****************************/
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(board.get_cell_color(i,j)==color)
            {
                int my_ready_explode=board.get_capacity(i,j)-board.get_orbs_num(i,j);
                if(my_ready_explode<least_sur_enemy_to_explode(board,color,i,j))
                {
                    *row=i;
                    *col=j;
                    return;
                }

            }
        }
    }
    while(1)
    {
        *row = rand() % 5;
        *col = rand() % 6;
        if(board.get_cell_color(*row, *col) == color || board.get_cell_color(*row, *col) == 'w')
            break;
    }
}

void record_step_to_explode(Board board,char color,int*record_1,int*record_2,int*record_3)
{
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<6; j++)
        {
            if(board.get_cell_color(i,j)==color)
            {
                if(board.get_capacity(i,j)-board.get_orbs_num(i,j)==1)
                {
                    one_step_to_explode[*record_1][0]=i;
                    one_step_to_explode[*record_1][1]=j;
                    (*record_1)++;
                }
                else if(board.get_capacity(i,j)-board.get_orbs_num(i,j)==2)
                {
                    two_step_to_explode[*record_2][0]=i;
                    two_step_to_explode[*record_2][1]=j;
                    (*record_2)++;
                }
                else if(board.get_capacity(i,j)-board.get_orbs_num(i,j)==3)
                {
                    three_step_to_explode[*record_3][0]=i;
                    three_step_to_explode[*record_3][1]=j;
                    (*record_3)++;
                }
            }
        }
    }
}

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
    }
}

int find_critiacal(Board tmp_board,char color)
{
    int add=0;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<6;j++)
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
                DFS(tmp_board,color,i,j);
                if(continue_critial>1)add+=continue_critial;
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
                if(i-1>=0)
                {
                    if(tmp_board.get_cell_color(i-1,j)!='w'&&tmp_board.get_cell_color(i-1,j)!=color)
                    {
                        if(tmp_board.get_orbs_num(i-1,j)==tmp_board.get_capacity(i-1,j)-1)
                        {
                            sc=sc-((5-(tmp_board.get_capacity(i-1,j)))*tmp_board.get_orbs_num(i,j));
                            flag=0;
                        }
                    }
                }
                if(i+1<5)
                {
                    if(tmp_board.get_cell_color(i+1,j)!='w'&&tmp_board.get_cell_color(i+1,j)!=color)
                    {
                        if(tmp_board.get_orbs_num(i+1,j)==tmp_board.get_capacity(i+1,j)-1)
                        {
                            sc=sc-((5-(tmp_board.get_capacity(i+1,j)))*tmp_board.get_orbs_num(i,j));
                            flag=0;
                        }
                    }
                }
                if(j-1>=0)
                {
                    if(tmp_board.get_cell_color(i,j-1)!='w'&&tmp_board.get_cell_color(i,j-1)!=color)
                    {
                        if(tmp_board.get_orbs_num(i,j-1)==tmp_board.get_capacity(i,j-1)-1)
                        {
                            sc=sc-((5-(tmp_board.get_capacity(i,j-1)))*tmp_board.get_orbs_num(i,j));
                            flag=0;
                        }
                    }
                }
                if(j+1<6)
                {
                    if(tmp_board.get_cell_color(i,j+1)!='w'&&tmp_board.get_cell_color(i,j+1)!=color)
                    {
                        if(tmp_board.get_orbs_num(i,j+1)==tmp_board.get_capacity(i,j+1)-1)
                        {
                            sc=sc-((5-(tmp_board.get_capacity(i,j+1)))*tmp_board.get_orbs_num(i,j));
                            flag=0;
                        }
                    }
                }

                if(flag)
                {
                    if(tmp_board.get_capacity(i,j)==3)
                        sc+=2;
                    else if(tmp_board.get_capacity(i,j)==2)
                        sc+=3;
                    if(tmp_board.get_orbs_num(i,j)==tmp_board.get_capacity(i,j)-1)
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
    if(enemy_orb==0&&my_orb>1)return 10000;
    if(my_orb==0&&enemy_orb>1)return -10000;
    //sc+=1*find_critiacal(tmp_board,color);
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
