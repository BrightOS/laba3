#pragma ide diagnostic ignored "hicpp-multiway-paths-covered"
#pragma ide diagnostic ignored "cert-err34-c"
#pragma ide diagnostic ignored "performance-inefficient-string-concatenation"

#include <cstdio>
#include <cmath>
#include <deque>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>

using namespace std;

short a;
int b, n, k;
long c;
long long d;
double e;
float f;
vector<unsigned char> list;

void set_color(int text_color) {
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE); // Console descriptor
    SetConsoleTextAttribute(hStdOut, (WORD) (text_color));
}

/**
 * Функции с побитовыми операциями.
 */

static string get_byte(const unsigned char *p) {
    unsigned char mask = 0x80;

    string s;

    for (unsigned char i = 0; i < 8; i++) {
        if (((mask >> i) & *p) == 0)
            s += "0";
        else
            s += "1";

        if (i % 4 == 3)
            s += " ";
    }

    return s;
}

template<typename T>
static void reverse_at_position(T &number, int pos) {
    unsigned long long mask = 0x80;
    for (int i = 0; i < sizeof(number) - 1; i++)
        mask *= 0x100;

    number ^= mask >> (pos - 1);
}

template<typename T>
static void set_at_position(T &number, int pos, bool x) {
    unsigned long long mask = 0x80;
    for (int i = 0; i < sizeof(number) - 1; i++)
        mask *= 0x100;

    number ^= (-x ^ number) & (mask >> (pos - 1));
}

/**
 * Функции вывода конкретных видов представления числа.
 */

template<typename T>
static string internal(T number) {
    auto *p = reinterpret_cast<unsigned char *>(&number);

    string internal;

    for (int i = 0; i < sizeof(number); i++)
        internal = get_byte(p++) + internal;

    return internal;
}

template<typename T>
static string reversed(T number) {
    if (number >= 0)
        return internal(number);

    T x = number;
    x--;

    return internal(x);
}

template<typename T>
static string straight(T number) {
    if (number >= 0)
        return internal(number);

    for (int i = 2; i <= sizeof(number) * 8; i++)
        reverse_at_position(number, i);

    T x = number;
    x++;

    return internal(x);
}

/**
 * Функции, которые просят пользователя ввести что-либо конкретное.
 */

void input_bit_num() {
    set_color(11);
    printf("\nВведите номер бита:\n");

    set_color(10);
    printf("> ");
    set_color(7);

    scanf("%d", &n);

    set_color(7);
    printf("%hd", a);
    set_color(10);
    printf(" -> ");
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    start:
    n = 0;
    set_color(11);
    printf("Выберите одно из заданий:\n");
    set_color(7);
    printf("1. Побитовая работа с числом (short).\n");
    printf("2. Отображение числа в памяти компьютера (integral).\n");
    printf("3. Отображение числа в памяти компьютера (real).\n");
    printf("4. Решето Эратосфена.\n");
    printf("0. Выйти из программы.\n");

    n = 5;
    do {
        set_color(10);
        printf("> ");
        set_color(7);
        scanf("%d", &n);
    } while (n > 4 || n < 0);

    if (n == 0)
        goto end;

    set_color(11);
    printf("\rВыбрано задание: ");
    set_color(7);

    switch (n) {
        case 1:
            printf("Побитовая работа с числом (short).\n\n");
            set_color(11);
            printf("Введите оперируемое число:\n");

            a = 0;

            set_color(10);
            printf("> ");
            set_color(7);
            scanf("%hd", &a);
            printf("\n");

            while (true) {
                set_color(11);
                printf("Текущее оперируемое число: ");
                set_color(7);
                printf("%d\n", a);
                printf("Внутреннее представление -> %s\n", internal(a).c_str());

                set_color(11);
                printf("Выберите одно из действий:\n");
                set_color(7);
                printf("1. Изменить бит числа на противоположный.\n");
                printf("2. Сделать бит числа нулём.\n");
                printf("3. Сделать бит числа единицей.\n");
                printf("4. Показать представление числа во внутренней памяти компьютера.\n");
                printf("0. Назад.\n");

                n = 5;
                do {
                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%d", &n);
                } while (n > 4 || n < 0);

                switch (n) {
                    case 0:
                        printf("\n");
                        goto start;

                    case 1:
                        input_bit_num();
                        reverse_at_position(a, n);
                        set_color(7);
                        printf("%hd\n\n", a);
                        break;

                    case 2:
                        input_bit_num();
                        set_at_position(a, n, false); // false = 0
                        set_color(7);
                        printf("%hd\n\n", a);
                        break;

                    case 3:
                        input_bit_num();
                        set_at_position(a, n, true); // true = 1
                        set_color(7);
                        printf("%hd\n\n", a);
                        break;

                    case 4:
                        printf("Прямой код -> %s\n", straight(a).c_str());
                        printf("Обратный код -> %s\n", reversed(a).c_str());
                        printf("Дополнительный код -> %s\n\n", internal(a).c_str());
                        break;

                    default:
                        break;
                }
            }
        case 2:
            printf("Отображение числа в памяти компьютера (integral).\n\n");

            set_color(11);
            printf("Выберите тип целочисленного числа:\n");
            set_color(7);
            printf("1. short\n");
            printf("2. int\n");
            printf("3. long\n");
            printf("4. long long\n");

            n = 5;
            do {
                set_color(10);
                printf("> ");
                set_color(7);
                scanf("%d", &n);
            } while (n < 0 || n > 4);

            set_color(11);
            printf("\rВыбран тип: ");
            set_color(7);

            switch (n) {
                case 1:
                    printf("short.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    a = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%hd", &a);

                    printf("\nDUMP -> %s\n", internal(a).c_str());
                    printf("Прямой код -> %s\n", straight(a).c_str());
                    printf("Обратный код -> %s\n", reversed(a).c_str());
                    printf("Дополнительный код -> %s\n\n", internal(a).c_str());

                    goto start;
                case 2:
                    printf("int.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    b = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%d", &b);

                    printf("\nDUMP -> %s\n", internal(b).c_str());
                    printf("Прямой код -> %s\n", straight(b).c_str());
                    printf("Обратный код -> %s\n", reversed(b).c_str());
                    printf("Дополнительный код -> %s\n\n", internal(b).c_str());

                    goto start;

                case 3:
                    printf("long.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    c = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%ld", &c);

                    printf("\nDUMP -> %s\n", internal(c).c_str());
                    printf("Прямой код -> %s\n", straight(c).c_str());
                    printf("Обратный код -> %s\n", reversed(c).c_str());
                    printf("Дополнительный код -> %s\n\n", internal(c).c_str());

                    goto start;

                case 4:
                    printf("long long.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    d = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%lld", &d);

                    printf("\nDUMP -> %s\n", internal(d).c_str());
                    printf("Прямой код -> %s\n", straight(d).c_str());
                    printf("Обратный код -> %s\n", reversed(d).c_str());
                    printf("Дополнительный код -> %s\n\n", internal(d).c_str());

                    goto start;
                default:
                    break;
            }
            break;
        case 3:
            printf("Отображение числа в памяти компьютера (real).\n\n");

            set_color(11);
            printf("Выберите тип целочисленного числа:\n");
            set_color(7);
            printf("1. float\n");
            printf("2. double\n");

            n = 3;
            do {
                set_color(10);
                printf("> ");
                set_color(7);
                scanf("%d", &n);
            } while (n < 0 || n > 2);

            set_color(11);
            printf("\rВыбран тип: ");
            set_color(7);

            switch (n) {
                case 1:
                    printf("float.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    f = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%f", &f);

                    printf("\nВнутреннее представление -> %s\n\n", internal(f).c_str());

                    goto start;
                case 2:
                    printf("double.\n\n");

                    set_color(11);
                    printf("Введите оперируемое число:\n");

                    e = 0;

                    set_color(10);
                    printf("> ");
                    set_color(7);
                    scanf("%f", &e);

                    printf("\nВнутреннее представление -> %s\n\n", internal(e).c_str());

                    goto start;
                default:
                    break;
            }

        case 4:
            printf("Решето Эратосфена.\n\n");

            n = 10000000;

            ofstream fout("simple.txt");

            for (int i = 0; i <= n / 8; ++i)
                list.push_back(0xFF); // Каждый байт заполняем единицами

            for (int i = 2; i <= n; i++) {

                if (i % 100 == 0)
                    fout << "\n";

                if (list[i / 8] & (0x80 >> i % 8)) {
                    fout << i << " ";

                    for (int j = 2 * i; j <= n; j += i)
                        list[j / 8] &= ~(0x80 >> (j % 8));
                }
            }

            set_color(10);
            printf("Программа завершила свою работу! Проверяйте файл simple.txt!\n\n");

            goto start;
    }
    end:
    printf("\n");
}