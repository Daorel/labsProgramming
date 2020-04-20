#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#include <locale.h>
#include <string.h>

#define MAXLEN 80

typedef struct
{
    char* name;                         //��������
    char* address;                      //�����
    float* fuelPrices;                 //���� ���� �� �������(92,95,98,������)
    int* rating;                        //������� ���(1-10)
    int* stuff;                         //���-�� �����������
} GSDesc;
/*----------------------------�������------------------------------*/
int Menu();                                     //����
void OutputMenu(GSDesc*, int);                  //������� ������, int - ���-�� ���������
void Info();                                    //�������
void OutputGasStationsTable(GSDesc*, int);      //����� ���������� � ���� �������, int - ���-�� ���������
void OutputGasStationsText(GSDesc*, int);       //����� ���������� � ���� ������, int - ���-�� ���������
void InputInfo(GSDesc);                         //���� ���������
void InputText(char*);                          //���� ������
GSDesc* Process(GSDesc*, int, int*);            //��������� ������
int PrepareStruct(GSDesc*);                     //��������� ������ ��� ����� ���������
void free_struct(GSDesc*, int);                 //������������ ������
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc  *GasStations = NULL,       //���
            *GSResult = NULL;          //��������� ������
    int i = 0,                          //���-�� ���
        ri = 0,                         //���-�� ��� ����� ���������
        MenuItem;                       //��������� ����� ����
    do
    {
        MenuItem = Menu();
        switch(MenuItem)
        {
            case 1:
                Info();
                break;
            case 2:
                GasStations = (GSDesc*)realloc(GasStations, (i+1)*sizeof(GSDesc));
                if(GasStations != NULL)
                {
                    if(PrepareStruct(GasStations+i))
                    {
                        InputInfo(GasStations[i]);
                        i++;
                    }
                }
                break;
            case 3:
                if(GasStations != NULL) OutputMenu(GasStations, i);
                else
                {
                    puts("�� ���� ������� ���������� �� ���");
                    system("pause");
                }
                break;
            case 4:
                if(GasStations != NULL)
                {
                    free_struct(GSResult, ri);
                    ri = 0;
                    GSResult = Process(GasStations, i, &ri);
                }
                else puts("�� ���� ������� ���������� �� ���"),system("pause");
                break;
            case 5:
                if(GSResult != NULL) OutputMenu(GSResult, ri);
                else
                {
                    puts("��������� ���������� �� ����������, ���� �� ���� ��� �� �������� ��� ��������� �������");
                    system("pause");
                }
                break;
        }
    } while(MenuItem);
    free_struct(GasStations, i);
    free_struct(GSResult, ri);
    return 0;
}

void InputInfo(GSDesc Station)
{
    system("cls");
    int i;
    puts("������� �������� ���: ");
    InputText(Station.name);
    puts("\n������� �����: ");
    InputText(Station.address);
    printf("\n������� ���� �� �������(92,95,98,������): ");
    for(i = 0; i < 4; i++)
    {
        do
        {
            scanf("%f", Station.fuelPrices+i);
            if(Station.fuelPrices[i] < 1 || Station.fuelPrices[i] > 10000) puts("1-10000");
        } while(Station.fuelPrices[i] < 1 || Station.fuelPrices[i] > 10000);
    }
    printf("������� ������� ���: ");
    do
    {
        scanf("%d", Station.rating);
        if(*(Station.rating) < 1 || *(Station.rating) > 10) puts("1-10");
    } while(*(Station.rating) < 1 || *(Station.rating) > 10);
    printf("������� ���������� �����������: ");
    do
    {
        scanf("%d", Station.stuff);
        if(*(Station.stuff) < 1 || *(Station.stuff) > 1000000) puts("1-1000000");
    } while(*(Station.stuff) < 1 || *(Station.stuff) > 1000000);
    system("pause");
}

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

void OutputGasStationsTable(GSDesc* GasStations, int lines)
{
    system("cls");
    int i,
        namelen,
        addresslen;
    namelen = 0, addresslen = 0;
    for(i = 0; i < lines; i++)
    {
        if(strlen(GasStations[i].name) > namelen) namelen = strlen(GasStations[i].name);
        if(strlen(GasStations[i].address) > addresslen) addresslen = strlen(GasStations[i].address);
    }
    if(namelen < 8) namelen = 8;
    if(addresslen < 5) addresslen = 5;
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|�����������|\n", namelen, "��������", addresslen, "�����");
	for(i = 0; i < lines; i++)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|%11d|\n", namelen, GasStations[i].name, addresslen, GasStations[i].address,
         GasStations[i].fuelPrices[0], GasStations[i].fuelPrices[1], GasStations[i].fuelPrices[2], GasStations[i].fuelPrices[3], *(GasStations[i].rating), *(GasStations[i].stuff));
    system("pause");
}

void OutputGasStationsText(GSDesc* GasStations, int lines)
{
    system("cls");
    int i,
        j;
    for(i = 0; i < lines; i++)
    {
        printf("��������: %s", GasStations[i].name);
        printf("\n�����: %s", GasStations[i].address);
        printf("\n����(92,95,98,������): ");
        for(j = 0; j < 4; j++) printf("%.2f ", GasStations[i].fuelPrices[j]);
        printf("\n�������: %d", *(GasStations[i].rating));
        printf("\n���������� �����������: %d", *(GasStations[i].stuff));
        printf("\n\n");
    }
    system("pause");
}

GSDesc* Process(GSDesc* GasStations, int lines, int* rlines)
{
    GSDesc* result = NULL;
    int i,
        j = 0,
        k;
    for(i = 0; i < lines; i++)
        if(*(GasStations[i].rating) > 7 && GasStations[i].fuelPrices[2] < 54.0)
        {
            result = (GSDesc*)realloc(result, (j+1)*sizeof(GSDesc));
            if(PrepareStruct(result+j))
            {
                //printf("%p %p\n%p %p\nBLA BLA\n", result[j].name, GasStations[i].name, result[j].address, GasStations[i].address);
                strcpy(result[j].name, GasStations[i].name);
                strcpy(result[j].address, GasStations[i].address);
                for(k = 0; k < 4; k++)
                    result[j].fuelPrices[k] = GasStations[i].fuelPrices[k];
                *(result[j].rating) = *(GasStations[i].rating);
                *(result[j].stuff) = *(GasStations[i].stuff);
                //result[j] = GasStations[i];
                //printf("%p %p\n%p %p\n", result[j].name, GasStations[i].name, result[j].address, GasStations[i].address);
                j++;
            }
        }
    *rlines = j;
    if(result == NULL) puts("��� ���, ��������������� ������������ ��������");
    else puts("��������� ������ �������");
    system("pause");
    return result;
}

int PrepareStruct(GSDesc* Station)
{
    int res = 0;
    if(Station != NULL)
    {
        Station->name = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->address = (char*)malloc((MAXLEN+1)*sizeof(char));
        Station->fuelPrices = (float*)malloc(4*sizeof(float));
        Station->rating = (int*)malloc(sizeof(int));
        Station->stuff = (int*)malloc(sizeof(int));
        res++;
    }
    return res;
}
//------------------------------------------------���� � �������---------------------------------------------
int Menu()
{
    system("cls");
    int selected;
    puts("****************����****************");
    puts("1 - �������");
    puts("2 - ���� ���������� �� ���");
    puts("3 - ����������� ����� ��������� ����������");
    puts("4 - ��������� ����������");
    puts("5 - ����� ������������ ����������");
    puts("0 - �����");
    do
    {
        scanf("%d", &selected);
        if(selected < 0 || selected > 5) puts("������� ������ ���� �� ����������");
    } while(selected < 0 || selected > 5);
    fflush(stdin);
    return selected;
}

void OutputMenu(GSDesc* GasStations, int lines)
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
        if(item == 1) OutputGasStationsTable(GasStations, lines);
        else if(item == 2) OutputGasStationsText(GasStations, lines);
    }while(item);
}

void Info()
{
    system("cls");
    puts("������� ���������: ������� ���� 7, ���� �� 98 ������ ���� 54");
    system("pause");
}

void free_struct(GSDesc* Stations, int lines)
{
    if(Stations != NULL)
    {
        int i;
        for(i = 0; i < lines; i++)
        {
            free(Stations[i].name);
            Stations[i].name = NULL;
            free(Stations[i].address);
            Stations[i].address = NULL;
            free(Stations[i].fuelPrices);
            Stations[i].fuelPrices = NULL;
            free(Stations[i].rating);
            Stations[i].rating = NULL;
            free(Stations[i].stuff);
            Stations[i].stuff = NULL;
            free(Stations+i);
        }
        Stations = NULL;
    }
}
