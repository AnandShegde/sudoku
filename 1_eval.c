#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

int t,n,k;

struct tree
{
    int x,y,h,d,c,p;
    int price,weight,flag,profit;
    char direction;
};

struct tree *tree_info;

int main()
{
    int i;
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
    return 0;
}

int cutup_profit(int a,int *cuts)
{ 

    int profit=0;
	int min=-1;
	int i;
    for (i=0; i<k; i++) {
		if (tree_info[i].x == tree_info[a].x && tree_info[i].y > tree_info[a].y&& tree_info[i].flag==1) {
			min = i;
			break;
		}

	}
    for (int j=i+1; j<k ;j++) {
		if (tree_info[j].x == tree_info[a].x && tree_info[j].y > tree_info[a].y && tree_info[j].y < tree_info[min].y &&tree_info[i].flag==1) {
			min = j;
		}
	}
    
    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>abs(tree_info[a].y-tree_info[min].h))
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
    for (i=0; i<k; i++) {
		if (tree_info[i].x == tree_info[a].x && tree_info[i].y < tree_info[a].y&& tree_info[i].flag==1) {
			min = i;
			break;
		}

	}
    for (int j=i+1; j<k ;j++) {
		if (tree_info[j].x == tree_info[a].x && tree_info[j].y < tree_info[a].y && tree_info[j].y > tree_info[min].y &&tree_info[i].flag==1) {
			min = j;
		}
	}
    
    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>abs(tree_info[a].y-tree_info[min].h))
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
    for (i=0; i<k; i++) {
		if (tree_info[i].x < tree_info[a].x && tree_info[i].y == tree_info[a].y&& tree_info[i].flag==1) {
			min = i;
			break;
		}
	}

    for (int j=i+1; j<k ;j++) {
		if (tree_info[j].x < tree_info[a].x && tree_info[j].y == tree_info[a].y && tree_info[j].x > tree_info[min].x &&tree_info[i].flag==1) {
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>abs(tree_info[a].y-tree_info[min].h))
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
    for (i=0; i<k; i++) {
		if (tree_info[i].x > tree_info[a].x && tree_info[i].y == tree_info[a].y&& tree_info[i].flag==1) {
			min = i;
			break;
		}
	}

    for (int j=i+1; j<k ;j++) {
		if (tree_info[j].x > tree_info[a].x && tree_info[j].y == tree_info[a].y && tree_info[j].x < tree_info[min].x &&tree_info[i].flag==1) {
			min = j;
		}
	}

    if(min!=-1)
    {
        if(tree_info[min].weight<tree_info[a].weight && tree_info[a].h>abs(tree_info[a].y-tree_info[min].h))
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
