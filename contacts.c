#include<string.h>
#include<stdio.h>   
#include<stdlib.h>  
#define N 1000
#define L 100   //the max lens of string

typedef struct telebook
{
    char num[4];
    char name[10];
    char phonenum[15];
    char address[20];
}TELEBOOK;

int numLen = 4, nameLen = 10, phonenumLen = 15, addressLen = 20, maxLen = L;

void printMenu();
void printheader();
void output(TELEBOOK temp[], int num);  //
void printdata(TELEBOOK pp);
void Disp(TELEBOOK temp[], int n);
float stringinput(char *t, int lens, char *notice);
int Locate(TELEBOOK temp[], int n, char findmess[], char nameorphonenum[]);
int Add(TELEBOOK temp[], int n);
void Qur(TELEBOOK temp[], int n);
int Del(TELEBOOK temp[], int n);
void Modify(TELEBOOK temp[], int n);
int Insert(TELEBOOK temp[], int n);
void SelectSort(TELEBOOK temp[], int n);
void Save(TELEBOOK temp[], int n);
int input(TELEBOOK temp[], int num);    //

int main()
{
    char keyboardInput[N];
    int keyInputNum = 0;
    int n = 0;
    TELEBOOK * temp;
    temp = (TELEBOOK *)malloc(N * sizeof(TELEBOOK));

    while (1)
    {
        /*
        若选择0，判断并推出；
        若选择1，则调用Add（）函数，执行增加记录操作；
        若选择2，则调用Disp（）函数，执行以表格形式打印输出记录至屏幕的操作；
        若选择3，则调用Del（）函数，执行删除记录操作；
        若选择4，则调用Qur（）函数，执行查询记录操作；
        若选择5，则调用Modify（）函数，执行修改记录操作；
        若选择6，则调用Insert（）函数，执行插入记录操作；
        若选择7，则调用SelectSort（）函数，执行按升序排序记录的操作；
        若选择8，则调用Save（）函数，执行存储记录的操作；若输入除此之外的数，则调用Wrong（）函数，给出按键错误的提示*/
        printMenu();
        stringinput(keyboardInput, 2, "Please Enter a number(0 ~8)");

        //puts(keyboardInput);
        if (keyboardInput[0] <= '9' && keyboardInput >= '0' && keyboardInput[1] == '\0')
        {
            printMenu();
            sscanf(keyboardInput, "%d", &keyInputNum);
            printf("There are %d recorders\n", n);
            switch (keyInputNum)
            {
            case 1:
                n = Add(temp, n);   //retrun n++
                break;
            case 2:
                Disp(temp, n);
                break;
            case 3:
                n = Del(temp, n);
                break;
            case 4:
                Qur(temp, n);
                break;
            case 5:
                Modify(temp, n);
                break;
            case 7:
                SelectSort(temp, n);
                break;
            case 8:
                Save(temp, n);
                break;
            case 0:
                printf("Will save and quit\n");;
                Save(temp, n);
                return 0;
            }
        }
        else
            printf("#ERROR# Enter a number 0 ~ 8\n");
    }
    return 0;
}

void printMenu()
{
    system("cls"); //调用DOS命令，清屏.与clrscr()功能相同
    
    printf("                        Welcom\n");
    printf("                                                                 \n");
    printf("    ************************* main menu *************************\n");
    printf("    *                                                           *\n");
    printf("    *           1 add contact            2 print contants       *\n");
    printf("    *                                                           *\n");
    printf("    *           3 delete contant         4 search contant       *\n");
    printf("    *                                                           *\n");
    printf("    *           5 edit contant           6 insert contant       *\n");
    printf("    *                                                           *\n");
    printf("    *           7 sort contant           8 save                 *\n");
    printf("    *                                                           *\n");
    printf("    *           0 exit                                          *\n");
    printf("    *                                                           *\n");
    printf("    *************************************************************\n");
    //cprintf()送格式化输出至文本窗口屏幕中
}

int Add(TELEBOOK temp[], int n)
{
    if (input(temp, n))
        return n + 1;
    else
        return n;
}

void Disp(TELEBOOK temp[], int n)
{
    printf("There are the Contacts:\n");
    printheader();
    int i = 0;
    for (i = 0; i < n; i++)
    {
        output(temp, i);
    }
    printf("%d contacts in total\n", n);
}

int Del(TELEBOOK temp[], int n)
{

    // n can not be 0
    if (n == 0)
    {
        printf("No recorder\n");
        return 0;
    }

    int i = 0, j = 0;
    int delNum = 0;
    char nameOrPhoneNumber[L];
    char delStr[16];
    for (i = 0; i < 16; i++)
    {
        delStr[i] = '\0';
    }

    stringinput(nameOrPhoneNumber, maxLen, "Which type of data do you want to search? 'name' or 'phonenumber'");

    printf("Which comtact do you want to delete?\n");
    if (strcmp(nameOrPhoneNumber, "name") == 0)
    {
        stringinput(delStr, nameLen, "Please Enter the name");
    }
    else if (strcmp(nameOrPhoneNumber, "phonenumber") == 0)
    {
        stringinput(delStr, phonenumLen, "Please Enter the phonenumber");
    }
    else
    {
        printf("#ERROR# Enter 'name' or 'phonenumber'\n");  //go back
        return n;
    }

    delNum = Locate(temp, n, delStr, nameOrPhoneNumber);
    if (n == delNum)
    {
        printf("can not find a compatible recorder\n");
        
    }
    else
    {
        printf("A compatible recorder founded:\n");
        printheader();
        output(temp, delNum);
        n = n - 1;
        for (i = delNum; i < n; i++)
        {
            temp[i] = temp[i + 1];
        }
        printf("A compatible recorder delete complited\n");
        
    }
    return n;
}

float stringinput(char *t, int lens, char *notice)
{
    char str[N];
    puts(notice);
    printf(">>>");

    scanf(" ");
    gets(str);
    printf("\n");
    if (lens > strlen(str))
    {
        strcpy(t, str);
        return 1;
    }
    else
    {
        printf("Input Error\n");
        return 0;
    }
}

int Locate(TELEBOOK temp[], int n, char findmess[], char nameOrPhoneNumber[])  //temp findmess delStr
// n is the member quantity of the temp (0 ~ n - 1), if not founded, will return n, if founded, return the member number
{
    int i = 0;

    if (~strcmp(nameOrPhoneNumber, "name"))
    {

        for (i = 0; i < n; i++)
        {
            if (~strcmp(temp[i].name, findmess))  //founded
            {
                break;
            }
            return n;
        }
    }

    else if (~strcmp(nameOrPhoneNumber, "phonenumber"))
    {

        for (i = 0; i < n; i++)
        {
            if (~strcmp(temp[i].phonenum, findmess))  //founded
            {
                break;
            }
            return n;
        }
    }


    return i;
        /*scanf("%d", &input);
        if (input == 0)
        {
            continue;
        }

        else
        {
            n = n - 1;
            for (j = i; j < n; j++)
            {
                temp[j] = temp[j + 1];
            }
            break;
        }*/
}

void Modify(TELEBOOK temp[], int n)
{
    // n can not be 0
    if (n == 0)
    {
        printf("No recorder\n");
        return 0;
    }

    int i = 0;
    int modifyNum = 0;
    char modifyStr[16];
    char nameOrPhoneNumber[L];

    stringinput(nameOrPhoneNumber, maxLen, "Which type of data do you want to search? 'name' or 'phonenumber'");

    printf("Which comtact do you want to delete?\n");
    if (~strcmp(nameOrPhoneNumber, "name"))
    {
        stringinput(modifyStr, nameLen, "Please Enter the name");
    }
    else if (~strcmp(nameOrPhoneNumber, "phonenumber"))
    {
        stringinput(modifyStr, phonenumLen, "Please Enter the phonenumber");
    }
    else
    {
        printf("'name' or 'phonenumber'");  //go back
    }
    
    modifyNum = Locate(temp, n, modifyStr, nameOrPhoneNumber);
    if (n == modifyNum)
    {
        printf("can not find a compatible record\n");

    }
    else
    {
        printf("A compatible recorder founded:\n");
        printheader();
        output(temp, modifyNum);
        printf("Enter new data please\n");
        if(input(temp, modifyNum))
            printf("Refresh complited\n");
    }
}

int input(TELEBOOK temp[], int num)
{
    if (stringinput(temp[num].num, numLen, "Please Enter the School Num"))   //if error ???????????
        if (stringinput(temp[num].name, nameLen, "Please Enter the Name"))
            if (stringinput(temp[num].phonenum, phonenumLen, "Please Enter the Phone Number"))
                if (stringinput(temp[num].address, addressLen, "Please Enter the Adress"))
                    return 1;
    printf("Check your input, please\n");
    return 0;
}

void printheader()
{
    printf("======================================================\n");
    printf("+----+----------+---------------+--------------------+\n");
    printf("|num |name      |phonenum       |adress              |\n");
    printf("+----+----------+---------------+--------------------+\n");
}

void output(TELEBOOK temp[], int num)
{
    printf("|%-4s|%-10s|%-15s|%-20s|\n", temp[num].num, temp[num].name, temp[num].phonenum, temp[num].address);
    printf("+----+----------+---------------+--------------------+\n");
}


void SelectSort(TELEBOOK temp[], int n)
{
    TELEBOOK t;
    int i = 0, j = 0;

    for(i = 0 ; i < n ; i++)
    {
        for(j = i + 1 ; j < n ; j++)
        {
            if(~strcmp(temp[i].num, temp[j].num))
            {
                t = temp[j];
                temp[j] = temp[i];
                temp[i] = t;
            }
        }
    }
    printf("Sorted\n");
}

void Qur(TELEBOOK temp[], int n)
{
    // n can not be 0
    if (n == 0)
    {
        printf("No recorder\n");
        return;
    }

    int i = 0, j = 0;
    int ourNum = 0;
    char nameOrPhoneNumber[L];
    char ourStr[16];
    for (i = 0; i < 16; i++)
    {
        ourStr[i] = '\0';
    }

    stringinput(nameOrPhoneNumber, maxLen, "Which type of data do you want to search? 'name' or 'phonenumber'");

    printf("Which comtact do you want to print?\n");
    if (~strcmp(nameOrPhoneNumber, "name"))     //if "name"
    {
        stringinput(ourStr, nameLen, "Please Enter the name");
    }
    else if (~strcmp(nameOrPhoneNumber, "phonenumber"))     //if "phone number"
    {
        stringinput(ourStr, phonenumLen, "Please Enter the phonenumber");
    }
    else
    {
        printf("#ERROR# Enter 'name' or 'phonenumber'\n");  //go back !!!!!!!!!!!!!
        return;
    }

    ourNum = Locate(temp, n, ourStr, nameOrPhoneNumber);
    if (n == ourNum)
    {
        printf("can not find a compatible recorder\n");

    }
    else
    {
        printf("A compatible recorder founded:\n");
        printheader();
        output(temp, ourNum);
    }
}

void Save(TELEBOOK temp[], int n)
{
    FILE *fp;
    if ((fp = fopen("D:\\fp.txt", "w")) != NULL)
    {
        printf("fp.txt opened complited\n");
    }
    fprintf(fp, "hello world\n");

    fprintf(fp, "======================================================\n"
                "+----+----------+---------------+--------------------+\n"
                "|num |name      |phonenum       |adress              |\n"
                "+----+----------+---------------+--------------------+\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "|%-4s|%-10s|%-15s|%-20s|\n", temp[i].num, temp[i].name, temp[i].phonenum, temp[i].address);
        fprintf(fp, "+----+----------+---------------+--------------------+\n");
    }
   
    fclose(fp);
    printf("Save complited\n");
}

int Insert(TELEBOOK temp[], int num)
{
    printf("I do not know what do you mean...\n");
    return 0;
}
