#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int t,n,k;
int currentX = 0, currentY = 0; //location of current tree(lumberjack)
struct tree
{
    int x,y,h,d,c,p;
    int price,weight,flag,profit;
    char direction;
    int* indicesOfDominos;
};

struct tree *tree_info;

int mod(int x, int y)
{
    if(x>y)
    {
        return x-y;
    }
    else
    {
        return y-x;
    }
}

int cutup_profit(int a,int *cuts)
{
    int profit=0;
	int min=-1;
	int i;
    for (i=0; i<k; i++)
    {
		if (tree_info[i].x == tree_info[a].x && tree_info[i].y > tree_info[a].y && tree_info[i].flag==1)
		{
			min = i;
			break;
		}
	}
	if(min==-1) return 0;
    for (int j=min+1; j<k ;j++)
    {
		if (tree_info[j].x == tree_info[a].x && tree_info[j].y > tree_info[a].y && tree_info[j].y < tree_info[min].y &&tree_info[j].flag==1)
		{
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>mod(tree_info[a].y,tree_info[min].y))
        {
            cuts[cuts[0]++]=min; // i have used the 0th element of the
            //array to store the number of trees cut by domino.
            profit= tree_info[min].price+ cutup_profit(min,cuts);
            return profit;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int cutdown_profit(int a,int *cuts)
{

    int profit=0;
	int min=-1;
	int i;
    for (i=0; i<k; i++)
    {
		if (tree_info[i].x == tree_info[a].x && tree_info[i].y < tree_info[a].y&& tree_info[i].flag==1)
		{
			min = i;
			break;
		}

	}
	if(min==-1) return 0;
    for (int j=min+1; j<k ;j++)
    {
		if (tree_info[j].x == tree_info[a].x && tree_info[j].y < tree_info[a].y && tree_info[j].y > tree_info[min].y &&tree_info[j].flag==1)
        {
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>mod(tree_info[a].y,tree_info[min].y))
        {
            cuts[cuts[0]++]=min; // i have used the 0th element of the
            //array to store the number of trees cut by domino.
            profit= tree_info[min].price+ cutdown_profit(min,cuts);
            return profit;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int cutleft_profit(int a,int *cuts)
{

    int profit=0;
	int min=-1;
	int i;
    for (i=0; i<k; i++)
    {
		if (tree_info[i].x < tree_info[a].x && tree_info[i].y == tree_info[a].y&& tree_info[i].flag==1)
		{
			min = i;
			break;
		}
	}
    if(min==-1) return 0;
    for (int j=min+1; j<k ;j++)
    {
		if (tree_info[j].x < tree_info[a].x && tree_info[j].y == tree_info[a].y && tree_info[j].x > tree_info[min].x &&tree_info[j].flag==1)
		{
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>mod(tree_info[a].x,tree_info[min].x))
        {
            cuts[cuts[0]++]=min; // i have used the 0th element of the
            //array to store the number of trees cut by domino.
            profit= tree_info[min].price+ cutleft_profit(min,cuts);
            return profit;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int cutright_profit(int a,int *cuts)
{

    int profit=0;
	int min=-1;
	int i;
    for (i=0; i<k; i++)
    {
		if (tree_info[i].x > tree_info[a].x && tree_info[i].y == tree_info[a].y&& tree_info[i].flag==1)
        {
			min = i;
			break;
		}
	}
    if(min==-1) return 0;
    for (int j=min+1; j<k ;j++)
    {
		if (tree_info[j].x > tree_info[a].x && tree_info[j].y == tree_info[a].y && tree_info[j].x < tree_info[min].x &&tree_info[j].flag==1)
        {
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>mod(tree_info[a].x,tree_info[min].x))
        {
            cuts[cuts[0]++]=min; // i have used the 0th element of the
            //array to store the number of trees cut by domino.
            profit= tree_info[min].price+ cutleft_profit(min,cuts);
            return profit;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}

int calculate_profit()
{
    int mark=0;
    int* indicesOfDominos;
    int currentProfit;
    int finalProfit;
    indicesOfDominos = (int*) malloc(sizeof(int)*(k+1)); //temperory array to store the indices in each direction
    for(int i=0; i<k ; i++)
    {
        if(tree_info[i].flag == 1)
        {
            int treeTime = mod(tree_info[i].x, currentX) + mod(tree_info[i].y, currentY) + tree_info[i].d;
            if( treeTime <= t )
            {
                mark=1;
                indicesOfDominos[0]=0;
                currentProfit = tree_info[i].price + cutup_profit(i, indicesOfDominos);
                finalProfit = currentProfit;
                tree_info[i].direction = 'u';
                tree_info[i].indicesOfDominos = (int*) malloc(sizeof(int)*(indicesOfDominos[0]+1));
                for(int j=0; j<indicesOfDominos[0]+1; j++)
                {
                    tree_info[i].indicesOfDominos[j] = indicesOfDominos[j];
                }
                //checking in downward direction
                indicesOfDominos[0] = 0;
                currentProfit = tree_info[i].price + cutdown_profit(i, indicesOfDominos);
                if( finalProfit < currentProfit )
                {
                    finalProfit = currentProfit;
                    tree_info[i].direction = 'd';
                    free(tree_info[i].indicesOfDominos);
                    tree_info[i].indicesOfDominos = (int*) malloc(sizeof(int)*(indicesOfDominos[0]+1));
                    for(int j=0; j<indicesOfDominos[0]+1; j++)
                    {
                        tree_info[i].indicesOfDominos[j] = indicesOfDominos[j];
                    }
                }
                //checking in rightward_direction
                indicesOfDominos[0] = 0;
                currentProfit = tree_info[i].price + cutright_profit(i, indicesOfDominos);
                if(finalProfit < currentProfit)
                {
                    finalProfit = currentProfit;
                    tree_info[i].direction = 'r';
                    free(tree_info[i].indicesOfDominos);
                    tree_info[i].indicesOfDominos = (int*) malloc(sizeof(int)*(indicesOfDominos[0]+1));
                    for(int j=0; j<indicesOfDominos[0]+1; j++)
                    {
                        tree_info[i].indicesOfDominos[j] = indicesOfDominos[j];
                    }
                }
                //checking in downward direction
                indicesOfDominos[0] = 0;
                currentProfit = tree_info[i].price + cutleft_profit(i, indicesOfDominos);
                if(finalProfit < currentProfit)
                {
                    finalProfit = currentProfit;
                    tree_info[i].direction = 'l';
                    free(tree_info[i].indicesOfDominos);
                    tree_info[i].indicesOfDominos = (int*) malloc(sizeof(int)*(indicesOfDominos[0]+1));
                    for(int j=0; j<indicesOfDominos[0]+1; j++)
                    {
                        tree_info[i].indicesOfDominos[j] = indicesOfDominos[j];
                    }
                }
                tree_info[i].profit = finalProfit;
                free(indicesOfDominos);
           }
        }
    }
    return mark;
}

int search_max_profit()
{
    int max_profit = -1,index,treeTime;
    for(int i=0;i<k;i++)
    {
        treeTime = mod(tree_info[i].x, currentX) + mod(tree_info[i].y, currentY) + tree_info[i].d;
        if(max_profit<tree_info[i].profit && treeTime<=t)
        {
            max_profit=tree_info[i].profit;
            index=i;
        }
    }
    return index;
}

void path(int index)
{
    t=t-(mod(tree_info[index].x, currentX) + mod(tree_info[index].y, currentY) + tree_info[index].d);
    for(int i=1;i<tree_info[index].indicesOfDominos[0]+1;i++)
    {
        tree_info[tree_info[index].indicesOfDominos[i]].flag=0;
    }
    tree_info[index].flag=0;
    if(tree_info[index].x >= currentX)
    {
        for(int i=0;i<mod(tree_info[index].x,currentX);i++)
        {
            printf("move right\n");
        }
    }
    else
    {
        for(int i=0;i<mod(tree_info[index].x,currentX);i++)
        {
            printf("move left\n");
        }
    }
    if(tree_info[index].y >= currentY)
    {
        for(int i=0;i<mod(tree_info[index].y,currentY);i++)
        {
            printf("move up\n");
        }
    }
    else
    {
        for(int i=0;i<mod(tree_info[index].y,currentY);i++)
        {
            printf("move down\n");
        }
    }
    currentX=tree_info[index].x;
    currentY=tree_info[index].y;
    switch(tree_info[index].direction)
    {
        case 'u':printf("cut up\n");
        break;
        case 'd':printf("cut down\n");
        break;
        case 'l':printf("cut left\n");
        break;
        case 'r':printf("cut right\n");
        break;
    }
}

void time_pass_path()
{
    if(t > 0)
    {
        if(currentX==n)
        {
           if(t%2==0)
           {
              for(int i=0;i<t/2;i++)
                   printf("move left\nmove right\n");
           }
           else
           {
              printf("move left\n");
              for(int i=0;i<t/2;i++)
                  printf("move right\nmove left\n");
           }
        }
        else
        {
           if(t%2==0)
           {
              for(int i=0;i<t/2;i++)
                   printf("move right\nmove left\n");
           }
           else
           {
              printf("move right\n");
              for(int i=0;i<t/2;i++)
                  printf("move left\nmove right\n");
           }
        }
    }
}

int main()
{
    int i,mark,max_index;
    scanf("%d%d%d",&t,&n,&k);
    tree_info=(struct tree*)malloc(sizeof(struct tree)*k);
    for(i=0;i<k;i++)
    {
        scanf("%d%d%d%d%d%d",&tree_info[i].x,&tree_info[i].y,&tree_info[i].h,&tree_info[i].d,&tree_info[i].c,&tree_info[i].p);
        tree_info[i].price=tree_info[i].h*tree_info[i].d*tree_info[i].p;
        tree_info[i].weight=tree_info[i].h*tree_info[i].d*tree_info[i].c;
        tree_info[i].flag=1;
        tree_info[i].profit=tree_info[i].price;
    }
    while(t>0)
    {
       mark=calculate_profit();
       if(mark==1)
       {
           max_index=search_max_profit();
           path(max_index);
       }
       else
       {
           time_pass_path();
           break;
       }
    }
    free(tree_info);
    return 0;
}
