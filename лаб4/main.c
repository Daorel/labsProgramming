#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80

typedef struct Gaslist
{
    char* name;                                 //��������
    char* address;                              //�����
    float fuelPrices[4];                        //���� ���� �� �������(92,95,98,������)
    int rating;                                 //������� ���(1-10)
    struct Gaslist* next;                       //������ �� ��������� ���������
} GSDesc;

/*----------------------------�������------------------------------*/
int MainMenu();                                 //���� ������ ������(���� ��� �������)
int MenuStack();                                //���� ��� �����
int MenuQueue();                                //���� ��� �������
void OutputMenu(GSDesc*);                       //���� ������
void Help();                                    //�������

GSDesc* DeleteItem_Stack(GSDesc*);              //�������� �������� �� �����
GSDesc* DeleteItem_Queue(GSDesc*);              //�������� �������� �� �������

void GetItem_Stack(GSDesc*);                    //����� �������� �������� �����
void GetItem_Queue(GSDesc*);                    //����� �������� �������� �������

GSDesc* Push_Stack(GSDesc*);                    //���������� � ����
GSDesc* Push_Queue(GSDesc*);                    //���������� � �������
GSDesc* InputStation();                         //���� ������ �� ���

int PrepareStruct(GSDesc*);                     //��������� ������ ��� ����� ���������
void CopyStruct(GSDesc*, GSDesc*);              //����������� ���������

void OutputGasStationsTable(GSDesc*);           //����� ���������� � ���� �������
void OutputGasStationsText(GSDesc*);            //����� ���������� � ���� ������

void free_station(GSDesc*);                     //������������ ������ ����� ���
void free_list(GSDesc*);                        //������������ ������ ������ ���
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc*    First = NULL;                    //������ ������
    int MenuItem;
    do
    {
        MenuItem = MainMenu();
        switch(MenuItem)
        {
            case 1:
                Help();
                break;
            case 2:
                do
                {
                    MenuItem = MenuStack();
                    switch(MenuItem)
                    {
                        case 1:
                            First = Push_Stack(First);
                            break;
                        case 2:
                            if(First) GetItem_Stack(First);
                            else
                            {
                                puts("�� ������ �� �����, ������ ��� ����! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                        case 3:
                            if(First) OutputMenu(First);
                            else
                            {
                                puts("�� ������ �� �����, ������ ��� ����! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                        case 4:
                            if(First) First = DeleteItem_Stack(First);
                            else
                            {
                                puts("�� ������ �� �����, ������ ��� ����! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                    }
                    fflush(stdin);
                } while(MenuItem < 5);
                if(MenuItem == 6) MenuItem = 0;
                break;
            case 3:
                do
                {
                    MenuItem = MenuQueue();
                    switch(MenuItem)
                    {
                        case 1:
                            First = Push_Queue(First);
                            break;
                        case 2:
                            if(First) GetItem_Queue(First);
                            else
                            {
                                puts("�� ������ �� �����, ������ ��� ����! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                        case 3:
                            if(First) OutputMenu(First);
                            else
                            {
                                puts("��� ������ ��� ������! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                        case 4:
                            if(First) First = DeleteItem_Queue(First);
                            else
                            {
                                puts("�� ������ �� �����, ������ ��� ����! ��������� ����� 1");
                                system("pause");
                            }
                            break;
                    }
                    fflush(stdin);
                } while(MenuItem < 5);
                if(MenuItem == 6) MenuItem = 0;
                break;
            case 4:
                free_list(First);
                puts("������ �������!");
                system("pause");
                break;
        }
    } while(MenuItem);
    free_list(First);
    return 0;
}
//------------------------------------------------------����------------------------------------------------------
int MainMenu()
{
    system("cls");
    int selected;
    puts("****************������� ����****************");
    puts("1 - �������");
    puts("2 - �������� � �������, ��� �� ������");
    puts("3 - �������� � �������, ��� � ��������");
    puts("4 - �������� ��������� ������");
    puts("0 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 4) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 4);
    fflush(stdin);
    return selected;
}

int MenuStack()
{
    system("cls");
    int selected;
    puts("****************����(����)****************");
    puts("1 - ���������� ��� � ���������� ������");
    puts("2 - ������� ��������� ������� ������");
    puts("3 - ����� ������� ������ ���");
    puts("4 - ������� ��������� ������� ������");
    puts("5 - ����� � ������ ������ ������");
    puts("6 - ��������� ������ ���������");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 6);
    fflush(stdin);
    return selected;
}

int MenuQueue()
{
    system("cls");
    int selected;
    puts("****************����(�������)****************");
    puts("1 - ���������� ��� � ���������� ������");
    puts("2 - ������� ������ ������� ������");
    puts("3 - ����� ������� ������ ���");
    puts("4 - ������� ������ ������� ������");
    puts("5 - ����� � ������ ������ ������");
    puts("6 - ��������� ������ ���������");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 6) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 6);
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

void OutputItem(GSDesc* item)
{
    int selected;
    do
    {
        system("cls");
        puts("****************�����****************");
        puts("1 - � ���� �������");
        puts("2 - � ���� ������");
        puts("0 - �����");
        do
        {
            scanf("%d", &selected);
            if(selected < 0 || selected > 2) puts("������� ������ ���� �� ����������");
        } while(selected < 0 || selected > 2);
        fflush(stdin);
        if(selected == 1) OutputGasStationsTable(item);
        else if(selected == 2) OutputGasStationsText(item);
    }while(selected);
}

void Help()
{
    system("cls");
    puts("  ������ ��������� ������������� ��� ������ ��� ������� ���, ������� ��������� ���������:");
    puts("��������, �����, ���� �� ������� � ������� - � ���� �������:");
    puts("����(����������, �������� � ��������� ���������� ��������)");
    puts("� �������(�� �� ��������, �� � ������ ���������). � ������ ������ ����� ������� ������ ������ ���");
    puts("  � ������� ���� �� ������ ������� ����� ������");
    puts("����� ��������, ���, ��������� � ����� ������, ����� �������� ��� � ��� �� ������� ����");
    puts("� ��������� ����� ������ �� ����� ����� ������� ������");
    puts("  ��� ������� ����� �������� ��� ������, ������ � ������� ���� ���������� �����\n");
    system("pause");
}
//------------------------------------------------------�������� �� �������------------------------------------------------------
GSDesc* DeleteItem_Stack(GSDesc* First)
{
    system("cls");
    GSDesc* buff = NULL;
    GSDesc* temp = NULL;
    for(buff = First; buff->next != NULL; buff = buff->next);
    if(First->next != buff && First->next != NULL)
    {
        for(temp = First; temp->next != buff; temp = temp->next);
        temp->next = NULL;
    }
    else if(First == buff)
        First = First->next;
    else if(First->next == buff)
        First->next = NULL;
    free_station(buff);
    return First;
}

GSDesc* DeleteItem_Queue(GSDesc* First)
{
    system("cls");
    GSDesc* buff = NULL;
    buff = First;
    First = First->next;
    free_station(buff);
    return First;
}

void GetItem_Stack(GSDesc* Stations)
{
    system("cls");
    GSDesc* last = NULL;
    for(last = Stations; last->next != NULL; last = last->next);
    OutputItem(last);
}

void GetItem_Queue(GSDesc* first)
{
    system("cls");
    GSDesc* item = NULL;
    item = (GSDesc*)malloc(sizeof(GSDesc));
    CopyStruct(item, first);
    item->next = NULL;
    OutputItem(item);
    free_station(item);
}

GSDesc* Push_Queue(GSDesc* OtherStations)                     //���������� � ������
{
    GSDesc* Station = NULL;
    Station = InputStation();
    Station->next = OtherStations;
    return Station;
}

GSDesc* Push_Stack(GSDesc* OtherStations)                    //���������� � �����
{
    GSDesc* Station = NULL;
    GSDesc* connector = NULL;
    Station = InputStation();
    if(OtherStations)
    {
        for(connector = OtherStations; connector->next != NULL ; connector = connector->next);
        connector->next = Station;
    }
    else
        OtherStations = Station;
    return OtherStations;
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
        if(c == 13 && i == 0)
            puts("������ �� ����� ���� ������!");
    } while(i < MAXLEN && (c != 13 || i == 0));
    string[i] = '\0';
    fflush(stdin);
}

GSDesc* InputStation()
{
    system("cls");
    int i;
    GSDesc* Station = NULL;
    Station = (GSDesc*)malloc(sizeof(GSDesc));
    if(Station != NULL)
    {
        if(PrepareStruct(Station))
        {
            system("cls");
            puts("������� �������� ���");
            InputText(Station->name);
            puts("\n������� �����");
            InputText(Station->address);
            puts("\n������� ���� �� �������(92,95,98,������). ���� �� ���� 10000");
            for(i = 0; i < 4; i++)
            {
                do
                {
                    scanf("%f", &(Station->fuelPrices[i]));
                    if(Station->fuelPrices[i] < 1.0 || Station->fuelPrices[i] > 10000.0) puts("���� �� 1 �� 10000");
                } while(Station->fuelPrices[i] < 1.0 || Station->fuelPrices[i] > 10000.0);
            }
            puts("������� ������� ��� �� 1 �� 10");
            do
            {
                scanf("%d", &(Station->rating));
                if(Station->rating < 1 || Station->rating > 10) puts("������� �� 1 �� 10!");
            } while(Station->rating < 1 || Station->rating > 10);
        }
    }
    system("pause");
    return Station;
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
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|\n", namelen, "��������", addresslen, "�����");
	for(buff = first; buff != NULL; buff = buff->next)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, buff->name, addresslen, buff->address,
         buff->fuelPrices[0], buff->fuelPrices[1], buff->fuelPrices[2], buff->fuelPrices[3], buff->rating);
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
        printf("\n\n");
    }
    system("pause");
}
//------------------------------------------------------������------------------------------------------------------
int PrepareStruct(GSDesc* Station)
{
    int res = 0,
        i;
    if(Station != NULL)
    {
        Station->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        for(i = 0; i < 4; i++) Station->fuelPrices[i] = 0;
        Station->rating = 0;
        Station->next = NULL;
        res++;
    }
    return res;
}

void free_station(GSDesc* Station)
{
    if(Station != NULL)
    {
        free(Station->name);
        Station->name = NULL;
        free(Station->address);
        Station->address = NULL;
        Station->next = NULL;
        free(Station);
        Station = NULL;
    }
}

void free_list(GSDesc* item)
{
    if(item != NULL)
    {
        GSDesc* buff = NULL;
        for(; item != NULL; item = buff)
        {
            buff = item->next;
            free_station(item);
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
    }
}
