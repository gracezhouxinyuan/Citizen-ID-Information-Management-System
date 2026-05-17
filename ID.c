#include <stdio.h>
#include <string.h>
#define N 100
struct birth
{
    int     year;
    int     month;
    int     day;
};
struct person
{
    char    ID[19];
    char    name[20];
    struct  birth  birthday;
    int flag;//校验位是否正确, 1代表正确，0代表错误
};

int read(struct person p[])
{
   
}

int checkID(char *ID)
{

}

struct birth get_birth(char *ID)
{

}

void get_all_person(struct person p[], int n)
{

}

void display_person(struct person p[], int n, int flag)
{

}

int birth_cmp(struct birth birth1, struct birth birth2)
{

}

void birth_sort(struct person p[], int n)
{

}

int search(struct person p[], int n, char *name)
{
    int i;
    int cnt=0;
    printf("\n同名且身份证校验正确的信息如下:\n");
    printf("%-20s %-12s %-12s\n", "ID", "Name", "Birthday");
    printf("----------------------------------------------------\n");
    for (i=0;i<n;i++)
    {
        if (p[i].flag==1&&strcmp(p[i].name, name)==0)
        {
            printf("%-20s %-12s %04d-%02d-%02d\n",p[i].ID, p[i].name,p[i].birthday.year, p[i].birthday.month, p[i].birthday.day);
            cnt++;
        }
    }
    printf("\n名为%s的人有%d个\n", name, cnt);
    return cnt;
}

void save(struct person p[], int n)
{

}

int prompt(void)
{
    int cmd=0;
    printf("-------------------\n");
    printf("1.  公民信息显示（不含错误信息）\n");
    printf("2.  错误信息查询\n");
    printf("3.  按出生日期排序（不含错误信息）\n");
    printf("4.  重名查询（不含错误信息）\n");
    printf("0.  退出\n");
    printf("-------------------\n");
    printf("请输入你的选择(0-4):");
    scanf("%d", &cmd);
    return cmd;
}

int main(void)
{
    struct person p[N];
    int cmd, n;
    char*name;
    name=(char*)malloc(20*sizeof(char));
    n=read(p);
    get_all_person(p, n);
    save(p, n);
    while (1)
    {   cmd=prompt();
        if (cmd==0)
        {
            printf("程序结束。\n");
            break;
        }
        if (cmd==1)
        {
            display_person(p, n, 1);
        }
        else if (cmd==2)
        {
            display_person(p, n, 0);
        }
        else if (cmd==3)
        {
            birth_sort(p, n);
            display_person(p, n, 1);
        }
        else if (cmd==4)
        {
            printf("请输入要查询的姓名:");
            scanf("%19s", name);
            search(p, n, name);
        }
        else
        {
            printf("输入无效，请重新输入。\n");
        }
    } 
    free(name);
    return 0;
}
