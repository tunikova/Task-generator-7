#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

    void graphics(int* width, int* height, int* I, int* N, int resolution[]);
    void audio(int* s, int* b, int* f, int* t, int frequency[], int* volume, int format[], int resolut[]);

    int main() {
        setlocale(LC_ALL, "Rus");

        int i, N, width, height;
        int I = 0;
        int resolution[] = { 300, 800, 1024, 1280, 1366, 1600, 1920, 2560, 3840 }; // в Кбайт


        int s, b, f, volume, t;
        int format[] = { 1, 2, 4 };
        int resolut[] = { 16, 24, 32 }; // в бит
        int frequency[] = { 32, 44, 48, 64 }; // кГц


        int choice;

        do {
            printf("Выберете тип 7 задания: 1 - кодирование графической информации, 2 - кодирование звука\n");
            scanf_s("%d", &choice);
            if (choice < 0 || choice > 2) printf("Ошибка\n");

            switch (choice) {
            case 1: graphics(&width, &height, &I, &N, resolution); break;
            case 2: audio(&s, &b, &f, &t, frequency, &volume, format, resolut); break;
            case 0: printf("Выход\n"); break;
            default: printf("Ошибка\n"); break;
            }
        } while (choice != 0 && (choice < 1 || choice > 2));

        if (choice == 1) {
            printf("Автоматическая фотокамера производит растровые изображения размером %d х %d пикселей. При этом объем файла с изображением не может превышать %d Кбайт, упаковка данных не производится. Какое максимальное количество цветов можно использовать в палитре?\n\n", width, height, I);
            printf("Правильный ответ: %d\n", N);
        }


        if (choice == 2) {
            printf("Производится %d-канальная звукозапись с частотой дискретизация %d кГц и %d-битным разрешением.В результате был получен файл размером %d Мбайт без учета заголовка и без сжатия данных.Определите длительность звукозаписи в минутах.\n\n", s, f, b, volume);
            printf("Правильный ответ: %d\n", t);
        }
        return 0;
    }

    void graphics(int* width, int* height, int* I, int* N, int resolution[]) {

        int i;
        int num_resolution = sizeof(resolution) / sizeof(resolution[0]);

        srand(time(0));
        int rand_width = rand() % num_resolution;
        int rand_height = rand() % num_resolution;

        *width = resolution[rand_width];
        *height = resolution[rand_height];

        while(1) {
            *I = rand() % (14400 - 11 + 1) + 11; // отдельно нашла мин и  задала макс значение при 512 возм цветах
            i = *I * 1024 * 8 / (*width * *height);
            *N = (int)pow(2, i);
            if ((i >= 1) && (i <= 9))
                break;
        } 

    }

    void audio(int* s, int* b, int* f, int* t, int frequency[], int* volume, int format[], int resolut[]) {

        int num_format = sizeof(format) / sizeof(format[0]);

        srand(time(0));
        int rand_s = rand() % num_format;
        *s = format[rand_s];

        int num_resolut = sizeof(resolut) / sizeof(resolut[0]);

        srand(time(0));
        int rand_b = rand() % num_resolut;
        *b = resolut[rand_b];

        int num_frequency = sizeof(frequency) / sizeof(frequency[0]);

        srand(time(0));
        int rand_f = rand() % num_frequency;
        *f = frequency[rand_f];

        while(1) {
            *volume = rand() % (1758 - 4 + 1) + 4; // отдельно нашла мин и задала макс знач при времени 30 мин
            *t = *volume * 1024 * 1024 * 8 / (*f * 1000 * *b * 60 * *s); 
            if ((*t <= 30) && (*t >= 1))
                break;
        }
    }
