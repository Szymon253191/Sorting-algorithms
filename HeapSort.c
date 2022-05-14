#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <math.h>

long long int readQPC()
{
    LARGE_INTEGER count;
    QueryPerformanceCounter(&count);
    return ((long long int)count.QuadPart);
}

void KopcowanieSort(int arr[], int n)
{
    int i,j,k,m,x,temp;
    
    for (i = 1; i <= n; i++)
    {
        j = i;
        k = j / 2;
        x = arr[i];
        while ((k > 0) && (arr[k] < x))
        {
            arr[j] = arr[k];
            j = k;
            k = j / 2;
        }
        arr[j] = x;
    }

    for (i = n; i > 1; i--)
    {
        temp = arr[i];
        arr[i] = arr[1];
        arr[1] = temp;

        j = 1;
        k = 2;
        while (k < i)
        {
            if ((k + 1 < i) && (arr[k + 1] > arr[k]))
                m = k + 1;
            else
                m = k;
            if (arr[m] <= arr[j])
                break;
            temp = arr[j];
            arr[j] = arr[m];
            arr[m] = temp;
            j = m;
            k = j + j;
            
        }

        if (arr[i] <= arr[0])
        {
            temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            //printf("Element 0: %d\n",arr[0]);
        }
    }
}

int main()
{
    int howMuch = 1000000;
    int *numberArray = malloc(1000000*sizeof(int));

    int howMuchArr[] = {100, 500, 2500, 5000, 25000, 100000, 250000, 500000, 750000, 1000000};


    printf("----------- Wczytanie liczb ----------\n");

    FILE *myFile;
    myFile = fopen("liczby.txt", "r");

    printf("Ilosc wczytywanych liczb: %d\n", howMuchArr[(sizeof(howMuchArr) / sizeof(howMuchArr[1])) - 1]);


    // read file into array
    for (int i = 0; i < howMuchArr[sizeof(howMuchArr) / sizeof(howMuchArr[1]) - 1]; i++)
    {
        fscanf(myFile, "%d,", &numberArray[i]);
    }
    
    printf("-------------- Sortowanie ------------\n");

    FILE *ftw;
    ftw = fopen("wynik_Kopcowanie.txt", "w+");

    FILE *ftw2;
    ftw2 = fopen("wynik_Kopcowanie_liczby.txt", "w+");

    printf("Sortowanie rozpoczete\n");

    for (int i = 0; i < sizeof(howMuchArr) / sizeof(howMuchArr[1]); i++)
    {
        long long int elapsed, frequency, start;
        elapsed = 0;
        QueryPerformanceFrequency((LARGE_INTEGER *)&frequency);

        start = readQPC();
        KopcowanieSort(numberArray, howMuchArr[i]);
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

    printf("Data saved to file: \"%s\"\n", "wynik_Kopcowanie.txt");
    printf("Data saved to file: \"%s\"\n", "wynik_Kopcowanie_liczby.txt");

    return 0;
}
