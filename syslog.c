#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_UZUNLUK 512

// Dugum yapisi (Ba�l� listenin her eleman� i�in yap�)
typedef struct Dugum {
    char veri[MAX_UZUNLUK]; // Syslog sat�r�n� tutan karakter dizisi
    struct Dugum* sonraki;  // Sonraki d���m� i�aret eden pointer
} Dugum;

// Listeye yeni d���m ekleme fonksiyonu
void ekle(Dugum** bas, char* satir) {
    // Yeni d���m i�in bellek tahsis et
    Dugum* yeni = (Dugum*)malloc(sizeof(Dugum));
    if (!yeni) {
        printf("Bellek tahsis hatasi!\n");
        return;
    }
    // Yeni d���me veri kopyala
    strncpy(yeni->veri, satir, MAX_UZUNLUK);
    yeni->veri[MAX_UZUNLUK - 1] = '\0'; // G�venlik i�in son karakteri null yap
    yeni->sonraki = NULL;

    // E�er liste bo�sa, ba� d���m olarak yeni d���m� ata
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

// Listeyi yazd�rma fonksiyonu
void yazdir(Dugum* bas) {
    Dugum* temp = bas;
    while (temp != NULL) {
        printf("%s", temp->veri); // Syslog sat�r�n� ekrana yazd�r
        temp = temp->sonraki;
    }
}

// Listeyi temizleme fonksiyonu (Belle�i serbest b�rakma)
void temizle(Dugum** bas) {
    Dugum* temp = *bas;
    while (temp != NULL) {
        Dugum* silinecek = temp;
        temp = temp->sonraki;
        free(silinecek); // Belle�i serbest b�rak
    }
    *bas = NULL;
}

int main() {
    // Syslog dosyas�n� a�
    FILE* dosya = fopen("/var/log/syslog", "r");
    if (!dosya) {
        printf("Syslog dosyasi acilamadi!\n");
        return 1;
    }

    Dugum* bas = NULL; // Ba�l� liste ba�lang�c�
    char satir[MAX_UZUNLUK];

    // Syslog dosyas�n� sat�r sat�r oku ve ba�l� listeye ekle
    while (fgets(satir, sizeof(satir), dosya)) {
        ekle(&bas, satir);
    }

    fclose(dosya); // Dosyay� kapat

    printf("Syslog kayitlari:\n");
    yazdir(bas); // Kay�tlar� ekrana yazd�r

    temizle(&bas); // Belle�i temizle
    return 0;
}
