#include <stdio.h>

#include <stdlib.h>

#include <string.h>



#define TRUE 1



struct sehirler

{

    int plaka;

    char sehirAdi[15];

    char bolge[2];

    int komsuSayisi;

    struct sehirler *prev;

    struct sehirler *next;

    struct komsular *knext;

};



struct komsular

{

    int komsu_plaka;

    int *knext;

};



/** FONKSIYON PROTOTIPLERI **/

int kelimelereAyir(char *base, char target[50][50]);

int kelimeSayisiBul(char *chpt);

void dosyadanOku2();

void dosyadanOku();

struct sehirler* nodeOlustur(int plaka, char *sehirAdi, char *bolge, int komsuSayisi);

void sonaEkle(int plaka, char *sehirAdi, char *bolge, int komsuSayisi);

void sonaEkleListele();

void basaSehirEkle(int plaka, char *sehirAdi, char *bolge, int komsuSayisi);

void basaSehirEkleListele();

void arayaSehirEkle(int birondekiSehir);

void bastanSehirSil();

void sondanSehirSil();

void aradanSehirSil(int silinecekSehirPlk);

void aradanSehirSilListele();

void yazdir();

int PlakayaGoreSehirAramasi(char *aranacakSehir);

void SehirAdinaGoreAramaYapma(int plkNo);

int SehirAdinaGoreSehirArama(char *aranacakSehir);

void PlakayaGoreArama(int plkNo);

void BolgeyeGoreSehirArama(char *aranacakBolge);

void BolgeyeGoreListeleme();

void KomsuSayisinaGoreArama(int aranacakKomsuSayisi);

void KomsuSayisinaGoreListeleme();

int menu();






/** DOSYADAN OKUMA2 ISLEMI ICIN **/

int kelimelereAyir(char *base, char target[50][50])

{

    int n=0,i,j=0;

    for(i=0; TRUE; i++)

    {

        if(base[i]!=',')

        {

            target[n][j++]=base[i];

        }

        else

        {

            target[n][j++]='\0';

            n++;

            j=0;

        }

        if(base[i]=='\0')

            break;

    }

    printf("kelime sayisi:%d\n",n+1);

    printf("komsu sayisi:%d\n\n",n-2);

    printf("*******************************************************************************\n");

    return n;

}



/** KOMSU SAYISINI BULMAK ICIN **/

int kelimeSayisiBul(char *chpt)

{

    int i=0;

    int kelimeSayisi=0;

    while (chpt[i]!='\0')

    {

        if(chpt[i]==',')

            kelimeSayisi++;

        i++;

    }

    return kelimeSayisi-2;

}



/** DOSYADAN OKUMA **/

void dosyadanOku2()

{

    int sayac=0;

    char *temp[100],*kontrol,satir[100];



    int i=sayac;

    int n; //kelime sayisi

    int j; //counter dongusu

    char arr[50][50];



    char str[100];

    int komsuSayisi=0;



    FILE *kaynak=fopen("sehirler.txt","r"); //text dosyasýndan satýr satýr okuyup bunu diziye atmak istiyorum.



    do

    {

        kontrol=fgets(satir,sizeof(satir),kaynak);

        if(kontrol!=NULL)

        {

            temp[sayac]=malloc(strlen(satir)+1);

            strcpy(temp[sayac],satir);

            printf("sehirler: %s ",temp[sayac]);

            sayac++;

            printf("\n");



            n=kelimelereAyir(temp[i],arr);



            for(j=0; j<=n; j++)

            {

                //printf("%s\n",arr[j]);

            }

        }

        i++;

    }



    while(kontrol!=NULL);

}



/** BAGLI LISTE ISLEMLERI **/

void dosyadanOku()

{

    int sayac=0;

    char *temp[100],*kontrol,satir[100];



    int i=sayac;

    int n;

    int j;

    char arr[50][50];



    char str[100];

    int komsuSayisi=0;



    FILE *kaynak=fopen("sehirler.txt","r");


    do

    {

        kontrol=fgets(satir,sizeof(satir),kaynak);

        if(kontrol!=NULL)

        {

            //printf("%s\n",satir);

            strcpy(str,satir);

            char *a1,*a2,*a3;

            a1 = strtok(satir,",");

            a2 = strtok(NULL,",");

            a3 = strtok(NULL,",");

            komsuSayisi = kelimeSayisiBul(str);

            sonaEkle(atoi(a1),a2,a3,komsuSayisi);

        }

        i++;

    }



    while(kontrol!=NULL);

}



/***************************************************/
/*** BAGLI LISTE EKLEME,CIKARMA,SILME ISLEMLERI ***/
/***************************************************/



struct sehirler *start = NULL;



/** YENI SEHIR DUGUMU OLUSTURMAK **/

struct sehirler* nodeOlustur(int plaka, char *sehirAdi, char *bolge, int komsuSayisi)

{

    struct sehirler* yeniNode = (struct sehirler*)malloc(sizeof(struct sehirler));

    yeniNode->plaka = plaka;

    strcpy(yeniNode->sehirAdi,sehirAdi);

    strcpy(yeniNode->bolge,bolge);

    yeniNode->komsuSayisi = komsuSayisi;

    yeniNode->prev = NULL;

    yeniNode->next = NULL;

    yeniNode->knext = NULL;

    return yeniNode;

}



/** SEHIR DUGUMUNU SONA EKLEMEK **/

void sonaEkle(int plaka, char *sehirAdi, char *bolge, int komsuSayisi)

{

    struct sehirler* sonaEklenecek = nodeOlustur(plaka,sehirAdi,bolge,komsuSayisi);

    if(start == NULL)

    {

        start = sonaEklenecek;

    }

    else

    {

        struct sehirler* temp = start;

        while (temp->next != NULL)

        {

            temp = temp->next;

        }

        sonaEklenecek->prev = temp;

        temp->next = sonaEklenecek;

    }

}



void sonaEkleListele()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int p,ks;

    char ad[15],blg[3];

    printf("Sona ekleyeceginiz sehrin plakasi:\n");

    scanf("%d",&p);

    printf("Sona ekleyeceginiz sehrin adi:\n");

    scanf("%s",ad);

    printf("Sona ekleyeceginiz sehrin bolgesi:\n");

    scanf("%s",blg);

    printf("Sona ekleyeceginiz sehrin komsu sayisi:\n");

    scanf("%d",&ks);

    sonaEkle(p,ad,blg,ks);

    fprintf(yaz,"Sona ekleyeceginiz sehrin plakasi:%d\n",p);

    fprintf(yaz,"Sona ekleyeceginiz sehrin adi:%s\n",ad);

    fprintf(yaz,"Sona ekleyeceginiz sehrin bolgesi:%s\n",blg);

    fprintf(yaz,"Sona ekleyeceginiz sehrin komsu sayisi:%d\n",ks);

    fprintf(yaz,"%d %s %s %d\n\n",p,ad,blg,ks);



    fclose(yaz);

}



/** SEHIR DUGUMUNU BASA EKLEMEK **/

void basaSehirEkle(int plaka, char *sehirAdi, char *bolge, int komsuSayisi)

{

    struct sehirler* basaEklenecek = nodeOlustur(plaka,sehirAdi,bolge,komsuSayisi);

    if (start == NULL)

    {

        start = basaEklenecek;

        return;

    }



    start->prev = basaEklenecek;

    basaEklenecek->next = start;

    start = basaEklenecek;

}



void basaSehirEkleListele()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int p,ks,i;

    char ad[15],blg[3];

    printf("Basa ekleyeceginiz sehrin plakasi:\n");

    scanf("%d",&p);

    printf("Basa ekleyeceginiz sehrin adi:\n");

    scanf("%s",ad);

    printf("Basa ekleyeceginiz sehrin bolgesi:\n");

    scanf("%s",blg);

    printf("Basa ekleyeceginiz sehrin komsu sayisi:\n");

    scanf("%d",&ks);

    basaSehirEkle(p,ad,blg,ks);



    fprintf(yaz,"Basa ekleyeceginiz sehrin plakasi:%d\n",p);

    fprintf(yaz,"Basa ekleyeceginiz sehrin adi:%s\n",ad);

    fprintf(yaz,"Basa ekleyeceginiz sehrin bolgesi:%s\n",blg);

    fprintf(yaz,"Basa ekleyeceginiz sehrin komsu sayisi:%d\n",ks);

    fprintf(yaz,"%d %s %s %d\n\n",p,ad,blg,ks);



    fclose(yaz);

}





/** SEHIR DUGUMUNU ARAYA EKLEMEK **/

void arayaSehirEkle(int sehirdenonce)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int ks;

    int arayaEklenecekSekirPlk;

    int i;

    char ad[15],blg[3];

    printf("eklemek istediginiz sehrin plakasini girin:\n");

    scanf("%d",&arayaEklenecekSekirPlk);

    printf("eklemek istediginiz sehrin adini girin:\n");

    scanf("%s",ad);

    printf("eklemek istediginiz sehrin bolgesini girin:\n");

    scanf("%s",blg);

    printf("eklemek istediginiz sehrin komsu sayisini girin:\n");

    scanf("%d",&ks);



    fprintf(yaz,"eklemek istediginiz sehrin plakasini girin:%d\n",arayaEklenecekSekirPlk);

    fprintf(yaz,"eklemek istediginiz sehrin adini girin:%s\n",ad);

    fprintf(yaz,"eklemek istediginiz sehrin bolgesini girin:%s\n",blg);

    fprintf(yaz,"eklemek istediginiz sehrin komsu sayisini girin:%d\n",ks);

    fprintf(yaz,"%d %s %s %d\n\n",arayaEklenecekSekirPlk,ad,blg,ks);



    for(i=1; i<=81; i++)

    {

        if(arayaEklenecekSekirPlk==i)

        {

            printf("Zaten mevcut olan plaka girdiniz!\n");

            fprintf(yaz,"Zaten mevcut olan plaka girdiniz!\n");

        }

    }

    struct sehirler* temp=start;

    struct sehirler* arayaEklenecek=nodeOlustur(arayaEklenecekSekirPlk,ad,blg,ks);

    struct sehirler* onceki= NULL;

    if(start== NULL)

    {

        start=arayaEklenecek;

    }

    else if(start->plaka == sehirdenonce)

    {

    }

    else

    {

        while(temp->next!= NULL)

        {

            if(temp->plaka == sehirdenonce)

            {

                onceki=temp->prev;

                break;

            }

            temp=temp->next;

        }

        temp->prev = arayaEklenecek;

        arayaEklenecek->next = temp;

        arayaEklenecek->prev = onceki;

        onceki->next =arayaEklenecek;

    }

    fclose(yaz);

}



/** BASTAN SEHIR SIL **/

void bastanSehirSil()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    if (start == NULL)

    {

        printf("\n Liste zaten bos ....");

        fprintf(yaz,"\n Liste zaten bos ....");

        return;

    }

    if (start->next == NULL)

    {

        free(start);

        start = NULL;

        return;

    }

    struct sehirler* yeni2 = start->next;

    free(start);

    yeni2->prev = NULL;

    start = yeni2;



    fclose(yaz);

}



/** SONDAN SEHIR SIL **/

void sondanSehirSil()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    if (start == NULL)

    {

        printf("\n Liste bos!");

        fprintf(yaz,"\n Liste bos!");

        return;

    }

    if (start->next == NULL)

    {

        bastanSehirSil();

        return;

    }

    struct sehirler* temp = start;

    while (temp->next != NULL)

    {

        temp = temp->next;

    }

    struct sehirler* onceki = temp->prev;

    free(temp);

    onceki->next = NULL;



    fclose(yaz);

}



/** ARADAN SEHIR SIL **/

void aradanSehirSilListele()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int silinecekSehirPlaka,i;

    printf("Silmek istediginiz sehrin plakasini giriniz:\n");

    scanf("%d",&silinecekSehirPlaka);



    fprintf(yaz,"Silmek istediginiz sehrin plakasini giriniz:%d\n",silinecekSehirPlaka);



    for(i=1; i<=81; i++)

    {

        if(silinecekSehirPlaka==i)

        {

            aradanSehirSil(i);

        }

    }

    fclose(yaz);

}



void aradanSehirSil(int silinecekSehirPlk)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    struct sehirler* temp = start;

    while (temp->next != NULL)

    {

        if (temp->plaka == silinecekSehirPlk)

        {

            break;

        }

        temp = temp->next;

    }

    if(temp == NULL)

    {

        printf("Silinecek Sehir Listede Yok");

        fprintf(yaz,"Silinecek Sehir Listede Yok");

    }

    struct sehirler* sonraki = temp->next;

    struct sehirler* onceki = temp->prev;

    free(temp);

    onceki->next = sonraki;

    sonraki->prev = onceki;

}



/** DUGUM YAZDIR **/

void yazdir()

{

    struct sehirler* temp = start;



    while (temp != NULL)

    {

        printf("Plaka: %d --->Sehir Adi: %s---> Bolge: %s ---->Komsu Sehirler:%d ", temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

        printf("\n");

        temp = temp->next;

    }

}



int PlakayaGoreSehirAramasi(char *aranacakSehir)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int secim;

    struct sehirler *temp=start;

    while(temp!=NULL)

    {

        if(strcmp(temp->sehirAdi,aranacakSehir)==0)

        {

            return temp->plaka;



        }

        temp =temp->next;

    }





}



void SehirAdinaGoreAramaYapma(int plkNo)

{

    struct sehirler* temp=(struct sehirler*)malloc(sizeof(struct sehirler));

    temp=start;

    while(temp!=NULL)

    {

        if(temp->plaka==plkNo)

        {

            printf("Plaka Kodu:%d -- Sehir Adi:%s -- Bolge:%s -- Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

            break;

        }

        temp=temp->next;

    }

    if(temp==NULL)

    {



    }

}



int SehirAdinaGoreSehirArama(char *aranacakSehir)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int plaka,secim;

    char sehirAdi[15];

    char bolge[2];

    int komsuSayisi;

    struct sehirler* temp = (struct sehirler*)malloc(sizeof(struct sehirler));

    temp =start;

    while (temp != NULL)

    {

        if(strcmp(temp->sehirAdi,aranacakSehir) == 0)

        {

            printf("Plaka Kodu:%d -- Sehir Adi:%s -- Bolge:%s -- Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

            return temp->plaka;

        }

        temp = temp->next;

    }

    fclose(yaz);

}



void PlakayaGoreArama(int plkNo)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","r");

    int secim;

    struct sehirler* temp = (struct sehirler*)malloc(sizeof(struct sehirler));

    temp = start;

    while (temp != NULL)

    {

        if(temp->plaka == plkNo)

        {

            printf("Plaka Kodu:%d -- Sehir Adi:%s -- Bolge:%s -- Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

            break;

        }

         if(temp->plaka != plkNo)
        {



            printf("Sehir listede yok!\n");

            printf("Eklemek ister misiniz?(Evet:1,Hayir:0):\n");

            scanf("%d",&secim);



            fprintf(yaz,"Sehir listede yok!\n");

            fprintf(yaz,"Eklemek ister misiniz?(Evet:1,Hayir:0):%d\n",secim);



            if(secim==1)
            {

                int kyt;

                printf("-->1 Basa Kayit Ekle\n");

                printf("-->2 Sona Kayit Ekle\n");

                printf("-->3 Araya Kayit Ekle\n");

                printf("Seciminizi giriniz:\n");

                scanf("%d",&kyt);



                fprintf(yaz,"-->1 Basa Kayit Ekle\n");

                fprintf(yaz,"-->2 Sona Kayit Ekle\n");

                fprintf(yaz,"-->3 Araya Kayit Ekle\n");

                fprintf(yaz,"Seciminizi giriniz:%d\n",kyt);



                if(kyt==1)

                {

                    basaSehirEkleListele();

                    yazdir();

                }

                else if(kyt==2)

                {



                    sonaEkleListele();

                    yazdir();

                }

                else if(kyt==3)

                {

                    int i,onuneEklenecekPlaka;

                    printf("\nonune eklemek istediginiz sehrin plakasini girin:");

                    scanf("%d",&onuneEklenecekPlaka);



                    fprintf(yaz,"\nonune eklemek istediginiz sehrin plakasini girin:%d",onuneEklenecekPlaka);



                    for(i=1; i<=81; i++)

                    {

                        if(onuneEklenecekPlaka==i)

                        {

                            arayaSehirEkle(i);

                        }

                    }

                    yazdir();

                }

                fclose(yaz);

            }

            else if(secim==0)
            {



            }

        }

        temp = temp->next;

    }



}



void BolgeyeGoreSehirArama(char *aranacakBolge)

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    struct sehirler *temp = start;

    while (temp != NULL)

    {

        if(strcmp(temp->bolge,aranacakBolge) == 0)

        {

            printf("Plaka Kodu:%d -- Sehir Adi:%s -- Bolge:%s -- Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

            fprintf(yaz,"Plaka Kodu:%d -- Sehir Adi:%s -- Bolge:%s -- Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

        }

        temp = temp->next;

    }

    fclose(yaz);

}



void BolgeyeGoreListeleme()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int sayi;

    printf("--1-- AK\n");

    printf("--2-- DA\n");

    printf("--3-- EG\n");

    printf("--4-- GA\n");

    printf("--5-- IA\n");

    printf("--6-- KA\n");

    printf("--7-- MA\n");

    printf("Aramak istediginiz bolge numarasini giriniz:[1-7]\n");

    scanf("%d",&sayi);



    fprintf(yaz,"--1-- AK\n");

    fprintf(yaz,"--2-- DA\n");

    fprintf(yaz,"--3-- EG\n");

    fprintf(yaz,"--4-- GA\n");

    fprintf(yaz,"--5-- IA\n");

    fprintf(yaz,"--6-- KA\n");

    fprintf(yaz,"--7-- MA\n");

    fprintf(yaz,"Aramak istediginiz bolge numarasini giriniz:[1-7]%d\n",sayi);



    switch(sayi)

    {

    case 1:

        printf("Bolgesi AK olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("AK");

        break;

    case 2:

        printf("Bolgesi DA olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("DA");

        break;

    case 3:

        printf("Bolgesi EG olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("EG");

        break;

    case 4:

        printf("Bolgesi GA olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("GA");

        break;

    case 5:

        printf("Bolgesi IA olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("IA");

        break;

    case 6:

        printf("Bolgesi KA olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("KA");

        break;

    case 7:

        printf("Bolgesi MA olan sehirler listeleniyor...\n");

        BolgeyeGoreSehirArama("MA");

        break;

    }

    fclose(yaz);

}



void KomsuSayisinaGoreArama(int aranacakKomsuSayisi) //buyuk veya esit

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    struct sehirler *temp = start;

    while (temp != NULL)

    {

        if(temp->komsuSayisi >= aranacakKomsuSayisi)

        {

            printf("Plaka Kodu:%d--Sehir Adi:%s--Bolge:%s--Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

            fprintf(yaz,"Plaka Kodu:%d--Sehir Adi:%s--Bolge:%s--Komsu Sayisi:%d\n",temp->plaka,temp->sehirAdi,temp->bolge,temp->komsuSayisi);

        }

        temp = temp->next;

    }

}



void KomsuSayisinaGoreListeleme()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    int sayi;

    printf("Aramak istediginiz min komsu sayisi giriniz:[1-9]\n");

    scanf("%d",&sayi);



    fprintf(yaz,"Aramak istediginiz min komsu sayisi giriniz:[1-9]%d\n",sayi);



    switch(sayi)

    {

    case 1:

        printf("Komsu sayisi 1 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 2:

        printf("Komsu sayisi 2 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 3:

        printf("Komsu sayisi 3 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 4:

        printf("Komsu sayisi 4 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 5:

        printf("Komsu sayisi 5 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 6:

        printf("Komsu sayisi 6 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 7:

        printf("Komsu sayisi 7 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 8:

        printf("Komsu sayisi 8 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    case 9:

        printf("Komsu sayisi 9 olan sehirler listeleniyor...\n");

        KomsuSayisinaGoreArama(sayi);

        break;

    }

    fclose(yaz);

}



int menu()

{

    FILE *yaz;

    yaz = fopen("cikti.txt","a");

    char input[15];

    int secim;

    printf("\n*******MENU*******\n");

    printf("[1] LISTELE\n");

    printf("[2] KAYIT EKLE\n");

    printf("[3] KAYIT SIL\n");

    printf("[4] KAYIT BUL\n");

    printf("[5] CIK\n");

    printf("SECIMINIZI GIRINIZ:\n");

    scanf("%d",&secim);



    fprintf(yaz,"\n*******MENU*******\n");

    fprintf(yaz,"[1] LISTELE\n");

    fprintf(yaz,"[2] KAYIT EKLE\n");

    fprintf(yaz,"[3] KAYIT SIL\n");

    fprintf(yaz,"[4] KAYIT BUL\n");

    fprintf(yaz,"[5] CIK\n");

    fprintf(yaz,"SECIMINIZI GIRINIZ:%d\n",secim);



    if(secim==1)

    {

        dosyadanOku();

        yazdir();

    }

    else if(secim==2)

    {

        int kyt;

        printf("-->1 Basa Kayit Ekle\n");

        printf("-->2 Sona Kayit Ekle\n");

        printf("-->3 Araya Kayit Ekle\n");

        printf("Seciminizi giriniz:\n");

        scanf("%d",&kyt);



        fprintf(yaz,"-->1 Basa Kayit Ekle\n");

        fprintf(yaz,"-->2 Sona Kayit Ekle\n");

        fprintf(yaz,"-->3 Araya Kayit Ekle\n");

        fprintf(yaz,"Seciminizi giriniz:%d\n",kyt);



        if(kyt==1)

        {

            basaSehirEkleListele();

            yazdir();

        }

        else if(kyt==2)

        {



            sonaEkleListele();

            yazdir();

        }

        else if(kyt==3)

        {

            int i,onuneEklenecekPlaka;

            printf("\nonune eklemek istediginiz sehrin plakasini girin:");

            scanf("%d",&onuneEklenecekPlaka);



            fprintf(yaz,"\nonune eklemek istediginiz sehrin plakasini girin:%d",onuneEklenecekPlaka);



            for(i=1; i<=81; i++)

            {

                if(onuneEklenecekPlaka==i)

                {

                    arayaSehirEkle(i);

                }

            }

            yazdir();

        }

    }

    else if(secim==3)

    {

        int kyt;

        printf("-->1 Bastan Kayit Sil\n");

        printf("-->2 Sondan Kayit Sil\n");

        printf("-->3 Aradan Kayit Sil\n");

        printf("Seciminizi giriniz:\n");

        scanf("%d",&kyt);



        fprintf(yaz,"-->1 Bastan Kayit Sil\n");

        fprintf(yaz,"-->2 Sondan Kayit Sil\n");

        fprintf(yaz,"-->3 Aradan Kayit Sil\n");

        fprintf(yaz,"Seciminizi giriniz:%d\n",kyt);



        if(kyt==1)

        {

            bastanSehirSil();

            yazdir();

        }

        if(kyt==2)

        {

            sondanSehirSil();

            yazdir();

        }

        if(kyt==3)

        {

            aradanSehirSilListele();

            yazdir();

        }

    }

    else if(secim==4)

    {

        int kyt;

        printf("-->1 Plakaya Gore Sehir Arama\n");

        printf("-->2 Sehir Adina Gore Arama\n");

        printf("-->3 Bolgeye Gore Sehir Arama\n");

        printf("-->4 Komsu Sayisina Gore Sehir Arama\n");

        printf("Seciminizi giriniz:\n");

        scanf("%d",&kyt);



        fprintf(yaz,"-->1 Plakaya Gore Sehir Arama\n");

        fprintf(yaz,"-->2 Sehir Adina Gore Arama\n");

        fprintf(yaz,"-->3 Bolgeye Gore Sehir Arama\n");

        fprintf(yaz,"-->4 Komsu Sayisina Gore Sehir Arama\n");

        fprintf(yaz,"Seciminizi giriniz:%d\n",kyt);



        if(kyt==1)

        {

            int i,aranmasiGerekenPlaka;

            printf("Aramak istediginiz plaka numarasini giriniz:\n");

            scanf("%d",&aranmasiGerekenPlaka);



            fprintf(yaz,"Aramak istediginiz plaka numarasini giriniz:%d\n",aranmasiGerekenPlaka);



            for(i=1; i<=81; i++)

            {

                if(aranmasiGerekenPlaka==i)

                {

                    PlakayaGoreArama(i);

                }

            }

            fclose(yaz);

        }

        if(kyt==2)

        {

            char aranan[20];

            printf("Aramak istediginiz sehrin ismini giriniz:\n");

            scanf("%s",aranan);



            fprintf(yaz,"Aramak istediginiz sehrin ismini giriniz:%s\n",aranan);



            SehirAdinaGoreAramaYapma(PlakayaGoreSehirAramasi(aranan));

        }

        if(kyt==3)

        {

            BolgeyeGoreListeleme();

        }

        if(kyt==4)

        {

            KomsuSayisinaGoreListeleme();

        }

    }

    else if(secim==5)

    {

        printf("Menuden cikis yaptiniz...\n\n");

        fprintf(yaz,"Menuden cikis yaptiniz...\n\n");

        exit(1);

    }

    else

        printf("Yanlis Giris\n\n");

    fclose(yaz);

}



int main()

{

    while(1)

    {

        menu();

    }

    return 0;

}

