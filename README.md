# Citizen-ID-Information-Management-System
## 01 项目介绍
本项目是一个基于 C 语言实现的“公民身份证信息管理系统”。

程序从 `person.txt` 读取公民身份证号与姓名，完成身份证校验、出生日期提取、信息展示、出生日期排序、重名查询，并将校验通过的数据保存到 `person_checked.txt`。
## 02 核心函数说明
1. `int read(struct person p[]);`
   功能：从 `person.txt` 读取公民信息到结构体数组 `p`，返回读取到的记录数。

2. `int checkID(char *ID);`
   功能：校验 18 位身份证号是否有效；有效返回 `1`，无效返回 `0`。

3. `struct birth get_birth(char *ID);`
   功能：从身份证号中提取出生年、月、日并返回 `birth` 结构体。

4. `void get_all_person(struct person p[], int n);`
   功能：遍历 `p` 中前 `n` 条记录，补全每条记录的出生日期，并写入校验结果 `flag`。

5. `void display_person(struct person p[], int n, int flag);`
   功能：按 `flag` 显示信息。

- `flag == 1`：显示校验正确的信息及人数
- `flag == 0`：显示校验错误的信息及人数

6. `int birth_cmp(struct birth birth1, struct birth birth2);`
   功能：比较两个生日大小。

- `birth1` 晚于 `birth2`：返回正数
- 相等：返回 `0`
- `birth1` 早于 `birth2`：返回负数

7. `void birth_sort(struct person p[], int n);`
   功能：按出生日期排序（年龄从大到小，即出生早的在前）。

8. `int search(struct person p[], int n, char *name);`
   功能：在 `p` 中查询与 `name` 同名且校验正确的人数，并输出对应记录。

9. `void save(struct person p[], int n);`
   功能：将校验正确的记录（身份证号、姓名、出生年月日）写入 `person_checked.txt`。

10. `int prompt(void);`
    功能：输出菜单并返回用户输入的功能编号。

11. `int main(void);`
    功能：主控流程，负责调用以上函数完成系统运行。
## 03 项目目录结构
下载后推荐保持如下结构：
```text
project-root/
├── ID.c
└── person.txt
```
程序运行后会在同级目录生成：
```text
person_checked.txt
```
## 04 运行方式
#### 1) Windows（CMD）
进入项目目录后执行：
```cmd
cd YOURPATH
gcc -Wall -Wextra -std=c11 ID.c -o ID.exe
ID.exe
```
如果你使用 Visual Studio 编译器：
```cmd
cd YOURPATH
cl /W4 ID.c
ID.exe
```
#### 2) macOS
进入项目目录后执行：
```bash
cd "/Users/your_name/your_path/project-root"
gcc -Wall -Wextra -std=c11 ID.c -o ID
./ID
```
## 05 输入文件格式
`person.txt` 每行一条记录，格式如下：
```text
身份证号 姓名
```
示例：
```text
11010519491231002x zhangli
440524198001010013 wangxiao
```
