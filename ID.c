#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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
    FILE *fp;
    int n=0;
    fp = fopen("person.txt", "r");
    if (fp == NULL)
    {
        printf("文件打开失败！\n");
        return 0;
    }
    while (n < N && fscanf(fp, "%18s%19s", p[n].ID, p[n].name) == 2)
    {
        n++;
    }
    fclose(fp);
    return n;  
}

int checkID(char *ID)
{     if (strlen(ID) != 18)
        return 0;   
    int weight[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
    char checkCode[] = "10X98765432";
    int sum = 0;   
    int i;
    for (i = 0; i < 17; i++)
    {
        if (!isdigit((unsigned char)ID[i]))
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
struct birth b;
     char year_str[5], month_str[3], day_str[3];
     strncpy(year_str, ID + 6, 4);
     year_str[4] = '\0';
     strncpy(month_str, ID + 10, 2);
     month_str[2] = '\0';
     strncpy(day_str, ID + 12, 2);
     day_str[2] = '\0';
     b.year = atoi(year_str);
     b.month = atoi(month_str);
     b.day = atoi(day_str);
     return b;
}

void get_all_person(struct person p[], int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        p[i].birthday = get_birth(p[i].ID);
        p[i].flag = checkID(p[i].ID);
    }
}

void display_person(struct person p[], int n, int flag)
{
    int i;
    int count = 0;
    printf("\n%-20s %-12s %-20s %-10s\n", "身份证", "姓名", "出生年月", "校验位");

    for (i = 0; i < n; i++)
    {
        if (p[i].flag == flag)
        {
            printf("%-10s ", p[i].name);
            printf("%-18s ", p[i].ID);
            printf("%4d年%02d月%02d日 ",
                   p[i].birthday.year,
                   p[i].birthday.month,
                   p[i].birthday.day);

            if (flag == 1)
                printf(" 正确\n");
            else
                printf(" 错误\n");

            count++;
        }
    }

    if (flag == 1)
        printf("正确信息人数：%d\n", count);
    else
        printf("错误信息人数：%d\n", count);
}

int birth_cmp(struct birth birth1, struct birth birth2)
{
if (birth1.year != birth2.year)
         return birth1.year - birth2.year;
     if (birth1.month != birth2.month)
         return birth1.month - birth2.month;
     return birth1.day - birth2.day;
}

void birth_sort(struct person p[], int n) 
    {
    struct person temp;
    int i,j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (birth_cmp(p[j].birthday, p[j + 1].birthday) > 0) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int search(struct person p[], int n, char *name)
{
    int i;
    int cnt=0;
    for (i=0;i<n;i++)
    {
        if (p[i].flag==1&&strcmp(p[i].name, name)==0)
        {
            cnt++;
        }
    }
    printf("\n名为%s的人有%d个\n", name, cnt);
    return cnt;
}

void save(struct person p[], int n) {
    FILE *fp = fopen("person_checked.txt", "w");
    if (fp == NULL) {
        printf("无法创建或写入 person_checked.txt 文件！\n");
        return;
    }
    int i;
    for (i = 0; i < n; i++) {
        if (p[i].flag == 1) {
            fprintf(fp, "%-18s %-10s %d %d %d\n", 
                    p[i].ID, 
                    p[i].name, 
                    p[i].birthday.year, 
                    p[i].birthday.month, 
                    p[i].birthday.day);
        }
    }
    fclose(fp);
    printf("已成功将身份证号码正确的数据保存至 person_checked.txt 文件中。\n");
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
