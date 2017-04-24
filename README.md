# DataStructuresH3
Data structures and algorithms homework 3
Bu ödevde verilen iki kelime için, her adımda sadece 1 harfi değiştirerek 1. kelimenin,
2. kelimeye dönüşüp dönüşmediğini, dönüşüyorsa arada hangi kelimelerden geçildiğini bulan bir
kelime oyunu yazılacaktır. Aşağıdaki örnek, prove kelimesinin guess kelimesine dönüşümünü
göstermektedir.
prove → prose → prese → prest → wrest → weest → geest → guest → guess
Verilen bir kelimeden, her adımda bir harf değiştirerek bir başka kelimeye ulaşmak için graf veri
yapısı kullanılacaktır. Grafın düğümlerini kelimeler oluşturmalıdır. Eğer bir kelimenin sadece 1
harfini değiştirerek diğer kelime elde ediliyorsa iki kelime arasında bağlantı vardır. Örneğin
yukarıdaki örnekte prove ve prose kelimeleri arasında bağlantı vardır. Fakat prove ve wrest kelimeleri
arasında bağlantı yoktur. 
İşlem Adımları :
1. Ödevde 5 harfli, küçük harfle yazılmış kelimelerden oluşan ekteki kelime.txt dosyasında
bulunan kelimeler kullanılacaktır.
2. Kelime grafını oluşturunuz (30 puan) : Dosyadaki kelimeleri önce bir string dizisine
yerleştiriniz. Daha sonra bu kelimeleri kullanarak grafı elde ediniz. Grafı oluşturmak için
NxN’lik bir komşuluk matrisi (adjacency matrix) kullanabilirsiniz. Bu durumda örneğin string
dizinizin 0. kelimesi 0. düğümü gösterir. Eğer iki kelime arasında tek harf değişimi varsa bu iki
kelime arasında bağlantı olduğu için matrisin ilgili adresindeki değer 1, değilse 0 yapılır.
3. Grafı doğru oluşturduğunuzu laboratuvarda gösterbilmek için bir fonksiyon yazınız. Bu
fonksiyon, oluşturduğunuz matriste bulunan iki kelime giriş bilgisi olarak verildiğinde, iki
kelime arasında tek harf değişimi var veya yok mesajı vermelidir.
4. İki kelime arasında dönüşüm olup olmadığını ve dönüşüm varsa kaç adım sürdüğünü
bulunuz (70 puan): Verilen iki kelime için, birinci kelimeden ikinci kelimeye dönüşüm olup
olmadığını bulmak için kuyruk(queue) veri yapısı kullanılacaktır. Bunun için aşağıdaki
adımları uygulayınız:
 İlk adımda birinci kelime’ye ait düğümü kuyruğa yerleştiriniz.
 Kuyruk tamamen boşalana kadar veya çıkış düğümüne(ikinci kelime) ulaşana
kadar aşağıdaki işlemleri yapınız:
o Kuyruğun başındaki düğümü kuyruktan çekiniz.
 Eğer bu düğüm ikinci kelime ise işlem tamamlanmıştır.
 Eğer bu düğüm ikinci kelime değilse düğüme ait kelimeyi ekrana
yazdırınız, Bu düğümün daha önceden kuyruğa gimemiş bütün
komşularını kuyruğa ekleyiniz. Bir düğümün daha önceden kuyruğa
girmiş olup olmadığını görmek için yedek bir dizi kullanabilirsiniz.
Örnek :
Kelime 1: beer Kelime 2: beat
Yol 1: beer -> bear -> fear -> feat -> beat 4 harf değişimi
Yol 2: beer -> bear -> dear -> fear -> feat -> beat 5 harf değişimi
