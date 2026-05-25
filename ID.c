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
    int weight[17] = {7,9,10,5,8,4,2,1,6,3,7,9,10,5,8,4,2};
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
if (birth1.year != birth2.year)
         return birth1.year - birth2.year;
     if (birth1.month != birth2.month)
         return birth1.month - birth2.month;
     return birth1.day - birth2.day;
}

void birth_sort(struct person p[], int n)
{
    struct person temp;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (p[j].flag == 1 && p[j+1].flag == 1)
            {
                if (birth_cmp(p[j].birthday, p[j+1].birthday) > 0)
                {
                    temp = p[j];
                    p[j] = p[j+1];
                    p[j+1] = temp;
                }
            }
            else if (p[j].flag == 0 && p[j+1].flag == 1)
            {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
    printf("按出生日期排序完成！\n");

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
    FILE *fp = fopen("person_processed.txt", "w");
    if (fp == NULL)
    {
        printf("保存文件失败！无法创建备份文件。\n");
        return;
    }
    
    fprintf(fp, "姓名\t\t身份证号\t\t出生日期\t\t校验状态\n");
    fprintf(fp, "---------------------------------------------------------\n");
    
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%-10s\t%-18s\t%04d-%02d-%02d\t%s\n",
                p[i].name,
                p[i].ID,
                p[i].birthday.year,
                p[i].birthday.month,
                p[i].birthday.day,
                p[i].flag == 1 ? "校验正确" : "校验错误");
    }
    fclose(fp);   文件关闭(fp);
    printf("系统初始化：已成功将格式化数据备份至 person_processed.txt\n");

}

int prompt(void)   int提示(空白)
{
    int cmd=0;
    printf("-------------------\n");
    printf("1.  公民信息显示（不含错误信息）\n");
    printf("2.  错误信息查询\n");   printf("2. Error Information Inquiry\n");
    printf("3.  按出生日期排序（不含错误信息）\n");
    printf("4.  重名查询（不含错误信息）\n");
    printf("0.  退出\n");   printf("0.  退出\n");
    printf("-------------------\n");
    printf("请输入你的选择(0-4):");
    scanf("%d", &cmd);   scanf("%d", &cmd);
    return cmd;   返回cmd;
}

int main(void)   int主要(空白)
{
    struct person p[N];   struct   结构体 person p[N]；
    int cmd, n;   Int cmd, n；
    char*name;   char *名称;
    name=(char*)malloc(20*sizeof(char));
    n=read(p);   n =阅读(p);
    get_all_person(p, n);   获取所有人员(p, n)；
    save   保存(p, n);   保存(p, n);
    while (1)   而(1)
    {   cmd=prompt();   迅速将cmd = ();
        if (cmd==0)   如果(cmd = = 0)
        {
            printf("程序结束。\n");   printf("程序结束。\n");
            break;   打破;
        }
        if (cmd==1)   如果(cmd = = 1)
        {
            display_person(p, n, 1);   显示人物(p, n， 1)；
        }
        else if (cmd==2)   否则if   如果 （cmd==2）
        {
            display_person(p, n, 0);   显示人物(p, n， 0)；
        }
        else if (cmd==3)   否则if   如果 （cmd==3）
        {
            birth_sort(p, n);
            display_person(p, n, 1);   显示人物(p, n， 1)；
        }
        else if (cmd==4)   否则if   如果 （cmd==4）
        {
            printf("请输入要查询的姓名:");
            scanf("%19s", name);   scanf("%19s", name);
            search(p, n, name);   搜索（p, n, name）；
        }
        else   其他
        {
            printf("输入无效，请重新输入。\n");
        }
    } 
    free(name);   免费(名称);
    return 0;   返回0;
}
