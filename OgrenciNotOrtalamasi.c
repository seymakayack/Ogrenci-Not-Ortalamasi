//SEYMA KAYACIK 201180064
#include <stdio.h>
#include <stdlib.h>

struct ogrenci_s
{
	double vize_notu;
	double final_notu;
};

typedef struct ogrenci_s Ogrenci;
float *hesaplama(int ogrenci_numarasi);
int *odev(int arraySize);

int main()
{
	//Gerekli tanýmlamalar
	int ogrenci_numarasi;
	char ogrenciNo[12];
	char* control='1';
	float odev_ort,sinif_toplam=0,sinif_ort=0;
	float* notlar;
	float eb_not=0,ek_not=100;
	float genel_not,ogrenci_sayisi=1;
	
	printf("NOT ORTALAMASI HESAPLAMA\n************************\n\n");


	while(control=='1')
	{
		
		printf("Lutfen ogrenci numarasini giriniz:");
  		scanf("%s", ogrenciNo);

  		//Dogrulama Islemi
  		int len=strlen(ogrenciNo);
  		while (len < 9 || len > 10) 
		{  //Ogrenci numarasi girisi (Eger 9 haneden fazla ya da az ise kabul edilmez)
		    printf("Girilen sayi 9 ve 10 basamak arasinda degil. Lutfen tekrar deneyin:");
		    scanf("%s", ogrenciNo);
		    len = strlen(ogrenciNo); 
  		}
  		int i;
  		for (i = 0; i < len; i++) 
		{ 
		    if (!isdigit(ogrenciNo[i])) 
			{  // Eðer sayýnýn bir basamaðý harfse
		      printf("Girilen sayida harf var. Lutfen tekrar deneyin.\n");
		      len = 0; 
		      break; 
	    	}
  		}
		ogrenci_numarasi = atoi(ogrenciNo);
		//Fonksiyon çaðrilamsi
		notlar = hesaplama(ogrenci_numarasi);
		
		//Genel not ve odev not ortalamasinin yazilmasi
		printf("%d numarali ogrencinin not ortalamasi: %.2f\n", ogrenci_numarasi,notlar[0]);
		printf("%d numarali ogrencinin odev not ortalamasi: %.2f\n", ogrenci_numarasi,notlar[1]); 
		//Not buyuk mu kucuk mu uygulamasi
		genel_not=notlar[0];
		if(genel_not>eb_not){
			eb_not=genel_not;
		}
		
		if(genel_not<ek_not){
			ek_not=genel_not;
		}
		//Butun notlarin toplanmasi
		sinif_toplam+=notlar[0];
		
		
		//Yeni öðrenci giriþi yada Çýkýþ iþlemi
		do{
			control='1';
			printf("\nYeni bir ogrenci notu hesaplamak icin '1' cikmak icin '0' tuslayiniz:");
			scanf("%s",&control);
			if(control=='1'){
				ogrenci_sayisi++;
			}	
			if(control!='0' && control!='1')
				printf("Hatali secim yaptiniz. Lutfen tekrar giriniz.");
			else if(control == '0')
				printf("Cikis yapiliyor...");
		}while(control!='1' && control!='0');
	}
	//Sýnýf ort hesabý
	sinif_ort=sinif_toplam/ogrenci_sayisi;
	
	printf("\nDersi alan %.0f kisi arasinda en buyuk not: %.2f\nDersi alan %.0f kisi arasinda en kucuk not: %.2f\nDersi alan %.0f kisi için sinif ortalamasi %.2f ",ogrenci_sayisi, eb_not, ogrenci_sayisi,ek_not,ogrenci_sayisi,sinif_ort);
	return 0;
}

//Not hesaplama fonksiyonu
float *hesaplama(int ogrenci_numarasi)
{
	//Gerekli tanýmlamalar
	Ogrenci ogrenci;
	float toplam=0,odev_ort=0;
	char odevSayisi[10];
	int n = 0;
	float sayac = 0;
	int *odevNot;
	float not_ortalamasi=0;
	float toplaM=0;
	static float ogrenciNotlari[3];
	   
		//Vize notu girisi (0-100 arasýnda olmali)
		do{
			printf("%d numarali ogrenci icin vize notunu giriniz:", ogrenci_numarasi);
			scanf("%lf",&(ogrenci.vize_notu));
			if(ogrenci.vize_notu<0 || ogrenci.vize_notu>100)
				printf("Girdiginiz sayi 0-100 arasinda olmalidir\n");
		}while(ogrenci.vize_notu<0 || ogrenci.vize_notu>100 );
		//Final notu girisi (0-100 arasýnda olmali)
		do{
			printf("%d numarali ogrenci icin final notunu giriniz:", ogrenci_numarasi);
			scanf("%lf",&ogrenci.final_notu);
			if(ogrenci.final_notu<0 || ogrenci.final_notu>100)
				printf("Girdiginiz sayi 0-100 arasinda olmalidir\n");
		}while(ogrenci.final_notu<0 || ogrenci.final_notu>100 );	
		do
		{
			printf("%d numarali ogrenci icin odev sayisini giriniz:", ogrenci_numarasi);
			scanf("%d",&n);
			if(n<0 || n>10)
			{
				printf("Odev sayisi 0-10 arasinda olmalidir.\n");
			}
		}while(n<0 || n>10);
		//Eðer girilen ödev sayýsý 0 dan farklý ise odev fonksiyonu çaðýrýlýr.
		if(n != 0){
			odevNot=odev(n);
			int x;
			for(x=0;x<n;x++){
				toplaM += odevNot[x];
				sayac++;
			}
			odev_ort=(toplaM / sayac);
			not_ortalamasi=ogrenci.vize_notu*0.3+odev_ort*0.3+ogrenci.final_notu*0.4;
			ogrenciNotlari[0]=not_ortalamasi;
			ogrenciNotlari[1]=odev_ort;
			
			return ogrenciNotlari;
		}
		else{
			not_ortalamasi = ogrenci.vize_notu*0.6+ogrenci.final_notu*0.4;
			ogrenciNotlari[0]=not_ortalamasi;
			ogrenciNotlari[1]=0;
			
			return ogrenciNotlari;
		}
		
}
//Odev sayisi fonksiyonu
int *odev(int arraySize)
{
	//Gerekli tanýmlamalar
	int notlar[arraySize];
	//Notlarin istenmesi
	int i;
	for(i=0;i<arraySize;i++){
		printf("%d. odev notu:",i+1);
		scanf("%d",&notlar[i]);	
	}
	return notlar;
}
