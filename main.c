#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#define true 1
#define false 0
int czyPrzegrana = 0;
char inputNyga = '0';
int doZbicia[4];
char planszaGry[20][10];
int kS[4][2];
char strona = 0;

int planszaGryKolory[20][10];
int kolorSpadajocego;

const char *kolory[] = {"\x1b[32m", "\x1b[33m", "\x1b[34m", "\x1b[35m", "\x1b[36m", "\x1b[31m",  "\x1b[0m" };

void* inputo_trzymacz(void* arg) {
    while (1) {
        scanf(" %c", &inputNyga);
    }
}
void losowyKlocek() {
    kS[0][0] = 0;
    kS[0][1] = 4;
    int liczby[] = {-1,1};
    int kierunekNowy[2];
    for (int i = 1; i < 4; i++)
    {
        int aCzyB = rand() % 2;
        int plusCzyMinus = liczby[rand() % 2];
        //mango mango mango 67
        while (true)
        {
            for (int y = 0; y < 2; y++) {kierunekNowy[y] = kS[i-1][y];}

            kierunekNowy[aCzyB] = kS[i-1][aCzyB] + plusCzyMinus;
            int boolMango67 = true;
            for (int x = 0; x < i; x++) {
                if (kierunekNowy[0] == kS[x][0] && kierunekNowy[1] == kS[x][1]) {boolMango67 = false;}
            }
            if (boolMango67) {break;}

            if (plusCzyMinus == -1) {plusCzyMinus = 1;}
            else {plusCzyMinus = -1;}

            aCzyB = rand() % 2;
        }
        for (int y = 0; y < 2; y++) { kS[i][y] = kierunekNowy[y]; }
    }
    int z = 0;
    for (int i = 0; i < 4; i++) { if (kS[i][0] < z ) {z = kS[i][0];} }
    for (int i = 0; i < 4; i++) {kS[i][0] -= z;}

    kolorSpadajocego = rand() % 5;
}
void rotation() {
    char i[4][4];
    char m[4][4];

    //szukamy punktu minimum
    int punktMinimum[2];

    punktMinimum[0] = kS[0][0];
    punktMinimum[1] = kS[0][1];

    for (int z = 0; z < 4; z++) {
        if (punktMinimum[0] > kS[z][0] ) { punktMinimum[0] = kS[z][0]; }
        if (punktMinimum[1] > kS[z][1])  { punktMinimum[1] = kS[z][1]; }}

    //czyszczenie
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++)
        { m[y][x] = 0; } }

    for (int x = 0; x < 4; x++)
    { m[ kS[x][0] - punktMinimum[0] ][ kS[x][1] - punktMinimum[1] ] = 1; }

    for (int z = 0; z < 4; z++) {
        for (int y = 0; y < 4; y++)
        {
            i[z][y] =  m[y][z];
        }
    }
    int mangosLicznik = 3;
    for (int z = 0; z < 4; z++) {
        for (int y = 0; y < 4; y++)
        {
            m[z][y] = i[mangosLicznik][y];
        }
        mangosLicznik--;
    }
    //zwrócenie danych
    int licznikUwusny = 0;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (m[y][x]) {
                kS[licznikUwusny][0] = y + punktMinimum[0];
                kS[licznikUwusny][1] = x + punktMinimum[1];
                licznikUwusny++;
            }
        }
    }
}
void zerowanie()
{
    char znakFunkcji;
    strona = 0;
    for (int y = 0; y < 20; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            znakFunkcji = '#';
            planszaGry[y][x] = znakFunkcji;
            planszaGryKolory[y][x] = 6;
            if (y == 19) {
                znakFunkcji = '.';
                planszaGryKolory[y][x] = 1;
            }
        }
    }
}
void wypisywanieZawartosci()
{
    char planszaRobocza[20][10];

    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++) {
            planszaRobocza[y][x] = planszaGry[y][x];
        }
    }
    for (int i = 0; i < 4; i++) {
        int y = kS[i][0];
        int x = kS[i][1];
        planszaRobocza[ y ][ x ] = 'M';
    }
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++)
        {
            if (planszaRobocza[y][x] != 'M') { printf("%s%c%s", kolory[  planszaGryKolory[y][x]   ], planszaRobocza[y][x], kolory[6]); }
            else { printf("%s%c%s", kolory[5], planszaRobocza[y][x], kolory[6]); }
        }
        printf("\n");
    }
}
int lewoPrawo()
{
    int bool = 1;
    int prawoLewoPlusMinus = 0;

    if (inputNyga == 'a') { prawoLewoPlusMinus = -1; }
    else if (inputNyga == 'd') { prawoLewoPlusMinus = 1; }

    for (int z = 0; z < 4; z++) {
        if ( kS[z][1] <= 0 || kS[z][1] >= 9 ) {return 0;}
    }
    for (int i = 0; i < 4; i++)
    {
        int y = kS[i][0];
        int x = kS[i][1];

        if (planszaGry[y] [ x + prawoLewoPlusMinus ] != '#') {
            bool = 0;
        }
    }
    if (bool)
    {
        for (int i = 0; i < 4; i++) {
            kS[i][1] += prawoLewoPlusMinus;
        }
    }
    return 0;
}
void klocekSpada()
{
    int bool = 1;

    for (int i = 0; i < 4; i++)
    {
        if (planszaGry[kS[i][0] + 1] [ kS[i][1]] != '#'  ) {
            bool = 0;
        }
    }

    if (bool) {
        for (int i = 0; i < 4; i++) {
            kS[i][0]++;
        }
    }
    else
    {   //ustawienie tego na stałe
        for (int i = 0; i < 4; i++)
        {
            if (kS[i][0] < 1) {czyPrzegrana=1; return;}
            planszaGry[kS[i][0]] [ kS[i][1]] = 'F';
        }
        for (int i = 0; i < 4; i++) {planszaGryKolory[ kS[i][0] ][ kS[i][1] ] = kolorSpadajocego;}
        losowyKlocek();
    }
}
int czyZbijanie()
{
    int bool;
    for (int y = 0; y < 4; y++) {doZbicia[y] = -1;}

    int licznikNygaMeow = 0;

    for (int y = 0; y < 20; y++)
    {
        bool = 1;
        for (int x = 0; x < 10; x++)
        {
            if (planszaGry[y][x] != 'F') { bool= 0; }
        }
        if (bool) { doZbicia[licznikNygaMeow] = y;
            licznikNygaMeow++; }
    }

    if (licznikNygaMeow > 0) {return 1;}
    else {return 0;}
}
void zbijanie(int czyWOguleZaczac) {
    if (!czyWOguleZaczac) {return;}

    for (int i = 0; i < 4; i++)
    {
        if (doZbicia[i] < 0) {return;}

        for (int y = doZbicia[i]; y > 0; y--)
        {
            for (int x = 0; x < 10; x++ ) {
                planszaGry[y][x] = planszaGry[y-1][x];
            }
        }
        for (int x = 0; x < 10; x++) {
            planszaGry[0][x] = '#';
        }
    }
}
void poprawkiPoRotacji()
{
    int bool = 1;
    int najmniejszy = 0;
    int najwiekszy = 9;
    for (int i = 0; i < 4; i++) {
        if (kS[i][1] > najwiekszy)
        {najwiekszy = kS[i][1];}
        else if (kS[i][1] < najmniejszy)
        {najmniejszy = kS[i][1];}
    }
    if (najmniejszy < 0 )
    { for (int y = 0; y < 4; y++) {
            kS[y][1] = kS[y][1] + (najmniejszy * -1);
        }
    }
    else if (najwiekszy > 9) {
        printf("mango mango mango 67, sigma boy już leci na ciebie");
        for (int y = 0; y < 4; y++) {
            kS[y][1] = kS[y][1] - (najwiekszy - 9) ;
        }
    }
    //part 1
    bool = 1;
    while (true) {
        bool = 1;
        for (int i = 0; i < 4; i++) {
            if (planszaGry[ kS[i][0] ][ kS[i][1] ] != '#' ) { bool = 0; }
        }
        if (!bool)
        {
            for (int y = 0; y < 4; y++) {kS[y][0]--;}
        }
        else { break; }
    }
}
int main() {
    srand(time(NULL));

    pthread_t input_thread;
    pthread_create(&input_thread, NULL, inputo_trzymacz, NULL);
    zerowanie();
    losowyKlocek();
    while (true)
    {
        system("clear");
        zbijanie(czyZbijanie());
        wypisywanieZawartosci();
        usleep(900000);
        if (inputNyga == 'r') {
            rotation();
            poprawkiPoRotacji();
        }
        lewoPrawo();
        klocekSpada();
        inputNyga = '0';
        system("clear");
        if (czyPrzegrana) { break; }
    }
    pthread_join(input_thread, NULL);
}