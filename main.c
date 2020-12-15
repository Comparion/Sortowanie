#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
funkcja zamienia miejscami ze soba dwa elementy
*/

void swap(int *first, int *second)
{
    int temporary = *first;
    *first = *second;
    *second = temporary;
}

/*
funkcja znadjuje lewgo potomka dla kopcowania
*/
static inline int get_left_child_index(int index)
{
    return (index << 1) + 1;
}
/*
funkcja znadjuje prawego potomka dla kopcowania
*/
static inline int get_right_child_index(int index)
{
    return (index << 1) + 2;
}
/*
funkcja potrzebna dla heapsorta, aby przodek był wiekszy od swoich potomków
*/
void heapify(int array[], int index, unsigned int size)
{
    int left = get_left_child_index(index),
        right = get_right_child_index(index),
        largest = index;
    if(left<=size)
        if(array[left]>array[index])
                largest = left;
    if(right<=size)
        if(array[right]>array[largest])
            largest = right;
    if(largest!=index) {
        swap(&array[index],&array[largest]);
        heapify(array,largest,size);
    }
}
/*
funkcja  buduje kopiec w tablicy która ma byc posortowana
*/
void build_heap(int array[],const int number_of_elements)
{
    int i;
    for(i=number_of_elements/2;i>=0;i--)
        heapify(array,i,number_of_elements-1);
}
/*
glowna funkcja heap sort
*/
void heapsort(int array[],int last_index)
{

    int i;

    build_heap(array,last_index);
    for(i=last_index;i>0;i--){
        swap(&array[0],&array[i]);
        heapify(array,0,--last_index);
    }
}

/*
funkcja sortuje bąbelkowo
*/

void bubblesort(int tab[], int n)
{
    int i,j;
    for(i=1;i<n;i++){
        for(j=n-1;j>=1;j--){
            if(tab[j]<tab[j-1]){
                int swap;
                swap=tab[j-1];
                tab[j-1]=tab[j];
                tab[j]=swap;
            }
        }
    }
}

/*
funkcja potrzebna do quicksort, ma na celu podzielenie tablicy na 2 czesci
*/

int partition(int array[], int low, int high)
{
    int pivot = array[low];
    int i = low-1, j = high+1;

    while(i<j) {
        while(array[--j]>pivot)
            ;
        while(array[++i]<pivot)
            ;
        if(i<j)
            swap(&array[i],&array[j]);
    }
    return j;
}

/*
glowna czesc funkcji quicksort
*/

void quicksort(int array[], int low, int high)
{
    if(low<high) {
        int partition_index = partition(array,low,high);
        quicksort(array, low, partition_index);
        quicksort(array, partition_index+1, high);
    }
}

/*
funkcja jest odpwieidzalana za zakres losowanych liczb, oraz za ich wylosowanie
*/

void fill_zakres(int tab[], int n)
{
    srand(time(NULL));
    int i;

    int a,b,y,z;
    printf("Podaj zakres losowania liczb:\n");
    printf("Od: ");
    scanf("%d", &a);
    printf("Do: ");
    scanf("%d", &b);
    printf("Zakres %d %d\n", a,b);
    y=a;
    z=b;
    if(a<0){
        y=a*(-1);
    }
    if(b<0){
        z=b*(-1);
    }
    printf("y: %d z: %d\n", y,z);

    int x;
    if(a>=0){
        x=b-a+1;
    }
    else{
        x=y+z+1;
    }
    for(i=0;i<n;i++){
        tab[i]=(rand()%x)+a;
    }
    system("cls");
    printf("Zakres %d %d\n", a,b);

}
/*
funkcja wypisuje elementy tablicy
*/
void print_tab(int tab[],int n)
{
    int i;
    for(i=0;i<n;i++){
        printf("%d ",tab[i]);
    }
}
/*
funkcja kopiujaca zawartosc jednej tablicy do drugiej
*/
void copy_tab(int tab[], int tab2[], int n)
{
    int i;
    for(i=0;i<n;i++){
        tab2[i]=tab[i];
    }
}
/*
funkcja funkcja zapisujaca zawartosc tablicy do pliku
*/
void write_file(int tab[], FILE *f, int n)
{
    int i;
    for(i=0;i<n;i++){
        fprintf(f,"%d ",tab[i]);
    }
}

/*
glowana funkcja w ktorej jest zawarte menu i najwazniejsza czesc programu
wywolujaca inne podfunckje
*/

int main()
{
/*
inicjacja zmiennych potrzebnych do mierzenia czasu, obsługi menu oraz plików
*/
    clock_t start,stop;
    double czas;
    int numer;

    FILE *f;



    while(1){
        system("cls");
        printf("Co chcesz zrobic: \n\n");

        printf("1.Mierzenie czasu sortowania babelkowego dla n elemenow\n");
        printf("2.Wyswietlenie tablicy przed i po sortowaniu\n");
        printf("3.Mierzenie czasu sortowania quicksort dla n elemenow\n");
        printf("4.Sortowanie liczb podanych przez uzytkownika\n");
        printf("5.Porownanie czasu bubblesort, quicksort oraz heapsort\n");
        printf("6.Mierzenie czasu sortowania heapsort dla n elemenow\n");
        printf("0.Zakoncz dzialanie programu \n");
        scanf("%d", &numer);
/*
fragment kodu odpowiadajacy za pobranie od uzytkownika ilosci liczb do wylosowania,
zakresu losowanych liczb a nastepnie zmierzenia czasu trwania sortowania
*/
        if(numer==1){
            system("cls");

            int n;
            printf("Ile liczb wylosowac: ");
            scanf("%d", &n);

            int tab[n];
            fill_zakres(tab,n);

            start = clock();
            bubblesort(tab,n);
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;
            printf("Posortowanie metoda babelkowa %d liczb zajmie: %lf s\n",n,czas);
            puts("");
            system("pause");
        }
/*
fragment kodu:
uzupełniający tablice wylosowanymi z podanego zakresu liczbami
otwarcie pliku *.txt oraz uzupełnienie go wylosowanymi liczbami
wybór rodzaju sortowania
wpisanie do pliku posortowanej tablicy

*/
        else if(numer==2){
            system("cls");
            int n;
            printf("Ile liczb wylosowac: ");
            scanf("%d", &n);

            int tab[n];
            fill_zakres(tab,n);

            if ((f = fopen("przed_sortowaniem.txt", "w+")) == 0)
            {
                system("cls");
                puts("Blad z plikiem");
                system("pause");
            }
            write_file(tab, f , n);
            fclose(f);

            puts("");
            printf("Wylosowane liczby zostaly zapisane do pliku przed_sortowaniem.txt\n");
            puts("");
            printf("Jakiego sortowania chcesz uzyc:\n1.Bubblesort\n2.Quicksort\n3.Heapsort\n");
            int x;
            scanf("%d", &x);

            if(x==1){
                system("cls");
                puts("\nPrzed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                bubblesort(tab,n);
                print_tab(tab,n);
            }
            else if(x==2){
                system("cls");
                puts("\nPrzed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                quicksort(tab,0,n-1);
                print_tab(tab,n);
            }

            else if(x==3){
                system("cls");
                puts("\nPrzed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                heapsort(tab,n-1);
                print_tab(tab,n);
            }
            else{
                printf("Zla wartosc");
            }
            puts("");

            if ((f = fopen("po_sortowaniu.txt", "w+")) == 0)
            {
                system("cls");
                puts("Blad z plikiem");
                system("pause");
            }
            write_file(tab, f , n);
            fclose(f);

            printf("Posortowane liczby zostaly zapisane do pliku po_sortowaniu.txt\n");


            system("pause");
        }

         else if(numer==3){
            system("cls");

            int n;
            printf("Ile liczb wylosowac: ");
            scanf("%d", &n);

            int tab[n];
            fill_zakres(tab,n);

            start = clock();
            quicksort(tab,0,n-1);
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;
            printf("Posortowanie metoda quicksort %d liczb zajmie: %lf s\n",n,czas);
            puts("");
            system("pause");
         }

          else if(numer==6){
            system("cls");

            int n;
            printf("Ile liczb wylosowac: ");
            scanf("%d", &n);

            int tab[n];
            fill_zakres(tab,n);

            start = clock();
            heapsort(tab,n-1);
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;
            printf("Posortowanie metoda heapsort %d liczb zajmie: %lf s\n",n,czas);
            puts("");
            system("pause");
         }
/*
kod odpowiedzialny za:
pobranie od uzytkownika ilości liczb które chce wprowadzić
uzupełnienie tablicy podanymi przez uzytkownika liczbami
uzupełnienie jednego pliku warotściami wpisanymi a drugiego posortownymi
*/
         else if(numer==4){
            system("cls");
            int n, i, dane;
            printf("Ile liczb chcesz wprowadzic: ");
            scanf("%d", &n);
            int tab[n];

            for(i=0;i<n;i++){
                system("cls");
                printf("Aktualna zawartosc tablicy:\n");
                print_tab(tab,i);
                printf("\nWprowadz liczbe: ");
                scanf("%d", &dane);
                tab[i]=dane;
            }
            system("cls");

             if ((f = fopen("przed_sortowaniem.txt", "w+")) == 0)
            {
                system("cls");
                puts("Blad z plikiem");
                system("pause");
            }
            write_file(tab, f , n);
            fclose(f);

            puts("");
            printf("Wpisane liczby zostaly zapisane do pliku przed_sortowaniem.txt\n");
            puts("");
            printf("Jakiego sortowania chcesz uzyc:\n1.Bubblesort\n2.Quicksort\n3.Heapsort\n");
            int sortowanie;
            scanf("%d", &sortowanie);

            if(sortowanie==1){
                system("cls");
                puts("Przed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                bubblesort(tab,n);
                print_tab(tab,n);
            }
            else if(sortowanie==2){
                system("cls");
                puts("Przed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                quicksort(tab,0,n-1);
                print_tab(tab,n);
            }
             else if(sortowanie==3){
                system("cls");
                puts("Przed sortowaniem :");
                print_tab(tab,n);
                puts("");
                puts("Po sortowaniu: ");
                heapsort(tab,n-1);
                print_tab(tab,n);
            }
            else{
                printf("Zla wartosc");
            }

            puts("");

            if ((f = fopen("po_sortowaniu.txt", "w+")) == 0)
            {
                system("cls");
                puts("Blad z plikiem");
                system("pause");
            }
            write_file(tab, f , n);
            fclose(f);

            printf("Posortowane liczby zostaly zapisane do pliku po_sortowaniu.txt\n");

            system("pause");
        }

/*
kod odpowiedzialny za:
pobranie ilości liczb oraz zakresu do ich wylosowania
skopiowanie uzupełnionej tablicy tak aby każdy rodzaj sortowania działał na tych samych liczbach
wykonanie każdego sortowania sprawdzająć czas działania
*/
        else if(numer == 5){
            system("cls");
            int n;
            printf("Ile liczb wylosowac: ");
            scanf("%d", &n);

            int tab[n];
            int tab2[n];
            int tab3[n];
            double wynik, a, b;

            fill_zakres(tab,n);
            copy_tab(tab,tab2,n);
            copy_tab(tab,tab3,n);

            start = clock();
            bubblesort(tab2,n);
            stop = clock();
            a = czas = (double)(stop-start)/CLOCKS_PER_SEC;
            printf("Posortowanie metoda babelkowa zajmie: %lf s\n",czas);
            puts("");

            start = clock();
            quicksort(tab,0,n-1);
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;

            printf("Posortowanie metoda quicksort zajmie: %lf s\n",czas);
            puts("");

            start = clock();
            heapsort(tab3,n);
            stop = clock();
            czas = (double)(stop-start)/CLOCKS_PER_SEC;
            printf("Posortowanie metoda heapsort zajmie: %lf s\n",czas);
            puts("");

            system("pause");
        }
/*
warunek odpowiedzialny za zakończenie działania programu
*/
        else if(numer == 0){
            system("cls");
            printf("Zakonczono dzialanie.");
            return 0;
        }
/*
warunek sprawdzający czy została wybrana prawidłowa opcja z menu głównego
*/
        else{
            system("cls");
            puts("Blad! Podaj odpowiednia wartosc.");
            system("pause");
        }
    }
}
