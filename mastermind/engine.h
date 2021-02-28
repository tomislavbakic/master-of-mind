#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <ctime>

using namespace std;

class Engine {
public:
    int brojPokusaja;
    int finalScore;
    char* lastCombination = NULL;

    struct Kombinacija {
        char niz[5];
        struct Kombinacija* sledeci;
    };

    struct Kombinacija* poc = NULL;

    Engine() {
        poc = init();
        finalScore = 0;
    }

    void restart() {
        finalScore += brojPokusaja;
        poc = init();
    }

    int dajUkupniScore() {
        return finalScore;
    }

    struct Kombinacija* init() {
        lastCombination = NULL;
        brojPokusaja = 0;
        int i, j, k, l;
        struct Kombinacija* poc = (struct Kombinacija*)malloc(sizeof(struct Kombinacija));
        struct Kombinacija* temp = NULL;
        poc = NULL;
        for (i = 0;i <= 9;i++) {
            for (j = 0;j <= 9;j++) {
                for (k = 0;k <= 9;k++) {
                    for (l = 0;l <= 9;l++) {
                        if (i == j || i == k || i == l || j == k || j == l || k == l) {
                            continue;
                        }
                        struct Kombinacija* novi = (struct Kombinacija*)malloc(sizeof(struct Kombinacija));
                        novi->niz[0] = i + '0';
                        novi->niz[1] = j + '0';
                        novi->niz[2] = k + '0';
                        novi->niz[3] = l + '0';
                        novi->niz[4] = '\0';

                        novi->sledeci = NULL;

                        if (poc == NULL) {
                            poc = novi;
                            temp = novi;
                        }
                        else {
                            temp->sledeci = novi;
                            temp = novi;
                        }

                    }
                }
            }
        }
        return poc;
    }

    void ispis() {
        struct Kombinacija* p = poc;
        int a = 0;
        while (p) {
            printf("%c %c %c %c\n", p->niz[0], p->niz[1], p->niz[2], p->niz[3]);
            a++;
            p = p->sledeci;
        }
        printf("UKUPNO ELEMENATA %d\n", a);
    }

    char* dajKombinaciju() {
        brojPokusaja++;
        if (poc == NULL) {
            char a[] = "error";
            return a;
        }
        struct Kombinacija* p = poc;
        int count = 0;
        struct Kombinacija* t = p;
        while (p != NULL) {
            p = p->sledeci;
            count++;
        }
        srand(time(0));
        int r = rand() % count;

        for (int i = 0;i < r;i++) {
            t = t->sledeci;
        }

        lastCombination = t->niz;

        return t->niz;
    }

    int provera(struct Kombinacija* cvor, int naMestu, int pogresnoMesto, char* str) {
        int i, j;
        int count = 0;
        if (cvor == NULL) {
            return -1;
        }
        pogresnoMesto = pogresnoMesto - naMestu;
        for (i = 0;i < 4;i++) {
            if (cvor->niz[i] == str[i]) {
                count++;
            }
        }
        if (naMestu != count) {
            return 0;
        }
        count = 0;
        for (i = 0;i < 4;i++) {
            for (j = 0;j < 4;j++) {
                if (i == j) {
                    continue;
                }
                if (cvor->niz[i] == str[j]) {
                    count++;
                }
            }
        }
        if (count != pogresnoMesto) {
            return 0;
        }
        return 1;
    }

    void redukujListu(int pogresnoMesto, int naMestu) {
        char* str = lastCombination;
        struct Kombinacija* pret;
        struct Kombinacija* tren;
        int a;
        while (1) {
            a = provera(poc, naMestu, pogresnoMesto, str);
            if (a == 0) {

                poc = poc->sledeci;
            }
            if (a == -1) {

                poc = NULL;
                return;
            }
            if (a == 1) {

                break;
            }
        }
        pret = poc;
        tren = poc->sledeci;
        while (tren) {
            a = provera(tren, naMestu, pogresnoMesto, str);
            if (a == 0) {
                pret->sledeci = tren->sledeci;
                tren = tren->sledeci;
            }

            else if (a == 1) {
                pret = tren;
                tren = tren->sledeci;
            }
            else if (a == -1) {

                poc = NULL;
                return;
            }
        }
    }

    int dajScore() {
        return brojPokusaja;
    }

};

/*int main(){
    Engine e;

    int naMestu,pogodjeni;
    while(1){
        char *kombinacija;
        kombinacija = e.dajKombinaciju();
        printf("%s\n",kombinacija);
        scanf("%d %d",&pogodjeni,&naMestu);
        if(naMestu==4){
            printf("KRAJJJ\n");
            cout << e.dajScore();
            break;
        }
        e.redukujListu(pogodjeni,naMestu,kombinacija);
        e.ispis();

    }

    e.restart();//za restartovanje engine-a
    e.ispis();

}*/
