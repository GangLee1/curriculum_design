#include"stdio.h"
#include"stdlib.h"
#include"malloc.h"
#define M 50		//MΪ��Ƹ�������������

typedef int Integer;
struct employee
{
	Integer num;
	Integer Fwish;	//��һ־Ը
	Integer Swish;	//�����еڶ�־Ը������û�У�û��Ϊ0
	int grade;
	Integer enroll;	//�Ƿ�¼ȡ����¼ȡ�͸�ֵΪ¼ȡ�Ĺ��ֺţ�����Ϊ-1
	int Q;	//��һ����ǣ������ж��Ѿ���������ɸѡ
};//ӦƸ����Ϣ

struct Emp
{
	int n;	//nΪ�����Ա�(����)��ʵ���ж��ٸ�ӦƸ��
	struct employee e[M];
};//��ӦƸ�߷�װ��������Ƹ��Ϣ��

struct hire
{
	int m;	//ʵ���ж��ٸ�����
	int *number;	//ÿ�������ж�����
	struct Emp h[M];
};//��˳����װ�����ɹ�����Ϣ��

struct hire *Luqv(struct hire *h,struct Emp *p)
{
	int i,l=0;
	int d=1;	//d��ʼֵΪ1��ʹ��Ƹ��Ա��ʱ�����˳�
	struct hire *increase(struct hire *,struct employee );
	struct Emp *sort(struct Emp *);

	for(i=0;i<h->m;i++)l=l+h->number[i];	//m�����ֹ���Ƹ���ٸ���
	printf("\n");
	printf("������Ƹ����Ƹ%d����;\n",l);

	for(i=0;i<p->n && d<=l;i++)	//����Ƹ���������Ѷ�ȫ��ӦƸ�߶�����¼�ô���ʱ�˳�
	{
		if(p->e[i].enroll==-1 && p->e[i].Q<2)	//δ��¼���Ҳ��ܴ���һ��ɸѡ
		{
			if(p->e[i].Q==0)
			{
				p->e[i].Q++;	//һ��ɸѡQ��1
				if(h->number[p->e[i].Fwish] > h->h[p->e[i].Fwish].n)	//��һ־Ը��������δ����
				{
					d++;	//��¼���ٸ��˱�¼ȡ
					p->e[i].enroll=p->e[i].Fwish;				
				}
			}
			else
			{
				if(p->e[i].Swish!=-1 && p->e[i].Q==1)	//�еڶ�־Ը���Ѿ�����һ��ɸѡ
				{
					p->e[i].Q++;
					if(h->number[p->e[i].Swish] > h->h[p->e[i].Swish].n)	//�ڶ�־Ը��������δ����
					{
						d++;
						p->e[i].enroll=p->e[i].Swish;						
					}
				}
			}
			h=increase(h,p->e[i]);
			if(p->e[i].Q==2)		//�������������ɸѡ��˵���ɼ�������5����Ҫ����
						p->e[i].grade+=5;

		if(p->e[i].Q>1 || p->e[i].enroll!=-1)continue;//��������ɸѡ���ѱ�¼ȡ���˳�¼��
			else
				if(p->e[i].Swish!=-1)	//�Ƿ��еڶ�־Ը
				{
					p->e[i].grade=p->e[i].grade-5;
					p=sort(p);
					i--;	//��һ־Ըδ��¼ȡ���ܵ�������Ϣ���������ƶ�������i��1
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
	if(p.Q==1)	//����һ��ɸѡ
	{
		if(q->number[p.Fwish]>q->h[p.Fwish].n) //��һ־Ը�Ĺ�����Ƹ����δ��
		{
			q->h[p.Fwish].e[q->h[p.Fwish].n].num=p.num; //����һ־Ը���ֺ����
			q->h[p.Fwish].e[q->h[p.Fwish].n].grade=p.grade;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Fwish=p.Fwish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Swish=p.Swish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].enroll=p.Fwish;
			q->h[p.Fwish].e[q->h[p.Fwish].n].Q++;
			q->h[p.Fwish].n++;	//¼ȡһ���˺�ù���������1
		}
	}
	
	else 
		if(p.Q==2)//�Ѿ�������ɸѡ
		{
			if(q->number[p.Swish]>q->h[p.Swish].n)//�ڶ�־Ը�Ĺ�����Ƹ����δ��
			{
				q->h[p.Swish].e[q->h[p.Swish].n].num=p.num; //���ڶ�־Ը���ֺ����
				q->h[p.Swish].e[q->h[p.Swish].n].grade=p.grade;
				q->h[p.Swish].e[q->h[p.Swish].n].Fwish=p.Fwish;
				q->h[p.Swish].e[q->h[p.Swish].n].Swish=p.Swish;
				q->h[p.Swish].e[q->h[p.Swish].n].enroll=p.Swish;
				q->h[p.Swish].e[q->h[p.Swish].n].Q++;
				q->h[p.Swish].n++;	//¼ȡһ���˺�ù���������1
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
					p->e[i].enroll=h->h[j].e[k].enroll;	//ֻ��Ҫ¼ȡ��Ϣ
					
				
	}	

	return p;
}
void print(struct Emp *p,struct hire *h)
{
	
	for(int i=0;i<h->m;i++)
		printf("��%d����������%d����,��ʣ%d������;\n",i,h->h[i].n,h->number[i]-h->h[i].n);
	printf("\n");

	while(1)
	{
		int a;
		printf("��������Ҫ�Ĳ���:1-��ѯ 2-��� 3-�˳�:");
		scanf("%d",&a);
		printf("\n");
		
		if(a==1)
		{
			int number;
			printf("������Ҫ��ѯ�ı��:");
			scanf("%d",&number);
			for(int i=0;i<p->n && p->e[i].num != number;i++);
			if(p->e[i].num == number)	
			{
				printf("���Ϊ%d�ĳɼ�Ϊ:%d;\n",number,p->e[i].grade);
				printf("���Ϊ%d�ı���%d������¼ȡ;\n",number,p->e[i].enroll);
				printf("\n");
			}
			else
			{
				printf("û����Ҫ��ѯ����Ϣ;\n");
				printf("\n");
			}
		}

		if(a==2)
		{
			int i;
			printf("�������ѱ�¼ȡ���˵���Ϣ(�����˳�����):\n");
			for(i=0;i < p->n;i++)
			{
				if(p->e[i].enroll!=-1)	//��¼ȡ
				{
					printf("���Ϊ%d�ĳɼ�Ϊ:%d;\n",i,p->e[i].grade);
					printf("���Ϊ%d�ı���%d������¼ȡ;\n",i,p->e[i].enroll);
				}
			}
			printf("\n");
			printf("������δ��¼ȡ���˵���Ϣ(�����˳�����):\n");
			for(i=0;i<p->n;i++)
			{
				if(p->e[i].enroll==-1)
				{
					printf("���Ϊ%d�ĳɼ�Ϊ:%d;\n",i,p->e[i].grade);
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
	printf("�����빲�ж��ٸ�ӦƸ��:");
	scanf("%d",&p->n);
	printf("\n");
	printf("��ʾ:�밴ӦƸ�������ӦƸ����Ϣ;\n");
	
	int i;
	for(i=0;i<p->n;i++)
	{
		p->e[i].num=i;	//��Ŵ�0��ʼ
		p->e[i].enroll=-1;	//Ŀǰδ��¼ȡ
		p->e[i].Q=0;	//δ������һ־Ը��ɸѡ
		printf("��������Ϊ%d��ӦƸ�߳ɼ�:",i);
		scanf("%d",&p->e[i].grade);
		if(p->e[i].grade>100 || p->e[i].grade<0)
		{
			printf("�����������ӦƸ����Ϣ,�ɼ��������;\n");
			i--;
			continue;
		}
		printf("��������Ϊ%d��ӦƸ�ߵĵ�һ־Ը(���ֺ�):",i);
		scanf("%d",&p->e[i].Fwish);
		if(p->e[i].Fwish>=b || p->e[i].Fwish<-1)
		{
			printf("�����������ӦƸ����Ϣ,���ֺŴ���;\n");
			i--;
			continue;
		}
		printf("��������Ϊ%d��ӦƸ�ߵĵڶ�־Ը(û��������-1):",i);
		scanf("%d",&p->e[i].Swish);
		if(p->e[i].Swish>=b || p->e[i].Swish<-1)
		{
			printf("�����������ӦƸ����Ϣ,���ֺŴ���;\n");
			i--;
			continue;
		}
		if(p->e[i].Swish==p->e[i].Fwish)
		{
			printf("��һ־Ը�͵ڶ�־Ը����һ��,��ѵڶ�־Ը��Ϊ-1;\n");
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
				exchange = 0;		//�޸ı�־λ
			}
		if(exchange) break;
	}
	

	return p;
}//���ɼ��Ӵ�С����
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
				exchange = 0;		//�޸ı�־λ
			}
		if(exchange) break;
	}

	return p;
}//����Ŵ�С��������

int main()
{
	int i,j,b=0;
	int aa[M];
	
	struct Emp *p,*q;
	struct hire *h;

	printf("�����빲�ж��ٸ�����:");
	scanf("%d",&b);
	h=init(b);
	h->m=b;
	
	for(i=0;i<b;i++)
	{
		printf("�����%d��������Ҫ��Ƹ������:",i);	//���ִ�0��ʼ
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