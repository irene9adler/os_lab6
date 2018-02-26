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
}*L; /*LΪͷָ��*/

typedef struct LNode LN;
LN *find;
int n = 0;
//int n = MEM_SIZE;//nΪ�������ĳ��ȣ�����


void InsertList(int size,int start)
{	// �ڴ�ͷ���ĵ������α�ͷ�������
	LN *p,*s,*t;
	p=L;
	t=p->next;
	s=getpch(LN);  //�����½��
	s->size=size;
	s->start=start;
	s->end=start + size ;
	s->next=t;          //����L��
	p->next=s;
	if(t)   t->front=s;
	s->front=p;
}

void PrintList() /*��ӡ*/
{
	LN *p; int i;
	p=L->next;

	printf("\n��������  ����  ��ʼλ��  ��ֹλ��\n");
	for(i=1;i<=n;i++)
	{
		printf(" %3d\t  %3d\t%3d\t  %4d\n",i,p->size, p->start,p->end);
		p=p->next;
	}

}

void BFSortList() /*�����Ӧ�㷨������*/
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

void SortList() /*�״κ�ѭ���״���Ӧ�㷨������*/
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

//void GetFree()  /*���ɿ��з�����*/
void initNC()//��ʼ������ΪMEM_SIZE�Ŀ��з���
{
	int size,start,i;
        L=getpch(LN);  /*����һ����ͷ���*/
	L->next=NULL;
	L->front=NULL;
	int m =0;
	printf("�������������:");
	scanf("%d",&n);
	for(i=1;i<=n;i++)
       // for(i=0;i<MEM_SIZE;i++)
	{
		printf("�������%2d�������Ĵ�С��ʼַ:",i);
		scanf("%3d,%3d",&size,&start);
		InsertList(size,start);
		//InsertList(1,i);//��ʼ��200����СΪ1�Ŀ�����
		m+=size;
		//n++;
		if(m>=MEM_SIZE)
        {
            printf("�Ѵﵽ256MB�ڴ�ռ䣡\n");
            size = MEM_SIZE - start;
            break;
            getchar();
        }
	}
	//printf("\n�����������");
	printf("��ǰ����������%d\n",n);
	printf("\n�����������:\n");
	PrintList();
	getchar();
}

void allocateNC_1(int size) /*�����Ӧ�㷨���״���Ӧ�㷨���з����ķ���*/
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
			   printf("û���㹻��Ŀ��������䣡���䲻�ɹ�");
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
			printf("����ɹ���\n");
			printf("�����Ŀ��������������:\n");
			PrintList();
			getchar();
			break;
		}
	}
}
int flag=-1;
void allocateNC_NF(int size)/*ѭ���״���Ӧ�㷨�ķ���*/
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
			   printf("û���㹻��Ŀ��������䣡���䲻�ɹ�");
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
			printf("����ɹ���\n");
		    flag=1;
			printf("�����Ŀ�������������£�\n");
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
			   printf("û���㹻��Ŀ��������䣡���䲻�ɹ�");
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
			printf("����ɹ���\n");

			printf("�����Ŀ�������������£�");
			//PrintList(L);
			PrintList();
			getchar();

			break;
		}

	}

 }
}// end of NF_Assign
void  freeNC(int start, int end)  /*����*/
{
	LN *p,*t;
	int size,flag=0;
	size=end-start;
	p=L->next;
	t=p->next;


	while(p)
	{
	   if(t && p->end==start && t->start==end)//�������������������м�
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
		else if(p->end == start)//�������ڿ������·�
		{
			flag=1;
			p->size = p->size + size;
			p->end = p->end + size ;
			//SortList(L);
			SortList();

		 break;
		}
		else if( p->start == end)//�������ڿ������Ϸ�
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
    //�����������κ�һ������������
	if(flag==0)
            { InsertList(size,start);  n++;}

	 printf("���պ�Ŀ��������������:");
	   PrintList();

        printf("\n�����������");

}
int main(void)
{

	int start,end,size;
	int m;

	initNC();
	//getch();
	getchar();

        system("cls");/*����*/
        printf("��ѡ���������:\n");
        printf("\t1:�״���Ӧ�㷨\n");
        printf("\t2:ѭ���״���Ӧ�㷨\n");
       	printf("\t3:�����Ӧ�㷨\n");
       // printf("\t4:�����ڴ�\n");
        printf("\t0:�˳�\n");
        printf("\t������Ҫ��ѡ��:");
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
	    	         SortList();  printf("\n�����������:\n");
	                        PrintList();
                            //printf("�����������Ҫ�Ŀ�������С:");
			                //scanf("%d",&size);
			                size = rand()%500;
			                printf("���ɵ������Ϊ%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("��Ҫ�����ڴ棡\n");
                                printf("��������������׵�ַ����ֹ��ַ:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
                            allocateNC_1(size);
			                //printf("\n�����������");

	    	   }
	    	    break;
		       case 2:
		           while(loop2--)
                   {
		           	   SortList();  printf("\n�����������:\n");
	                        PrintList();
                            printf("�����������Ҫ�Ŀ�������С:");
			                //scanf("%d",&size);
			                size = rand()%500;
                            printf("���ɵ������Ϊ%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("��Ҫ�����ڴ棡\n");
                                printf("��������������׵�ַ����ֹ��ַ:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
			                allocateNC_NF(size);
			                //printf("\n�����������");
                   }
                            break;

	          	case 3:
	          	       while(loop3--)
                       {
	          	    	    BFSortList();  printf("\n�����������:\n");
                          	PrintList();
                            printf("�����������Ҫ�Ŀ�������С:");
			                //scanf("%d",&size);
			                size = rand()%500;
			                printf("���ɵ������Ϊ%d\n",size);
			                if(size>MEM_SIZE)
			                {
			                    printf("��Ҫ�����ڴ棡\n");
                                printf("��������������׵�ַ����ֹ��ַ:");
				                scanf("%3d,%3d",&start,&end);
				                freeNC(start,end);
			                }
			                allocateNC_1(size);
			                //printf("\n�����������");
                       }
			                break;

                /*case 4:	    printf("��������������׵�ַ����ֹ��ַ:");
				            scanf("%3d,%3d",&start,&end);
				            freeNC(start,end);
				            break;*/

                case 0:	    exit(0);

                default : printf("\n\t\t�������,����������"); getchar();
		 }
		        getchar();
		        system("cls");/*����*/
		        printf("��ѡ���������:\n");
                printf("\t1:�״���Ӧ�㷨\n");
                printf("\t2:ѭ���״���Ӧ�㷨\n");
         	    printf("\t3:�����Ӧ�㷨\n");
                printf("\t4:�����ڴ�\n");
                printf("\t0:�˳�\n");
                printf("\t������Ҫ��ѡ��:");
                scanf("%d",&m);

        }
  return 0;
}
