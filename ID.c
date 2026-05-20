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
{    FILE *fp = fopen("person.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return 0;
    }
    int n = 0;
    while (fscanf(fp, "%s %s", p[n].ID, p[n].name) != EOF && n < N)
    {
        n++;
    }
    fclose(fp);
    return n;  
}

int checkID(char *ID)
{     if (strlen(ID) != 18)
        return 0;   
    int weight[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2}；
    char checkCode[] = "10X98765432";
    int sum = 0;   
    for (int i = 0; i < 17; i++)
    {
        if (!isdigit(ID[i]))
            return 0;   
        sum += (ID[i] - '0') * weight[i];
    }
    int mod = sum % 11;
    char last = ID[17];   
    if (last >= 'a' && last <= 'z')
        last -= 32;   
    return (last == checkCode[mod]) ? 1 : 0;
}

struct birth get_birth(char *ID)
{

}

void get_all_person（struct person p[], int n）get_all_person(struct person p[], int n)
{
int i;
    int count = 0;

    // 表头
    printf("姓名\t\t身份证\t\t\t出生年月\t\t校验位\n");
    printf("------------------------------------------------------------\n");

    for (i = 0; i < n; i++)
    {
        // 只显示指定类型（正确/错误）
        if (p[i].flag == flag)
        {
            printf("%-10s", p[i].name);
            printf("%-18s", p[i].ID);
            printf("%4d年%02d月%02d日\t",
                   p[i].birthday.year,
                   p[i].birthday.month,
                   p[i].birthday.day);

            if (flag == 1)
                printf("正确\n");
            else
                printf("错误\n");

            count++;
        }
    }

    if (flag == 1)
        printf("正确信息人数：%d\n", count);
    else
        printf("错误信息人数：%d\n", count);
}

void display_person(struct person p[], int n, int flag)
{
int i;
    for (i = 0; i < n; i++)
    ｛
        p[i].birthday = get_birth(p[i].ID)
        p[i].flag = checkID(p[i].ID);
    }
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
