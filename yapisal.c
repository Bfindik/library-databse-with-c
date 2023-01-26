#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Yazar { 
 int yazarID;
 char yazarAd[30]; 
 char yazarSoyad[30]; 
 struct Yazar *next;
 }YAZAR;
 typedef struct Ogrenci { 
 char ogrID[9]; 
 char ad[30]; 
 char soyad[30]; 
 int puan; 
 struct Ogrenci *next; 
 struct Ogrenci *prev;
 }OGRENCI;
 typedef struct KitapOrnek { 
 char EtiketNo[20]; 
 char Durum[8]; 
 struct KitapOrnek *next; 
 }KITAPORNEK;
 typedef struct Kitap {
 char kitapAdi[30]; 
 char ISBN[13]; 
 int adet; 
 struct Kitap *next; 
 struct KitapOrnek *head;
  }KITAP;
 typedef struct KitapYazar{ 
 char ISBN[13]; 
 int YazarID;
 }KITAPYAZAR;
 typedef struct Tarih{ 
 unsigned int gun:5; 
 unsigned int ay:4; 
 unsigned int yil:12;
 }TARIH;
 typedef struct KitapOdunc{ 
 char EtiketNo[20]; 
 char ogrID[9];  
 unsigned int islemTipi:1; 
 struct Tarih islemTarihi;
 }KITAPODUNC;
 void freeOgrenci(OGRENCI *head){
 	OGRENCI *tmp;
 	while(head!=NULL){
 		tmp=head;
 		head=head->next;
 		free(tmp);
	 }
 }
 void freeKitap(KITAP *head){
 	KITAP *tmp;
 	KITAPORNEK *tmp2,*tmp3;
 	while(head!=NULL){
 		tmp2=head->head;
 		while(tmp2!=NULL){
 			tmp3=tmp2;
 			tmp2=tmp2->next;
 			free(tmp3);
		 }
		 tmp=head;
		 head=head->next;
		 free(tmp);
	 }
 }
 void freeYazar(YAZAR *head){
 	YAZAR *tmp;
 	while(head!=NULL){
 		tmp=head;
 		head=head->next;
 		free(tmp);
	 }
 }
 void teslimEdilmeyenKitaplar(KITAPODUNC *dizi){
 	int gun,ay,yil,gunfarki,i,N;
 	printf("bugunun tarihini giriniz gun.ay.yil formatiyla: ");
 	scanf("%d.%d.%d",&gun,&ay,&yil);
 	TARIH t;
 	t.gun=gun;
 	t.ay=ay;
 	t.yil=yil;
 	N=KitapOduncSayi();
 	for(i=0;i<N;i++){
 		if(dizi[i].islemTipi==0){
 		 gunfarki+=(t.yil-dizi[i].islemTarihi.yil)*365;
		 gunfarki+=(t.ay-dizi[i].islemTarihi.ay)*30;
		 gunfarki+=(t.gun-dizi[i].islemTarihi.gun);
		 if(gunfarki>15){
			printf("%s--%s--%d--%d.%d.%d\n",dizi[i].EtiketNo,dizi[i].ogrID,dizi[i].islemTipi,dizi[i].islemTarihi.gun,dizi[i].islemTarihi.ay,dizi[i].islemTarihi.yil);
		 }
		 gunfarki=0;
	   }
	 }
 }
 void ogrenciGoruntuleme(OGRENCI *head,KITAPODUNC *dizi,int opt){
 	OGRENCI *tmp=head,*tmp2=head;
 	int N,i,found;
 	char id[9],ad[30],soyad[30];
 	if(opt==1){
 		printf("id giriniz:");
 	    scanf("%s",id);
 	    while(tmp!=NULL){
 		   if(strcmp(id,tmp->ogrID)==0){
 			found=1;
		 }
		 tmp=tmp->next;
	 }   
    }
    if(opt==2){
    	printf("ad giriniz:");
 	    scanf("%s",ad);
 	    while(tmp!=NULL){
 		  if(strcmp(ad,tmp->ad)==0){
 			found=1;
 			strcpy(id,tmp->ogrID);
		 }
		 tmp=tmp->next;
	 }
	}
	if(opt==3){
		printf("soyad giriniz:");
 	    scanf("%s",soyad);
 	    while(tmp!=NULL){
 		  if(strcmp(soyad,tmp->soyad)==0){
 			found=1;
 			strcpy(id,tmp->ogrID);
		 }
		 tmp=tmp->next;
	 }
	}
	if(found!=1){
		printf("islem basarisiz");
	}else{
 	N=KitapOduncSayi();
 		while(tmp2!=NULL){
 			if(strcmp(tmp2->ogrID,id)==0)
 			   printf("%s--%s--%s--%d\n",tmp2->ogrID,tmp2->ad,tmp2->soyad,tmp2->puan);
 			tmp2=tmp2->next;
		 }
		 for(i=0;i<N;i++){
 				if(strcmp(dizi[i].ogrID,id)==0){
 					printf("%s--%s--%d--%d.%d.%d\n",dizi[i].EtiketNo,dizi[i].ogrID,dizi[i].islemTipi,dizi[i].islemTarihi.gun,dizi[i].islemTarihi.ay,dizi[i].islemTarihi.yil);
				 }
			 }
   }
 }
 void cezaliOgrenciListele(OGRENCI *head){
 	while(head!=NULL){
 		if(head->puan<100){
 			printf("%s--%s--%s--%d\n",head->ogrID,head->ad,head->soyad,head->puan);
		 }
		 head=head->next;
	 }
 }
  void tumOgrencileriListele(OGRENCI *head){
 	while(head!=NULL){
 			printf("%s--%s--%s--%d\n",head->ogrID,head->ad,head->soyad,head->puan);
		 head=head->next;
	 }
 }
 void TeslimEdilmemisOgrenci(KITAP *head,OGRENCI *head2){
 	OGRENCI *temp=head2;
 	char durum[10]={"rafta"};
 	KITAPORNEK *tmp;
 	while(head!=NULL){
 		tmp=head->head;
 		while(tmp!=NULL){
 			if(strcmp(tmp->Durum,durum)!=0){ 
 				while(temp!=NULL){
 					if(strcmp(temp->ogrID,tmp->Durum)==0){
 						printf("%s--%s--%s--%d\n",temp->ogrID,temp->ad,temp->soyad,temp->puan);
					 }
					 temp=temp->next;
				 }
				 temp=head2;
			 }
			 tmp=tmp->next;
		 }
		 head=head->next;
	 }
 }
 KITAPODUNC* dosyadanOku5(KITAP *head){
 	FILE *fp;
 	KITAPODUNC *tmp;
 	KITAPORNEK *tmp2;
 	int N=0,i=0,j;
 	char line[255],*token;
 	N=KitapOduncSayi();
	fp=fopen("KitapOdunc.csv","r");
	tmp=(KITAPODUNC*)malloc(N*sizeof(KITAPODUNC));
	while(fgets(line,sizeof(line),fp)!=NULL){
	 	token=strtok(line,",");
	    strcpy(tmp[i].EtiketNo,token);
	 	token=strtok(NULL,",");
	 	strcpy(tmp[i].ogrID,token);
	 	token=strtok(NULL,",");
	 	int x=atoi(token);
	 	tmp[i].islemTipi=x;
	 	token=strtok(NULL,",");
	 	unsigned int a,b,c;
	 	sscanf(token,"%d.%d.%d",&a,&b,&c);
	    TARIH t;
	 	t.gun=a;
	 	t.ay=b;
	 	t.yil=c;
	 	tmp[i].islemTarihi=t;
	 	//printf("%s %s %d %u.%u.%u\n",tmp[i].EtiketNo,tmp[i].ogrID,tmp[i].islemTipi,tmp[i].islemTarihi.gun,tmp[i].islemTarihi.ay,tmp[i].islemTarihi.yil);
	 	i++;
		 }
		 fclose(fp);
	 	while(head!=NULL){
	 		tmp2=head->head;
	 		while(tmp2!=NULL){
	 			for(j=0;j<N;j++){
	 				if(strcmp(tmp[j].EtiketNo,tmp2->EtiketNo)==0 && tmp[j].islemTipi==0){
	 				   strcpy(tmp2->Durum,tmp[j].ogrID);
	 			    }
				 }
				 tmp2=tmp2->next;
			 }
			 head=head->next;
		 }
	 
	return tmp;
 }
int KitapOduncSayi(){
	FILE *fp;
	char line[255];
	int N=0;
 	fp=fopen("KitapOdunc.csv","r");
 	if(fp==NULL){
 		printf("dosya acilmadi");
 		return;
	 }
	 else{
	 	while(fgets(line,sizeof(line),fp)!=NULL){
	 		N++;
		 }
		fclose(fp);
	return N;
}
}
KITAPODUNC* KitapOduncAl(KITAPODUNC *dizi,OGRENCI *head,KITAP *head2){
	FILE *fp;
	char ogrenciNo[9],etiketNo[20],durum[10]={"rafta"};
	int found=0,found2=0,sayac=0,error=0;
	int gun,ay,yil,N,i;
	KITAPORNEK *tmp;
	printf("ogrencinin numarasi: ");
	scanf("%s",ogrenciNo);
	printf("kitabin etiket numarasi: ");
	scanf("%s",etiketNo);
	printf("tarihi giriniz gun.ay.yil sirayla : ");
	scanf("%d.%d.%d",&gun,&ay,&yil);
	TARIH t;
	t.gun=gun;
	t.ay=ay;
	t.yil=yil;
	N=KitapOduncSayi();
	while(head!=NULL){//ogrenci kayitli mi deðil mi
		if(strcmp(ogrenciNo,head->ogrID)==0){
			if(head->puan>0){
				found=1;
			}else{
				printf("puaniniz 0 in altinda\n");
			}
		}
		head=head->next;
	}
	while(head2!=NULL){//etiket no ya sahip kitap örneði var mi
		tmp=head2->head;
		while(tmp!=NULL){
			if(strcmp(tmp->EtiketNo,etiketNo)==0 && strcmp(tmp->Durum,durum)==0){
				found2=1;
			}
			tmp=tmp->next;
		}
		head2=head2->next;
	}
	if(found2==1){// daha önce kitap alýnmýþ ve býrakýlmamýþ mý
		while(sayac<N){
			if(strcmp(dizi[sayac].EtiketNo,etiketNo)==0 && dizi[sayac].islemTipi==0){
				error=1;
			}sayac++;
		}
	}
	if(found==0 || found2==0 || error==1){
		printf("islem yapamazsiniz");
	}else{
	dizi=(KITAPODUNC*)realloc(dizi,(N+1)*sizeof(KITAPODUNC));
	strcpy(dizi[N].EtiketNo,etiketNo);
	dizi[N].islemTipi=0;
	strcpy(dizi[N].ogrID,ogrenciNo);
	dizi[N].islemTarihi=t;
	while(head2!=NULL){//etiket no ya sahip kitap örneðinin durumunu güncelleme
		tmp=head2->head;
		while(tmp!=NULL){
			if(strcmp(tmp->EtiketNo,etiketNo)==0){
				strcpy(tmp->Durum,ogrenciNo);
			}
			tmp=tmp->next;
		}
		head2=head2->next;
	}
	fp=fopen("KitapOdunc.csv","a");
    fprintf(fp,"\n%s,%s,%d,%d.%d.%d",dizi[N].EtiketNo,dizi[N].ogrID,dizi[N].islemTipi,dizi[N].islemTarihi.gun,dizi[N].islemTarihi.ay,dizi[N].islemTarihi.yil);
	fclose(fp);
}
    return dizi;
}
void KitapTeslimEt(KITAPODUNC *dizi,OGRENCI *head,KITAP *head2){
	char etiketNo[20],ogrenciNo[9],durum[10]={"rafta"};
	int N,i,found=0,gunfarki=0,found2=0;
	int gun,ay,yil;
	FILE *fp;
	KITAPORNEK *tmp;
	printf("teslim edilecek kitabin etiket numarasý: ");
	scanf("%s",etiketNo);
	printf("ogrenci no: ");
	scanf("%s",ogrenciNo);
	printf("tarihi giriniz gun.ay.yil sirayla : ");
	scanf("%d.%d.%d",&gun,&ay,&yil);
	TARIH t;
	t.gun=gun;
	t.ay=ay;
	t.yil=yil;
	N=KitapOduncSayi();
	for(i=0;i<N;i++){
		if(strcmp(dizi[i].EtiketNo,etiketNo)==0 && strcmp(dizi[i].ogrID,ogrenciNo)==0 && dizi[i].islemTipi==0){
			dizi[i].islemTipi=1;
			found=1;
			gunfarki+=(t.yil-dizi[i].islemTarihi.yil)*365;
			gunfarki+=(t.ay-dizi[i].islemTarihi.ay)*30;
			gunfarki+=(t.gun-dizi[i].islemTarihi.gun);
			if(gunfarki>15){
				found2=1;
			}
		}
	}
	if(found2==1){
		fp=fopen("Ogrenciler.csv","w");
		if(fp==NULL){
			return;
		}else{
		  while(head!=NULL){
			if(strcmp(head->ogrID,ogrenciNo)==0){
				head->puan-=10;
			}
			if(head->next==NULL){
				fprintf(fp,"%s,%s,%s,%d",head->ogrID,head->ad,head->soyad,head->puan);
			}else{
			fprintf(fp,"%s,%s,%s,%d\n",head->ogrID,head->ad,head->soyad,head->puan);
		}
			head=head->next;
		  }
		  fclose(fp);
        }
		
	}
	if(found==0){
		printf("islem basarisiz\n");
	}else{
		while(head2!=NULL){
			tmp=head2->head;
			while(tmp!=NULL){
				if(strcmp(tmp->EtiketNo,etiketNo)){
					strcpy(tmp->Durum,durum);
				}
				tmp=tmp->next;
			}
			head2=head2->next;
		}
		fp=fopen("KitapOdunc.csv","w");
		if(fp==NULL){
			printf("error");
			return;
		}else{
			for(i=0;i<N;i++){
				if(i==N-1){
				    fprintf(fp,"%s,%s,%d,%d.%d.%d",dizi[i].EtiketNo,dizi[i].ogrID,dizi[i].islemTipi,dizi[i].islemTarihi.gun,dizi[i].islemTarihi.ay,dizi[i].islemTarihi.yil);
				}else{
				fprintf(fp,"%s,%s,%d,%d.%d.%d\n",dizi[i].EtiketNo,dizi[i].ogrID,dizi[i].islemTipi,dizi[i].islemTarihi.gun,dizi[i].islemTarihi.ay,dizi[i].islemTarihi.yil);}
			}
			 fclose(fp);
		}
	}
}
void kitapYazarEslestir(KITAPYAZAR *dizi){
	char isbn[13];
	int i;
	int id,N,error=0;
	FILE *fp;
	printf("eslestirmek istediginiz kitabin ISBN:");
	scanf("%s",isbn);
	printf("eslestirmek istediginiz yazarin id:");
	scanf("%d",&id);
    N=KitapYazarSayi();
    for(i=0;i<N;i++){
    	if(strcmp(dizi[i].ISBN,isbn)==0 && dizi[i].YazarID==id){
    		printf("bu kitap yazar KAYITLI");
    		error=1;
		}
	}
	dizi=(KITAPYAZAR*)realloc(dizi,(N+1)*sizeof(KITAPYAZAR));
	strcpy(dizi[N].ISBN,isbn);
	dizi[N].YazarID=id;
	if(error==0){
		fp=fopen("KitapYazar.csv","a");
		if(fp==NULL){
			printf("dosya acilamiyor");
		}else{
			fprintf(fp,"\n%s,%d",isbn,id);
		}
		fclose(fp);
	}
}
KITAPYAZAR* dosyadanOku4(){
	FILE *fp;
	KITAPYAZAR *tmp,*tmp2;
	char line[255];
	int N=0,i=0;
	fp=fopen("KitapYazar.csv","r");
	if(fp==NULL){
		printf("error");
	}else{
		while(fgets(line,sizeof(line),fp)!=NULL){
	 		N++;
		 }
		fclose(fp);
		fp=fopen("KitapYazar.csv","r");
		tmp=(KITAPYAZAR*)malloc(N*sizeof(KITAPYAZAR));
		while(!feof(fp)){
			fscanf(fp,"%[^,],%d\n",tmp[i].ISBN,&tmp[i].YazarID);
			i++;
		}
		fclose(fp);

		return tmp;
	}
	
}
void KitapOrnekOku(KITAP *head,int adet){
 	int sayac=adet;
 	char c[3],durum[10]={"rafta"},etiket[20];
 	KITAPORNEK *tmp2,*end;
 		while(sayac<=head->adet){
 			tmp2=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
 			if(sayac==1){
 				head->head=tmp2;
 				end=tmp2;
			 }else{
			end->next=tmp2;
 			end=end->next;
			 }
			itoa(sayac,c,10);
 			strcpy(etiket,head->ISBN);
 			etiket[13]='_';
 			etiket[14]=c[0];
 			etiket[15]=c[1];
 			etiket[16]=c[2];
 			strcpy(tmp2->EtiketNo,etiket);
 			strcpy(tmp2->Durum,durum);
 			sayac++;
		 }	
 }
 void KitapOrnekEkle(KITAP *ornek,int adet){
 	int sayac=ornek->adet+1;
 	char c[3],durum[10]={"rafta"},etiket[20];
 	KITAPORNEK *tmp2,*end=ornek->head;
 	while(end->next!=NULL){
 		end=end->next;
	 }
 	while(sayac<=adet){
 		tmp2=(KITAPORNEK*)malloc(sizeof(KITAPORNEK));
 		end->next=tmp2;
 		itoa(sayac,c,10);
 		strcpy(etiket,ornek->ISBN);
 		etiket[13]='_';
 		etiket[14]=c[0];
 		etiket[15]=c[1];
 		etiket[16]=c[2];
 		strcpy(tmp2->EtiketNo,etiket);
 		strcpy(tmp2->Durum,durum);
 		sayac++;
 		end=end->next;
	 }
 }

 KITAP* dosyadanOku3(){
 	FILE *fp;
 	KITAP *head=NULL,*tmp,*end;
 	KITAPORNEK *tmp2;
 	char etiket[20],c;
 	char durum[10]={"Rafta"};
 	int sayac=0;
 	fp=fopen("Kitaplar.csv","r");
 	if(fp==NULL){
 		printf("dosya acilamadi");
	 }
	 else{
	 	while(!feof(fp)){
	 		tmp=(KITAP*)malloc(sizeof(KITAP));
	 		fscanf(fp,"%[^,],%[^,],%d\n",tmp->kitapAdi,tmp->ISBN,&tmp->adet);
	 		tmp->next=NULL;
	 		if(head==NULL){
	 			head=end=tmp;
			 }
			else{
				end->next=tmp;
	 			end=end->next;
			}
		 }
		 fclose(fp);
		 tmp=head;
		 while(tmp!=NULL){
		 	KitapOrnekOku(tmp,1);
		 	tmp=tmp->next;
		 }
	 }
	 return head;
 }
 KITAP kitapEkle(KITAP **head){
 	KITAP *temp;
 	KITAP *tmp=*head;
 	FILE *fp;
 	int found=0;
 	temp=(KITAP*)malloc(sizeof(KITAP));
 	if(temp==NULL){
 		printf("error");
	 }else{
	 	printf("Kitabin ISBN:");
	 	scanf("%s",temp->ISBN);
	 	printf("Kitabin adi:");
	 	scanf(" %[^\n]%*c",temp->kitapAdi);
	 	printf("Kitabin adeti:");
	 	scanf("%d",&temp->adet);
	 	while(tmp!=NULL && found!=1){
	 		if(strcmp(temp->ISBN,tmp->ISBN)==0){
	 			found=1;
	 			printf("bu kitap kayitli");
			 }
			 tmp=tmp->next;
		 }
		if(found==0){
		 tmp=*head;
	 	 if(*head==NULL){
	 		*head=temp;
		 }else{
		 	while(tmp->next!=NULL){
		 		tmp=tmp->next;
			 }
			 tmp->next=temp;
		 }
		 KitapOrnekOku(temp,1);
		 fp=fopen("Kitaplar.csv","a");
		 if(fp==NULL){
 		  printf("dosya acilmadi");
	     }
	     else{
	    	fprintf(fp,"\n%s,%s,%d",temp->kitapAdi,temp->ISBN,temp->adet);	
		 }
	     fclose(fp);
	    }
	 }
	 
 }
void kitapSil(KITAP **head){
	FILE *fp;
	char id[13];
	int found=0,N,i;
	printf("ISBN giriniz :");
	scanf("%s",id);
	KITAP *tmp = *head;
	KITAP *prev = NULL;
	KITAP *tmp2= *head;
	while(tmp !=NULL && found==0){
		if (strcmp(tmp->ISBN,id)==0){
			found =1;
			if(prev== NULL){
				*head = tmp->next;
			}
			else{
				prev->next= tmp->next;
			}
			free(tmp);
		}
		prev = tmp;
		tmp = tmp ->next;
	}
	if(found==1){
	    fp=fopen("Kitaplar.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp2!= NULL){
	    		if(tmp2->next==NULL){
	    			fprintf(fp,"%s,%s,%d",tmp2->kitapAdi,tmp2->ISBN,tmp2->adet);
				}else{
	    		fprintf(fp,"%s,%s,%d\n",tmp2->kitapAdi,tmp2->ISBN,tmp2->adet);}
	    		tmp2=tmp2->next;
			}	
		}
	    fclose(fp);
}
	if(found==0){
		printf("kitap bulunamadi");
	}
}
void kitapGuncelle(KITAP **head){
	FILE *fp;
	int adet;
	int option,found=0;
	char id[13],isbn[17];
	printf("degistirmek istediginiz kitabin ISBN: ");
	scanf("%s",id);
	printf("deðistirmek istedginiz ISBN icin 1,ad icin 2,adet arttirmak icin 3: ");
	scanf("%d",&option);
	KITAP *tmp = *head;
	while(tmp!=NULL && found==0){
		if(strcmp(tmp->ISBN,id)==0){
			found=1;
			switch(option){
				case 1:
					printf("degistirmek istediginiz kitabin ISBN'i': ");
					scanf("%s",tmp->ISBN);
					break;
				case 2:
				    printf("degistirmek istediginiz kitap adi:");
					scanf(" %[^\n]%*c",tmp->kitapAdi);
					break;	
				case 3:
				    printf("degistirmek istediginiz kitap adeti: ");
					scanf("%d",&adet);
					KitapOrnekEkle(tmp,adet);
					tmp->adet=adet;	
					break;
				default:
					printf("gecerli numara giriniz");
			}
		}
		tmp=tmp->next;
	}
	tmp=*head;
	fp=fopen("Kitaplar.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp!= NULL){
	    		if(tmp->next==NULL){
	    			fprintf(fp,"%s,%s,%d",tmp->kitapAdi,tmp->ISBN,tmp->adet);
				}else{
	    		fprintf(fp,"%s,%s,%d\n",tmp->kitapAdi,tmp->ISBN,tmp->adet);
	    	}
	    		tmp=tmp->next;
			}
		}
	fclose(fp);
	if(found==0){
		printf("kitap bulunamadý");
	}
}
void kitapGoruntule(KITAP *head,char kitapadi[30]){
	KITAPORNEK *tmp=head->head;
	int found=0;
	while(head!=NULL && found!=1){
		if(strcmp(head->kitapAdi,kitapadi)==0){
			found=1;
			printf("%s--%s--%d\n",head->kitapAdi,head->ISBN,head->adet);
			while(tmp!=NULL){
				printf("%s--%s\n",tmp->EtiketNo,tmp->Durum);
				tmp=tmp->next;
			}
		}
		head=head->next;
	}
}
void raftakiKitaplar(KITAP *head){
	KITAPORNEK *tmp=head->head;
	char durum[10]={"rafta"};
	while(head!=NULL){
		tmp=head->head;
	  while(tmp!=NULL){
		if(strcmp(tmp->Durum,durum)==0){
			printf("%s--%s\n",tmp->EtiketNo,tmp->Durum);
		}
		tmp=tmp->next;
	}
	head=head->next;
}
}
void kitabinYazariniGuncelle(KITAPYAZAR* dizi){
	char isbn[13];
	int N,i,id,id1,found=0;
	FILE *fp;
	printf("guncellemek istediginiz kitabin ISBN numarasi:");
	scanf("%s",isbn);
	printf("guncellemek istedginiz yazarýn ID:");
	scanf("%d",&id1);
	printf("yeni yazarýn ID:");
	scanf("%d",&id);
	N=KitapYazarSayi();
	for(i=0;i<N;i++){
	   	if(strcmp(dizi[i].ISBN,isbn)==0 && dizi[i].YazarID==id1 && found==0){
	   		found=1;
			dizi[i].YazarID=id;
		}
	}
	fp=fopen("KitapYazar.csv","w");
	for(i=0;i<N;i++){
		if(i==N-1){
			fprintf(fp,"%s,%d",dizi[i].ISBN,dizi[i].YazarID);
		}else{
		fprintf(fp,"%s,%d\n",dizi[i].ISBN,dizi[i].YazarID);
	}
	}
	fclose(fp);
}
 OGRENCI* dosyadanOku2(){
 	FILE *fp;
 	OGRENCI *head=NULL,*tmp,*end;
 	fp=fopen("Ogrenciler.csv","r");
 	if(fp==NULL){
 		printf("dosya acilmadi");
	 }
	 else{
	 	while(!feof(fp)){
	 		tmp=(OGRENCI*)malloc(sizeof(OGRENCI));
	 		fscanf(fp,"%[^,],%[^,],%[^,],%d\n",tmp->ogrID,tmp->ad,tmp->soyad,&tmp->puan);
	 		tmp->next=NULL;
	 		if(head==NULL){
	 			head=end=tmp;
			 }
	 		else{
	 			end->next=tmp;
	 			tmp->prev=end;
	 			end=end->next;
			 }
		 }
		 fclose(fp);
	 }
 	return head;
 }
 void ogrenciEkle(OGRENCI **head){
 	OGRENCI *temp;
 	OGRENCI *tmp=*head;
 	FILE *fp;
 	int found=0;
 	temp=(OGRENCI*)malloc(sizeof(OGRENCI));
 	if(temp==NULL){
 		printf("error");
	 }else{
	 	printf("Ogrencinin ID,ad ve soyadi sirasiyla");
	 	scanf("%s %s %s",&temp->ogrID,&temp->ad,&temp->soyad);
	 	temp->puan=100;
	 	while(tmp!=NULL && found!=1){
	 		if(strcmp(temp->ogrID,tmp->ogrID)==0){
	 			found=1;
	 			printf("bu yazar kayitli");
			 }
			 tmp=tmp->next;
		 }
		if(found==0){
		 tmp=*head;
	 	 if(tmp==NULL){
	 	 	temp->prev=NULL;
	 		tmp=temp;
		 }else{
		 	while(tmp->next!=NULL){
		 		tmp=tmp->next;
			 }
			 tmp->next=temp;
			 temp->prev=tmp;
			 temp->next=NULL;
		 }
		 fp=fopen("Ogrenciler.csv","a");
		 if(fp==NULL){
 		  printf("dosya acilmadi");
	     }
	     else{
	    	fprintf(fp,"\n%s,%s,%s,%d",temp->ogrID,temp->ad,temp->soyad,temp->puan);	
		 }
	     fclose(fp);
	    }
	 }
 }
void ogrenciSil(OGRENCI **head){
 	FILE *fp;
	char id[9];
	int found=0;
	printf("id giriniz :");
	scanf("%s",id);
	OGRENCI *tmp = *head;
	OGRENCI *prev = NULL;
	OGRENCI *tmp2= *head;
	while(tmp !=NULL && found==0){
		if (strcmp(tmp->ogrID,id)==0){
			found =1;
			if (*head == tmp)
               *head = tmp->next;
            if (tmp->next != NULL)
               tmp->next->prev = tmp->prev;
            if (tmp->prev != NULL)
               tmp->prev->next = tmp->next;
            free(tmp);
		}
		prev = tmp;
		tmp = tmp ->next;
	}
	fp=fopen("Ogrenciler.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp2!= NULL){
	    		if(tmp2->next==NULL){
	    			fprintf(fp,"%s,%s,%s,%d",tmp2->ogrID,tmp2->ad,tmp2->soyad,tmp2->puan);
				}else{
	    		fprintf(fp,"%s,%s,%s,%d\n",tmp2->ogrID,tmp2->ad,tmp2->soyad,tmp2->puan);
	    	}
	    		tmp2=tmp2->next;
			}
		}
	fclose(fp);
 }
 void ogrenciGuncelle(OGRENCI **head){
 	FILE *fp;
	char id[9];
	int option,found=0;
	printf("degistirmek istediginiz ogrencinin id'si: ");
	scanf("%s",id);
	printf("deðistirmek istedginiz id icin 1,ad icin 2,soyad icin 3,puan icin 4: ");
	scanf("%d",&option);
	OGRENCI *tmp = *head;
	while(tmp!=NULL && found!=1){
		if(strcmp(tmp->ogrID,id)==0){
			found=1;
			switch(option){
				case 1:
					printf("id: ");
					scanf("%s",tmp->ogrID);
					break;
				case 2:
				    printf("ad: ");
					scanf(" %[^\n]%*c",tmp->ad);
					break;	
				case 3:
				    printf("soyad: ");
					scanf(" %[^\n]%*c",tmp->soyad);
					break;
				case 4:
					printf("puan: ");
					scanf("%d",&tmp->puan);
					break;
				default:
					printf("gecerli numara giriniz");
			}
		}
		tmp=tmp->next;
	}
	tmp=*head;
	fp=fopen("Ogrenciler.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp!= NULL){
	    		if(tmp->next==NULL){
	    			fprintf(fp,"%s,%s,%s,%d",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
				}else{
	    		fprintf(fp,"%s,%s,%s,%d\n",tmp->ogrID,tmp->ad,tmp->soyad,tmp->puan);
	    	}
	    		tmp=tmp->next;
			}
		}
	fclose(fp);
	if(found==0){
		printf("ogrenci bulunamadý");
	}
 }
 YAZAR* dosyadanOku(){
 	FILE *fp;
 	YAZAR *head=NULL,*tmp,*end;
 	fp=fopen("Yazarlar.csv","r");
 	if(fp==NULL){
 		printf("dosya acilmadi");
	 }
	 else{
	 	while(!feof(fp)){
	 		tmp=(YAZAR*)malloc(sizeof(YAZAR));
	 		fscanf(fp,"%d,%[^,],%s\n",&tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
	 		tmp->next=NULL;
	 		if(head==NULL){
	 			head=end=tmp;
			 }
	 		else{
	 			end->next=tmp;
	 			end=end->next;
			 }
		 }
		 fclose(fp);
	 }
 	return head;
 }
int KitapYazarSayi(){
	FILE *fp;
	char line[255];
	int N=0;
 	fp=fopen("KitapYazar.csv","r");
	if(fp==NULL){
		printf("error");
	}else{
		while(fgets(line,sizeof(line),fp)!=NULL){
	 		N++;
		 }
	fclose(fp);
	return N;
 }
}
 void yazarListele(YAZAR *head,char ad[30],char soyad[30],KITAPYAZAR *dizi,KITAP *head2){
 	YAZAR *tmp=head;
 	KITAP *tmp2=head2;
 	int found=0,i=0,N=0;
 	N=KitapYazarSayi();
 	while(tmp!=NULL && found!=1){
 		if(strcmp(tmp->yazarAd,ad)==0 && strcmp(tmp->yazarSoyad,soyad)==0){
 			printf("%d--%s--%s\n",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
            for(i=0;i<N;i++){
            	if(dizi[i].YazarID==tmp->yazarID){
            		tmp2=head2;
            		while(tmp2!=NULL){
            			if(strcmp(tmp2->ISBN,dizi[i].ISBN)==0){

            				printf("%s--%s--%d\n",tmp2->kitapAdi,tmp2->ISBN,tmp2->adet);
						}
						tmp2=tmp2->next;
					}
				}
			}
		 }
		tmp=tmp->next;
	 }
 }
 void yazarEkle(YAZAR **head){
 	YAZAR *temp;
 	YAZAR *tmp=*head;
 	FILE *fp;
 	int found=0,sayac=1;
 	temp=(YAZAR*)malloc(sizeof(YAZAR));
 	if(temp==NULL){
 		printf("error");
	 }else{
	 	printf("Yazarin ad ve soyadi sirasiyla: ");
	 	scanf(" %s %s",&temp->yazarAd,&temp->yazarSoyad);
	 	while(tmp!=NULL && found!=1){
	 		if(strcmp(temp->yazarAd,tmp->yazarAd)==0 && strcmp(temp->yazarSoyad,tmp->yazarSoyad)==0){
	 			found=1;
	 			printf("bu yazar kayitli");
			 }
			 tmp=tmp->next;
			 sayac++;
		 }
		if(found==0){
		 tmp=*head;
	 	 if(*head==NULL){
	 	 	temp->yazarID=1;
	 		*head=temp;
		 }else{
		 	while(tmp->next!=NULL){
		 		tmp=tmp->next;
			 }
			 temp->yazarID=sayac+1;
			 tmp->next=temp;
		 }
		 fp=fopen("Yazarlar.csv","a");
		 if(fp==NULL){
 		  printf("dosya acilmadi");
	     }
	     else{
	    	fprintf(fp,"\n%d,%s,%s",temp->yazarID,temp->yazarAd,temp->yazarSoyad);	
		 }
	     fclose(fp);
	    }
	 }
	 
 }
void yazarSil(YAZAR **head,KITAPYAZAR* dizi){
	FILE *fp;
	int id,N,i;
	int found=0;
	printf("id giriniz :");
	scanf("%d",&id);
	YAZAR *tmp = *head;
	YAZAR *prev = NULL;
	YAZAR *tmp2= *head;
	while(tmp !=NULL && found==0){
		if (tmp->yazarID==id){	
			found =1;
			if(prev== NULL){
				*head = tmp->next;
			}
			else{
				prev->next= tmp->next;
			}
			free(tmp);
		}
		prev = tmp;
		tmp = tmp ->next;
	}
	fp=fopen("Yazarlar.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp2!= NULL){
	    		if(tmp2->next==NULL){
	    			fprintf(fp,"%d,%s,%s",tmp2->yazarID,tmp2->yazarAd,tmp2->yazarSoyad);
				}else{
	    		fprintf(fp,"%d,%s,%s\n",tmp2->yazarID,tmp2->yazarAd,tmp2->yazarSoyad);}
	    		tmp2=tmp2->next;
			}
		}
	fclose(fp);
	if(found==0){
		printf("kayitli yazar yok");
	}
	N=KitapYazarSayi();
	if(found==1){
		for(i=0;i<N;i++){
			if(dizi[i].YazarID==id){
				dizi[i].YazarID=-1;
			}
		}
		fp=fopen("KitapYazar.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	for(i=0;i<N;i++){
	    		if(i==N-1){
	    			fprintf(fp,"%s,%d",dizi[i].ISBN,dizi[i].YazarID);
				}else{
	    		fprintf(fp,"%s,%d\n",dizi[i].ISBN,dizi[i].YazarID);
	    	}
			}
		}
		fclose(fp);
	}
}
void yazarGuncelle(YAZAR **head){
	FILE *fp;
	char ad[30],soyad[30];
	int option,found=0;
	printf("degistirmek istediginiz yazarin adi: ");
	scanf("%s",ad);
	printf("degistirmek istediginiz yazarin soyadi: ");
	scanf("%s",soyad);
	printf("deðistirmek istedginiz id icin 1,ad icin 2,soyad icin 3: ");
	scanf("%d",&option);
	YAZAR *tmp = *head;
	while(tmp!=NULL && found==0){
		if(strcmp(tmp->yazarAd,ad)==0 && strcmp(tmp->yazarSoyad,soyad)==0){
			found=1;
			switch(option){
				case 1:
					printf("degistirmek istediginiz id: ");
					scanf("%d",&tmp->yazarID);
					break;
				case 2:
				    printf("degistirmek istediginiz ad: ");
					scanf("%s",tmp->yazarAd);
					break;	
				case 3:
				    printf("degistirmek istediginiz soyad: ");
					scanf("%s",tmp->yazarSoyad);
					break;
				default:
					printf("gecerli numara giriniz");
			}
		}
		tmp=tmp->next;
	}
	tmp=*head;
	fp=fopen("Yazarlar.csv","w");
		if(fp==NULL){
 		  printf("dosya acilmadi");
	    }
	    else{
	    	while(tmp!= NULL){
	    		if(tmp->next==NULL){
	    			fprintf(fp,"%d,%s,%s",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);
				}else{
	    		fprintf(fp,"%d,%s,%s\n",tmp->yazarID,tmp->yazarAd,tmp->yazarSoyad);}
	    		tmp=tmp->next;
			}
		}
	fclose(fp);
	if(found==0){
		printf("yazar bulunamadý");
	}
}

 int main(){
 	YAZAR *head;
 	OGRENCI *head2;
 	KITAP *head3;
 	KITAPODUNC *dizi;
 	KITAPYAZAR *dizi2;
 	int option,option2=0,i,opt,exit=0;
 	char ad[30],soyad[30],kitapadi[30];
 	head=dosyadanOku();
 	head2=dosyadanOku2();
 	head3=dosyadanOku3();
 	dizi2=dosyadanOku4();
 	dizi=dosyadanOku5(head3);
 	while(exit==0){
 	printf("--------------------------\n");
 	printf("yazarlar icin 1\nogrenciler icin 2\nkitap icin 3\ncikmak icin 4: ");
 	scanf("%d",&option);
    if(option==1){
    	while(option2!=7){
    		printf("--------------------------\n");
    		printf("eklemek icin 1\nsilmek icin2\nguncellemek icin 3\nyazari goruntulemek icin 4\nkitap-yazar eslestirmek icin 5\nust menuye donmek icin 6: ");
    		scanf("%d",&option2);
    		switch(option2){
    			case 1 :
    				yazarEkle(&head);
    				break;
    			case 2:
    				yazarSil(&head,dizi2);
    				break;
    			case 3: 
    			    yazarGuncelle(&head);
    			    break;
    			case 4:
    				printf("listelemek istediginiz yazarin adi: ");
    				scanf("%s",ad);
    				printf("listelemek istediðiniz yazarin soyadi: ");
    				scanf("%s",soyad);
    				yazarListele(head,ad,soyad,dizi2,head3);
    				break;
    			case 5:
    				kitapYazarEslestir(dizi2);
    				break;
    			case 6:
    				option2=7;
    				break;
    			default:
    				printf("gecerli sayi giriniz");
			}
		}
	}
	if(option==2){
		while(option2!=10){
			printf("--------------------------\n");
    		printf("eklemek icin 1\nsilmek icin2 \nguncellemek icin 3\nkitap odunc almak icin 4\nkitap teslim etmek icin 5\nkitap teslim etmemis ogrencileri listelemek icin 6\n");
    		printf("cezali ogrencileri listelemek icin 7\ntum ogrencileri listelemek icin 8\nogrenci bilgisi goruntulemek icin 9\nust menuye donmek icin 10: ");
    		scanf("%d",&option2);
    		switch(option2){
    			case 1 :
    				ogrenciEkle(&head2);
    				break;
    			case 2:
    				ogrenciSil(&head2);
    				break;
    			case 3: 
    			    ogrenciGuncelle(&head2);
    			    break;
    			case 4:
    				KitapOduncAl(dizi,head2,head3);
    				break;
    			case 5:
    				KitapTeslimEt(dizi,head2,head3);
    				break;
    			case 6:
    				TeslimEdilmemisOgrenci(head3,head2);
    				break;
    			case 7:
    				cezaliOgrenciListele(head2);
    				break;
    			case 8:
    				tumOgrencileriListele(head2);
    				break;
    			case 9:
    				printf("id icin 1,ad icin 2,soyad icin 3: ");
    				scanf("%d",&opt);
    				ogrenciGoruntuleme(head2,dizi,opt);
    				break;
    			case 10:
    				option2=10;
    				break;
    			default:
    				printf("gecerli sayi giriniz\n");
			}
		}
	}
	if(option==3){
		while(option2!=8){
			printf("--------------------------\n");
    		printf("eklemek icin 1\nsilmek icin2\nguncellemek icin 3\nkitap goruntulemek icin 4\nraftaki kitaplari goruntulemek icin 5\nkitap-yazar guncellemek icin 6\n");
    		printf("zamaninda teslim edilemeyen kitaplarý listelemek icin 7\nust menuye donmek icin 8:");
    		scanf("%d",&option2);
    		switch(option2){
    			case 1 :
    				kitapEkle(&head3);
    				kitapYazarEslestir(dizi2);
    				break;
    			case 2:
    				kitapSil(&head3);
    				break;
    			case 3: 
    			    kitapGuncelle(&head3);
    			    break;
    			case 4:
    				printf("kitap adi giriniz: ");
    				scanf(" %[^\n]%*c",kitapadi);
    				kitapGoruntule(head3,kitapadi);
    				break;
    			case 5:
    				raftakiKitaplar(head3);
    				break;
    			case 6:
    				kitabinYazariniGuncelle(dizi2);
    				break;
    			case 7:
    				teslimEdilmeyenKitaplar(dizi);
    				break;
    			case 8:
    				option2=8;
    				break;
    			default:
    				printf("gecerli sayi giriniz");
			}
		}
	}
	if(option==4){
		exit=1;
	}
}
    free(dizi);
    free(dizi2);
    freeKitap(head3);
    freeYazar(head);
    freeOgrenci(head2);	
	return 0;
 }
