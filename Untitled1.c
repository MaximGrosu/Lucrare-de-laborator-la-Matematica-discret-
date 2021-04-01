//Lucrare de laborator Nr4.
 //           Tema:Drum minim (Alg. Ford si Belman-Kalaba).
#include <stdio.h>
#include <conio.h>
#include <malloc.h>
#define MAX 30000
//===================================================================
		 /* Declararea structurilor si variabilelor globale */
struct List{
	int v;
	int w;
	struct List *next;
		};
struct Graph{
	int h;
	int p;
	struct List *first;
	struct List *last;
		}*G;
int N,V;
//-------------------------------------------------------------------
						/* Initializarea functiilor */
void F();
void BK();
void Menu();
void Prezt();
void ListAd();
void ElebList();
void DrumFord(int);
//-------------------------------------------------------------------
							 /* Corpul principal */
void main()
{ Prezt();
  Menu();
}
//-------------------------------------------------------------------
					 /* Algoritmul drum minim Ford */
void F()
{ int i,f=1;
  struct List *c;

  if(G==NULL) return;
  for(i=0;i<N;i++)
  { G[i].p=-1;
	 G[i].h=MAX;
  }
  printf("\n\t");
   printf("Dati virful initial: ");
  scanf("%d",&V);

  G[--V].h=0;
  while(f)
  { f=0;
	 for(i=0;i<N;i++)
	 { c=G[i].first;
		while(c!=G[i].last)
		{ if(G[c->v].h>G[i].h+c->w)
		  { G[c->v].h=G[i].h+c->w;
			 G[c->v].p=i;
			 f=1;
		  }
		  c=c->next;
		}
	 }
  }
  for(i=0;i<N;i++)
  {  printf("\n\r  Drum min din %d in %d este",V+1,i+1);
	 if(G[i].h==MAX) { printf(" nu exista.");}
	  else
	  { DrumFord(i);
		  printf(" : Are lungimea %d.\r",G[i].h);

	  }
  }
}
//-------------------------------------------------------------------
			  /* Algoritmul drum minim Belman-Kalaba */
void BK()
{ int *t,i,j,k,f=1;
  struct List *c;
  int *P=(int *)malloc(N*sizeof(int ));
  int *VK=(int *)malloc(N*sizeof(int ));
  int **M=(int **)malloc(N*sizeof(int *));
  int *VK_1=(int *)malloc(N*sizeof(int ));

  for(i=0;i<N;i++) M[i]=(int *)malloc(N*sizeof(int));
  for(i=0;i<N;i++)
	for(j=0;j<N;j++) M[i][j]=(i==j)?0:MAX;
  for(i=0;i<N;i++)
  { c=G[i].first;
	 while(c!=G[i].last)
	 { M[i][c->v]=c->w;
		c=c->next;
	 }
  }
  printf("\n\t");
   printf("Dati virful final: ");
  scanf("%d",&V);

  V--;
  for(i=0;i<N;i++)
  { VK_1[i]=M[i][V];
	 P[i]=-1;
  }
  while(f)
  { for(i=0;i<N;i++) VK[i]=MAX;
	 for(i=0;i<N;i++)
	  for(j=0;j<N;j++)
		if(i!=j && VK[i]>VK_1[j]+M[i][j])
		{ VK[i]=VK_1[j]+M[i][j];
		  P[i]=j;
		}
	 VK[V]=0;
	 for(i=0;i<N && VK[i]==VK_1[i];i++);
	 f=(i==N)?0:1;
	 t=VK_1; VK_1=VK; VK=t;
  }
  for(i=0;i<N;i++)
  {  printf("\n  Drumul min din %d in %d este",i+1,V+1);
	 if(VK_1[i]==MAX) { printf(" nu exista.");}
	  else
	  { for(k=i,j=0;j<N && P[k]!=-1 && k!=V;j++)
		 { if(!j) printf(": %d",k+1);
			 else printf("->%d",k+1);
			k=P[k];
		 }
		 if(k==V || i<N-1) printf("->A%d",V+1);
		  else printf(":A %d",V+1);
		 printf(" : Are lungimea: %d.\r",VK_1[i]);

	  }
  }
  for(i=0;i<N;i++) free(M[i]);
  free(P); free(M); free(VK); free(VK_1);
}
//-------------------------------------------------------------------
							/* Meniul principal */
void Menu()
{ int m;
   printf("\nBLIN!");

  printf("\n\
		ษอออออออออออออออออออออออออออออออออออออออออป\n\
		บ               [ MENIU ]                 บ\n\
		ฬอออออออออออออออออออออออออออออออออออออออออ%c\n\
		บ [1] - Introducerea grafului:  ( LstAd ).บ\n\
		บ                                         บ\n\
		บ [2] - Drum minim:          (Alg. Ford ).บ\n\
		บ                                         บ\n\
		บ [3] - Drum minim:   (Alg.Belman-Kalaba).บ\n\
		บ                                         บ\n\
		บ Esc - Iesirea.                          บ\n\
		ศอออออออออออออออออออออออออออออออออออออออออผ\n",185);
  do m=getch();
	while((m<49 || m>51) && m!=27);

  switch(m) {
	case 49: ListAd();      break;
	case 50: F(); getch();  break;
	case 51: BK(); getch(); break;
	case 27: ElebList();   return;
  }
  Menu();
}
//-------------------------------------------------------------------
							/* Prezentarea temei */
void Prezt()
{

  printf("\n\n\n\n\t\t");
  printf("Lucrare de laborator Nr4 la Matematica Discreta.");
  printf("\r\n\n\t\t\t\t");
  printf("Drum minim.");

  getch();
}
//-------------------------------------------------------------------
			/* Lista de adiacenta si matricea ponderilor*/
void ListAd()
{ int i,v,w;
  struct List *c;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								  /* LstAd */

  if(G) ElebList();
  printf("\n\t");
   printf("Dati nr de virfuri a grafului : ");
  scanf("%d",&N);
  G=(struct Graph *)malloc(N*sizeof(struct Graph));
  printf("\n\t");
   printf("Introduceti lista de adiacenta: \n\n\r");
  for(i=0;i<N;i++)
  { printf("%d|",i+1);

	 G[i].first=(struct List*)malloc(sizeof(struct List));
	 G[i].last=G[i].first;
	 G[i].last->next=NULL;
	 G[i].last->v=-1;
	 scanf("%d",&v);;
	 if(N<v || v<0)
	 {
		printf("\n\n\n\n\n\t\t\t");

		printf("Eroare!");

		getch();
		Menu();
	 }
	 while(v)
	 {	G[i].last->v=v-1;
		G[i].last->next=(struct List*)malloc(sizeof(struct List));
		G[i].last=G[i].last->next;
		G[i].last->next=NULL;
		G[i].last->v=-1;
		scanf("%d",&v);
		if(N<v || v<0)
		{
		  printf("\n\n\n\n\n\t\t\t");

		  printf("Eroare!");

		  getch();
		  Menu();
		}
	 }
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
								  /* MatPnd */

  printf("\n\t");
 printf("Introduceti ponderea pentru fiecare arc:\n\n\r");
  for(i=0;i<N;i++)
  { G[i].last=G[i].first;
	 while(G[i].last->v+1)
	 { printf("  u%d%d| ",i+1,G[i].last->v+1);

		scanf("%d",&w);
		G[i].last->w=w;
		G[i].last=G[i].last->next;
	 }
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
}
//-------------------------------------------------------------------
							/* Eleberarea listei */
void ElebList()
{ struct List *c,*t;
  while(N--)
  { c=G[N].first;
	 while(c!=G[N].last)
	 {	t=c->next;
		free(c);
		c=t;
	 }
  }
  free(G);
}
//-------------------------------------------------------------------
					/* Vizualizarea drumului minim Ford */
void DrumFord(int v)
{ int k;
  if(v!=V) {k=v; DrumFord(G[v].p);}
  if(k!=v) printf(": %d",v+1);
	else {printf("->%d",v+1); k++;}
}
//===================================================================
