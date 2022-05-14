#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <stdlib.h>

long long int readQPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}

void sort(int array[], int n)
{
    int temp;
    for (int x = 0; x < n - 1; x++)
    {
        for (int y = 0; y < n - 1 - x; y++)
        {
            if (array[y] > array[y + 1])
            {
                temp = array[y + 1];
                array[y + 1] = array[y];
                array[y] = temp;
            }
        }
    }
}

int main()
{
    int howMuch = 1000000;
    int *numberArray = malloc(1000000 * sizeof(int));

    int howMuchArr[] = {100, 500, 2500, 5000, 25000, 100000, 250000, 500000, 750000, 1000000};

    printf("---------- Wczytanie liczb -----------\n");

    FILE *myFile;
    myFile = fopen("liczby.txt", "r");

    printf("Ilosc wczytywanych liczb: %d\n", howMuchArr[(sizeof(howMuchArr) / sizeof(howMuchArr[1])) - 1]);

    // read file into array
    for (int i = 0; i < howMuchArr[(sizeof(howMuchArr) / sizeof(howMuchArr[1])) - 1]; i++)
    {
        fscanf(myFile, "%d,", &numberArray[i]);
    }

    printf("------------- Sortowanie -------------\n");

    FILE *ftw;
    ftw = fopen("wynik_Bombelkowe.txt", "w+");

    FILE *ftw2;
    ftw2 = fopen("wynik_Bombelkowe_liczby.txt", "w+");

    printf("Sortowanie rozpoczete\n");

    for (int i = 0; i < sizeof(howMuchArr) / sizeof(howMuchArr[1]); i++)
    {
        long long int elapsed, frequency, start;
        elapsed = 0;
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        start = readQPC();
        sort(numberArray, howMuchArr[i]);
        elapsed = (readQPC() - start);

        float elapsedInSec = floor(frequency * elapsed) / frequency / frequency;

        fprintf(ftw, "Sortowanie dla: %d plikow. \n ", howMuchArr[i]);
        fprintf(ftw, "Czas: %lf. \n \n", elapsedInSec);

        printf("Sortowanie %d\\%d zakonczone\n", i + 1, sizeof(howMuchArr) / sizeof(howMuchArr[1]));

        if (i == (sizeof(howMuchArr) / sizeof(howMuchArr[1])) - 1)
        {
            fprintf(ftw2, "%d", numberArray[0]);
            for (int j = 1; j < howMuchArr[sizeof(howMuchArr) / sizeof(howMuchArr[1]) - 1]; ++j)
            {
                fprintf(ftw2, ", %d", numberArray[j]);
            }
        }
    }

    printf("---- Zapis i czyszczenie pamieci ----\n");

    free(numberArray);

    fclose(ftw);
    fclose(ftw2);

    printf("Data saved to file: \"%s\"\n", "wynik_Bombelkowe.txt");
    printf("Data saved to file: \"%s\"\n", "wynik_Bombelkowe_liczby.txt");

    return 0;
}