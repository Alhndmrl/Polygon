/*Alihan Demirel
 * kullanicidan aldigi noktalarla tanimli,
 * bir polygonun alanini rastgele N tane nokta uretip
 * bu noktalardan polygonun icerisine dusenlerin sayisini kullanarak
 *  polygonun alanini hesaplar.
 */


#include <stdio.h>
#include <stdlib.h>

#define N 1000000        		/* alan hesabi icin kullanilacak nokta sayisi 			*/

double points[100][2];			/* polygonu tanimlamak icin kullanilacak noktalar		*/
int np = 0;						/* polygonun nokta sayisi. 								*/

/*y = mx +b icin
 * m[i], i.kenarin egimi m
 * m[i], i.kenarin b degerini tutacak.*/
double *m = NULL, *b = NULL;	/* kenarlar denklemleri icin m ve b degerlini tutacak	*/

/*points dizisine nokta ekler ve nokta sayisini bir arttirir*/
int addPoint(double x, double y);


 /*  bu fonksiyon m ve b icin alan ayirip her bir kenar icin bu degerleri hesaplayacak*/
int generateCoeffs();

/*verilen noktanin polygonun icerisinde olup olmadigini bulur*/
int isInside(double *point);

/*[a,b] artaliginda rastgele nokta olusturur*/
int generateRandomPoint(double *point, double a, double b);

/*width, height araliginda rastgele N tane nokta uretip alani hesaplar */
double findArea(double width, double height);


/**
 * points[np]'ye bir nokta ekler ve np'nin degerini bir artirir
 * increases np by 1, and returns np
 */
int addPoint(double x, double y){
	printf("nokta:%d- x:%lf, y:%lf \n",np+1, x, y);
	/*TODO: points[np][0]'a x'n degerini points[np][1]'e de y nin degerini atayin.*/
	 /*TODO: Sonra np yi bir artirin*/
	points[np][0]=x;
	points[np][1]=y;
	np++;
	return np;
}

/**
 * x [0,a] ve y [0, b] araliginda olacak sekilde bir nokta olusturur
 */
int generateRandomPoint(double *point, double a, double b) {
	/*TODO: [0, a] ve [0, b] araliginda iki tane double rastgele sayi ureterek
	 *  point[0] ve point[1]'e atayin*/
	 
	point[0]=a*(rand()/(double)RAND_MAX); /* [0,a] aralıgında sayi uretir */
	point[1]=b*(rand()/(double)RAND_MAX); /* [0,b] aralıgında sayi uretir */
	 
	return 0;
}

/**
 * m ve b degerleri icin alan ayirdiktan sonra
 * her bir i kenari icin m[i] ve b[i] degerlini bulur
 */
int generateCoeffs(){
	/*yine polygonun i. kenari (points[i][0],points[i][1])
	 * (points[i+1][0],points[i+1][1]) noktalariyla tanimlidir.
	 *
	 * Ayrica son kenar
	 * (points[0][0],points[0][1])
	 * (points[np-1][0],points[np-1][1]) noktalariyla tanimlidir. */
	/*TODO: b ve m pointerlari icin malloc kullanarak np tane double icin
	 * yer ayirin
	 */
	/*TODO her bir kenar icin m[i] ve b[i] degerlerini bulun
	 * burada m[i] = (y2-y1)/(x2-x1)
	 * b[i] = y2- m[i]*x2*/
	
	m=(double*) malloc(np * sizeof(double)); /* yer ayırma*/
	b=(double*) malloc(np * sizeof(double)); /* yer ayırma*/
	
	for(int i=0; i<np-1 ;i++){
		
		m[i]=(points[i+1][1] - points[i][1])/(points[i+1][0] - points[i][0]);
		b[i]=points[i+1][1] - m[i] * points[i+1][0];
	}
	    m[np-1] = (points[np-1][1]-points[0][1])/(points[np-1][0]-points[0][0]);
	    b[np-1] = points[np-1][1] - m[np-1]*points[np-1][0];
	
	return 0;
}

/**
 * point ile verilen noktanin polygonun icerisinde olup olmadigini belirler
 */
int isInside(double *point) { 
	/*x noktanin x, y noktanin y koordinati olsun*/
	/*polygonun i. kenari (points[i][0],points[i][1])
	 * (points[i+1][0],points[i+1][1]) noktalariyla tanimlidir.
	 *
	 * Ayrica son kenar
	 * (points[0][0],points[0][1])
	 * (points[np-1][0],points[np-1][1]) noktalariyla tanimlidir. */

	/*TODO: (x, y) noktasindan yukari dogru cizilen dogrunun,
	 *  kac tane kenari kestigini (kesenSayisi) bulmak icin bir dongu olusturun
	 * bu dongu tum kenarlari kapsamali*/
	int cutnumber=0;
	double ykesisim;
	double x1,x2,y1,y2;
	for(int z=0; z<np;z++) {
		 
		if(z == np-1){
			x1=points[0][0];
			x2=points[np-1][0];
			y1=points[0][1];
			y2=points[np-1][1];
		 }
		 else{
			x1=points[z][0];
			x2=points[z+1][0];
			y1=points[z][1];
			y2=points[z+1][1];
		 
		 if((point[0] > x1) && (point[0] > x2))
				continue;
		 
		 if((point[0] < x1) &&  (point[0] < x2))
				continue;
		 
		 if((point[1] > y1) && (point[1] > y2)) 
				continue;
			
		 else{
			ykesisim = m[z]*point[0] + b[z];
			if(ykesisim > point[1])
				cutnumber++;
			}
		}
	}	   
	if(cutnumber%2 == 1){
		 return 1;
	}else 
		 return 0;
}
	/*bu dongunun icerisinde*/

		/*TODO:eger noktanin x koordinati,
		 * i.kenarin her iki x koordinatinin da sagina dusuyorsa,
		 * bir sey yapmadan diger kenara gecin */

		/*TODO: eger noktanin x koordinati,
		 * i.kenarin her iki x koordinatinin da soluna dusuyorsa,
		 * diger kenara gecin */

		/*TODO: eger noktanin y koordinati,
		 * i.kenarin her iki y koordinatinin da uzerinde ise,
			 * diger kenara gecin */

		/*Yukaridaki durumlardan hic birisi degilse*/
		/*TODO kenar icin */

/*TODO: noktadan cizilen dogrunun kenari hangi y noktasinda kestigini bulun
		  ykesisim = m[i]xnokta + b[i] */

    	/*TODO: eger ykesisim, ynokta dan buyukse ise
    	 * o zaman bu kenar bu noktadan cizilen dogruyu kesmektedir.
	     * kesenSayisini bir artirin*/

	/*TODO: donguden sonra
	 * eger kesen sayisi tek ise return 1, diger durumlarda return 0*/

	


/**
 * en: generates N random point and estimates the area of polygon
 * tr: generateRandomPoint fonksiyonunu kullanarak,
 * rastgele N nokta olusturur, isInside fonksiyonu ile
 * rastgele N noktadan kac tanesinin iceri dustugunu bulur ve alani hesaplar
 */
double findArea(double width, double height){
	/*TODO: bir tane rastgele noktayi tutmak icin iki elemanli bir dizi olusturun*/
	/*TODO: generateRandomPoint fonksiyonunu bu dizi ve width ve height arguman degerleriyle
	 * cagirarak bir tane rastgele nokta elde edin*/ 
	/*TODO: isInside() fonksiyonunu bu nokta ile cagirarak bu noktanin icerde olup olmadigini belirleyin*/
	/*TODO: eger nokta icerideyse, icerdeki noktalarin sayisini bir artirin*/

	/*TODO: yukarida yapilanlari N defa tekrar ettirin*/

	/*TODO height X width ve
	 * toplam  nokta sayisi ile iceri dusenlerin oranini kullanarak alani hesaplayip return edin*/
	int inpoint=0;
	double keep[2]={0};    
	for( int k=0; k<N; k++) {
		
		generateRandomPoint(keep,width,height);
		if(isInside(keep)==1){ 
			inpoint++;
		}
		 
	}
	double alan=((double)inpoint/N)*height*width; /* alan bulma */
	 
	return alan;
}



/**
 * frees allocated memory
 */
int resetAll(){
	free(m);
	free(b);
	np = 0;
	return np;
}


