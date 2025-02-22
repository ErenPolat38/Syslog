#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UZUNLUK 512

// Dugum yapisi (Baðlý listenin her elemaný için yapý)
typedef struct Dugum {
    char veri[MAX_UZUNLUK]; // Syslog satýrýný tutan karakter dizisi
    struct Dugum* sonraki;  // Sonraki düðümü iþaret eden pointer
} Dugum;

// Listeye yeni düðüm ekleme fonksiyonu
void ekle(Dugum** bas, char* satir) {
    // Yeni düðüm için bellek tahsis et
    Dugum* yeni = (Dugum*)malloc(sizeof(Dugum));
    if (!yeni) {
        printf("Bellek tahsis hatasi!\n");
        return;
    }
    // Yeni düðüme veri kopyala
    strncpy(yeni->veri, satir, MAX_UZUNLUK);
    yeni->veri[MAX_UZUNLUK - 1] = '\0'; // Güvenlik için son karakteri null yap
    yeni->sonraki = NULL;

    // Eðer liste boþsa, baþ düðüm olarak yeni düðümü ata
    if (*bas == NULL) {
        *bas = yeni;
    } else {
        // Listenin sonuna ekleme yap
        Dugum* temp = *bas;
        while (temp->sonraki != NULL) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeni;
    }
}

// Listeyi yazdýrma fonksiyonu
void yazdir(Dugum* bas) {
    Dugum* temp = bas;
    while (temp != NULL) {
        printf("%s", temp->veri); // Syslog satýrýný ekrana yazdýr
        temp = temp->sonraki;
    }
}

// Listeyi temizleme fonksiyonu (Belleði serbest býrakma)
void temizle(Dugum** bas) {
    Dugum* temp = *bas;
    while (temp != NULL) {
        Dugum* silinecek = temp;
        temp = temp->sonraki;
        free(silinecek); // Belleði serbest býrak
    }
    *bas = NULL;
}

int main() {
    // Syslog dosyasýný aç
    FILE* dosya = fopen("/var/log/syslog", "r");
    if (!dosya) {
        printf("Syslog dosyasi acilamadi!\n");
        return 1;
    }

    Dugum* bas = NULL; // Baðlý liste baþlangýcý
    char satir[MAX_UZUNLUK];

    // Syslog dosyasýný satýr satýr oku ve baðlý listeye ekle
    while (fgets(satir, sizeof(satir), dosya)) {
        ekle(&bas, satir);
    }

    fclose(dosya); // Dosyayý kapat

    printf("Syslog kayitlari:\n");
    yazdir(bas); // Kayýtlarý ekrana yazdýr

    temizle(&bas); // Belleði temizle
    return 0;
}
