#include"stdio.h"
#include"stdlib.h"
#include"malloc.h"
#define M 50		//M为招聘的限制最大人数

typedef int Integer;
struct employee
{
	Integer num;
	Integer Fwish;	//第一志愿
	Integer Swish;	//可以有第二志愿，可以没有，没有为0
	int grade;
	Integer enroll;	//是否被录取，被录取就赋值为录取的工种号，否则为-1
	int Q;	//是一个标记，用于判断已经经过几次筛选
};//应聘者信息

struct Emp
{
	int n;	//n为此线性表(工种)中实际有多少个应聘者
	struct employee e[M];
};//将应聘者封装，构成招聘信息表

struct hire
{
	int m;	//实际有多少个工种
	int *number;	//每个工种招多少人
	struct Emp h[M];
};//将顺序表封装，构成雇用信息表

struct hire *Luqv(struct hire *h,struct Emp *p)
{
	int i,l=0;
	int d=1;	//d初始值为1可使招聘人员满时立即退出
	struct hire *increase(struct hire *,struct employee );
	struct Emp *sort(struct Emp *);

	for(i=0;i<h->m;i++)l=l+h->number[i];	//m个工种共招聘多少个人
	printf("\n");
	printf("本次招聘共招聘%d个人;\n",l);

	for(i=0;i<p->n && d<=l;i++)	//当招聘额满，或已对全部应聘者都做了录用处理时退出
	{
		if(p->e[i].enroll==-1 && p->e[i].Q<2)	//未被录用且不能大于一次筛选
		{
			if(p->e[i].Q==0)
			{
				p->e[i].Q++;	//一次筛选Q加1
				if(h->number[p->e[i].Fwish] > h->h[p->e[i].Fwish].n)	//第一志愿工种人数未招满
				{
					d++;	//记录多少个人被录取
					p->e[i].enroll=p->e[i].Fwish;				
				}
			}
			else
			{
				if(p->e[i].Swish!=-1 && p->e[i].Q==1)	//有第二志愿且已经经过一次筛选
				{
					p->e[i].Q++;
					if(h->number[p->e[i].Swish] > h->h[p->e[i].Swish].n)	//第二志愿工种人数未招满
					{
						d++;
						p->e[i].enroll=p->e[i].Swish;						
					}
				}
			}
			h=increase(h,p->e[i]);
			if(p->e[i].Q==2)		//如果经过了两次筛选，说明成绩被减了5，需要加上
						p->e[i].grade+=5;

		if(p->e[i].Q>1 || p->e[i].enroll!=-1)continue;//经过两次筛选或已被录取，退出录用
			else
				if(p->e[i].Swish!=-1)	//是否有第二志愿
				{
					p->e[i].grade=p->e[i].grade-5;
					p=sort(p);
					i--;	//第一志愿未被录取，总的排序信息表不能往后移动，所以i减1
				}		
		}
	}

	return h;

}

struct hire *init(int b)
{
	struct hire *h;
	h=(struct hire*)malloc(sizeof(struct hire));
	h->m=b;

	return h;
}

struct hire *increase(struct hire *q,struct employee p)
{
	if(p.Q==1)	//经过一轮筛选
	{
		if(q->number[p.Fwish]>q->h[p.Fwish].n) //第一志愿的工种招聘人数未满
		{
			q->h[p.Fwish].e[q->h[p.Fwish].n].num=p.num; //往第一志愿工种后添加
			q->h[p.Fwish].e[q->h[p.Fwish].n].grade=p.grade;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Fwish=p.Fwish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Swish=p.Swish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].enroll=p.Fwish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Q++;
			q->h[p.Fwish].n++;	//录取一个人后该工种人数加1
		}
	}
	
	else 
		if(p.Q==2)//已经过两轮筛选
		{
			if(q->number[p.Swish]>q->h[p.Swish].n)//第二志愿的工种招聘人数未满
			{
				q->h[p.Swish].e[q->h[p.Swish].n].num=p.num; //往第二志愿工种后添加
				q->h[p.Swish].e[q->h[p.Swish].n].grade=p.grade;
				q->h[p.Swish].e[q->h[p.Swish].n].Fwish=p.Fwish;
				q->h[p.Swish].e[q->h[p.Swish].n].Swish=p.Swish;
				q->h[p.Swish].e[q->h[p.Swish].n].enroll=p.Swish;
				q->h[p.Swish].e[q->h[p.Swish].n].Q++;
				q->h[p.Swish].n++;	//录取一个人后该工种人数加1
			}
		}

	return q;	
}

struct Emp *re_sort(struct hire *h,struct Emp *p)
{
	int i,j,k;
    for(i=0;i < p->n;i++)
	{
		for(j=0;j<h->m;j++)
			for(k=0;k<h->h[j].n;k++)
				if(p->e[i].num == h->h[j].e[k].num)			
					p->e[i].enroll=h->h[j].e[k].enroll;	//只需要录取信息
					
				
	}	

	return p;
}
void print(struct Emp *p,struct hire *h)
{
	
	for(int i=0;i<h->m;i++)
		printf("第%d个工种已招%d个人,还剩%d个招满;\n",i,h->h[i].n,h->number[i]-h->h[i].n);
	printf("\n");

	while(1)
	{
		int a;
		printf("请输入想要的操作:1-查询 2-输出 3-退出:");
		scanf("%d",&a);
		printf("\n");
		
		if(a==1)
		{
			int number;
			printf("请输入要查询的编号:");
			scanf("%d",&number);
			for(int i=0;i<p->n && p->e[i].num != number;i++);
			if(p->e[i].num == number)	
			{
				printf("编号为%d的成绩为:%d;\n",number,p->e[i].grade);
				printf("编号为%d的被第%d个工种录取;\n",number,p->e[i].enroll);
				printf("\n");
			}
			else
			{
				printf("没有您要查询的信息;\n");
				printf("\n");
			}
		}

		if(a==2)
		{
			int i;
			printf("以下是已被录取的人的信息(按编号顺序输出):\n");
			for(i=0;i < p->n;i++)
			{
				if(p->e[i].enroll!=-1)	//被录取
				{
					printf("编号为%d的成绩为:%d;\n",i,p->e[i].grade);
					printf("编号为%d的被第%d个工种录取;\n",i,p->e[i].enroll);
				}
			}
			printf("\n");
			printf("以下是未被录取的人的信息(按编号顺序输出):\n");
			for(i=0;i<p->n;i++)
			{
				if(p->e[i].enroll==-1)
				{
					printf("编号为%d的成绩为:%d;\n",i,p->e[i].grade);
				}
			}
			printf("\n");
		}
		if(a==3)
			exit(0);
	}
}

struct Emp *information(int b)
{
	struct Emp *p;
	p=(struct Emp*)malloc(sizeof(struct Emp));
	p->n=0;
	printf("请输入共有多少个应聘者:");
	scanf("%d",&p->n);
	printf("\n");
	printf("提示:请按应聘编号输入应聘者信息;\n");
	
	int i;
	for(i=0;i<p->n;i++)
	{
		p->e[i].num=i;	//编号从0开始
		p->e[i].enroll=-1;	//目前未被录取
		p->e[i].Q=0;	//未经过第一志愿的筛选
		printf("请输入编号为%d的应聘者成绩:",i);
		scanf("%d",&p->e[i].grade);
		if(p->e[i].grade>100 || p->e[i].grade<0)
		{
			printf("请重新输入该应聘者信息,成绩输入错误;\n");
			i--;
			continue;
		}
		printf("请输入编号为%d的应聘者的第一志愿(工种号):",i);
		scanf("%d",&p->e[i].Fwish);
		if(p->e[i].Fwish>=b || p->e[i].Fwish<-1)
		{
			printf("请重新输入该应聘者信息,工种号错误;\n");
			i--;
			continue;
		}
		printf("请输入编号为%d的应聘者的第二志愿(没有请输入-1):",i);
		scanf("%d",&p->e[i].Swish);
		if(p->e[i].Swish>=b || p->e[i].Swish<-1)
		{
			printf("请重新输入该应聘者信息,工种号错误;\n");
			i--;
			continue;
		}
		if(p->e[i].Swish==p->e[i].Fwish)
		{
			printf("第一志愿和第二志愿不能一样,请把第二志愿改为-1;\n");
			i--;
			continue;
		}
	}
	return(p);
}

struct Emp *sort(struct Emp *p)
{
	int i,j,exchange = 1;

    for(i=0;i<p->n-1;i++)
	{
		exchange = 1;
		for(j=0;j<p->n-i-1;j++)
			if(p->e[j+1].grade > p->e[j].grade)
			{ 
				struct employee *c;
				c=(struct employee*)malloc(sizeof(struct employee));

				c->Fwish=p->e[j+1].Fwish;
				c->grade=p->e[j+1].grade;
				c->num=p->e[j+1].num;
				c->Swish=p->e[j+1].Swish;
				c->enroll=p->e[j+1].enroll;
				c->Q=p->e[j+1].Q;

				p->e[j+1].enroll=p->e[j].enroll;
				p->e[j+1].Fwish=p->e[j].Fwish;
				p->e[j+1].Swish=p->e[j].Swish;
				p->e[j+1].grade=p->e[j].grade;
				p->e[j+1].num=p->e[j].num;
				p->e[j+1].Q=p->e[j].Q;

				p->e[j].enroll=c->enroll;
				p->e[j].grade=c->grade;
				p->e[j].Fwish=c->Fwish;
				p->e[j].num=c->num;
				p->e[j].Swish=c->Swish;
				p->e[j].Q=c->Q;

				free(c);
				exchange = 0;		//修改标志位
			}
		if(exchange) break;
	}
	

	return p;
}//按成绩从大到小排序
struct Emp *sort2(struct Emp *p)
{
	int i,j,exchange = 1;

    for(i=0;i<p->n-1;i++)
	{
		exchange = 1;
		for(j=0;j<p->n-i-1;j++)
			if(p->e[j+1].num < p->e[j].num)
			{ 
				struct employee *c;
				c=(struct employee*)malloc(sizeof(struct employee));

				c->Fwish=p->e[j+1].Fwish;
				c->grade=p->e[j+1].grade;
				c->num=p->e[j+1].num;
				c->Swish=p->e[j+1].Swish;
				c->enroll=p->e[j+1].enroll;
				c->Q=p->e[j+1].Q;

				p->e[j+1].enroll=p->e[j].enroll;
				p->e[j+1].Fwish=p->e[j].Fwish;
				p->e[j+1].Swish=p->e[j].Swish;
				p->e[j+1].grade=p->e[j].grade;
				p->e[j+1].num=p->e[j].num;
				p->e[j+1].Q=p->e[j].Q;

				p->e[j].enroll=c->enroll;
				p->e[j].grade=c->grade;
				p->e[j].Fwish=c->Fwish;
				p->e[j].num=c->num;
				p->e[j].Swish=c->Swish;
				p->e[j].Q=c->Q;

				free(c);
				exchange = 0;		//修改标志位
			}
		if(exchange) break;
	}

	return p;
}//按编号从小到大排序

int main()
{
	int i,j,b=0;
	int aa[M];
	
	struct Emp *p,*q;
	struct hire *h;

	printf("请输入共有多少个工种:");
	scanf("%d",&b);
	h=init(b);
	h->m=b;
	
	for(i=0;i<b;i++)
	{
		printf("输入第%d个工种需要招聘的人数:",i);	//工种从0开始
		scanf("%d",&aa[i]);
	}
	h->number=aa;

	for(i=0;i<h->m;i++)
	{
		h->h[i].n=0;
		for(j=0;j<h->number[j];j++)
		{
			h->h[i].e[j].enroll=-1;
			h->h[i].e[j].Q=0;
			h->h[i].e[j].Fwish=0;
			h->h[i].e[j].grade=0;
			h->h[i].e[j].num=0;
			h->h[i].e[j].Swish=0;
		}
	}

	p=information(b);
	q=p;

	p=sort(p);
	h=Luqv(h,p);

	q=sort2(q);
	q=re_sort(h,q);
	print(q,h);
	free(p);
	free(h);
	return 1;
}