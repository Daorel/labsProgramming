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
    float* fuelPrices;                  //���� ���� �� �������(92,95,98,������)
    int* rating;                        //������� ���(1-10)
} GSDesc;
/*----------------------------�������------------------------------*/
int Menu();                                     //����
void OutputMenu(GSDesc*, int);                  //������� ������, int - ���-�� ���������
void Info();                                    //�������
void OutputGasStationsTable(GSDesc*, int);      //����� ���������� � ���� �������, int - ���-�� ���������
void OutputGasStationsText(GSDesc*, int);       //����� ���������� � ���� ������, int - ���-�� ���������
GSDesc* InputInfo(int*);                        //���� ���������
void InputText(char*);                          //���� ������
GSDesc* Process(GSDesc*, int, int*);            //��������� ������
int PrepareStruct(GSDesc*);                     //��������� ������ ��� ����� ���������
GSDesc* free_struct(GSDesc*, int);                 //������������ ������
/*-----------------------------------------------------------------*/
int main()
{
    setlocale(LC_ALL, "russian");
    GSDesc  *GasStations = NULL,        //���
            *GSResult = NULL;           //��������� ������
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
                GasStations = free_struct(GasStations, i);
                GasStations = InputInfo(&i);
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
                    GSResult = free_struct(GSResult, ri);
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
    GasStations = free_struct(GasStations, i);
    GSResult = free_struct(GSResult, ri);
    return 0;
}

GSDesc* InputInfo(int* amount)
{
    GSDesc* Stations = NULL;
    int i,
        j = 0,
        f;
    do
    {
        system("cls");
        Stations = (GSDesc*)realloc(Stations, (j+1)*sizeof(GSDesc));
        if(PrepareStruct(&Stations[j]))
        {
            puts("������� �������� ���: ");
            InputText(Stations[j].name);
            puts("\n������� �����: ");
            InputText(Stations[j].address);
            printf("\n������� ���� �� �������(92,95,98,������): ");
            for(i = 0; i < 4; i++)
            {
                do
                {
                    scanf("%f", Stations[j].fuelPrices+i);
                    if(Stations[j].fuelPrices[i] < 1 || Stations[j].fuelPrices[i] > 10000) puts("1-10000");
                } while(Stations[j].fuelPrices[i] < 1 || Stations[j].fuelPrices[i] > 10000);
            }
            printf("������� ������� ���: ");
            do
            {
                scanf("%d", Stations[j].rating);
                if(*(Stations[j].rating) < 1 || *(Stations[j].rating) > 10) puts("1-10");
            } while(*(Stations[j].rating) < 1 || *(Stations[j].rating) > 10);
            j++;
            puts("������� ����� �����, �������� �� ����, ���� ������ ���������� ���� ������");
            scanf("%d", &f);
        }
        else f = 0;
    } while(f);
    *amount = j;
    system("pause");
    return Stations;
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
        if(c == 13 && i == 0)
            puts("������ �� ����� ���� ������!");
    } while(i < MAXLEN && (c != 13 || i == 0));
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
    printf("|%*s|%*s|���� 92 �������|���� 95 �������|���� 98 �������|���� ������|�������|\n", namelen, "��������", addresslen, "�����");
	for(i = 0; i < lines; i++)
		printf("|%*s|%*s|%15.2f|%15.2f|%15.2f|%11.2f|%7d|\n", namelen, GasStations[i].name, addresslen, GasStations[i].address,
         GasStations[i].fuelPrices[0], GasStations[i].fuelPrices[1], GasStations[i].fuelPrices[2], GasStations[i].fuelPrices[3], *(GasStations[i].rating));
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
                strcpy(result[j].name, GasStations[i].name);
                strcpy(result[j].address, GasStations[i].address);
                for(k = 0; k < 4; k++)
                    result[j].fuelPrices[k] = GasStations[i].fuelPrices[k];
                *(result[j].rating) = *(GasStations[i].rating);
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
        res++;
    }
    return res;
}
/*------------------------------------------------���� � �������---------------------------------------------*/
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
        if(selected == 1) OutputGasStationsTable(GasStations, lines);
        else if(selected == 2) OutputGasStationsText(GasStations, lines);
    }while(selected);
}

void Info()
{
    system("cls");
    puts("  ������ ��������� ��������� ��� ������ ��� ������� ���,");
    puts("������� ��������� ���������: ��������, �����, ���� �� ������� � �������");
    puts("  ����� '���������' ������������� ��� ����� ����� ��� ���,");
    puts("������� ������������� ��������� ��������:");
    puts("������� ���� 7, ���� �� 98 ������ ���� 54\n");
    puts("  ��������! ���-�� ���� � �������� � ������ �� ����� ��������� 80!\n");
    system("pause");
}

GSDesc* free_struct(GSDesc* Stations, int lines)
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
            free(Stations+i);
        }
        Stations = NULL;
    }
    return NULL;
}
