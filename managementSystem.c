#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>
int man=0;//����һ��ʼ����Ϊ�� 
struct address
{
	char adname[20];
	char adnum[20];
	int num;
	char e[20];
	struct  address *next;	//nextָ�� ָ��struct address���͵ı��� 
 } ;
 
 
 //���溯��	
 void Save(struct address *head)
 {
 	FILE *fp;		//����һ���ļ�ָ�룬����fopen�ķ���ֵ���������Ĺر��ļ�
 	struct address *t;		//����һ��ָ�룬��ͷ��β����һ�鵥�������ļ���д��
 	if((fp=fopen("filetext.txt","w"))==NULL)		//д���ļ� 
 	{
 		printf("Open file failure!");
 		exit(0);
	 }
	t=head->next;		//��ֵ��t��ͷ��ʼ
	while(t!=NULL)		//tΪ���������
	{
		fprintf(fp,"%s %s %d %s\n",t->adname,t->adnum,t->num,t->e);//д���ļ� 
		t=t->next;	//���� 
	 } 
	 fclose(fp);		//�ر��ļ�
	 printf("Save successfully.");
	 getchar();
 }
 
  
 //���ӹ���
struct address * Add_List(struct address *head)
 {
 	int i=0,k=0; //�жϱ�־
	char flag;   //��ű�־ 
 	struct address *p1,*p2,*p3,*add;//add����������ӵ���Ϣ�ģ�p1��p2��������ʱ�ƶ���
 	p1=p2=head;
 	add=(struct address*)malloc(sizeof(struct address));
 	while(p1!=NULL)
 	{
 		p2=p1;
 		p1=p1->next; 		//��p2�Ƶ�����棬p1����� 
	 }
	 printf("Enter the name:\n");
	 scanf("%s",add->adname);
	 printf("Enter the number:\n");
	 scanf("%s",add->adnum);
	 printf("Enter the number of type:\n");
	 printf("1.�칫��  2.������  3.������\n");
	 scanf("%d",&add->num);
	 printf("Enter the e-mail:\n");
	 scanf("%s",add->e); 
	 p3=head;//��ͷ����
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
		if(p1==head)//ͷ���Ϊ�� 
		{
			head=add;
		}
		else 
			p2->next=add;
		free(p1);
		printf("Add successfully.Wanna save it?(Y/N)\n");
		getchar();//�س���
		scanf("%c",&flag);
		if(flag=='y'||flag=='Y')
		{
			man++;
			Save(head);//���ô洢���� 
		 } 
		else
		{
			printf("Press any key to go back to menu.\n");
			getchar();
		}
	}
	return (head);
  }
 
//ɾ������
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
 	
 //�޸ĺ���
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
			break;//��ǰ����ѭ�� 
		}
		p1=p1->next;
	}
	if(p1!=NULL&&i==1)//���������� 
	{
		system("CLS");//���� 
		printf("Here's the contact you wanna revice:\n");
		printf("************************************\n\n");
		printf("Name : %s\n",p1->adname);
		printf("Number : %s\n",p1->adnum);
		if(p1->num==1)
			printf("Type : �칫��\n");
		else if(p1->num==2)
			printf("Type : ������\n");
		else if(p1->num==3)
			printf("Type : ������\n");
		else 
			printf("Unknown type\n");
		printf("E-mail : %s\n\n",p1->e);
		printf("*************************************\n\n");
		printf("Enter the number:\n");
		scanf("%s",p1->adnum);
		printf("Select the type of contact:\n");
		printf("1.�칫�� 2.������ 3.������\n");
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
 
 //��������
struct address * CreateList()
{
	struct address *pointer,*head,*q;	//headָ��Ϊͷ��㣬���ҵ������Ψһ����
	//pָ������ָ��������Ľ�㣬qָ������ָ��β���

	FILE *fp;
	pointer=(struct address *)malloc(sizeof(struct address));	//pָ��ָ���¿��ٵĽ���ڴ�
	head=pointer;	//����ͷ����ڴ�
	q=pointer;		//����β����ڴ�	q����ָ��β���
	q->next=NULL;/*��־����Ľ��� β�ڵ���ص���next��Ա��ֵΪNULL��
	�������һ���ڵ㣬��Ϊ��������ı�־��NULL��һ�����ų�����ʾֵΪ0�ĵ�ַ */
	fp=fopen("filetext.txt","r");		//���ļ� 
	if(fp==NULL)
	{
		printf("open file failure!");
		exit(0);
	}
	int i=0;
	while(1)
	{
		pointer=(struct address *)malloc(sizeof(struct address));	//pָ���¿��ٵĽ���ڴ�
		if(~fscanf(fp, "%s%s%d%s", pointer->adname,pointer->adnum,&pointer->num,pointer->e))
			man++;
		else
		{
			free(pointer); 
			break;
		 }
		q->next=pointer;	//���½��ҵ�β���֮��
		q=q->next;		//qָ��ָ���µ�β��� 
	 } 
	 q->next=NULL;		//��־����Ľ���
	 fclose(fp);
	 return head; 
 } 
 
 //��������ڵ�����(��ѯ������ 
void Print_List(struct address *head)
 {
 	struct address *pointer;
 	pointer=head->next;	//���������ݵĽ��
 	int choice1;
 	system("CLS");
 	printf("*******************************************\n");
 	printf("\n");
 	printf("Select the type of contacts you want:\n");
 	printf("1.�칫�� 2.������ 3.������.\n");
 	scanf("%d",&choice1);
 	getchar();
	while(pointer!=NULL)
	{
		if(pointer->num==choice1&&choice1==1)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("�칫�� ");
			printf("%s\n",pointer->e);
		}
		if(pointer->num==choice1&&choice1==2)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("������ ");
			printf("%s\n",pointer->e);
		}
		if(pointer->num==choice1&&choice1==3)
		{
			printf("%s ",pointer->adname);
			printf("%s ",pointer->adnum);
			printf("������ ");
			printf("%s\n",pointer->e);
		}
		pointer=pointer->next;	//ָ����һ����� 
	 }  
	 printf("\n");
	 printf("*******************************************\n");
  } 

//���溯�� 
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
 	printf("                          Limited  : 15    \n");//ͨѶ¼���� 
 	printf("                          Courrent : %d\n",man);//ͨѶ¼�������� 
 	printf("\n");
  	printf("********************************************\n");
 }

 int main()
  {
  	int choice;
  	struct address *head;
  	head=(struct address *)malloc(sizeof(struct address)); 	//����ռ� 
  	head=CreateList();
 	while(1)
 	{
 		face();//���� 
 		printf("Enter the number of function you want:");
 		scanf("%d",&choice);
 		getchar();//���ջس��� 
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

