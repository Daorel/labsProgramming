#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct Gaslist
{
    char* name;                         //��������
    char* address;                      //�����
    float fuelPrices[4];                  //���� ���� �� �������(92,95,98,������)
    int rating;                        //������� ���(1-10)
    int stuff;                         //���-�� �����������
    struct Gaslist* next;                      //������ �� ��������� ���������
} GSDesc;

/*----------------------------�������------------------------------*/
int Menu();                                     //����
int ListActions();                              //�������� �� �������
void OutputMenu(GSDesc*);                      //���� ������
GSDesc* InputMenu(GSDesc*);                   //���� ������ �����

int ListLen(GSDesc*);                          //����� ������
GSDesc* DeleteItem(GSDesc*);                  //�������� �������� �� ������
GSDesc* SortByRating(GSDesc*);                //���������� �� �������� ����   �������
void Swap(GSDesc*);                            //�������� �������    �������
//void GetItem(GSDesc*);                         //����� ��� �� �������� ���������� �������

GSDesc* PushBack(GSDesc*);                    //���������� � �����
GSDesc* PushForward(GSDesc*);                 //���������� � ������
GSDesc* InputStations();                       //���� ������ �� ���
GSDesc* Process(GSDesc*);                     //��������� ������

int PrepareStruct(GSDesc*);                    //��������� ������ ��� ����� ���������
void CopyStruct(GSDesc*, GSDesc*);              //����������� ���������

void OutputGasStationsTable(GSDesc*);          //����� ���������� � ���� �������
void OutputGasStationsText(GSDesc*);           //����� ���������� � ���� ������

void free_station(GSDesc*);                    //������������ ������ ����� ���
void free_list(GSDesc*);                       //������������ ������ ������ ���
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                           //������ ������
    GSDesc*    GResult = NULL;                         //������ ������ ����������
    int MenuItem, len;
    do
    {
        MenuItem = Menu();
        switch(MenuItem)
        {
            case 1:
                First = InputMenu(First);
                //free_list(First);
                //First = InputStations();
                break;
            case 2:
                if(First != NULL) OutputMenu(First);
                else
                {
                    puts("��� ������ ��� ������, ������ ����!");
                    system("pause");
                }
                break;
            case 3:
                do
                {
                    MenuItem = ListActions();
                    switch(MenuItem)
                    {
                        case 1:
                            len = ListLen(First);
                            printf("���������� ��������� � ������: %d\n",len);
                            system("pause");
                            break;
                        case 2:
                            First = DeleteItem(First);
                            break;
                        case 3:
                            //GetItem(First);
                            //Swap
                            break;
                        case 4:
                            break;
                    }
                } while(MenuItem != 5);
                break;
            case 4:
                if(First != NULL) GResult = Process(First);
                else
                {
                    puts("�� ���� ������� ������. ��������� ����� 1");
                    system("pause");
                }
                break;
            case 5:
                if(GResult != NULL) OutputMenu(GResult);
                else
                {
                    puts("�� ���� ���������� ����������. ��������� ����� 4");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    free_list(First);
    free_list(GResult);
    return 0;
}
//------------------------------------------------------����------------------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************����****************");
    puts("1 - ���� ���������� �� ���");
    puts("2 - ����� ���������� �� ���");
    puts("3 - �������� ��� ������� ���");
    puts("4 - ��������� ������");
    puts("5 - ����� ������");
    puts("0 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

int ListActions()
{
    system("cls");
    int selected;
    puts("****************����****************");
    puts("1 - ������ ���������� ��������� ������ ���");
    puts("2 - ������� ������� ������ ���");
    puts("3 - �������� ������� �������� ������ ���(�� ��������)");
    puts("4 - ���������� ��������� ������ ���(�� ��������)");
    puts("5 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

void OutputMenu(GSDesc* first)
{
    int item;
    do
    {
        system("cls");
        puts("****************�����****************");
        puts("1 - � ���� �������");
        puts("2 - � ���� ������");
        puts("0 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 2) puts("������� ������ ���� �� ����������");
        } while(item < 0 || item > 2);
        fflush(stdin);
        if(item == 1) OutputGasStationsTable(first);
        else if(item == 2) OutputGasStationsText(first);
    }while(item);
}

GSDesc* InputMenu(GSDesc* Stations)                       //���� ������ �����
{
    system("cls");
    int item;
    do
    {
        system("cls");
        puts("****************�����****************");
        puts("1 - �������� � ������");
        puts("2 - �������� � �����");
        puts("3 - ������ ��������� ������");
        puts("4 - �����");
        do
        {
            scanf("%d", &item);
            if(item < 0 || item > 4) puts("������� ������ ���� �� ����������");
        } while(item < 0 || item > 4);
        fflush(stdin);
        if(item == 1) Stations = PushForward(Stations);
        else if(item == 2) Stations = PushBack(Stations);
        else if(item == 3)
        {
            free_list(Stations);
            Stations = InputStations();
        }
    }while(item != 4);
    return Stations;
}
//------------------------------------------------------�������� �� �������------------------------------------------------------
int ListLen(GSDesc* Stations)
{
    GSDesc* buff = Stations;
    int len = 0;
    for(;buff != NULL; buff = buff->next) len++;
    return len;
}

GSDesc* DeleteItem(GSDesc* Stations)
{
    GSDesc* first = Stations;
    GSDesc* temp = Stations;
    GSDesc* toDel = NULL;
    int num;
    printf("������� ����� ��������, ������� ������ �������(����� %d ���������): ", ListLen(Stations));
    do
    {
        scanf("%d", &num);
        if(num < 1 || num > ListLen(Stations)) printf("�������� ��� ����� ������� ���. ������� �� 1 �� %d\n", ListLen(Stations));
    } while(num < 1 || num > ListLen(Stations));
    if(num == 1)
    {
        if(ListLen(Stations) == 1)
        {
            free_station(Stations);
            first = NULL;
        }
        else
        {
            first = first->next;
            free_station(temp);
            temp = NULL;
        }
    }
    else
    {
        toDel = temp->next;
        while(num > 2)
        {
            temp = temp->next;
            toDel = temp->next;
            num--;
        }
        temp->next = toDel->next;
        free_station(toDel);
    }
    system("pause");
    printf("%p", first);
    return first;
}

/*void GetItem(GSDesc* Stations)
{
    system("cls");
    GSDesc* result = NULL;
    GSDesc* buff = Stations;
    int ans;
    puts("�������� ���������, �� ������� �� ����");
    puts("1 - ���� �� �������");
    puts("2 - �������");
    puts("3 - ���������� �����������");
    do
    {
        scanf("%d", &ans);
        if(ans < 1 || ans > 3) puts("������� �� 1 �� 3");
    } while(ans < 1 || ans > 3);
    if(ans == 1)
    {
        do
        {
            s
        } while(buff != NULL);
    }
    else if(ans == 2)
    {
        s
    }
    else
    {
        s
    }
}*/

GSDesc* Process(GSDesc* Stations)                     //��������� ������
{
    GSDesc* result = NULL;
    GSDesc* temp = Stations;
    GSDesc* buff = NULL;
    do
    {
        if(temp->rating > 7 && temp->fuelPrices[2] < 54.0)
        {
            if(result == NULL)
            {
                result = (GSDesc*)malloc(sizeof(GSDesc));
                buff = result;
                CopyStruct(buff, temp);
            }
            else
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff = buff->next;
                CopyStruct(buff, temp);
            }
            buff->next = NULL;
        }
        temp = temp->next;
    } while(temp != NULL);
    if(result == NULL) puts("�� ���� ��� �� �������� ��� ��������");
    else puts("��������� ������ �������!");
    system("pause");
    return result;
}
//------------------------------------------------------����------------------------------------------------------
void InputText(char* string)
{
    char c;                     //��������� ������
    int i;
    i = 0;
    do
    {
        c = getch();
        if(c != 13 && c != 8)
        {
            string[i] = c;
            printf("%c", c);
            i++;
        }
        else if(c == 8)
        {
            if(i > 0)
            {
                string[i-1] = '\0';
                printf("\r%s %c", string, c);
                i--;
            }
        }
    } while(i < MAXLEN && c != 13);
    string[i] = '\0';
    fflush(stdin);
}

GSDesc* InputStations()
{
    system("cls");
    int i,
        f;
    GSDesc* first = NULL;
    GSDesc* buff = NULL;
    first = (GSDesc*)malloc(sizeof(GSDesc));
    if(first != NULL)
    {
        buff = first;
        for(f = 1;buff != NULL && f;)
        {
            if(PrepareStruct(buff))
            {
                system("cls");
                puts("������� �������� ���");
                InputText(buff->name);
                puts("\n������� �����");
                InputText(buff->address);
                puts("\n������� ���� �� �������(92,95,98,������). ���� �� ���� 10000");
                for(i = 0; i < 4; i++)
                {
                    do
                    {
                        scanf("%f", &(buff->fuelPrices[i]));
                        if(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0) puts("���� �� 1 �� 10000");
                    } while(buff->fuelPrices[i] < 1.0 || buff->fuelPrices[i] > 10000.0);
                }
                puts("������� ������� ��� �� 1 �� 10");
                do
                {
                    scanf("%d", &(buff->rating));
                    if(buff->rating < 1 || buff->rating > 10) puts("������� �� 1 �� 10!");
                } while(buff->rating < 1 || buff->rating > 10);
                puts("������� ���������� �����������");
                do
                {
                    scanf("%d", &(buff->stuff));
                    if(buff->stuff < 1 || buff->stuff > 1000000) puts("���-�� ����������� �� 1 �� 1000000");
                } while(buff->stuff < 1 || buff->stuff > 1000000);
                puts("���� ������ ���������� ���� ������, ������� ����� �����, �������� �� ����");
                scanf("%d", &f);
            }
            if(f)
            {
                buff->next = (GSDesc*)malloc(sizeof(GSDesc));
                buff = buff->next;
            }
        }
    }
    system("pause");
    return first;
}

GSDesc* PushForward(GSDesc* Stations)                     //���������� � ������
{
    GSDesc* temp = NULL;
    GSDesc* connector = NULL;
    temp = InputStations();
    for(connector = temp ; connector->next != NULL ; connector = connector->next);
    connector->next = Stations;
    return temp;
}

GSDesc* PushBack(GSDesc* Stations)                    //���������� � �����
{
    GSDesc* temp = NULL;
    GSDesc* connector;
    temp = InputStations();
    connector = temp;
    if(Stations != NULL)
    {
        for(connector = Stations->next ; connector->next != NULL ; connector = connector->next);
        connector->next = temp;
        connector = Stations;
    }
    return connector;
}
//------------------------------------------------------�����------------------------------------------------------
void OutputGasStationsTable(GSDesc* first)
{
    fflush(stdout);
    system("cls");
    int namelen,
        addresslen;
    GSDesc* buff = first;
    namelen = 8, addresslen = 5;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(buff->name) > namelen) namelen = strlen(buff->name);
        if(strlen(buff->address) > addresslen) addresslen = strlen(buff->address);
    }
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|�����������|\n", namelen, "��������", addresslen, "�����");
	for(buff = first; buff != NULL; buff = buff->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating, buff->stuff);
    system("pause");
}

void OutputGasStationsText(GSDesc* first)
{
    fflush(stdout);
    system("cls");
    GSDesc* buff = first;
    int i;
    for(; buff != NULL; buff = buff->next)
    {
        printf("��������: %s", buff->name);
        printf("\n�����: %s", buff->address);
        printf("\n����(92,95,98,������): ");
        for(i = 0; i < 4; i++) printf("%.2f ", buff->fuelPrices[i]);
        printf("\n�������: %d", buff->rating);
        printf("\n���������� �����������: %d", buff->stuff);
        printf("\n\n");
    }
    system("pause");
}
//------------------------------------------------------������------------------------------------------------------
int PrepareStruct(GSDesc* first)
{
    int res = 0,
        i;
    if(first != NULL)
    {
        first->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        for(i = 0; i < 4; i++) first->fuelPrices[i] = 0;
        first->rating = 0;
        first->stuff = 0;
        first->next = NULL;
        res++;
    }
    return res;
}

void free_station(GSDesc* List)
{
    if(List != NULL)
    {
        free(List->name);
        List->name = NULL;
        free(List->address);
        List->address = NULL;
        free(List->next);
        List->next = NULL;
        List = NULL;
    }
}

void free_list(GSDesc* item)
{
    if(item != NULL)
    {
        GSDesc* buff = NULL;
        for(; item != NULL;)
        {
            buff = item;
            free_station(item);
            item = buff->next;
            free(buff);
            buff = NULL;
        }
    }
}

void CopyStruct(GSDesc* ThisStation, GSDesc* OtherStation)
{
    int i;
    if(PrepareStruct(ThisStation))
    {
        strcpy(ThisStation->name, OtherStation->name);
        strcpy(ThisStation->address, OtherStation->address);
        for(i = 0; i < 4; i++)
            ThisStation->fuelPrices[i] = OtherStation->fuelPrices[i];
        ThisStation->rating = OtherStation->rating;
        ThisStation->stuff = OtherStation->stuff;
    }
}
