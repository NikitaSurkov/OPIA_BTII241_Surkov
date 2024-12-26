//Директивы
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_RECORDS 100

// Структура записи Wi-Fi роутеров
typedef struct
{
    char manufacturer[50];
    int wired_speed;
    char wifi_standard[10];
    int lan_ports;
    float max_wifi_speed;
    char vpn_features[50];
} WiFiRouter;

// Глобальные переменные
WiFiRouter routers[MAX_RECORDS];
int router_count = 0;

// Прототипы функций
void addRecord();
void addMultipleRecords();
void searchRecord();
void saveToFile();
void loadFromFile();
void printRecords();
void sortRecords();
void editRecord();

// Главная функция
int main()
{
    setlocale(LC_ALL, "RUS");
    int choice;
    loadFromFile();

    do
    {
        printf("\n--- База данных Wi-Fi роутеров ---\n");
        printf("1. Добавить запись\n");
        printf("2. Добавить несколько записей\n");
        printf("3. Поиск записи\n");
        printf("4. Сохранить в файл\n");
        printf("5. Загрузить из файла\n");
        printf("6. Печать всех записей\n");
        printf("7. Сортировка записей\n");
        printf("8. Редактировать запись\n");
        printf("9. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1: addRecord(); break;
        case 2: addMultipleRecords(); break;
        case 3: searchRecord(); break;
        case 4: saveToFile(); break;
        case 5: loadFromFile(); break;
        case 6: printRecords(); break;
        case 7: sortRecords(); break;
        case 8: editRecord(); break;
        case 9: printf("Выход...\n"); break;
        default: printf("Неверный ввод!\n");
        }
    } while (choice != 9);

    return 0;
}

// Добавление одной записи
void addRecord()
{
    if (router_count >= MAX_RECORDS)
    {
        printf("База данных переполнена!\n");
        return;
    }

    printf("Введите производителя: ");
    scanf("%s", routers[router_count].manufacturer);
    printf("Введите скорость проводного соединения (Мбит/с): ");
    scanf("%d", &routers[router_count].wired_speed);
    printf("Введите стандарт Wi-Fi: ");
    scanf("%s", routers[router_count].wifi_standard);
    printf("Введите количество LAN портов: ");
    scanf("%d", &routers[router_count].lan_ports);
    printf("Введите максимальную скорость Wi-Fi (Мбит/с): ");
    scanf("%f", &routers[router_count].max_wifi_speed);
    printf("Функции VPN (1 - да, 0 - нет): ");
    scanf("%s", routers[router_count].vpn_features);

    router_count++;
    printf("Запись успешно добавлена!\n");
}

// Добавление нескольких записей
void addMultipleRecords()
{
    int n;
    printf("Сколько записей вы хотите добавить? ");
    scanf("%d", &n);

    if (router_count + n > MAX_RECORDS)
    {
        printf("Недостаточно места для %d записей. Доступно максимум %d.\n", n, MAX_RECORDS - router_count);
        return;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nДобавление записи #%d:\n", i + 1);
        addRecord();
    }

    printf("%d записей успешно добавлено!\n", n);
}

// Поиск записи
void searchRecord()
{
    char manufacturer[50];
    printf("Введите производителя для поиска: ");
    scanf("%s", manufacturer);

    for (int i = 0; i < router_count; i++) {
        if (strcmp(routers[i].manufacturer, manufacturer) == 0)
        {
            printf("\nНайдена запись:\n");
            printf("Производитель: %s\n", routers[i].manufacturer);
            printf("Скорость (Мбит/с): %d\n", routers[i].wired_speed);
            printf("Стандарт Wi-Fi: %s\n", routers[i].wifi_standard);
            printf("LAN порты: %d\n", routers[i].lan_ports);
            printf("Макс. скорость Wi-Fi (Мбит/с): %.2f\n", routers[i].max_wifi_speed);
            printf("Функции VPN (1 - да, 0 - нет): %s\n", routers[i].vpn_features);
            return;
        }
    }
    printf("Запись не найдена!\n");
}

// Сохранение в файл
void saveToFile()
{
    FILE* file = fopen("wifi_routers.db", "wb");
    if (!file)
    {
        printf("Ошибка открытия файла для сохранения!\n");
        return;
    }
    fwrite(&router_count, sizeof(int), 1, file);
    fwrite(routers, sizeof(WiFiRouter), router_count, file);
    fclose(file);
    printf("Данные успешно сохранены в файл!\n");
}

// Загрузка из файла
void loadFromFile()
{
    FILE* file = fopen("wifi_routers.db", "rb");
    if (!file)
    {
        printf("Файл не найден, создание новой базы данных.\n");
        return;
    }
    fread(&router_count, sizeof(int), 1, file);
    fread(routers, sizeof(WiFiRouter), router_count, file);
    fclose(file);
    printf("Данные успешно загружены из файла!\n");
}

// Печать всех записей
void printRecords()
{
    if (router_count == 0)
    {
        printf("База данных пуста!\n");
        return;
    }
    for (int i = 0; i < router_count; i++)
    {
        printf("\nЗапись #%d:\n", i + 1);
        printf("Производитель: %s\n", routers[i].manufacturer);
        printf("Скорость (Мбит/с): %d\n", routers[i].wired_speed);
        printf("Стандарт Wi-Fi: %s\n", routers[i].wifi_standard);
        printf("LAN порты: %d\n", routers[i].lan_ports);
        printf("Макс. скорость Wi-Fi (Мбит/с): %.2f\n", routers[i].max_wifi_speed);
        printf("Функции VPN (1 - да, 0 - нет): %s\n", routers[i].vpn_features);
    }
}

// Сортировка по максимальной скорости Wi-Fi
void sortRecords()
{
    for (int i = 0; i < router_count - 1; i++)
    {
        for (int j = 0; j < router_count - i - 1; j++)
        {
            if (routers[j].max_wifi_speed < routers[j + 1].max_wifi_speed)
            {
                WiFiRouter temp = routers[j];
                routers[j] = routers[j + 1];
                routers[j + 1] = temp;
            }
        }
    }
    printf("Записи отсортированы по максимальной скорости Wi-Fi.\n");
}

// Редактирование записи
void editRecord()
{
    int index;
    printf("Введите номер записи для редактирования (1-%d): ", router_count);
    scanf("%d", &index);
    if (index < 1 || index > router_count)
    {
        printf("Некорректный номер записи!\n");
        return;
    }
    addRecord();
}