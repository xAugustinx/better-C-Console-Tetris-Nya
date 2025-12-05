#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define true 1
#define false 0

char planszaGry[20][10];
int kS[4][2];
char strona = 0;

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
            if (y == 19) {
                znakFunkcji = '.';
            }
            planszaGry[y][x] = znakFunkcji;

        }
    }
}
void wypisywanieZawartosci()
{
    for (int y = 0; y < 20; y++) {
        for (int x = 0; x < 10; x++)
        {
            printf("%c", planszaGry[y][x]);
        }
        printf("\n");
    }
}


int main() {
    srand(time(NULL));
    zerowanie();

    losowyKlocek();

    rotation();


}