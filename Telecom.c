#include<stdio.h>
#include<string.h>

struct customer
{
    char number[20];
    char name[50];
    char pass[22];
    int pay;
};

void list_records();
void modify_records();
void delete_records();
void search_records();
void paybill();
int login_ad();
int login_user();
char get;
void create();
struct customer q;


int main()
{
    int ok=1;
    system("cls");
    system("cls");
    printf("\n\n\t\t\tWELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM");
    shefat:
    printf("\n1. Admin\n2. User\n3. Exit");
    printf("\nEnter the choice: ");
    int n;
    scanf("%d",&n);
    if(n==2)
    {
        printf("Press 1 for login: \n");
        printf("press 2 for create account: \n");
        int c;
        scanf("%d",&c);
        if(c==1){
                if(login_user())
                {
                        printf("Press 1 for see your information: \n");
                        printf("press 2 for pay bill: \n");
                        int k;
                        scanf("%d",&k);
                        if(k==1)
                        {
                             printf("Name : %s\nAccount payable: %d\nContact: %s\n\n",q.name,q.pay,q.number);
                             printf("Press 1 for back to main menu\n");
                             int ch;
                             fflush(stdin);
                             scanf("%d",&ch);
                             goto shefat;
                        }
                        else {
                              paybill();
                              goto shefat;
                        }
                }
                else {
                    printf("Unsuccessful login!!!\n");
                    while(1){
                    printf("Press 1 for back to main menu\n");
                    int k;
                    scanf("%d",&k);
                    if(k==1){
                        goto shefat;
                    }
                    printf("Select a vaild number!!!\n");
                }
                }
        }
        else {
            create();
            goto shefat;
        }
   }
   else if(n==1)
{
    if(login_ad()==1)
        { printf("\n\n  TELECOM BILLING SYSTEM  ");
        while (1)
        {
            printf("\n\n  1 : List Of Records");
            printf("\n\n  2 : Modify Records.");
            printf("\n\n  3 : Search Records.");
            printf("\n\n  4 : Delete Records.\n\n \xDB\xDB 5 : Exit\n");
            printf("Enter Your Choice:-");
            int c;
            scanf("%d",&c);
            if(c==1){
                list_records();
            }
            else if(c==2){
              modify_records();
            }
            else if(c==3){
                search_records();
            }
            else if(c==4){
                delete_records();
            }
            else {
                return 1;
            }
        }
       }
       else {
             printf("Invalid login id or passwords\n");
             goto shefat;
       }
    }
    else return 1;
}
void create(){
    FILE *f;
    f=fopen("acc.txt","ab");
    printf("Enter Name : ");
    struct customer p;
    fflush(stdin);
    scanf("%s",p.name);
    fflush(stdin);
     printf("Enter Phone number: ");
    scanf("%s",p.number);
    fflush(stdin);
     printf("Enter Pass : ");
    scanf("%s",p.pass);
    p.pay=0;
    fwrite(&p,sizeof(p),1,f);
    fclose(f);
    printf("Created successfully\n");
    system("cls");
}
void list_records()
{
    FILE *f;
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    for(int i=0;i<=200;i++){
           int ok=0;
           for(int j=0;j<strlen(p[i].number);j++){
              if(p[i].number[j]>='0' &&  p[i].number[j]<='9')ok=0;
                else ok=1;
           }
           if(!ok && strlen(p[i].number)==11)
           printf("\n\nName: %s\nPhone: %s\naccount payable: %d\n",p[i].name,p[i].number,p[i].pay);
    }
    fclose(f);
}

void delete_records()
{
    FILE *f;
    printf("Enter Contact number: ");
    char name1[22];
    fflush(stdin);
    scanf("%s",name1);
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    fclose(f);
    f=fopen("acc.txt","wb");
    for(int i=0;i<200;i++){
        int x=strcmp(p[i].number,name1);
        if(x!=0){
           fwrite(&p[i],sizeof(p[i]),1,f);
        }
    }
    fclose(f);
    system("cls");
}

void search_records()
{
    FILE *f;
    printf("Enter Contact_number: ");
    char name1[22];
    fflush(stdin);
    scanf("%s",name1);
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    fclose(f);
    for(int i=0;i<200;i++){
        int x=strcmp(p[i].number,name1);
        if(x==0){
           printf("Name : %s\nContact_number: %s\nAccount payable: %d\n",p[i].name,p[i].number,p[i].pay);
        }
    }
    fclose(f);
}
void modify_records()
{
    FILE *f;
    printf("Enter Contact Number: ");
    char name1[22];
    fflush(stdin);
    scanf("%s",name1);
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    fclose(f);
    f=fopen("acc.txt","wb");
    for(int i=0;i<200;i++){
        int x=strcmp(p[i].number,name1);
        if(x==0){
                printf("Enter bill to be paid in this month\n");
                int a;
                scanf("%d",&a);
                p[i].pay+=a;
        }
       fwrite(&p[i],sizeof(p[i]),1,f);

    }
    fclose(f);
        system("cls");

}
void paybill()
{
    FILE *f;
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    if(f==NULL){
        printf("The user list is empty!!!");
    }
    fclose(f);
    f=fopen("acc.txt","wb");
    int ok=0;
    for(int i=0;i<200;i++){
        int x=strcmp(p[i].name,q.name);
        int y=strcmp(p[i].pass,q.pass);
        if(x==0 && y==0  && ok==0){
            printf("Enter amount: ");
            int amn;
            fflush(stdin);
            ok=1;
            scanf("%d",&amn);
            p[i].pay-=amn;
        }
        fwrite(&p[i],sizeof(p[i]),1,f);
    }
    fclose(f);
        system("cls");

}
int login_ad()
{
    char password[10],username[10];
    char user[10]="user";
    char pass[10]="pass";
    while(1)
    {

        printf("\n  **************************  LOGIN FORM  **************************  ");
        printf(" \n                       ENTER USERNAME:-");
        fflush(stdin);
        scanf("%s", &username);
        printf(" \n                       ENTER PASSWORD:-");
        fflush(stdin);
        scanf("%s",password);
        int x=strcmp(user,username);
        int y=strcmp(password,pass);
        if(x==0 && y==0){
            return 1;
        }
        else {
            printf("Invalid username or passwords\n");
        }
    }
    return 0;

}
int login_user(){

    FILE *f;
    printf("Enter username: ");
    char name1[22],passw[22];
    fflush(stdin);
    scanf("%s",name1);
    printf("Enter passwords: ");
        fflush(stdin);
    scanf("%s",passw);
    f=fopen("acc.txt","rb");
    struct customer p[200];
    fread(p,sizeof(struct customer),200,f);
    for(int i=0;i<200;i++){
        int x=strcmp(p[i].name,name1);
        int y=strcmp(p[i].pass,passw);
        if(x==0 && y==0){
            q=p[i];
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}
