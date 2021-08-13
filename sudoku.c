
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
typedef long double LD;
typedef long long ll;
#define int ll
#define pb push_back
#define mp make_pair
#define REP(i,n) for (int i = 0; i < n; i++)
#define FOR(i,a,b) for (int i = a; i < b; i++)
#define REPD(i,n) for (int i = n-1; i >= 0; i--)
#define FORD(i,a,b) for (int i = a; i >= b; i--)
// -----<SCANF>-----
#define sfi(x) scanf("%d",&x);
#define sfi2(x,y) scanf("%d%d",&x,&y);
#define sfi3(x,y,z) scanf("%d%d%d",&x,&y,&z);

#define sfl(x) scanf("%lld",&x);
#define sfl2(x,y) scanf("%lld%lld",&x,&y);
#define sfl3(x,y,z) scanf("%lld%lld%lld",&x,&y,&z);
#define sfl4(x,y,z,x1) scanf("%lld%lld%lld%lld",&x,&y,&z,&x1);
#define sfl5(x,y,z,x1,y1) scanf("%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1);
#define sfl6(x,y,z,x1,y1,z1) scanf("%lld%lld%lld%lld%lld%lld",&x,&y,&z,&x1,&y1,&z1);

#define sfs(x) scanf("%s",x);
#define sfs2(x,y) scanf("%s%s",x,y);
#define sfs3(x,y,z) scanf("%s%s%s",x,y,z);
// ----</SCANF>-----

// ----<PRINTF>-----
#define pfi(x) printf("%d\n",x);
#define pfi2(x,y) printf("%d %d\n",x,y);
#define pfi3(x,y,z) printf("%d %d %d\n",x,y,z);

#define pfl(x) printf("%lld\n",x);
#define pfl2(x,y) printf("%lld %lld\n",x,y);
#define pfl3(x,y,z) printf("%lld %lld %lld\n",x,y,z);

#define pfs(x) printf("%s\n",x);
#define pfs2(x,y) printf("%s %s\n",x,y);
#define pfs3(x,y,z) printf("%s %s %s\n",x,y,z);

#define pwe(x) printf("%lld ",x); // print without end
// ----</PRINTF>----
int a,b,c,d,e,t,no,i,j,n,m,row,col,x;
void printarray(int *sudoku)
{
    REP(i,m)// this loop prints the solution
            {
                REP(j,n)
                {
                    //if(sudoku1[i][j]>9) sudoku1[i][j]=9;

                    printf("%d ",*(sudoku+i*9+j));
                }
                printf("\n");
            }
}

int check(const int *array,const int row,const int col,const int coloumn,const int rows)
{

    REP(i,coloumn)//check in the same row
    {
        if(i==col);
        else
        {
            if(*(array+coloumn*row+i)==*(array+coloumn*row+col)) return 1;
        }

    }
    REP(i,rows)//check in same coloumn
    {
        if(i==row);
        else if(*(array+coloumn*i+col)==*(array+coloumn*row+col))return 1;
    }
   i=(row/3)*3;

   while(i<(row/3)*3+3)//check in the square
   {


        j=(col/3)*3;
       while(j<(col/3)*3+3)
       {
           if(i==row&&j==col);
           else if(*(array+coloumn*i+j)==*(array+coloumn*row+col)) return 1;
           j++;
       }

       i++;
   }

    return 0;

}

void change(const int *zeros, int *sudoku,const int m,const int n)
{


    int present,value,row,colou;
    row=*zeros/10; //last row will have index 8
    colou=*zeros%10; //last coloumn will have index 8;


    *(sudoku+row*9+colou)=*(sudoku+row*9+colou)+1;//increment the value

    value=*(sudoku+row*9+colou);


    present= check(sudoku,row,colou,9,9);

    /*printf("value=%d ",value); printf("row=%d ",row+1);printf("col=%d ",colou+1);
    printf("present=%d\n",present);*/

    if(value>9)
    {

        *(sudoku+row*9+colou)=0;
        //printarray(sudoku);
    //getch();
        change(zeros-1,sudoku,9,9);
    }
    else
    {


        if(present==1)
            {
                if(value<9)
                {
                    change(zeros,sudoku,9,9);
                }
                else
                {
                    //printf("%d\n",*zeros);
                    *(sudoku+row*9+colou)=0;
                    change(zeros-1,sudoku,9,9);

                }
            }
        else if(present==0)
         {
             if(row+1==9&&colou+1==9)
                return;
            //printarray(sudoku);

            //getch();
            //printf("%d\n",*(zeros+1));
            if(value>9)
            {
            *(sudoku+row*9+colou)=0;
            //printarray(sudoku);
            getch();
                change(zeros-1,sudoku,9,9);
            }


             if((*(zeros+1))<89&&((*(zeros+1))>-1))
             {
                 change(zeros+1,sudoku,9,9);
             }



         }
    }

}

int main()
{
    m=9;n=9;// this are no of rows and colomns in problem
    int sudoku2 [9][9]={0,3,5,2,6,9,7,8,1,
    6,0,2,0,7,1,4,9,3,
    1,0,0,8,0,4,5,6,2,
    8,2,6,0,9,5,0,4,7,
    3,7,0,6,8,0,9,0,5,
    9,0,1,7,4,0,0,2,8,
    0,1,9,0,2,6,0,7,4,
    0,4,0,9,5,0,1,3,6,
    7,0,3,0,1,0,0,5,0};
    int sudoku1 [9][9]={0};// this is the problem
    int sudoku [m][n],zeros_address[100];// i need the actual problem for
    //reference, since i am going to change it, so this sudoku[m][n] is for
    //working
    //the zeros_address stores all the adresses at which there is a gap, in this case a zero
    REP(i,m)
    {
        REP(j,n)
        {
            if(sudoku1[i][j]==0)
            {
                zeros_address[x]=i*10+j; // as address is the box no and
                //is of the form (m,n) i am doing this to store it as a single no 0<=x<=88.
                x++;//this is no of zeros

            }
            sudoku[i][j]=sudoku1[i][j];// copying the whole sudoku
            printf("%d ",sudoku1[i][j]);// printing it just for fun
        }
        printf("\n");
    }
    printf("\npositions of zeros: ");
    REP(i,x)
        printf("%d ",zeros_address[i]);
    printf("\n \n \nthe answer to above question is\n");

      clock_t t;
    t = clock();
    change(zeros_address,sudoku1,m,n);// this should solve the problem

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

 REP(i,m)// this loop prints the solution
    {
        REP(j,n)
        {
            //if(sudoku1[i][j]>9) sudoku1[i][j]=9;

            printf("%d ",sudoku1[i][j]);
        }
        printf("\n");
    }

printf("time taken to solve is %f seconds",time_taken);









    return 0;
}





