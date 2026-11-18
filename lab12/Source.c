#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>
#ifdef _MSC_VER
#include <windows.h>
#endif

struct Truck
{
    char brand[50];
    char manufacturer[50];
    double capacity;
    int year;
    int day, month, reg_year;
};

struct Truck get_truck(void)
{
    struct Truck t = { 0 };

    printf("Марка автомобиля: ");
    scanf(" %49[^\n]", t.brand);
    printf("Производитель: ");
    scanf(" %49[^\n]", t.manufacturer);
    printf("Грузоподъемность (тонн): ");
    scanf("%lf", &t.capacity);
    printf("Год выпуска: ");
    scanf("%d", &t.year);
    printf("Дата регистрации (ДД.ММ.ГГГГ): ");
    scanf("%d.%d.%d", &t.day, &t.month, &t.reg_year);

    return t;
}

int show_truck(struct Truck t, int day, int month, int year)
{
    if (t.capacity > 3 &&
        (t.reg_year < year - 1 ||
            (t.reg_year == year - 1 && t.month < month) ||
            (t.reg_year == year - 1 && t.month == month && t.day < day)))
    {
        printf("\nМарка: %s\n", t.brand);
        printf("Производитель: %s\n", t.manufacturer);
        printf("Грузоподъемность: %.2f т\n", t.capacity);
        printf("Год выпуска: %d\n", t.year);
        printf("Дата регистрации: %02d.%02d.%04d\n", t.day, t.month, t.reg_year);
        return 1;
    }

    return 0;
}

void write_truck(FILE* file, struct Truck t)
{
    fprintf(file, "%s\t%s\t%.15g\t%d\t%02d.%02d.%04d\n",
        t.brand, t.manufacturer, t.capacity, t.year, t.day, t.month, t.reg_year);
}

int main(void)
{
    struct Truck truck1, truck2, truck3;
    int day = 0, month = 0, year = 0, count = 0, write_error;
    FILE* file;

    setlocale(LC_ALL, "Russian");
    setlocale(LC_NUMERIC, "C");
#ifdef _MSC_VER
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    printf("Введите текущую дату (ДД.ММ.ГГГГ): ");
    scanf("%d.%d.%d", &day, &month, &year);

    printf("\nГрузовик 1:\n");
    truck1 = get_truck();
    printf("\nГрузовик 2:\n");
    truck2 = get_truck();
    printf("\nГрузовик 3:\n");
    truck3 = get_truck();

    printf("\nПодходящие грузовики на дату %02d.%02d.%04d:\n", day, month, year);
    count += show_truck(truck1, day, month, year);
    count += show_truck(truck2, day, month, year);
    count += show_truck(truck3, day, month, year);

    if (count == 0)
        printf("Подходящих грузовиков нет.\n");

    file = fopen("trucks.txt", "w");
    if (file == NULL)
    {
        perror("trucks.txt");
        return 1;
    }

    write_truck(file, truck1);
    write_truck(file, truck2);
    write_truck(file, truck3);

    write_error = ferror(file);
    if (fclose(file) == EOF || write_error)
    {
        perror("trucks.txt");
        return 1;
    }

    printf("\nДанные записаны в trucks.txt.\n");

    return 0;
}
