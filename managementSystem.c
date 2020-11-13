#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
int man=0;//假设一开始人数为零 
struct address
{
	char adname[20];
	char adnum[20];
	int num;
	char e[20];
	struct  address *next;	//next指针 指向struct address类型的变量 
 } ;
 
 
 //保存函数	
 void Save(struct address *head)
 {
 	FILE *fp;		//定义一个文件指针，接收fopen的返回值，用于最后的关闭文件
 	struct address *t;		//定义一个指针，从头到尾遍历一遍单链表，向文件中写入
 	if((fp=fopen("filetext.txt","w"))==NULL)		//写入文件 
 	{
 		printf("Open file failure!");
 		exit(0);
	 }
	t=head->next;		//赋值给t从头开始
	while(t!=NULL)		//t为空链表结束
	{
		fprintf(fp,"%s %s %d %s\n",t->adname,t->adnum,t->num,t->e);//写入文件 
		t=t->next;	//后移 
	 } 
	 fclose(fp);		//关闭文件
	 printf("Save successfully.");
	 getchar();
 }
 
  
 //增加功能
struct address * Add_List(struct address *head)
 {
 	int i=0,k=0; //判断标志
	char flag;   //存放标志 
 	struct address *p1,*p2,*p3,*add;//add是用来放添加的信息的，p1，p2是用来临时移动的
 	p1=p2=head;
 	add=(struct address*)malloc(sizeof(struct address));
 	while(p1!=NULL)
 	{
 		p2=p1;
 		p1=p1->next; 		//把p2移到最后面，p1在最后 
	 }
	 printf("Enter the name:\n");
	 scanf("%s",add->adname);
	 printf("Enter the number:\n");
	 scanf("%s",add->adnum);
	 printf("Enter the number of type:\n");
	 printf("1.办公类  2.个人类  3.商务类\n");
	 scanf("%d",&add->num);
	 printf("Enter the e-mail:\n");
	 scanf("%s",add->e); 
	 p3=head;//从头遍历
	 while(p3!=NULL)
	 {
	 	if(strcmp(add->adname,p3->adname)==0)
	 	{
	 		free(add);
	 		printf("Contact already exists.\n");
	 		i=1; 
	 		printf("Press any key to go back to menu.\n");
	 		getch();
	 		break;
		 }
		if((strcmp(add->adname,p3->adname))&&(strcmp(add->adnum,p3->adnum)))
		 {
		 	i=0;
		 	break;
		 }
		 p3=p3->next;
	  } 
	if(i==0)
	{
		add->next=NULL;
		if(p1==head)//头结点为空 
		{
			head=add;
		}
		else 
			p2->next=add;
		free(p1);
		printf("Add successfully.Wanna save it?(Y/N)\n");
		getchar();//回车键
		scanf("%c",&flag);
		if(flag=='y'||flag=='Y')
		{
			man++;
			Save(head);//调用存储函数 
		 } 
		else
		{
			printf("Press any key to go back to menu.\n");
			getchar();
		}
	}
	return (head);
  }
 
//删除函数
struct address * Delete_List(struct address *head)
{
	char flag;
	char delname[20];
	int i=0;
	struct address *p1,*p2;
	p1=p2=head;
	printf("Please enter the name:\n");
	scanf("%s",delname);
	while(p1!=NULL)
	{
		if(strcmp(p1->adname,delname)==0)
		{
			i=1;
			break;
		}
		p2=p1; 
		p1=p1->next;
	}
	if(p1!=NULL&&i==1)
	{
		p2->next=p1->next;
	}
	else {
		printf("Could not find the contact you wanna delete.\n");
		getchar();
		return NULL; 
	}
	printf("Delete successfully!Wanna save(Y/N).\n");
	getchar();
	scanf("%c",&flag);
	if(flag=='y'||flag=='Y')
	{
		man--;
		Save(head);
	}
	else
	{
		getchar();
	}
	return head;
	
 } 	 
 	
 //修改函数
struct address * Revice_List(struct address *head)
{
	char flag;
	int i=0;
	char adname1[20];
	struct address *p1,*p2;
	p1=p2=head;
	printf("Enter the name :\n");
	scanf("%s",adname1);
	while(p1!=NULL)
	{
		if(strcmp(p1->adname,adname1)==0)
		{
			i=1;
			break;//提前跳出循环 
		}
		p1=p1->next;
	}
	if(p1!=NULL&&i==1)//尚在链表中 
	{
		system("CLS");//清屏 
		printf("Here's the contact you wanna revice:\n");
		printf("************************************\n\n");
		printf("Name : %s\n",p1->adname);
		printf("Number : %s\n",p1->adnum);
		if(p1->num==1)
			printf("Type : 办公类\n");
		else if(p1->num==2)
			printf("Type : 个人类\n");
		else if(p1->num==3)
			printf("Type : 商务类\n");
		else 
			printf("Unknown type\n");
		printf("E-mail : %s\n\n",p1->e);
		printf("*************************************\n\n");
		printf("Enter the number:\n");
		scanf("%s",p1->adnum);
		printf("Select the type of contact:\n");
		printf("1.办公类 2.个人类 3.商务类\n");
		scanf("%d",&p1->num);
		printf("Enter the e-mail:\n");
		scanf("%s",p1->e);
		getchar();	
		printf("Revice successfully!.Wanna save(Y/N)?\n");
		scanf("%c",&flag);
			
		if(flag=='Y'||flag=='y')
			Save(head);
	}
	if(i==0)
	{
		printf("Contact doesn't exist.Please check the name.\n");
		getchar();
	}
	return (head);
 }
 
 //创建链表
struct address * CreateList()
{
	struct address *pointer,*head,*q;	//head指针为头结点，是找到链表的唯一依据
	//p指针总是指向新申请的结点，q指针总是指向尾结点

	FILE *fp;
	pointer=(struct address *)malloc(sizeof(struct address));	//p指针指向新开辟的结点内存
	head=pointer;	//开辟头结点内存
	q=pointer;		//开辟尾结点内存	q总是指向尾结点
	q->next=NULL;/*标志链表的结束 尾节点的特点是next成员的值为NULL，
	它是最后一个节点，作为链表结束的标志，NULL是一个符号常量表示值为0的地址 */
	fp=fopen("filetext.txt","r");		//打开文件 
	if(fp==NULL)
	{
		printf("open file failure!");
		exit(0);
	}
	int i=0;
	while(1)
	{
		pointer=(struct address *)malloc(sizeof(struct address));	//p指向新开辟的结点内存
		if(~fscanf(fp, "%s%s%d%s", pointer->adname,pointer->adnum,&pointer->num,pointer->e))
			man++;
		else
		{
			free(pointer); 
			break;
		 }
		q->next=pointer;	//把新结点挂到尾结点之后
		q=q->next;		//q指针指向新的尾结点 
	 } 
	 q->next=NULL;		//标志链表的结束
	 fclose(fp);
	 return head; 
 } 
 
 //输出链表内的数据(查询函数） 
void Print_List(struct address *head)
 {
 	struct address *pointer;
 	pointer=head->next;	//跳过无数据的结点
 	int choice1;
 	system("CLS");
 	printf("*******************************************\n");
 	printf("\n");
 	printf("Select the type of contacts you want:\n");
 	printf("1.办公类 2.个人类 3.商务类.\n");
 	scanf("%d",&choice1);
 	getchar();
	while(pointer!=NULL)
	{
		if(pointer->num==choice1&&choice1==1)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("办公类 ");
			printf("%s\n",pointer->e);
		}
		if(pointer->num==choice1&&choice1==2)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("个人类 ");
			printf("%s\n",pointer->e);
		}
		if(pointer->num==choice1&&choice1==3)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("商务类 ");
			printf("%s\n",pointer->e);
		}
		pointer=pointer->next;	//指向下一个结点 
	 }  
	 printf("\n");
	 printf("*******************************************\n");
  } 

//界面函数 
 void face() 
 {
 	printf("*******************************************\n");
 	printf("\n");
 	printf("    Welcome to use Gray's Address List     \n");
  	printf("       Here's the Function List:           \n");
  	printf("\n");   
 	printf("1--->Check                                 \n");
 	printf("2--->Add                                   \n");
 	printf("3--->Revise                                \n");
 	printf("4--->Delete                                \n");
 	printf("5--->Eixt                                  \n");
 	printf("                          Limited  : 15    \n");//通讯录上限 
 	printf("                          Courrent : %d\n",man);//通讯录现有人数 
 	printf("\n");
  	printf("********************************************\n");
 }

 int main()
  {
  	int choice;
  	struct address *head;
  	head=(struct address *)malloc(sizeof(struct address)); 	//申请空间 
  	head=CreateList();
 	while(1)
 	{
 		face();//界面 
 		printf("Enter the number of function you want:");
 		scanf("%d",&choice);
 		getchar();//吸收回车键 
 		switch(choice)
   	 {
  		case 1:
  			Print_List(head);
  			break;
  		case 2:
  			if(man<15)
  			{
  				head=Add_List(head);
			}
  			else
  				printf("Address List is full.\n");
  			break;
 		case 3:
  			head=Revice_List(head);
  			break;
  		case 4:
  			head=Delete_List(head);
  			break;
  		case 5:
  			exit(0);
  			break;
  		default:printf("Error.\n");
 		
	 }
	 printf("Press ENTER to go back to menu.\n");
	 getchar();
	 system("CLS");
	}
  	return 0;
   }

