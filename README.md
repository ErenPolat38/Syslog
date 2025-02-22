Harika, şimdi projeniz için standartlara uygun bir README dosyası hazırlayalım. İşte önerdiğim README bölümü:

```markdown
# Syslog Reader

Bu proje, bir syslog dosyasını okuyarak bağlı liste yapısında saklayan ve ekrana yazdıran bir C programıdır.

## Özellikler

- Syslog dosyasını satır satır okur.
- Okunan satırları bağlı liste yapısında saklar.
- Bağlı listedeki syslog kayıtlarını ekrana yazdırır.
- Bellek yönetimi yaparak kullanılan belleği serbest bırakır.

## Kurulum

1. Proje dosyasını klonlayın veya indirin.
2. C derleyicinizin kurulu olduğundan emin olun.
3. Terminal veya komut satırında aşağıdaki komutu çalıştırarak programı derleyin:

    ```sh
    gcc -o syslog_reader syslog_reader.c
    ```

4. Programı çalıştırmak için aşağıdaki komutu kullanın:

    ```sh
    ./syslog_reader
    ```

## Kullanım

- Program, `/var/log/syslog` dosyasını okuyarak syslog kayıtlarını ekrana yazdırır.
- Programı çalıştırdıktan sonra syslog kayıtlarını terminalde görebilirsiniz.

## Katkıda Bulunma

Katkıda bulunmak isterseniz, lütfen şu adımları izleyin:

1. Bu projeyi forklayın.
2. Yeni bir dal (branch) oluşturun: `git checkout -b ozellik-adi`
3. Değişikliklerinizi yapın ve commit edin: `git commit -am 'Yeni özellik ekle'`
4. Dalınıza push yapın: `git push origin ozellik-adi`
5. Bir pull request açın.

