#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct magazin {

    int id_produs;
    float pret_unit;
    int cantitate;
    int ziua;
    int luna;
    int anul;
    float venit_total;
    char nume_produs[100];
    char categorie_produs[100];
    char tara[100];
    char orasul[100];
    char sub_categorie[100];
    char data[10];
    float total_luna[12];
    int numar_vanzari_total;
    char group[100];
    int check;
    int nr_tranzactii;
    char key[100];
}Magazin;

void max_sales_city_per_country(Magazin *m, int size,FILE *outputFile) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp(m[i].tara, n[j].tara) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].numar_vanzari_total = 0;
        n[i].orasul[0] = '\0';
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].tara, m[j].tara) == 0) {
                if (m[j].cantitate > n[i].numar_vanzari_total) {
                    n[i].numar_vanzari_total = m[j].cantitate;
                    strcpy(n[i].orasul, m[j].orasul);
                }
            }
        }
    }

    fprintf(outputFile,"\n\nOrasul cu cele mai multe vanzari pentru fiecare tara: \n\n");
    for (int i = 0; i < newSize-1; i++) {
        fprintf(outputFile,"%s, %s :   %d vanzari\n", n[i].tara, n[i].orasul, n[i].numar_vanzari_total);
    }

    free(n);
}

int Import(Magazin **m,FILE *file ){

    int size=10000;
    int counter = 0;
    char line[1000];

    fgets(line, sizeof(line), file);

    while(fscanf(file, "%d-%d-%d,%d,%99[^,],%99[^,],%99[^,],%f,%d,%99[^,],%99[^\n]\n", &(*m)[counter].anul, &(*m)[counter].luna, &(*m)[counter].ziua,
                 &(*m)[counter].id_produs, (*m)[counter].nume_produs, (*m)[counter].categorie_produs,(*m)[counter].sub_categorie,
                 &(*m)[counter].pret_unit, &(*m)[counter].cantitate, (*m)[counter].tara, (*m)[counter].orasul)==11) {

        if(counter>=size){
            size=size*2;
            *m=realloc(*m,size*sizeof(Magazin));
        }

        (*m)[counter].venit_total=(*m)[counter].pret_unit * (*m)[counter].cantitate;

        counter++;

    }

    return counter;

}

void month_income(Magazin **m,int counter,FILE *outputFile){
    int j=0;
    int an;
    printf("\nce an va intereseaza?\n");
    scanf("%d",&an);
    for(int i=0;i<12;i++){     (*m)->total_luna[i]=0;
        for(int j=0;j<counter;j++){
            if((*m)[j].luna==i+1 && (*m)[j].anul==an) {
                (*m)->total_luna[i] += (*m)[j].venit_total;
                j++;
            }
        }
    }
    fprintf(outputFile, "Luna,Venit Total\n");

    for (int i = 0; i < 12; i++) {
        fprintf(outputFile, "%d,%.2f\n", i + 1, (*m)->total_luna[i]);
    }
}
void sales_distribution(Magazin **m, int size,FILE *outputFile) {
    int count = 0;
    int newSize = 0;

    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp((*m)[i].categorie_produs, n[j].categorie_produs) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = (*m)[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].numar_vanzari_total = 0;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].categorie_produs, (*m)[j].categorie_produs) == 0) {
                n[i].numar_vanzari_total += (*m)[j].cantitate;
            }
        }
    }

    fprintf(outputFile, "\n\n Categorii: \n");

    for (int i = 0; i <newSize-1; i++) {
        fprintf(outputFile,"%d. %s :   %d vanzari\n", i + 1, n[i].categorie_produs, n[i].numar_vanzari_total);
    }

}
void best_income(Magazin **m, int size,FILE *outputFile) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp((*m)[i].nume_produs, n[j].nume_produs) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] =(*m)[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].venit_total = 0;
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].nume_produs,(*m)[j].nume_produs) == 0) {
                n[i].venit_total += (*m)[j].pret_unit * (*m)[j].cantitate;
            }
        }
    }

    Magazin temp;
    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < newSize - 1; j++) {
            if (n[j].venit_total < n[j + 1].venit_total) {
                temp = n[j];
                n[j] = n[j + 1];
                n[j + 1] = temp;
            }
        }
    }

    fprintf(outputFile,"\n\nTop 5 produse: \n");
    for (int i = 0; i < 5 && i < newSize; i++) {
        fprintf(outputFile,"%d. %s :   %.2f\n", i + 1, n[i].nume_produs, n[i].venit_total);
    }

    free(n);
}
void max_sales_city(Magazin *m, int size) {
    int count = 0;
    int newSize = 0;
    Magazin *n = malloc(newSize * sizeof(Magazin));

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < newSize; j++) {
            if (strcmp(m[i].tara, n[j].tara) == 0) {
                count++;
            }
        }

        if (count == 0) {
            newSize++;
            n = realloc(n, newSize * sizeof(Magazin));
            n[newSize - 1] = m[i];
        }

        count = 0;
    }

    for (int i = 0; i < newSize; i++) {
        n[i].numar_vanzari_total = 0;
        n[i].orasul[0] = '\0';
    }

    for (int i = 0; i < newSize; i++) {
        for (int j = 0; j < size; j++) {
            if (strcmp(n[i].tara, m[j].tara) == 0) {
                if (m[j].cantitate > n[i].numar_vanzari_total) {
                    n[i].numar_vanzari_total = m[j].cantitate;
                    strcpy(n[i].orasul, m[j].orasul);
                }
            }
        }
    }

    printf("\n\nOrasul cu cele mai multe vanzari pentru fiecare tara: \n");
    for (int i = 0; i < newSize-1; i++) {
        printf("%s, %s :   %d vanzari\n", n[i].tara, n[i].orasul, n[i].numar_vanzari_total);
    }

    free(n);
}

void tendinte_vanzari_lunare(Magazin **m, int counter,FILE *outputFile) {
    float total_vanzari_per_luna[12] = {0};
    int numar_produse_per_luna[12] = {0};

    int an;
    printf("\nce an va intereseaza?\n");
    scanf("%d",&an);


    for (int i = 0; i < counter; i++) {
        if((*m)[i].anul==an){
            total_vanzari_per_luna[(*m)[i].luna - 1] += (*m)[i].venit_total;
            numar_produse_per_luna[(*m)[i].luna - 1]++;
        }}
    float temp,procent;
    fprintf(outputFile,"\n\nTendinte in vanzarile lunare pentru diferite categorii de produse:\n\n");
    for (int i = 0; i < 12; i++) {


        fprintf(outputFile,"Luna %d:\n", i + 1);
        if(i==11){
            fprintf(outputFile,"  Total vanzari: %f\n", total_vanzari_per_luna[i]);
            fprintf(outputFile,"  Schimarea procentuala: %d\n",0);
            continue;
        }

        temp=total_vanzari_per_luna[i+1]-total_vanzari_per_luna[i];

        if(temp>0){
            procent=100*(total_vanzari_per_luna[i+1]-total_vanzari_per_luna[i])/total_vanzari_per_luna[i];
        }
        else if(temp<0) {
            procent=-100* (1-total_vanzari_per_luna[i+1]/total_vanzari_per_luna[i]);
        }

        fprintf(outputFile,"  Total vanzari: %f\n", total_vanzari_per_luna[i]);
        fprintf(outputFile,"  Schimarea procentuala: %.2f %\n",procent);

    }
}


int main() {

    FILE *file = fopen("sales.csv", "r");

    int size = 10000;
    Magazin *m = malloc(size * sizeof(Magazin));

    int counter=0;
    counter=Import(&m, file);
    int n;

    fclose(file);


    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL) {
        printf("Eroare.\n");
        return 1;
    }



    while(1){
        printf("1:Venitul total generat pe luna\n");
        printf("2:Top 5 produse dupa venit\n");
        printf("3:Distributia vanzarilor pe categoria de produse\n");
        printf("4:Orasul cu cele mai multe vanzari din fiecare tara\n");
        printf("5:Tendintele in vanzari\n");
        printf("6:Incheierea programului\n");
        scanf("%d",&n);

        switch(n){
            case(1):{
                month_income(&m,counter,outputFile);

            }break;

            case(2):{
                best_income(&m,counter,outputFile);
            }break;
            case(3):{
                sales_distribution(&m,counter,outputFile);
            }break;
            case(4):{
                max_sales_city_per_country(m, counter,outputFile);
            }break;
            case(5):{
                tendinte_vanzari_lunare(&m, counter,outputFile);
            }break;
            case(6):{
                fclose(file);
                fclose(outputFile);
                free(m);
                return 0;
            }
        }
    }

}
