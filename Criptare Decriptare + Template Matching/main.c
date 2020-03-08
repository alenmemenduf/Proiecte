#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct fereastra{
double cor;
unsigned int x;
unsigned int y;
unsigned int latime;
unsigned int inaltime;
unsigned int Arie;
unsigned char *Culoare;
};


void grayscale_image(char* nume_fisier_sursa,char* nume_fisier_destinatie)
{
   FILE *fin, *fout;
   unsigned int dim_img, latime_img, inaltime_img;
   unsigned char pRGB[3], header[54], aux;

   fin = fopen(nume_fisier_sursa, "rb");
   if(fin == NULL)
   	{
   		return;
   	}
   fout = fopen(nume_fisier_destinatie, "wb+");

   fseek(fin, 2, SEEK_SET);
   fread(&dim_img, sizeof(unsigned int), 1, fin);

   fseek(fin, 18, SEEK_SET);
   fread(&latime_img, sizeof(unsigned int), 1, fin);
   fread(&inaltime_img, sizeof(unsigned int), 1, fin);

   //copiaza octet cu octet imaginea initiala in cea noua
	fseek(fin,0,SEEK_SET);
	unsigned char c;
	while(fread(&c,1,1,fin)==1)
	{
		fwrite(&c,1,1,fout);
		fflush(fout);
	}
	fclose(fin);

	//calculam padding-ul pentru o linie
	int padding;
    if(latime_img % 4 != 0)
        padding = 4 - (3 * latime_img) % 4;
    else
        padding = 0;


	fseek(fout, 54, SEEK_SET);
	int i,j;
	for(i = 0; i < inaltime_img; i++)
	{
		for(j = 0; j < latime_img; j++)
		{
			//citesc culorile pixelului
			fread(pRGB, 3, 1, fout);
			//fac conversia in pixel gri
			aux = 0.299*pRGB[2] + 0.587*pRGB[1] + 0.114*pRGB[0];
			pRGB[0] = pRGB[1] = pRGB[2] = aux;
        	fseek(fout, -3, SEEK_CUR);
        	fwrite(pRGB, 3, 1, fout);
        	fflush(fout);
		}
		fseek(fout,padding,SEEK_CUR);
	}
	fclose(fout);
}


/// /// /// /// /// /// /// ///


//<--------CRIPTOGRAFIE-------->//


/// /// /// /// /// /// /// ///


void XORSHIFT(unsigned int R[],unsigned int seed,unsigned int inaltime,unsigned int latime)
{
    int i;
    unsigned int x = seed;
    for(i=1;i<2*inaltime*latime;i++)
    {
    x = x^x<<13;
    x = x^x>>17;
    x = x^x<<5;
    R[i]=x;
    }
}

unsigned int* to_Line(char *sursa) // LINIARIZAZE DE JOS IN SUS
{
    FILE *fin = fopen(sursa,"rb");
    unsigned int latime,inaltime;

    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);
    fseek(fin,54,SEEK_SET);

	int padding;
    if(latime % 4 != 0)
        padding = 4 - (3 * latime) % 4;
    else
        padding = 0;

unsigned int *liniarizare = malloc((3*latime+padding)*inaltime*sizeof(unsigned int));

for(int i=inaltime-1;i>=0;i--)
{
    for(int j=0;j<latime;j++)
    {
        fread(&liniarizare[i*latime+j],1,3,fin);
    }
    fseek(fin,padding,SEEK_CUR);
}
fclose(fin);
return liniarizare;
}

unsigned int* to_LineSusJos(char *sursa) // LINIARIZEAZA DE SUS IN JOS
{
    FILE *fin = fopen(sursa,"rb");
    unsigned int latime,inaltime;

    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);
    fseek(fin,54,SEEK_SET);

	int padding;
    if(latime % 4 != 0)
        padding = 4 - (3 * latime) % 4;
    else
        padding = 0;

unsigned int *liniarizare = malloc((3*latime+padding)*inaltime*sizeof(unsigned int));

for(int i=0;i<inaltime;i++)
{
    for(int j=0;j<latime;j++)
    {
        fread(&liniarizare[i*latime+j],1,3,fin);
    }
    fseek(fin,padding,SEEK_CUR);
}
fclose(fin);
return liniarizare;
}

void from_Line(char *sursa,char *destinatie,unsigned int *liniarizare) //SCRIE IN FISIERUL DESTINATIE DIN LINIARIZAREA FISIERULUI SURSA
{
    FILE *fin = fopen(sursa,"rb");
    FILE *fout = fopen(destinatie,"wb");
    unsigned int latime,inaltime;
    unsigned char x;
    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);
    fseek(fin,0,SEEK_SET);
    fseek(fout,0,SEEK_SET);
    for(int i=0;i<54;i++)
    {
        fread(&x,1,1,fin);
        fwrite(&x,1,1,fout);
        fflush(fout);
    }

	int padding;
    if(latime % 4 != 0)
        padding = 4 - (3 * latime) % 4;
    else
        padding = 0;

for(int i=inaltime-1;i>=0;i--)
{
    for(int j=0;j<latime;j++)
    {
        fwrite(&liniarizare[i*latime+j],1,3,fout);
        fflush(fout);
    }
    fseek(fout,padding,SEEK_CUR);
}

char c=0;
fseek(fout,-padding,SEEK_CUR);
fwrite(&c,padding,1,fout);

fclose(fin);
fclose(fout);
}

void Permutare(unsigned int R[],unsigned int P[],unsigned int inaltime,unsigned int latime)
{
 unsigned int r;
 unsigned int aux;

 for(unsigned int k =inaltime*latime-1;k>=1;k--)
 {
     r = R[k]%(inaltime*latime-k+1);
     aux = P[r];
     P[r]=P[inaltime*latime-k];
     P[inaltime*latime-k]=aux;
 }
}

void Permutare_inversa(unsigned int R[],unsigned int P[],unsigned int inaltime,unsigned int latime)
{
 unsigned int r;
 unsigned int aux;

 for(unsigned int k =1;k<inaltime*latime;k++)
 {
     r = R[k]%(inaltime*latime-k+1);
     aux = P[inaltime*latime-k];
     P[inaltime*latime-k]=P[r];
     P[r]=aux;
 }
}

void Criptare(char *sursa,char *destinatie,char *cheie)
{
    FILE *fin = fopen(sursa,"rb");
    FILE *fout = fopen(destinatie,"wb");
    FILE *fcheie = fopen(cheie,"r");
    int i;
    unsigned char c;
    unsigned int dimensiune,latime,inaltime,SV;
    unsigned int *C,*R,*liniarizare;


    fseek(fin,2,SEEK_SET);
    fread(&dimensiune,sizeof(unsigned int),1,fin);
    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);
    fseek(fin,0,SEEK_SET);

	int padding;
    if(latime % 4 != 0)
        padding = 4 - (3 * latime) % 4;
    else
        padding = 0;

    R = malloc(2*inaltime*latime*(4+padding));
    C = malloc(inaltime*latime*sizeof(unsigned int));
    liniarizare = to_Line(sursa);

    fscanf(fcheie,"%u%u",&R[0],&SV);

    XORSHIFT(R,R[0],inaltime,latime);
    Permutare(R,liniarizare,inaltime,latime);


        C[0] =SV^liniarizare[0]^R[latime*inaltime];
        for(int k=1;k<latime*inaltime;k++)
        {
            C[k] = C[k-1]^liniarizare[k]^R[latime*inaltime+k];
        }
from_Line(sursa,destinatie,C);

fclose(fin); fclose(fout); fclose(fcheie);
free(R); free(C); free(liniarizare);
}

void Decriptare(char *initiala,char *criptata,char *cheie)
{
    FILE *fin = fopen(criptata,"rb");
    FILE *fout = fopen("decriptata.bmp","wb");
    FILE *fcheie = fopen(cheie,"r");
    int i;
    unsigned char c;
    unsigned int latime,inaltime,SV;
    unsigned int *C,*R;
    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);

    fseek(fin,0,SEEK_SET);

    int padding;
    if(latime % 4 != 0) padding = 4 - (3 * latime) % 4;
    else padding = 0;

    R = malloc(2*inaltime*latime*(4+padding));
    C = malloc(inaltime*latime*sizeof(unsigned int));
    C = to_Line(criptata);
    fscanf(fcheie,"%u",&R[0]);
    fscanf(fcheie,"%u",&SV);

    XORSHIFT(R,R[0],inaltime,latime);

    for(int k=latime*inaltime-1;k>=1;k--)
    {
        C[k] = C[k-1]^C[k]^R[latime*inaltime+k];
    }
    C[0] = SV^C[0]^R[latime*inaltime];

Permutare_inversa(R,C,inaltime,latime);

from_Line(criptata,"decriptata.bmp",C);

fclose(fin);
fclose(fout);
fclose(fcheie);

free(R);
free(C);

}

void chipatrat(char* sursa) // CALCULEAZA VALORILE TESTULUI CHIPATRAT DIN FISIERUL "sursa"
{
FILE *fin = fopen(sursa,"rb");
    unsigned int latime,inaltime,padding;

    fseek(fin,18,SEEK_SET);
    fread(&latime,sizeof(unsigned int),1,fin);
    fread(&inaltime,sizeof(unsigned int),1,fin);
    fseek(fin,54,SEEK_SET);

    if(latime % 4 != 0) padding = 4 - (3 * latime) % 4;
    else padding = 0;

    float fbara = latime*inaltime/256;

    unsigned int **f = malloc(256*sizeof(unsigned int*));
    for(int i=0;i<256;i++)
    {
        f[i] = malloc(3*sizeof(unsigned int));
        f[i][0] = f[i][1] = f[i][2] = 0;
    }


    unsigned char x;

    for(int i=0;i<inaltime;i++)
    {
        for(int j=0;j<latime;j++)
        {

            fread(&x,1,1,fin);
            f[x][2]++;
            fread(&x,1,1,fin);
            f[x][1]++;
            fread(&x,1,1,fin);
            f[x][0]++;

        }
        fseek(fin,padding,SEEK_CUR);
    }
    float chib=0,chig=0,chir=0,b,g,r;
    for(int k=0;k<256;k++)
    {
        b = f[k][2]-fbara;
        b *= b;
        b /= fbara;
        chib = chib + b;


        g = f[k][1]-fbara;
        g *= g;
        g /= fbara;
        chig = chig + g;


        r = f[k][0]-fbara;
        r *= r;
        r /= fbara;
        chir = chir + r;
    }
    printf("R:%f\nG:%f\nB:%f\n",chir,chig,chib);

for(int i=0;i<256;i++)
    free(f[i]);
free(f);
fclose(fin);
}


/// /// /// /// /// /// /// ///


//<------TEMPLATE MATCHING------>//


/// /// /// /// /// /// /// ///

double MedieSablon(char* sablon)        //S-bara din formula de corelatie
{
    unsigned int x;
    unsigned int LatimeSablon,InaltimeSablon;
    double medie=0;
    FILE *fsablon = fopen (sablon,"rb");
    fseek(fsablon,18,SEEK_SET);
    fread(&LatimeSablon,sizeof(unsigned int),1,fsablon);
    fread(&InaltimeSablon,sizeof(unsigned int),1,fsablon);
    fseek(fsablon,54,SEEK_SET);


    unsigned int n = InaltimeSablon * LatimeSablon;
    for(int i=0;i<n;i++)
    {
        fread(&x,1,3,fsablon);
        medie += (unsigned char)x;
    }
    return (medie/(n));
    fclose(fsablon);
}

double MedieFimagine(unsigned int LatimeImagine,unsigned int Imagine_liniarizata[],unsigned int x,unsigned int y,unsigned int latimeSablon,unsigned int inaltimeSablon) // F-bara din formula de corelatie
{
    double medie=0;

    int n = latimeSablon * inaltimeSablon; //11*15 = 165;
    for(int i=0;i<inaltimeSablon;i++)
        for(int j=0;j<latimeSablon;j++)
            medie +=(unsigned char)Imagine_liniarizata[(x+i)*LatimeImagine+(y+j)];


    return medie/n;
}

double deviatieSablon(char* sablon)
{


    double ds=0,SBara;
    unsigned int n,LatimeSablon,InaltimeSablon,*Sablon_liniarizat;

    FILE *fsablon = fopen (sablon,"rb");
    fseek(fsablon,18,SEEK_SET);
    fread(&LatimeSablon,sizeof(unsigned int),1,fsablon);
    fread(&InaltimeSablon,sizeof(unsigned int),1,fsablon);

    SBara = MedieSablon(sablon);

n = LatimeSablon * InaltimeSablon;
Sablon_liniarizat = to_LineSusJos(sablon);
    for(int i=0;i<InaltimeSablon;i++)
        for(int j=0;j<LatimeSablon;j++)
            ds += pow(((unsigned char)Sablon_liniarizat[i*LatimeSablon+j] - SBara) , 2);

    free(Sablon_liniarizat);
    fclose(fsablon);
    return sqrt(ds/(n-1));
}

double deviatieFimagine(unsigned int Latime,unsigned int Imagine_liniarizata[],unsigned int x,unsigned int y,unsigned int LatimeSablon,unsigned int InaltimeSablon)
{


    double df=0,FBara;
    unsigned int n;

    FBara = MedieFimagine(Latime,Imagine_liniarizata,x,y,LatimeSablon,InaltimeSablon);
n = LatimeSablon * InaltimeSablon;

    for(int i=0;i<InaltimeSablon;i++)
        for(int j=0;j<LatimeSablon;j++)
            df += pow(((unsigned char)Imagine_liniarizata[(x+i)*Latime+(y+j)]-FBara),2);

    return sqrt(df/(n-1));
}


struct fereastra *Corelatie(char* imagine,char* sablon,double ps,unsigned int *nrferestre) // CALCULEAZA CORELATIA DINTRE FERESTRE SI SABLONUL ACTUAL
{                                                                                           // ps este pragul
    FILE *fimagine = fopen(imagine,"rb");
    FILE *fsablon = fopen (sablon,"rb");

    unsigned char x;
    unsigned int Latime,Inaltime,LatimeSablon,InaltimeSablon;
    unsigned int *Imagine_liniarizata,*Sablon_liniarizat;

    fseek(fimagine,18,SEEK_SET);
    fread(&Latime,sizeof(unsigned int),1,fimagine);
    fread(&Inaltime,sizeof(unsigned int),1,fimagine);
    fseek(fimagine,0,SEEK_SET);

    fseek(fsablon,18,SEEK_SET);
    fread(&LatimeSablon,sizeof(unsigned int),1,fsablon);
    fread(&InaltimeSablon,sizeof(unsigned int),1,fsablon);
    fseek(fsablon,0,SEEK_SET);

    //struct fereastra *f = malloc(sizeof(struct fereastra)*(Inaltime-InaltimeSablon)*(Latime-LatimeSablon));
    struct fereastra *f = malloc(sizeof(struct fereastra));
    Imagine_liniarizata = to_LineSusJos(imagine);
    Sablon_liniarizat = to_LineSusJos(sablon);
    unsigned int k,l,n;
    double corr=0,Sbara,Fbara,ds,df; // corr = corelatie ; intensitate medie sablon ; intensitate Fimagine ; deviatie sablon ; deviatie Fimagine

    n = LatimeSablon * InaltimeSablon;
    Sbara = MedieSablon(sablon);
    ds = deviatieSablon(sablon);

    int i,j;
    for(i=0;i<Inaltime;i++)
    {
        for(j=0;j<Latime-LatimeSablon;j++)
        {
            Fbara = MedieFimagine(Latime,Imagine_liniarizata,i,j,LatimeSablon,InaltimeSablon);
            df = deviatieFimagine(Latime,Imagine_liniarizata,i,j,LatimeSablon,InaltimeSablon);

            for(k=0;k<InaltimeSablon;k++)
            {
                for(l=0;l<LatimeSablon;l++)
                {
                    corr += ((((unsigned char)Imagine_liniarizata[(i+k)*Latime+(j+l)] - Fbara) * ((unsigned char)Sablon_liniarizat[k*LatimeSablon+l] - Sbara)) / (ds*df));
                }
            }

            corr = abs(corr);
            corr /= n;
            if(corr >= ps)
                {
                    f[*nrferestre].x = i;
                    f[*nrferestre].y = j;
                    f[*nrferestre].latime = LatimeSablon;
                    f[*nrferestre].inaltime = InaltimeSablon;
                    f[*nrferestre].cor = corr;

                    f = realloc(f,(*nrferestre+2)*sizeof(struct fereastra));
                    *nrferestre = *nrferestre + 1;
                }
            corr = 0;
        }

    }
    free(Imagine_liniarizata); free(Sablon_liniarizat);
    fclose(fimagine); fclose(fsablon);
    return f;
}

void Colorare(char *imagine,struct fereastra f,unsigned char Culoare[]) //COLOREAZA "imaginea" la coordonatele lui "f" cu cei 3 octeti din "Culoare";
{
    unsigned char c;
    unsigned int Latime,Inaltime;
    FILE *fimagine = fopen(imagine,"rb+");

    fseek(fimagine,18,SEEK_SET);
    fread(&Latime,sizeof(unsigned int),1,fimagine);
    fread(&Inaltime,sizeof(unsigned int),1,fimagine);
    fseek(fimagine,54,SEEK_SET);


    unsigned int padding;
    unsigned int InaltimeFereastra = f.inaltime;
    unsigned int LatimeFereastra = f.latime;
    unsigned int k = f.x;
    unsigned int l = f.y;

    if(Latime % 4 != 0)
        padding = 4 - (3 * Latime) % 4;
    else
        padding = 0;
fseek(fimagine,3*(k*Latime+l),SEEK_CUR);
for(int i=0;i<InaltimeFereastra;i++)
    {
        for(int j=0;j<LatimeFereastra;j++)
            {
                if(i==0 || i==InaltimeFereastra-1)
                {
                    fwrite(&Culoare[0],1,1,fimagine);
                    fflush(fimagine);
                    fwrite(&Culoare[1],1,1,fimagine);
                    fflush(fimagine);
                    fwrite(&Culoare[2],1,1,fimagine);
                    fflush(fimagine);
                }
                else if(j==0 || j==LatimeFereastra-1)
                {
                    fwrite(&Culoare[0],1,1,fimagine);
                    fflush(fimagine);
                    fwrite(&Culoare[1],1,1,fimagine);
                    fflush(fimagine);
                    fwrite(&Culoare[2],1,1,fimagine);
                    fflush(fimagine);
                }
                else fseek(fimagine,3,SEEK_CUR);

            }
        fseek(fimagine,3*(Latime-LatimeFereastra),SEEK_CUR);
    }

    fclose(fimagine);
}

int comparatie(struct fereastra *a,struct fereastra *b) // COMPARATOR PT QSORT // AJUTA LA SORTAREA VECTORULUI DE FERESTRE IN ORDINEA CORELATIEI
{
    if((*a).cor < (*b).cor) return 1;
    if((*a).cor == (*b).cor) return 0;
    if((*a).cor > (*b).cor) return -1;
}

float suprapunere(struct fereastra a,struct fereastra b) //SUPRAPUNEREA ARIILOR
{
    int latime_intersectat,inaltime_intersectat;
    float ab_intersectat,ab_reunit;
    if(a.x < b.x)
        latime_intersectat = a.x + a.latime - b.x;
    else
        latime_intersectat = b.x + b.latime - a.x;

    if (a.y < b.y)
        inaltime_intersectat = a.y + a.inaltime - b.y;
    else
        inaltime_intersectat = b.y + b.inaltime - a.y;

    if((latime_intersectat > 0 && latime_intersectat <= 11)
        &&(inaltime_intersectat > 0 && inaltime_intersectat <= 15))
        {
            ab_intersectat = latime_intersectat * inaltime_intersectat;
            ab_reunit = 2 * a.inaltime * a.latime - ab_intersectat;
            if(ab_intersectat / ab_reunit >= 0.2 && ab_intersectat / ab_reunit <= 1)
                return 1;
        }
    return 0;
}

void Eliminarea_nonMaximelor(struct fereastra D[],unsigned int nrTotalFerestre) // Eliminarea nonmaximelor ce foloseste ca parametrii
{
    for(int i=0;i<nrTotalFerestre;i++)                                           //numarul ferestrelor precum si vectorul ordonat D
        D[i].Arie = 165;
    for(int i=0;i<nrTotalFerestre-1;i++)
        for(int j=i+1;j<nrTotalFerestre;j++)
            if(suprapunere(D[i],D[j])==1)
                D[j].Arie = 0;
}

int main()
{
    char poza_initiala[] = "test.bmp"; // POZA INITIALA CU TOATE NUMERELE
	char poza_criptata[] = "test_crypted.bmp"; // POZA DUPA CRIPTARE /////// DECRIPTAREA CREEAZA UN FISIER BMP SEPARAT "decriptata.bmp"
    char cheie[] = "secret_key.txt";
    char poza_grayscale[] = "test_grayscale.bmp";
    char *sablon = malloc(100*sizeof(unsigned char));
    printf("CRIPTARE!\n");

    Criptare(poza_initiala,poza_criptata,cheie);//
    printf("\n");                                   //
    Decriptare(poza_initiala,poza_criptata,cheie);//            CRIPTARE + DECRIPTARE + CHI_TEST ///DECRIPTAREA SALVEAZA IN "decriptata.bmp"
    chipatrat(poza_initiala);                       //
    printf("\n");                                   //
    chipatrat(poza_criptata);                        //
    printf("\n\n\n");

    printf("TEMPLATE MATCHING\n");

    grayscale_image(poza_initiala,poza_grayscale); // POZA INITIALA => GRAYSCALE

    unsigned int nrsabloane = 10;
    printf("Numar de sabloane:10\n"); //CITIREA NUMARULUI DE SABLOANE

    float prag = 0.50;



    unsigned int *nrferestre;
    unsigned int p,nrFerestreTotal=0;
    nrferestre = &p;


    unsigned char Culoare[3];
    struct fereastra *f,*D;
    D = malloc(sizeof(struct fereastra));

//////////////////////////
char **v = malloc(10*sizeof(char*));
for(int i=0;i<10;i++)                   //VECTORUL V PENTRU CITIREA SIRURILOR INAINTEA EXECUTARII PROGRAMULUI (cifraX.bmp)
    v[i] = malloc(100*sizeof(char));
/*
for(int i=0;i<nrsabloane;i++)
{
    printf("Sablonul nr %u:\n\n",i+1);
    scanf("%s",v[i]);
}
*/
for (int i = 0; i < nrsabloane; i++)
{
    char x[] = "0";
    x[0] += i;
    char str[20] = "cifra";
    strcat(str, x);
    strcat(str, ".bmp");
    strcpy(v[i],str);
}
for(int i=0;i<nrsabloane;i++)
{
printf("sablonul %u\n",i);
        strcpy(sablon,v[i]);
        grayscale_image(sablon,"sablon_grayscale.bmp"); //ia cifraX.bmp si copiaza bitii grayscale in sablon_grayscale.bmp

        p=0;
        f = Corelatie(poza_grayscale,"sablon_grayscale.bmp",prag,nrferestre); //Corelatie intre cifraX.bmp(grayscale) si Imaginea initiala(grayscale)
        D = realloc(D,sizeof(struct fereastra)*(nrFerestreTotal+p+2));


        if(strcmp(sablon,"cifra0.bmp")==0)
            {
                for(int i=0;i<p;i++){
                    f[i].Culoare = malloc(3*sizeof(unsigned char));
                    f[i].Culoare[2] = 255; f[i].Culoare[1] = 0; f[i].Culoare[0] = 0;
                }
            }

        else if(strcmp(sablon,"cifra1.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 255; f[i].Culoare[1] = 255; f[i].Culoare[0] = 0;
            }
        }

        else if(strcmp(sablon,"cifra2.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 0; f[i].Culoare[1] = 255; f[i].Culoare[0] = 0;
            }
        }

        else if(strcmp(sablon,"cifra3.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 0; f[i].Culoare[1] = 255; f[i].Culoare[0] = 255;
            }
        }

        else if(strcmp(sablon,"cifra4.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 255; f[i].Culoare[1] = 0; f[i].Culoare[0] = 255;
            }
        }

        else if(strcmp(sablon,"cifra5.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 0; f[i].Culoare[1] = 0; f[i].Culoare[0] = 255;
            }
        }

        else if(strcmp(sablon,"cifra6.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 192; f[i].Culoare[1] = 192; f[i].Culoare[0] = 192;
            }
        }

        else if(strcmp(sablon,"cifra7.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 255; f[i].Culoare[1] = 140; f[i].Culoare[0] = 0;
            }
        }

        else if(strcmp(sablon,"cifra8.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 128; f[i].Culoare[1] = 0; f[i].Culoare[0] = 128;
            }
        }

        else if(strcmp(sablon,"cifra9.bmp")==0)
        {
            for(int i=0;i<p;i++){
                f[i].Culoare = malloc(3*sizeof(unsigned char));
                f[i].Culoare[2] = 128; f[i].Culoare[1] = 0; f[i].Culoare[0] = 0;
            }
        }

        for(int i=0;i<p;i++)
            D[nrFerestreTotal+i] = f[i];
        nrFerestreTotal += p;
}

        qsort(D,nrFerestreTotal,sizeof(D[0]),comparatie);

        Eliminarea_nonMaximelor(D,nrFerestreTotal);
        for(unsigned int i=0;i<nrFerestreTotal;i++)
            {   if(D[i].Arie!=0)
                    Colorare("test.bmp",D[i],D[i].Culoare);
                free(D[i].Culoare);
            }

/////////////////////////////////////////////////





	for(int i=0;i<10;i++)
        free(v[i]);
    free(v); free(f); free(sablon); free(D);
}
