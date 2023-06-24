//Kullanıcı ve Sifre ile Hesap Olusturulan, Para Yatırılıp Cekilebilen Banka Uygulaması.

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_HESAP 5 // Maksimum hesap sayısı

char kullaniciAdlari[MAX_HESAP][16];
char parolalar[MAX_HESAP][16];
double bakiyeler[MAX_HESAP];
int hesapSayisi = 0;
int giris;

void hesapBilgileriniGoster(int hesapNumara) {
    printf("Kullanici Adi: %s\n", kullaniciAdlari[hesapNumara]);
    printf("Bakiye: %.2f TL\n", bakiyeler[hesapNumara]);
}

void bakiyeleriGuncelle() {
    FILE *dosya = fopen("hesaplar.txt", "w");
    if (dosya == NULL) {
        printf("Hesaplar dosyasi acilamadi.\n");
        return;
    }

    for (int i = 0; i < hesapSayisi; i++) {
        fprintf(dosya, "%s %s %.2f\n", kullaniciAdlari[i], parolalar[i], bakiyeler[i]);
    }

    fclose(dosya);
    printf("Bakiyeler dosyaya kaydedildi.\n");
}


int hesapBul(const char *kullaniciAdi) {
    for (int i = 0; i < hesapSayisi; i++) {
        if (strcmp(kullaniciAdlari[i], kullaniciAdi) == 0) {
            return i;
        }
    }
    return -1;
}
void hesapKaydet() {
    FILE *dosya = fopen("hesaplar.txt", "w");
    if (dosya == NULL) {
        printf("Hesaplar dosyasi olusturulamadi.\n");
        return;
    }

    for (int i = 0; i < hesapSayisi; i++) {
        fprintf(dosya, "Kullanici Adi: %s\tSifre: %s\tBakiye: %.2fTL\n", kullaniciAdlari[i], parolalar[i], bakiyeler[i]);
    }

    fclose(dosya);
    printf("Hesaplar dosyaya kaydedildi.\n");
}

void hesapOlustur() {
    if (hesapSayisi >= MAX_HESAP) {
        printf("Maksimum hesap sayisina ulasildi.\n");
        return;
    }

    printf("Kullanici Adi: ");
    scanf("%s", kullaniciAdlari[hesapSayisi]);

    if (hesapBul(kullaniciAdlari[hesapSayisi]) != -1) {
        printf("Bu kullanici adi zaten kullaniliyor.\n");
        return;
    }

    printf("Parola: ");
    scanf("%s", parolalar[hesapSayisi]);
    printf("Bakiye: ");
    scanf("%lf", &bakiyeler[hesapSayisi]);

    hesapSayisi++;

    printf("Hesap olusturuldu.\n");
    hesapKaydet();
}

void hesabaGiris() {
    char kullaniciAdi[50];
    char parola[50];

    printf("Kullanici Adi: ");
    scanf("%s", kullaniciAdi);
    printf("Parola: ");
    scanf("%s", parola);

    int hesapNumara = hesapBul(kullaniciAdi);
    if (hesapNumara == -1 || strcmp(parolalar[hesapNumara], parola) != 0) {
        printf("Kullanici adi veya parola yanlis.\n");
        giris = -1;
        return;
    }

    printf("Giris yapildi.\n");
    hesapBilgileriniGoster(hesapNumara);
}

void paraYatir(int hesapNumara) {
    double miktar;
    printf("Yatirilacak miktar: ");
    scanf("%lf", &miktar);

    if(miktar<=0){
        printf("Gecersiz Tutar\n");
    }
    else{
        bakiyeler[hesapNumara] += miktar;
        printf("%.2f TL yatirildi.\n", miktar);
        hesapBilgileriniGoster(hesapNumara);
        bakiyeleriGuncelle();
    }

}

void paraCek(int hesapNumara) {
    double miktar;
    printf("Cekilecek miktar: ");
    scanf("%lf", &miktar);

    if (bakiyeler[hesapNumara] >= miktar) {
        bakiyeler[hesapNumara] -= miktar;
        printf("%.2f TL cekildi.\n", miktar);
    } else {
        printf("Yetersiz bakiye!!!\n");
    }
    hesapBilgileriniGoster(hesapNumara);
    bakiyeleriGuncelle();
}



void menuGoster() {
    printf("\n--- MOBIL BANKACILIK SISTEMI ---\n");
    printf("1. Hesap Olustur\n");
    printf("2. Hesaba Giris\n");
    printf("0. Cikis\n");
    printf("Seciminizi yapin: ");
}

void menu2Goster() 
{
    printf("1.Para Yatir\n");
    printf("2.Para Cek\n");
    printf("0.Geri Don\n");
}

int main() {
    int secim;

    while (true) {
        menuGoster();
        scanf("%d", &secim);

        switch (secim) {
            case 0:
                printf("Cikis yapiliyor.\n");
                return 0;
            case 1:
                printf("Lutfen Kullanici Adi ve Sifrede Bosluk Kullanmayiniz!!!\n");
                hesapOlustur();
                break;
            case 2:
                hesabaGiris();
                if(giris!=-1){
                    int secim2=0;
                    do{
                        menu2Goster();
                        printf("Secim: ");
                        scanf("%d", &secim2);
                        if(secim2==1){
                            char kullaniciAdi[50];
                            printf("Kullanici Adi: ");
                            scanf("%s", kullaniciAdi);

                            int hesapNumara = hesapBul(kullaniciAdi);
                            if (hesapNumara == -1) {
                                printf("Hesap bulunamadi.\n");
                            } else {
                                paraYatir(hesapNumara);
                            }
                        }

                        else if(secim2==2){
                            char kullaniciAdi[50];
                            printf("Kullanici Adi: ");
                            scanf("%s", kullaniciAdi);

                            int hesapNumara = hesapBul(kullaniciAdi);
                            if (hesapNumara== -1) {
                                printf("Hesap bulunamadi.\n");
                            } else {
                                paraCek(hesapNumara);
                            }
                        }
                        else if(secim2==0){
                            continue;
                        }
                        else{
                            printf("Gecersiz Islem!!!\n");
                        }
                    }while(secim2!=0);
                }
                default:
                    printf("Gecersiz Islemm Kodu");
        }
    }
    return 0;
}
