#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<stdbool.h>

char **visual;
char **ans;
char **ans1;
void RandomBomb(char*,char*,int32_t,int32_t,int32_t);
void Open(char*,char*,char*,int32_t,int32_t,int32_t,bool);
void Flag(char*,int32_t,int32_t);
void Printer(char*,int32_t,int32_t);
void win(char *,int32_t,int32_t,int32_t);

int main() 
{
	int32_t width,height,mine;
	int32_t option=0;
  do
	{
    printf("Please enter the width       (10-16):");
	  scanf("%d",&width);
    if(width<10||width>16)
	  {
		  printf("invaid input for width\n");
	  }
  }while(width<10||width>16);
  do
	{
    printf("Please enter the height      (10-16):");
	  scanf("%d",&height);
    if(height<10||height>16)
	  {
		  printf("invaid input for height\n");
	  }
  }while(height<10||height>16);
  do
	{
    printf("Please enter the mine number (30-90):");
	  scanf("%d",&mine);
    if(mine<30||mine>90)
	  {
		printf("invaid input for mine\n");
	  }
  }while(mine<30||mine>90);
	char visual[height][width];
	char ans[height][width];
	char ans1[height][width];
	for(int i=0;i<height;i++)
	{
		for(int j=0;j<width;j++)
		{
			visual[i][j]='*';
			ans[i][j]=' ';
			ans1[i][j]=' ';
		}
	}
  bool winorlose=1;
  RandomBomb(*ans,*ans1,width,height,mine);
 // Printer(&ans[0][0],width,height);
  //Printer(&ans1[0][0],width,height);
	while(1)
	{
    do
    {
      Printer(&visual[0][0],width,height);
		  printf("Your Option (1:Open , 2:Flag):");
		  scanf("%d",&option);
		  if(option==1)
		  {
			  Open(&visual[0][0],&ans[0][0],&ans1[0][0],width,height,mine,winorlose);
        win(&visual[0][0],width,height,mine); 
		  }
		  else if(option==2)
		  {
			  Flag(&visual[0][0],width,height);
	  	}
      if(option==1||option==2)
      continue;
      else
      printf("invaild input!\n");
      printf("\n");
    }while(option!=1||option!=2); 
	}
  return 0;	
}

void Printer(char *visual,int32_t width,int32_t height)
{
	printf("    ");
	for(int i=0;i<width;i++)
	{
		printf("%02d ",i);
	}
	printf("\n");
	for(int j=0;j<width*3+3;j++)
	{
		printf("-");
	}
	printf("\n");
	for(int k=0;k<height;k++)
	{
		printf("%02d| ",k);
		for(int l=0;l<width;l++)
		{
			printf("%2c ",visual[k*width+l]);
		}
		printf("\n");
	}
	printf("\n");
}

void Flag(char *visual,int32_t width,int32_t height)
{
	int32_t row,column;
  bool times=0;
  do
	{
    do
		{
		  printf("Position (row,column):");
		  scanf("%d %d",&row,&column);
      if(row>height || column>width)
      printf("invaild input1!\n");
      else break;
	  }while(row>height || column>width);
	  int32_t position=row*width+column;
	  if(visual[position]=='F')
	  {
		  visual[position]='*';
		  times=1;
	  }
	  else if(visual[position]=='*')
	  {
		  visual[position]='F';
		  times=1;
  	}
    else times=0;
    if(times==0)
    {
      printf("invaild input!\n");
    }
    else break;
  }while(times==0);
}

void Open(char*visual,char*ans,char*ans1,int32_t width,int32_t height,int32_t mine,bool winorlose)
{
  int32_t row,column;
  bool times=0;
  do
	{
    do
		{
		  printf("Position (row,column):");
		  scanf("%d %d",&row,&column);
      if(row>height || column>width)
      {
        printf("%d>%d||%d>%d\n",row,height,column,width);
        printf("invaild input!\n");
      }
      else break;
	  }while(row>height || column>width);
	  int32_t position=row*width+column;
	  if(ans[position]=='X')
  	{
	  	printf("Bomb! You lose!\n");
      exit(0);
	  }
    else 
	  {
		  if(visual[position]=='*')
      {
        visual[position]=ans1[position];
        times=1;
      }
      else
      times=0;
	  }
  }while(times==0);
}
//輸贏
void win(char *visual,int32_t width,int32_t height,int32_t mine)
{
  int test=0;
  int flag=0;
  for(int testX=0;testX<height;testX++)
  {
    for(int testY=0;testY<width;testY++)
    {
      if(visual[testX*width+testY]=='*')
      test++;
    }
  }
  if(test==mine)
  {
    printf("You win!Congratulation!\n");
    exit(0);
  }
  
}
//炸彈//
void RandomBomb(char*ans,char*ans1,int32_t width,int32_t height,int32_t mine)
{
	int i=0;
	int times;
	int sum=width*height;
	bool condition;
	srand(time(NULL));
  while(i<mine)
	{
	  int a=(rand()%height)+0;
	  int b=(rand()%width)+0;
	  if(ans[a*width+b]==' ')
  	{
	  	ans[a*width+b]='X';
		  i=i+1;
	  }
 	}
	char temp[9]={'0','1','2','3','4','5','6','7','8'};
  int array00[]={4,6,7};
  int array01[]={3,5,6};
  int array10[]={1,2,4};
  int array11[]={0,1,3};
  int arrayh0[]={3,4,5,6,7};
  int arrayh1[]={0,1,2,3,4};
  int arrayw0[]={1,2,4,6,7};
  int arrayw1[]={0,1,3,5,6};
	int Judge[8]={0};
	for(int judge=0;judge<8;)
	{
		for(int k=-1;k<2;k++)
		{
			for(int l=-1;l<2;l++)
			{
				if(k==0 && l==0)
				continue;
				else
				{
					Judge[judge]=k*width+l;
					judge++;
				}
			}
		}
	}
  for(int a=0;a<8;a++)
	{
	  printf("%d\n",Judge[a]);
	}			
	for(int x=0;x<height;x++)
	{
		for(int y=0;y<width;y++)
		{
			if(ans[x*width+y]=='X')
			ans1[x*width+y]='0';
			else
			{ 
				condition=1;
        if((x>0&&x<height-1)&&(y>0&&y<width-1))
        {
          for(int a=0;a<8;a++)
				  {
					  if(ans[x*width+y+Judge[a]]=='X')
					  times++;
				  }
        }
        
        else if(x==0&&y==0) 
        {
          for(int a=0;a<3;a++)
          {
            if(ans[x*width+y+Judge[array00[a]]]=='X')
					  times++;
          }
        }
        else if(x==0&&y==width-1) 
        {
          for(int a=0;a<3;a++)
          {
            if(ans[x*width+y+Judge[array01[a]]]=='X')
					  times++;
          }
        }
        else if(x==height-1&&y==0) 
        {
          for(int a=0;a<3;a++)
          {
            if(ans[x*width+y+Judge[array10[a]]]=='X')
					  times++;
          }
        }
        else if(x==height-1&&y==width-1) 
        {
          for(int a=0;a<3;a++)
          {
            if(ans[x*width+y+Judge[array11[a]]]=='X')
					  times++;
          }
        }
        else if(x==0&&(y!=0||y!=width-1)) 
        {
          for(int a=0;a<5;a++)
				  {
					  if(ans[x*width+y+Judge[arrayh0[a]]]=='X')
					  times++;
				  }
        }
        else if(x==width-1&&(y!=0||y!=width-1)) 
        {
          for(int a=0;a<5;a++)
				  {
					  if(ans[x*width+y+Judge[arrayh1[a]]]=='X')
					  times++;
				  }
        }
        else if((x!=0||x!=height-1)&&y==0) 
        {
          for(int a=0;a<5;a++)
				  {
					  if(ans[x*width+y+Judge[arrayw0[a]]]=='X')
					  times++;
				  }
        }
        else if((x!=0||x!=height-1)&&y==width-1) 
        {
          for(int a=0;a<5;a++)
				  {
					  if(ans[x*width+y+Judge[arrayw1[a]]]=='X')
					  times++;
				  }
        }
			}
			if(condition==1)
			ans1[x*width+y]=temp[times];
			times=0;
		}		
	}
}
