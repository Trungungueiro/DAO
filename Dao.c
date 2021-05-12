/**********************************************************************************
*	        Jogo DAO (C/C++);										              *	
*			Ailton Lopes;              											  *
*		    Eladio Jr.;                                                           *                                          
*			baseado em C: The Complete Reference, 4th Ed. by Herbert Schildt  	  *
*           ISBN: 0072121246, McGraw-Hill Osborne Media; 4 edition (2000)         *                                                             *
*		                                                                          *
*                                                                                 *
**********************************************************************************/

#include <stdio.h>   
#include <stdlib.h>  
#include <time.h>
 

#define N 4

short int tabul[N][N];   
int tipo_jogo(void);
void numeros(int n);
void linha(int n, int d);
void le_estado(void);
void inicia_tabul(void);
void mostra_tabul(void);
void jogada(int n, int jog, int tipo);
void jogada_Humano(int jog);
void jogada_PC(int jog, int n);
int fim_jogo(int n);
int avalia_tabul(int jog);
//void finaliza(int ti, int jog, char venc);
int dentro(int i, int j);
int validar_jogada(int xi, int yi, int xf, int yf );
int movimento_valido(int xi, int yi, int xf, int yf, int jog);
void executa_movimento(int xi, int yi, int xf, int yf, int jog);
void le_estado(int jog); 

int main(void)
{
  int fim, n, i, j, jog, tipo, ti, aux;
  char venc;

  printf("Jogo DAO - MIEEIC Humano vs PC\n");
  tipo = tipo_jogo();
  fim = -1; n = 0; jog = 0;
  printf("Para iniciar novo jogo introduza 1 \nPara iniciar um jogo gravado introduza 2\n");
  scanf("%d", &aux);
  if (aux==1)  inicia_tabul(); 
  else le_estado(jog);
  
        char jog1[60],jog2[60]; 
        
        fflush(stdin);  
         printf("           JOGO DAO\n");
         printf("           ==== ===\n\n\n\n");
         printf(" NOME DO JOGADOR 1: "); gets(jog1); 
         printf(" NOME DO JOGADOR 2: "); gets(jog2);
         printf("===============================================================\n");
         printf("JOGADOR 1: %s = \"X\"\n", jog1);
         printf("JOGADOR 2: %s = \"O\"\n", jog2);
         printf("===============================================================\n");
         printf("PRESSIONE \"ENTER\" PARA CONTINUAR..."); getchar();
         system("cls"); //Limpa a tela
  
 
  do {
     if (jog==1) jog = 2; else jog = 1;   
     printf("Jogada No: %d   Jogador1: %s   Jogador2: %s  - Av: %d\n", n, jog1, jog2, avalia_tabul(jog));
    mostra_tabul(); 
	clock_t start, end; 
    double cpu_time_used; 
   start = clock();                  
    jogada(n, jog, tipo);             
    fim = fim_jogo(n);
	end = clock(); 
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; 
    printf("Duracao do jogo: %lf s\n", cpu_time_used);  
  } while(fim==-1);   

  //finaliza(tipo,jog,fim);
  if (venc==1 && ti<3  || venc==2 && (ti==1 || ti==3)) 
    printf("Humano (Jogador: %s) Venceu!!!\n", jog1,jog2);
   else printf("A Maquina (Jogador: %s) Venceu!!!\n", jog1,jog2);
   mostra_tabul();
  
  system("PAUSE");
  return 0;
}

// Fun��o para imprimir os numeros assima da matriz 
void numeros(int n) {
  printf("  "); 
  for(int i=1; i<=n; i++)
      printf("%2d  ",i);   
} 
// Fun��o para fazer uma linha 
 void linha(int n, int d) {
   for(int i=0; i<n; i++) {
      printf("%c%c%c",45,45,45);  
      if(i!=n-1) printf("%c",d );   
   }    
} 

void le_estado(int jog)
{
FILE *ficheiro; 	
	if ((ficheiro = fopen("estado.txt","r"))==NULL){
	 	printf ("impossivel ler o ficheiro \n" ); return; }
	for (int i=0;i<N;i++)
	    	for (int j=0;j<N;j++) 
	     		fscanf(ficheiro,"%d", &tabul[i][j]);
   fscanf(ficheiro,"%d", &jog);
    fclose(ficheiro);	
}

void atualiza_estado(int jog)
{
FILE *ficheiro; 	
	if ((ficheiro = fopen("estado.txt","w"))==NULL){
	 	printf ("impossivel ler o ficheiro \n" ); return; }
	for (int i=0;i<N;i++)
	    	for (int j=0;j<N;j++) 
   			   fprintf(ficheiro,"%d\n",tabul[i][j] );
   fprintf(ficheiro,"%d\n",jog);		   
    fclose(ficheiro);	
}
// Inicializa o Tabuleiro 
void inicia_tabul(void)
{
   int i, j;
  
    for(i=0; i<4; i++)
       for(j=0; j<4; j++) 
       tabul[0][0] = 1;
	   tabul[1][1] = 1;   
	   tabul[2][2] = 1;
	   tabul[3][3] = 1;  
	   tabul[0][3] = 2;
	   tabul[1][2] = 2;
	   tabul[2][1] = 2;
	   tabul[3][0] = 2; 
}                  


// Pede ao utlizador que escolha um dos 4 modos de jogo possiveis
// Modos de jogo: 1-Hum/Hum 2-Hum/PC 3-PC/Hum 4-PC/PC
int tipo_jogo(void)
{
    int ti;
   do {
      printf("Escolha um modo de jogo: \n");
    printf("1-Hum/Hum 2-Hum/PC 3-PC/Hum 4-PC/PC\n"); 
    scanf("%d",&ti); 	  
    } while  (ti>4);  
    return ti;
}


// Finaliza o jogo indicando quem venceu ou se foi empate
/*void finaliza(int ti, int jog, char venc)
{
     /*if (venc==0) printf("Empate!!!\n");
     else*/
	 /* if (venc==1 && ti<3 || venc==2 && (ti==1 || ti==3)) 
        printf("Humano (Jogador: %d) Venceu!!!\n", jog);
        else printf("A Maquina (Jogador: %d ) Venceu!!!\n", jog);
     mostra_tabul();
}*/


// Dependendo do modo de jogo e do numero da jogada
// pede uma jogada ao humano ou calcula uma jogada para o PC
void jogada(int n, int jog, int tipo)
{
     if (n % 2 == 1) {
           if (tipo<=2) jogada_Humano(jog); else jogada_PC(jog,n);
     }
     else { 
          if (tipo==1 || tipo==3) jogada_Humano(jog); else jogada_PC(jog,n);
     }
} 

// Jogada do Humano - Pede coordenadas e verifica se s�o validas
// e se a casa est� vazia. Nesse caso coloca l� a pe�a respectiva
 void jogada_Humano(int jog)
{
    char  xi[20], yi[20];  
   char xf[20], yf[20];
   int i,j,k,l;
    do {
       	 printf("Posicao actual:\n ");
         scanf("%s%*c%s",  xi, yi); 
	
    	  printf("Mover peca para a posicao:\n ");
         scanf("%s%*c%s", xf, yf);
  i= atoi(xi);j= atoi(yi); k=atoi(xf); l=atoi(yf);        
          if(movimento_valido(i-1,j-1,k-1,l-1,jog)!=0) 
          {   switch (movimento_valido(i-1,j-1,k-1,l-1,jog)){
              case 1: printf(" Coordenadas iniciais invalidas,tente novamente.\n\n "); break;
              case 2: printf(" Coordenadas finais invalidas,tente novamente.\n\n"); break;
              case 3: printf(" Coordenada inicial vazia,tente novamente.\n\n  "); break;
              case 4: printf(" Peca escolhida invalida,tente novamente.\n\n"); break;
              case 5: printf(" Posicao final oucupada,tente novamente.\n\n "); break;
              case 6: printf(" Movimento invalido, nao pode salta uma peca,tente novamente.\n\n"); break;
              case 7: printf(" Movimento na direcao invalida,tente novamente.\n\n  "); break;
              case 8: printf(" Jogada invalida so e possivel movimentar-se para ultima posicao vazia.\n\n  "); break;
              }
          }
    } while  (movimento_valido(i-1,j-1,k-1,l-1,jog)!=0);  
    executa_movimento(i-1,j-1,k-1,l-1,jog); 
 
}  
int dentro(int x, int y)
{
    if(x<0 || x>N-1 || y<0 || y>N-1) return -1;
    return 0;   
} 
int validar_jogada (int xi, int yi, int xf, int yf)
{
   if( (xi>xf && yi>yf && xi-yi!=xf-yf) || (xi<xf && yi<yf && xi-yi!=xf-yf) || (xi>xf && yi<yf && xi+yi!=xf+yf) ||
   (xi<xf && yi>yf && xi+yi!=xf+yf))return -2;  
 
      else  if(xi==xf && yi<yf){
            for(int i=yi+1;i<yf;i++)
                if(tabul[xi][i]!=0) return -1;
                if (yf!=N-1 && tabul[xf][yf+1]==0) return -3;
      }                                    
      else if (xi==xf && yi>yf ){
           for(int i=yi-1;i>yf;i--)
                if(tabul[xi][i]!=0)return -1;
            if (yf!=0 && tabul[xf][yf-1]==0) return -3;
      }  
      else if (xi<xf && yi==yf){
           for(int i=xi+1;i<xf;i++)
                   if(tabul[i][yf]!=0)return -1;
            if (xf!=N-1 && tabul[xf+1][yf]==0) return -3;         
      }
      else if (xi>xf && yi==yf){
           for(int i=xf+1;i<xi;i++)
                  if(tabul[i][yf]!=0)return -1;
           if (xf!=0 && tabul[xf-1][yf]==0) return -3;    
      } 
      else if (xi>xf && yi>yf ){
           for(int i=xf+1,j=yf+1;i<xi,j<yi;i++,j++)
                   if(tabul[i][j]!=0)return -1;
           if (xf!=0 && yf!=0 && tabul[xf-1][yf-1]==0) return -3;                         
      } 
      else if (xi<xf && yi<yf ){
           for(int i=xi+1,j=yi+1;i<xf,j<yf;i++,j++)
                if(tabul[i][j]!=0)return -1;
      if (xf!=N-1 && yf!=N-1 && tabul[xf+1][yf+1]==0) return -3;
      }                         
      else if (xi>xf && yi<yf ){
           for(int i=xf+1,j=yi+1;i<xi,j<yf;i++,j++)
                if(tabul[i][j]!=0)return -1; 
           if (xf!=0 && yf!=N-1 && tabul[xf-1][yf+1]==0) return -3;
      } 
      else if (xi<xf && yi>yf ){
           for(int i=xi+1,j=yf+1;i<xf,j<yi;i++,j++)
               if(tabul[i][j]!=0)return -1;
           if (yf!=0 && xf!=N-1 && tabul[xf+1][yf-1]==0) return -3;
      }         
   return 0;  
}

int movimento_valido(int xi, int yi, int xf, int yf, int jog)
{
  	if (dentro(xi,yi)==-1)return 1; 
       else if (dentro(xf,yf)==-1)return 2; 
       else if (tabul[xi][yi]==0)return 3;
       else if (tabul[xi][yi]!=jog)return 4;
       else if (tabul[xf][yf]!=0 )return 5;
       else if (validar_jogada(xi,yi,xf,yf)==-1)return 6;
       else if (validar_jogada(xi,yi,xf,yf)==-2)return 7;
       else if (validar_jogada(xi,yi,xf,yf)==-3)return 8;
    return 0;        
}
 
void executa_movimento(int xi, int yi, int xf, int yf, int jog)
{
      tabul[xi][yi] = 0; 
      tabul[xf][yf] = jog;
      atualiza_estado(jog);
  }
 
   void jogada_PC(int jog, int n)
{
int i, j,k,l,bi, bj,bk, bl, av, maxav=-1000;

for(i=0; i<4; i++){     //para todas as posicoes da matriz 
  for(j=0; j<4; j++) {   //
    if (tabul[i][j]==jog){// se encontramos uma peca do jogador 
      for(k=0; k<4; k++) //vamos procurar novamente para todas as posicoes da matriz 
        for(l=0; l<4; l++) {
          if (tabul[k][l] == 0 && movimento_valido(i,j,k,l,jog)==0) {// uma posicao vazia onde a jogada � valida 
             tabul[i][j]=0; 	//executa a jogada
             tabul[k][l]=jog;	//executa a jogada
              av = avalia_tabul(jog);
              if (av>maxav) { maxav = av;  bi = i; bj = j, bk=k, bl=l; }// avalia o tabuleiro se av for maior que o anterior guarda as posicoes em bi,bj,bk,bl
              tabul[i][j]=jog;	 //desfaz jogada
              tabul[k][l]=0;    //desfaz jogada
          }
        }
      } 
    }
}   
  executa_movimento(bi,bj,bk,bl,jog); 
  return;
} 

 char conv(short int peca)
{
   if (peca==1) return 'X';    
   else if (peca==2) return 'O';    
   else return ' ';    
}  

void mostra_tabul(void){
    numeros(N);
    printf("\n %c",201); linha(N,203); printf("%c\n",187);
    for(int i=0; i<N; i++) {
         printf("%c",i+65);    
         for(int j=0; j<N; j++)
              printf("%c %c ", 186, conv (tabul[i][j]));  
         printf("%c%c\n ",186,i+65);
         if (i<N-1) {printf("%c",204), linha(N, 206); printf("%c\n", 185);}
    }
    printf("%c",200), linha(N, 202); printf("%c\n", 188);
    numeros(N);
    printf("\n\n");
}
 
  
 
int fim_jogo(int n)
{
  int i,j; 
 for(i=0; i<N; i++){
    if(tabul[i][0]==tabul[i][1] && tabul[i][0]==tabul[i][2] && tabul[i][2]==tabul[i][3] && tabul[i][0]!=0) 
       return tabul[i][0];
 }
  for(i=0; i<N; i++){
if(tabul[0][i]==tabul[1][i] && tabul[0][i]==tabul[2][i] && tabul[2][i]==tabul[3][i] && tabul[0][i]!=0) 
         return tabul[0][i];  
 }      
if(tabul[0][0]==tabul[0][3] && tabul[0][3]==tabul[3][0] && tabul[3][0]==tabul[3][3] && tabul[0][0]!=0) 
         return tabul[0][0];
   
  for(i=0; i<N-1; i++) { 
      for (j=0;j<N-1; j++)       
if(tabul[i][j]==tabul[i][j+1] && tabul[i][j+1]==tabul[i+1][j] && tabul[i+1][j]==tabul[i+1][j+1] && tabul[i][j]!=0)
         return tabul[i][j];  
  }
                                           
if(tabul[0][0]!=0 && tabul[0][1]== tabul[1][0] && tabul[1][0]== tabul[1][1] && tabul[0][0]!= tabul[0][1] && tabul[0][1]!=0)
         return tabul[0][1]; 
         
if(tabul[0][3]!=0 && tabul[0][2]== tabul[1][2] && tabul[1][2]== tabul[1][3] && tabul[0][3]!= tabul[1][3] && tabul[1][3]!=0)
         return tabul[1][3];  
            	   
if(tabul[3][0]!=0 && tabul[2][0]== tabul[2][1] && tabul[2][1]== tabul[3][1] && tabul[3][0]!= tabul[3][1] && tabul[3][1]!=0)
         return tabul[3][1];  
                  
if(tabul[3][3]!=0 && tabul[2][2]== tabul[2][3] && tabul[2][3]== tabul[3][2] && tabul[3][3]!= tabul[3][2] && tabul[3][2]!=0)
         return tabul[3][2];           
                                                                            
    return -1;      
  }                                                                    

int avalia(int jog)
{
    int i,j;
    int av = 0;
    if (fim_jogo(0) == jog) av+=1000; 
   
   
    
   for (i=0; i<3; i++) { //quadrado
         for (j=0; j<3; j++) 
      if (tabul[i][j]==jog &&(tabul[i][j+1]==jog || tabul[i+1][j]==jog || tabul[i+1][j+1]==jog)) av+=5;  
      if (tabul[i][j]==jog ||(tabul[i][j+1]==jog && tabul[i+1][j]==jog || tabul[i+1][j+1]==jog)) av+=5;
      if (tabul[i][j]==jog ||(tabul[i][j+1]==jog || tabul[i+1][j]==jog && tabul[i+1][j+1]==jog)) av+=5;
   } 
          
     if(tabul[0][1]== jog || tabul[1][0]==jog || tabul[1][1]==jog && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=5;      
     if(tabul[0][1]== jog || tabul[1][0]==jog && tabul[1][1]==jog && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=10;  
     if(tabul[0][1]== jog && tabul[1][0]==jog || tabul[1][1]==jog && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=10; 
    
     if(tabul[0][2]== jog || tabul[1][2]==jog || tabul[1][3]==jog && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=5;     
     if(tabul[0][2]== jog && tabul[1][2]==jog || tabul[1][3]==jog && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=10;
     if(tabul[0][2]== jog || tabul[1][2]==jog && tabul[1][3]==jog && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=10;
   
     if(tabul[2][0]== jog || tabul[2][1]==jog || tabul[3][1]==jog && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=5;     
     if(tabul[2][0]== jog && tabul[2][1]==jog || tabul[3][1]==jog && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=10;
     if(tabul[2][0]== jog || tabul[2][1]==jog && tabul[3][1]==jog && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=10;
     
     if(tabul[2][2]== jog || tabul[2][3]==jog || tabul[3][2]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=5; 
     if(tabul[2][2]== jog && tabul[2][3]==jog || tabul[3][2]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=10;
     if(tabul[2][2]== jog || tabul[2][3]==jog && tabul[3][2]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=10;
       
     for (i=0; i<4; i++) { //col
       if(tabul[i][0]==jog && (tabul[i][1]==jog || tabul[i][2]==jog || tabul[i][3]==jog)) av+=5;
       if(tabul[i][0]==jog || (tabul[i][1]==jog && tabul[i][2]==jog || tabul[i][3]==jog)) av+=5;
       if(tabul[i][0]==jog || (tabul[i][1]==jog || tabul[i][2]==jog && tabul[i][3]==jog)) av+=5;    
       }
    for (i=0; i<4; i++) {//lin
       if(tabul[0][i]==jog && (tabul[1][i]==jog || tabul[2][i]==jog || tabul[i][2]==jog)) av+=5;
       if(tabul[0][i]==jog || (tabul[1][i]==jog && tabul[2][i]==jog || tabul[i][2]==jog)) av+=5;
       if(tabul[0][i]==jog || (tabul[1][i]==jog || tabul[2][i]==jog && tabul[i][2]==jog)) av+=5;       
    }
    //cantos
    if(tabul[0][0]==jog && tabul[0][3]==jog || tabul[3][0]==jog || tabul[3][3]==jog)av+=5;
    if(tabul[0][0]==jog || tabul[0][3]==jog || tabul[3][0]==jog && tabul[3][3]==jog)av+=5; 
    if(tabul[0][0]==jog || tabul[0][3]==jog && tabul[3][0]==jog || tabul[3][3]==jog)av+=5;  
    
    
  for (i=0; i<3; i++) { 
         for (j=0; j<3; j++) 
      if (tabul[i][j]==jog &&(tabul[i][j+1]==jog && tabul[i+1][j]==jog || tabul[i+1][j+1]==jog)) av+=10;  
      if (tabul[i][j]==jog ||(tabul[i][j+1]==jog && tabul[i+1][j]==jog && tabul[i+1][j+1]==jog)) av+=10;
      if (tabul[i][j]==jog &&(tabul[i][j+1]==jog || tabul[i+1][j]==jog && tabul[i+1][j+1]==jog)) av+=10;
   }   
   for (i=0; i<3; i++) { 
         for (j=0; j<3; j++) 
           if (tabul[i][j]!=jog && (tabul[i][j+1]==jog && tabul[i+1][j]==jog || tabul[i+1][j]==jog)&& tabul[0][1]==jog+1||tabul[0][1]==jog+1) av+=10;  
           if (tabul[i][j]!=jog || (tabul[i][j+1]==jog && tabul[i+1][j]==jog && tabul[i+1][j]==jog)&& tabul[0][1]==jog+1||tabul[0][1]==jog+1) av+=10;  
           if (tabul[i][j]!=jog && (tabul[i][j+1]==jog || tabul[i+1][j]==jog && tabul[i+1][j]==jog)&& tabul[0][1]==jog+1||tabul[0][1]==jog+1) av+=10;  
      }  
     
     for (i=0; i<4; i++) { 
       if(tabul[i][0]==jog && (tabul[i][1]==jog && tabul[i][2]==jog || tabul[i][3]==jog)) av+=10;
       if(tabul[i][0]==jog || (tabul[i][1]==jog && tabul[i][2]==jog && tabul[i][3]==jog)) av+=10;
       if(tabul[i][0]==jog && (tabul[i][1]==jog || tabul[i][2]==jog && tabul[i][3]==jog)) av+=10;    
       }
    for (i=0; i<4; i++) {
       if(tabul[0][i]==jog && (tabul[1][i]==jog && tabul[2][i]==jog || tabul[i][2]==jog)) av+=10;
       if(tabul[0][i]==jog || (tabul[1][i]==jog && tabul[2][i]==jog && tabul[i][2]==jog)) av+=10;
       if(tabul[0][i]==jog && (tabul[1][i]==jog || tabul[2][i]==jog && tabul[i][2]==jog)) av+=10;       
    }   

       if(tabul[0][0]==jog && tabul[0][3]==jog && tabul[3][0]==jog || tabul[3][3]==jog)av+=10;  
       if(tabul[0][0]==jog || tabul[0][3]==jog && tabul[3][0]==jog && tabul[3][3]==jog)av+=10;  
       if(tabul[0][0]==jog && tabul[0][3]==jog && tabul[3][0]==jog && tabul[3][3]==jog)av+=10;  

    for (i=0; i<4; i++) {//lin
       if(tabul[0][i]==jog || (tabul[1][i]==jog && tabul[2][i]==jog && tabul[i][2]==jog+1||tabul[i][2]==jog-1)) av-=10;
       if(tabul[0][i]==jog+1 || tabul[0][i]==jog-1 && (tabul[1][i]==jog || tabul[2][i]==jog && tabul[i][2]==jog)) av-=10;
       if(tabul[0][i]==jog || (tabul[1][i]==jog && tabul[2][i]==jog+1 ||tabul[2][i]==jog-1 && tabul[i][2]==jog)) av-=10;       
    }
        // cantos 
       if(tabul[0][0]==jog || tabul[0][3]==jog && tabul[3][0]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av-=10;  
       if(tabul[0][0]==jog && tabul[0][3]==jog && tabul[3][0]==jog+1 ||tabul[3][0]==jog-1 || tabul[3][3]==jog)av-=10;  
       if(tabul[0][0]==jog+1 ||tabul[0][0]==jog-1  && tabul[0][3]==jog && tabul[3][0]==jog && tabul[3][3]==jog)av-=10;
       
    for (i=0; i<4; i++) { //col
       if(tabul[i][0]==jog && (tabul[i][1]==jog+1 ||tabul[i][1]==jog-1 && tabul[i][2]==jog && tabul[i][3]==jog)) av-=10;
       if(tabul[i][0]==jog+1 || tabul[i][0]==jog-1 && (tabul[i][1]==jog && tabul[i][2]==jog && tabul[i][3]==jog)) av-=10;
       if(tabul[i][0]==jog && (tabul[i][1]==jog && tabul[i][2]==jog+1 ||tabul[i][2]==jog-1 && tabul[i][3]==jog)) av-=10;  
    }
    
    for (i=0; i<3; i++) { //quadrado
         for (j=0; j<3; j++) 
            if (tabul[i][j]==jog &&(tabul[i][j+1]==jog+1 ||tabul[i][j+1]==jog-1 && tabul[i+1][j]==jog && tabul[i+1][j+1]==jog)) av+=-10;  
            if (tabul[i][j]==jog &&(tabul[i][j+1]==jog && tabul[i+1][j]==jog+1 ||tabul[i+1][j]==jog-1 && tabul[i+1][j+1]==jog)) av+=-10;
            if (tabul[i][j]==jog+1 ||tabul[i][j]==jog-1 && (tabul[i][j+1]==jog && tabul[i+1][j]==jog && tabul[i+1][j+1]==jog)) av+=- 10;
   }    
           
     if(tabul[0][1]== jog || tabul[1][0]==jog && tabul[1][1]== tabul[0][0] && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=-10;  
     if(tabul[0][1]== jog || tabul[1][1]==jog && tabul[1][0]== tabul[0][0] && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=-10; 
     if(tabul[0][1]== tabul[0][0] && tabul[1][0]== jog || tabul[1][1]==jog && tabul[0][0]==jog-1 ||tabul[0][0]==jog+1)av+=-10;  
    
     if(tabul[0][2]== tabul[0][3] && tabul[1][2]== jog || tabul[1][3]==jog && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=-10;
     if(tabul[0][2]== jog || tabul[1][3]==jog && tabul[1][2]== tabul[0][3] && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=-10;
     if(tabul[0][2]== jog || tabul[1][2]==jog && tabul[1][3]== tabul[0][3] && tabul[0][3]==jog+1 || tabul[0][3]==jog-1)av+=-10;
   
     if(tabul[2][0]== tabul[3][1] && tabul[2][1]==jog && tabul[3][1]==jog && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=-10;
     if(tabul[2][0]== jog && tabul[2][1]==jog && tabul[3][1]==tabul[3][1] && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=-10;
     if(tabul[2][0]== jog && tabul[2][1]==tabul[3][1] && tabul[3][1]==jog && tabul[3][1]==jog+1 || tabul[3][1]== jog-1)av+=-10;
     
     if(tabul[2][2]== tabul[3][3] && tabul[2][3]==jog && tabul[3][2]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=-10;
     if(tabul[2][2]== jog && tabul[2][3]==tabul[3][3] && tabul[3][2]==jog && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=-10;
     if(tabul[2][2]== jog && tabul[2][3]==jog && tabul[3][2]==tabul[3][3] && tabul[3][3]==jog+1 || tabul[3][3]==jog-1)av+=-10;    
      
     return av;    
}

int avalia_tabul(int jog)
{
    int a1, a2;
    a1 = avalia(1);
    a2 = avalia(2);
    if (jog==1) return 2*a1-3*a2; else return 2*a2-3*a1;  
}


