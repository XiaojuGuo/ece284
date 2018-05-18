#include <stdio.h>
#include <stdlib.h>

int getGCD(int a, int b){
  int c;
  while(a!=0){
    c=a; a=b%a; b=c;
  }
  return b;
}

void convertSplits(int L, int R,int **gcd,int **splitPositions,char *actor){
  int s,iL,iR;
  if(L==R){
    printf("%c",actor[L]);
  }
  else{
    s=splitPositions[L][R];
    iL=gcd[L][L+s]/gcd[L][R];
    iR=gcd[L+s+1][R]/gcd[L][R];
    printf("(%d",iL); convertSplits(L,L+s,gcd,splitPositions,actor);
    printf(")(%d",iR); convertSplits(L+s+1,R,gcd,splitPositions,actor);
    printf(")");
  }
}


  int main(){
    int i,j;
    int n=5;
    int produced[5]={0,3,3,4,1};
    int qG[6]={0,4,6,9,12,4};
    int **gcd;
    //char actor[6]=['Z','A','B','C','D','E'];
    int subcosts[n+1][n+1];
    int **splitPositions;
    int r,l,size,min_cost,total_cost,split,split_cost;
    gcd=(int**)malloc((n+1)*sizeof(int*));
    for(i=0;i<n+1;i++){
    	gcd[i]=(int*)malloc((n+1)*sizeof(int));
	}
    splitPositions=(int**)malloc((n+1)*sizeof(int*));
    for(i=0;i<n+1;i++){
      splitPositions[i]=(int*)malloc((n+1)*sizeof(int));
    }
    char* actor=(char*)malloc(6*sizeof(char));
    actor[1]='A'; actor[2]='B'; actor[3]='C'; actor[4]='D'; actor[5]='E';

  //compute gcd
  for(i=1;i<=n;i++){
    gcd[i][i]=qG[i];
    for(j=i+1;j<=n;j++){
      gcd[i][j]=getGCD(gcd[i][j-1],qG[j]);
    }
  } 

  //compute subcosts and splitPositions
  for(i=1;i<=n;i++)
    subcosts[i][i]=0;
  for(size=2;size<=n;size++){
    for(r=size;r<=n;r++){
      l=r-size+1;
      min_cost=32766;
      for(i=0;i<=size-2;i++){
        split_cost=(qG[l+i]/gcd[l][r])*produced[l+i];
        total_cost=split_cost+subcosts[l][l+i]+subcosts[l+i+1][r];
        if(total_cost<min_cost){
          split=i; min_cost=total_cost;
        }
      }
      subcosts[l][r]=min_cost;
      splitPositions[l][r]=split;
    }
  }
  printf("test: %d\n",splitPositions[4][4]);
  convertSplits(1,n,gcd,splitPositions,actor);
  printf("\n");

  for(i=0;i<n+1;i++){
    free(gcd[i]);
    free(splitPositions[i]);
  }
  free(gcd);free(splitPositions);free(actor);

  return 0;
}
