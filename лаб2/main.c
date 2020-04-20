#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80
#define DBG puts("DBG");

typedef struct
{
    char* name;                         //��������
    char* address;                      //�����
    float* fuelPrices;                  //���� ���� �� �������(92,95,98,������)
    int* rating;                        //������� ���(1-10)
    int* stuff;                         //���-�� �����������
} GSDesc;

typedef struct List
{
    struct List* next;
    GSDesc Station;
} Gaslist;
/*----------------------------�������------------------------------*/
int Menu();                                     //����
int ListActions();                              //�������� �� �������
void OutputMenu(Gaslist*);                      //���� ������
void OutputItem(GSDesc);                        //���� ������ ������ ���������� �� ���
Gaslist* InputMenu(Gaslist*);                       //���� ������ �����

int ListLen(Gaslist*);                          //����� ������
Gaslist* DeleteItem(Gaslist*);                  //�������� �������� �� ������   WTF?!??!?!? ������� ��������
Gaslist* SortByRating(Gaslist*);                //���������� �� �������� ����   �������
void Swap(Gaslist*);                            //�������� �������    �������
void GetItem(Gaslist*);                         //����� n-� ���

Gaslist* PushBack(Gaslist*);                    //���������� � �����
Gaslist* PushForward(Gaslist*);                 //���������� � ������
Gaslist* InputStations();                       //���� ������ �� ���
Gaslist* Process(Gaslist*);                     //��������� ������

int PrepareStruct(Gaslist*);                    //��������� ������ ��� ����� ���������

void OutputGasStationsTable(Gaslist*);          //����� ���������� � ���� �������
void OutputGasStationsText(Gaslist*);           //����� ���������� � ���� ������
void OutputStationTable(GSDesc);                //����� ���������� �� 1 ��� � ���� �������
void OutputStationText(GSDesc);                 //����� ���������� �� 1 ��� � ���� ������

void free_station(Gaslist*);                    //������������ ������ ����� ���
void free_list(Gaslist*);                       //������������ ������ ������ ���
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    Gaslist*    First = NULL;                           //������ ������
    Gaslist*    GResult = NULL;                         //������ ������ ����������
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
                            GetItem(First);
                            //Swap
                            break;
                        case 4:
                            break;
                    }
                } while(MenuItem != 5);
                break;
            case 4:
                /*if(First != NULL) GResult = Process(First);
                else
                {
                    puts("�� ���� ������� ������. ��������� ����� 1");
                    system("pause");
                }*/
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

void OutputMenu(Gaslist* first)
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

Gaslist* InputMenu(Gaslist* Stations)                       //���� ������ �����
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

void OutputItem(GSDesc Station)
{
    system("cls");
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
        if(item == 1) OutputStationTable(Station);
        else if(item == 2) OutputStationText(Station);
    }while(item);
}
//------------------------------------------------------�������� �� �������------------------------------------------------------
int ListLen(Gaslist* Stations)
{
    int len = 0;
    for(;Stations != NULL; Stations = Stations->next) len++;
    return len;
}

Gaslist* DeleteItem(Gaslist* Stations)
{
    Gaslist* first = Stations;
    Gaslist* temp = Stations;
    Gaslist* toDel = NULL;
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

void GetItem(Gaslist* Stations)
{
    system("cls");
    Gaslist* result = Stations;
    int num;
    printf("������� ����� ��������, ������� ������ �������(����� %d ���������): ", ListLen(Stations));
    do
    {
        scanf("%d", &num);
        if(num < 1 || num > ListLen(Stations)) printf("�������� ��� ����� ������� ���. ������� �� 1 �� %d\n", ListLen(Stations));
    } while(num < 1 || num > ListLen(Stations));
    num-=1;
    while(num)
    {
        result = result->next;
        num--;
    }
    OutputItem(result->Station);
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

Gaslist* InputStations()
{
    system("cls");
    int i,
        f;
    Gaslist* first = NULL;
    Gaslist* buff = NULL;
    first = (Gaslist*)malloc(sizeof(Gaslist));
    if(first != NULL)
    {
        buff = first;
        for(f = 1;buff != NULL && f;)
        {
            buff->next = NULL;
            if(PrepareStruct(buff))
            {
                system("cls");
                puts("������� �������� ���");
                InputText(buff->Station.name);
                puts("\n������� �����");
                InputText(buff->Station.address);
                puts("\n������� ���� �� �������(92,95,98,������). ���� �� ���� 10000");
                for(i = 0; i < 4; i++)
                {
                    do
                    {
                        scanf("%f", buff->Station.fuelPrices+i);
                        if(buff->Station.fuelPrices[i] < 1.0 || buff->Station.fuelPrices[i] > 10000.0) puts("���� �� 1 �� 10000");
                    } while(buff->Station.fuelPrices[i] < 1.0 || buff->Station.fuelPrices[i] > 10000.0);
                }
                puts("������� ������� ��� �� 1 �� 10");
                do
                {
                    scanf("%d", buff->Station.rating);
                    if(*(buff->Station.rating) < 1 || *(buff->Station.rating) > 10) puts("������� �� 1 �� 10!");
                } while(*(buff->Station.rating) < 1 || *(buff->Station.rating) > 10);
                puts("������� ���������� �����������");
                do
                {
                    scanf("%d", buff->Station.stuff);
                    if(*(buff->Station.stuff) < 1 || *(buff->Station.stuff) > 1000000) puts("���-�� ����������� �� 1 �� 1000000");
                } while(*(buff->Station.stuff) < 1 || *(buff->Station.stuff) > 1000000);
                puts("���� ������ ���������� ���� ������, ������� ����� �����, �������� �� ����");
                scanf("%d", &f);
            }
            if(f)
            {
                buff->next = (Gaslist*)malloc(sizeof(Gaslist));
                buff = buff->next;
            }
            else
                buff->next = NULL;
        }
    }
    system("pause");
    return first;
}

Gaslist* PushForward(Gaslist* Stations)                     //���������� � ������
{
    Gaslist* temp = NULL;
    Gaslist* connector = NULL;
    temp = InputStations();
    for(connector = temp->next ; connector->next != NULL ; connector = temp->next);//���
    connector->next = Stations;
    return temp;
}

Gaslist* PushBack(Gaslist* Stations)                    //���������� � �����
{
    Gaslist* temp = NULL;
    Gaslist* connector;
    temp = InputStations();
    connector = temp;
    if(Stations != NULL)
    {
        for(connector = Stations->next ; connector->next != NULL ; connector = connector->next);//���
        connector->next = temp;
        connector = Stations;
    }
    return connector;
}
//------------------------------------------------------�����------------------------------------------------------
void OutputGasStationsTable(Gaslist* first)
{
    fflush(stdout);
    system("cls");
    int namelen,
        addresslen;
    Gaslist* buff = first;
    namelen = 8, addresslen = 5;
    for(; buff != NULL; buff = buff->next)
    {
        if(strlen(first->Station.name) > namelen) namelen = strlen(first->Station.name);
        if(strlen(first->Station.address) > addresslen) addresslen = strlen(first->Station.address);
    }
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|�����������|\n", namelen, "��������", addresslen, "�����");
	for(; first != NULL; first = first->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, first->Station.name, addresslen, first->Station.address,
         first->Station.fuelPrices[0], first->Station.fuelPrices[1], first->Station.fuelPrices[2], first->Station.fuelPrices[3], *(first->Station.rating), *(first->Station.stuff));
    system("pause");
}

void OutputGasStationsText(Gaslist* first)
{
    system("cls");
    int i;
    for(; first != NULL; first = first->next)
    {
        printf("��������: %s", first->Station.name);
        printf("\n�����: %s", first->Station.address);
        printf("\n����(92,95,98,������): ");
        for(i = 0; i < 4; i++) printf("%.2f ", first->Station.fuelPrices[i]);
        printf("\n�������: %d", *(first->Station.rating));
        printf("\n���������� �����������: %d", *(first->Station.stuff));
        printf("\n\n");
    }
    system("pause");
}

void OutputStationTable(GSDesc Station)                //����� ���������� �� 1 ��� � ���� �������
{
    system("cls");
    int namelen,
        addresslen;
    namelen = 8, addresslen = 5;
    if(strlen(Station.name) > namelen) namelen = strlen(Station.name);
    if(strlen(Station.address) > addresslen) addresslen = strlen(Station.address);
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|�����������|\n", namelen, "��������", addresslen, "�����");
    printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, Station.name, addresslen, Station.address,
         Station.fuelPrices[0], Station.fuelPrices[1], Station.fuelPrices[2], Station.fuelPrices[3], *(Station.rating), *(Station.stuff));
    system("pause");
}

void OutputStationText(GSDesc Station)                 //����� ���������� �� 1 ��� � ���� ������
{
    system("cls");
    int i;
    printf("��������: %s", Station.name);
    printf("\n�����: %s", Station.address);
    printf("\n����(92,95,98,������): ");
    for(i = 0; i < 4; i++) printf("%.2f ", Station.fuelPrices[i]);
    printf("\n�������: %d", *(Station.rating));
    printf("\n���������� �����������: %d", *(Station.stuff));
    printf("\n\n");
    system("pause");
}
//------------------------------------------------------������------------------------------------------------------
int PrepareStruct(Gaslist* first)
{
    int res = 0;
    if(first != NULL)
    {
        first->Station.name = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->Station.address = (char*)malloc((MAXLEN+1)*sizeof(char));
        first->Station.fuelPrices = (float*)malloc(4*sizeof(float));
        first->Station.rating = (int*)malloc(sizeof(int));
        first->Station.stuff = (int*)malloc(sizeof(int));
        res++;
    }
    return res;
}

void free_station(Gaslist* List)
{
    if(List != NULL)
    {
        free(List->Station.name);
        List->Station.name = NULL;
        free(List->Station.address);
        List->Station.address = NULL;
        free(List->Station.fuelPrices);
        List->Station.fuelPrices = NULL;
        free(List->Station.rating);
        List->Station.rating = NULL;
        free(List->Station.stuff);
        List->Station.stuff = NULL;
        free(List->next);
        List->next = NULL;
        List = NULL;
    }
}

void free_list(Gaslist* item)
{
    if(item != NULL)
    {
        Gaslist* buff = NULL;
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
