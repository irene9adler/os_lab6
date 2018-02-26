#include<stdio.h>
#include<stdlib.h>
#define getpch(type) (type*)malloc(sizeof(type))

#define MEM_SIZE 256-56

struct LNode
{ int size;
  int start;
  int end;
  struct LNode *next;
  struct LNode *front;
}*L; /*L为头指针*/

typedef struct LNode LN;
LN *find;
int n = 0;
//int n = MEM_SIZE;//n为空闲区的长度？？？


void InsertList(int size,int start)
{	// 在带头结点的单链线形表头结点后插入
	LN *p,*s,*t;
	p=L;
	t=p->next;
	s=getpch(LN);  //生成新结点
	s->size=size;
	s->start=start;
	s->end=start + size ;
	s->next=t;          //插入L中
	p->next=s;
	if(t)   t->front=s;
	s->front=p;
}

void PrintList() /*打印*/
{
	LN *p; int i;
	p=L->next;

	printf("\n空闲区号  长度  起始位置  终止位置\n");
	for(i=1;i<=n;i++)
	{
		printf(" %3d\t  %3d\t%3d\t  %4d\n",i,p->size, p->start,p->end);
		p=p->next;
	}

}

void BFSortList() /*最佳适应算法的排序*/
{
	LN *p,*s,*t;
	int min_size,i;
	int size,start,end;
	t=L->next;
        p=L->next;
	for(i=0;i<n;i++)
	{
		s=p->next;
		min_size = p->size;
		while(s)
		{
			if(min_size > s->size)
			{
				min_size=s->size;
				t=s;
			}
			s=s->next;
		}
		size=t->size;
		start=t->start;
		end=t->end;

		t->size=p->size;
		t->start=p->start;
		t->end=p->end;

		p->size=size;
		p->start=start;
		p->end=end;

		t=p->next;
                p=p->next;

	}
}

void SortList() /*首次和循环首次适应算法的排序*/
{
	LN *p,*s,*t;
	int min_start,i;
	int size,start,end;
	t=L->next;
        p=L->next;
	for(i=0;i<n;i++)
	{
		s=p->next;
		min_start = p->start;
		while(s)
		{
			if(min_start > s->start)
			{
				min_start=s->start;
				t=s;
			}
			s=s->next;
		}
		size=t->size;
		start=t->start;
		end=t->end;

		t->size=p->size;
		t->start=p->start;
		t->end=p->end;

		p->size=size;
		p->start=start;
		p->end=end;

		t=p->next;
                p=p->next;

	}
}

//void GetFree()  /*生成空闲分区链*/
void initNC()//初始化长度为MEM_SIZE的空闲分区
{
	int size,start,i;
        L=getpch(LN);  /*生成一个表头结点*/
	L->next=NULL;
	L->front=NULL;
	int m =0;
	printf("请输入空闲区数:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
       // for(i=0;i<MEM_SIZE;i++)
	{
		printf("请输入第%2d空闲区的大小和始址:",i);
		scanf("%3d,%3d",&size,&start);
		InsertList(size,start);
		//InsertList(1,i);//初始化200个大小为1的空闲区
		m+=size;
		//n++;
		if(m>=MEM_SIZE)
        {
            printf("已达到256MB内存空间！\n");
            size = MEM_SIZE - start;
            break;
            getchar();
        }
	}
	//printf("\n按任意键继续");
	printf("当前空闲区个数%d\n",n);
	printf("\n空闲链表情况:\n");
	PrintList();
	getchar();
}

void allocateNC_1(int size) /*最佳适应算法和首次适应算法空闲分区的分配*/
{
	LN *p,*t;
	p=L->next;
	t=L;
	while(p)
	{
		if(size > p->size)
		{
			p=p->next;
			t=t->next;
			if(!p)
			{
			   printf("没有足够大的空闲区分配！分配不成功");
			   getchar();
			}
		}
		else
		{
			p->size = p->size - size;
			p->start= p->start + size ;
			if(p->size==0)
			{
				t->next = p->next ;
                                p->next->front=t;
				n--;
				free(p);
			}
			printf("分配成功！\n");
			printf("分配后的空闲链表情况如下:\n");
			PrintList();
			getchar();
			break;
		}
	}
}
int flag=-1;
void allocateNC_NF(int size)/*循环首次适应算法的分配*/
{
	LN *p,*t;
	int i=n;

	p=find->next;
	t=find;
	while(p)
	{
		if(size > p->size)
		{
			p=p->next;
			t=t->next;
			if(!p)
			{
			   printf("没有足够大的空闲区分配！分配不成功");
			   getchar();
			}
		}
		else
		{
			p->size = p->size - size;
			p->start= p->start + size ;
			find=p;
			if(p->size==0)
			{
				t->next = p->next;
                                p->next->front=t;
				n--;
				free(p);
			}
			printf("分配成功！\n");
		    flag=1;
			printf("分配后的空闲链表情况如下：\n");
			//Print(L);
			PrintList();
			getchar();

			break;
	         }
        }
 if(flag==-1)
 {	p=L->next;
	t=L;
	while(p!=find)
	{
		if(size > p->size)
		{
			p=p->next;
			t=t->next;
			if(!p)
			{
			   printf("没有足够大的空闲区分配！分配不成功");
			   getchar();
			}
		}
		else
		{
			p->size = p->size - size;
			p->start= p->start + size ;
			find=t;
			if(p->size==0)
			{
				t->next = p->next ;
                                p->next->front=t;
				n--;
				free(p);
			}
			printf("分配成功！\n");

			printf("分配后的空闲链表情况如下：");
			//PrintList(L);
			PrintList();
			getchar();

			break;
		}

	}

 }
}// end of NF_Assign
void  freeNC(int start, int end)  /*回收*/
{
	LN *p,*t;
	int size,flag=0;
	size=end-start;
	p=L->next;
	t=p->next;


	while(p)
	{
	   if(t && p->end==start && t->start==end)//回收区在两个空闲区中间
		{
			p->size = p->size + size + t->size;
			p->end = t->end;
			p->next=t->next;
            t->next->front=p;
			free(t);
			n--;
			//SortList(L);
			SortList();

			flag=1;
            break;
		}
		else if(p->end == start)//回收区在空闲区下方
		{
			flag=1;
			p->size = p->size + size;
			p->end = p->end + size ;
			//SortList(L);
			SortList();

		 break;
		}
		else if( p->start == end)//回收区在空闲区上方
		{
			p->size= p->size +size;
			p->start=start;
			//SortList(L);
			SortList();
			flag=1;

			break;
		}
            p=p->next;
            if(p)
               t=p->next;
	}
    //回收区不与任何一个空闲区相邻
	if(flag==0)
            { InsertList(size,start);  n++;}

	 printf("回收后的空闲链表情况如下:");
	   PrintList();

        printf("\n按任意键继续");

}
int main(void)
{

	int start,end,size;
	int m;

	initNC();
	//getch();
	getchar();

        system("cls");/*清屏*/
        printf("请选择服务类型:\n");
        printf("\t1:首次适应算法\n");
        printf("\t2:循环首次适应算法\n");
       	printf("\t3:最佳适应算法\n");
       // printf("\t4:回收内存\n");
        printf("\t0:退出\n");
        printf("\t输入您要的选项:");
        scanf("%d",&m); if(m==2) find=L;
        int loop1 = 10;
        int loop2 = 10;
        int loop3 = 10;
      while(m)
       {
       	  switch(m)
		 {
	    	   case 1:
	    	       while(loop1--){
	    	         SortList();  printf("\n空闲链表情况:\n");
	                        PrintList();
                            //printf("请输入进程需要的空闲区大小:");
			                //scanf("%d",&size);
			                size = rand()%500;
			                printf("生成的随机数为%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("需要回收内存！\n");
                                printf("请输入回收区的首地址和中止地址:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
                            allocateNC_1(size);
			                //printf("\n按任意键继续");

	    	   }
	    	    break;
		       case 2:
		           while(loop2--)
                   {
		           	   SortList();  printf("\n空闲链表情况:\n");
	                        PrintList();
                            printf("请输入进程需要的空闲区大小:");
			                //scanf("%d",&size);
			                size = rand()%500;
                            printf("生成的随机数为%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("需要回收内存！\n");
                                printf("请输入回收区的首地址和中止地址:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
			                allocateNC_NF(size);
			                //printf("\n按任意键继续");
                   }
                            break;

	          	case 3:
	          	       while(loop3--)
                       {
	          	    	    BFSortList();  printf("\n空闲链表情况:\n");
                          	PrintList();
                            printf("请输入进程需要的空闲区大小:");
			                //scanf("%d",&size);
			                size = rand()%500;
			                printf("生成的随机数为%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("需要回收内存！\n");
                                printf("请输入回收区的首地址和中止地址:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
			                allocateNC_1(size);
			                //printf("\n按任意键继续");
                       }
			                break;

                /*case 4:	    printf("请输入回收区的首地址和中止地址:");
				            scanf("%3d,%3d",&start,&end);
				            freeNC(start,end);
				            break;*/

                case 0:	    exit(0);

                default : printf("\n\t\t输入错误,请重新输入"); getchar();
		 }
		        getchar();
		        system("cls");/*清屏*/
		        printf("请选择服务类型:\n");
                printf("\t1:首次适应算法\n");
                printf("\t2:循环首次适应算法\n");
         	    printf("\t3:最佳适应算法\n");
                printf("\t4:回收内存\n");
                printf("\t0:退出\n");
                printf("\t输入您要的选项:");
                scanf("%d",&m);

        }
  return 0;
}
