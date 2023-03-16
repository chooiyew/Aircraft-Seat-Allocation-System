#include <stdio.h>
#include <string.h>

int lgtNR,lgtR,lgtT,i,j,k;
int seat[32][7];
float dist_X[31]={10.19,9.33,8.46,7.60,6.73,5.87,5.01,4.14,3.28,2.42,1.55,0.00,0.00,-1.55,-2.42,-3.28,-4.14,-5.01,-5.87,-6.73,-7.60,-8.46,-9.33,-10.19,-11.05,-11.92,-12.78,-13.64,-14.51,-15.37,-16.23};
float dist_Y[6]={-1.30,-0.93,-0.37,0.37,0.93,1.30};

int calWeight(int age[],char gender[][10],float weight[])					//function to calculate the weight of passengers
{
	if(age[i]<5)
		{
			weight[i]=15.00;
		}else if(age[i]>=5&&age[i]<=20)
		{
			weight[i]=0.0612*age[i]*age[i] + 1.4512*age[i] + 5.0362;
		}else if(age[i]>=21&&age[i]<=25)
		{
			if(*gender[i]=='M'){
				weight[i]=58.00;
			}else if(*gender[i]=='F'){
				weight[i]=53.00;
			}
		}else if(age[i]>=26&&age[i]<=30)
		{
			if(*gender[i]=='M'){
				weight[i]=65.00;
			}else if(*gender[i]=='F'){
				weight[i]=54.00;
			}
		}else if(age[i]>=31&&age[i]<=60)
		{
			if(*gender[i]=='M'){
				weight[i]=70.00;
			}else if(*gender[i]=='F'){
				weight[i]=58.00;
			}
		}else if(age[i]>=61)
		{
			if(*gender[i]=='M'){
				weight[i]=65.00;
			}else if(*gender[i]=='F'){
				weight[i]=55.00;
			}
		}
}

void WeightDescending(char name[][100], char IC[][100], int age[],char gender[][10],float weight[])					//function to sort the weight in descending order
{
	char DmName[100];
	char DmIC[100];
	char DmGen[10];
	char Dmcolumn[3];
	int Dmrow;
	int DmAge;
	int i, j;
	float DmWeight;
	for(i=lgtR; i<lgtT-1;i++)
	{
		for(j=lgtR;j<lgtT-1;j++)
		{
			if(weight[j]<weight[j+1])
			{
				strcpy(DmName, name[j]);
				strcpy(DmIC,IC[j]);
				strcpy(DmGen,gender[j]);
				DmAge=age[j];
				DmWeight=weight[j];
				
				
				strcpy(name[j], name[j+1]);
				strcpy(IC[j],IC[j+1]);
				strcpy(gender[j],gender[j+1]);
				age[j]=age[j+1];
				weight[j]=weight[j+1];
			
				strcpy(name[j+1], DmName);
				strcpy(IC[j+1],DmIC);
				strcpy(gender[j+1],DmGen);
				age[j+1]=DmAge;	
				weight[j+1]=DmWeight;
			}		
		}		
	}
}

void SeatAscending(char name[][100], char IC[][100], int age[], char gender[][10], char seat_column[][3],int seat_row[],float weight[])					//sort alphabatical order of the seat_row
{
	char DmName[100];					
	char DmIC[100];
	char DmGen[10];
	char Dmcolumn[10];
	int DmAge;
	int Dmrow;
	float Dmweight;
	for(i=0; i<lgtT-1;i++)
	{
		for(j=0;j<lgtT-1-i;j++)
		{
			if(seat_row[j]>seat_row[j+1])
			{	
				strcpy(DmName, name[j]);
				strcpy(DmIC,IC[j]);
				strcpy(DmGen,gender[j]);
				strcpy(Dmcolumn,seat_column[j]);
				DmAge=age[j];
				Dmrow=seat_row[j];
				Dmweight=weight[j];
				
				strcpy(name[j], name[j+1]);
				strcpy(IC[j],IC[j+1]);
				strcpy(gender[j],gender[j+1]);
				strcpy(seat_column[j],seat_column[j+1]);
				age[j]=age[j+1];
				seat_row[j]=seat_row[j+1];
				weight[j]=weight[j+1];
				
				strcpy(name[j+1], DmName);
				strcpy(IC[j+1],DmIC);
				strcpy(gender[j+1],DmGen);
				strcpy(seat_column[j+1],Dmcolumn);
				age[j+1]=DmAge;	
				seat_row[j+1]=Dmrow;
				weight[j+1]=Dmweight;
			}		
		}		
	}
}

void main()					//main function
{
	char bin[100];
	
	FILE *f1=fopen("NoReserve.dat","r");					//open NoReserve.dat 
	FILE *f2=fopen("WithReserve.dat","r");					//open WithReserve.dat
	
	fscanf(f1,"%s%d",bin,&lgtNR);					//start reading NoReserve.dat
	fscanf(f2,"%s%d",bin,&lgtR);					//start reading WithReserve.dat
	
	lgtT=lgtNR+lgtR;
	
	char name[lgtT][100];					//define all variables
	char gender[lgtT][10];
	char IC[lgtT][100];
	char seat_column[lgtT][3];
	char M , F;
	int birthyear[lgtT] , age[lgtT] , seat_row[lgtT] , num;
	float weight[lgtT];

	for(i=1;i<8;i++)					//start reading WithReserve.dat
	{
		fscanf(f2,"%s",bin);
	}
	for(i=0;i<lgtR;i++)
	{
		fscanf(f2,"%d%s%s%s%d%d%s",&num,name[i],gender[i],IC[i],&birthyear[i],&seat_row[i],seat_column[i]);
		age[i]=2020-birthyear[i];
		calWeight(age,gender,weight);
	}
	fclose(f2);					//close WithReserve.dat
	
	char c;					//To assign availability of seat
	for(i=0;i<lgtR;i++)
	{
		for(j=0;j<31;j++)
		{
			for(c='A';c<='F';c++)
			{
				if(seat_row[i]==j && seat_column[i][0]==c)
				seat[j][((int)c-64)]=1;
			}
		}
	}
	
	float premoment_X=0, Sum_X[lgtR];					//calculate moment in X direction
	for(i=0;i<lgtR;i++)
	{					
			for(j=0;j<32;j++)
			{
				if(seat_row[i]==j+1)
				Sum_X[i]=weight[i]*dist_X[j];
			}
			premoment_X+=Sum_X[i];
	}
	
	float premoment_Y=0, Sum_Y[lgtR];					//Calculate moment in Y direction
	for(i=0;i<lgtR;i++)
	{					
			for(j=65;j<=70;j++)
			{
				if((int)seat_column[i][0]==j)
				Sum_Y[i]=weight[i]*dist_Y[j-65];
			}
			premoment_Y+=Sum_Y[i];
	}
	
	for(i=1;i<6;i++)					//start reading No.Reserve.dat
	{
		fscanf(f1,"%s",bin);
	}
	for(i=lgtR;i<lgtT;i++)
	{
		fscanf(f1,"%d%s%s%s%d",&num,name[i],gender[i],IC[i],&birthyear[i]);
		age[i]=2020-birthyear[i];
		calWeight(age,gender,weight);
	}
	fclose(f1);					//close NoReserve.dat
	
	WeightDescending(name,IC,age,gender,weight);					//function to sort the weight in descending order
	
	int SRow=31,SCol=4,TCol=4,TRow=1,CRow=1,CCol=3,ARow=31,ACol=3;					//to assign no reserve to available seats
	char ABCDEF[6]={'A','B','C','D','E','F'};
	int empty12=0;					//check how many seat empty at row12 where dist_X=0.00
	j=0,k=1;
	for(i=1;i<7;i++){
		if(seat[12][i]==0)
			empty12+=1;
	}
	for(i=lgtR;i<lgtR+empty12;i++)					//assign heaviest passengers on empty seats on Row12
	{ 
		if(seat[12][k]==0)
		{
			seat_row[i]=12;
			seat_column[i][0]=ABCDEF[j];
			seat[12][k]=2;
			j+=1,k+=1;
		}else j+=1,k+=1,i-=1;
	}
	for(i=lgtR+empty12;i<lgtT;i++)				//assign passengers to remaining seats
	{
		if(premoment_X>0&&premoment_Y<0)
		{
			if(seat[SRow][SCol]==0&&SRow!=13)
			{
				seat_row[i]=SRow;
				seat_column[i][0]=ABCDEF[SCol-1];
				seat[SRow][SCol]=2;
				premoment_X+=weight[i]*dist_X[SRow-1];
				premoment_Y+=weight[i]*dist_Y[SCol-1];
				SCol+=1;
				if(SCol>6)
				{
					SRow-=1;
					SCol=4;
				}
			}else {
				SCol+=1;
				i-=1;
				if(SCol>6)
				{
					SRow-=1;
					SCol=4;
				}
			}
		}else if(premoment_X<0&&premoment_Y<0)
		{
			if(seat[TRow][TCol]==0&&TRow!=13)
			{
				seat_row[i]=TRow;
				seat_column[i][0]=ABCDEF[TCol-1];
				seat[TRow][TCol]=2;
				premoment_X+=weight[i]*dist_X[TRow-1];
				premoment_Y+=weight[i]*dist_Y[TCol-1];
				TCol+=1;
				if(TCol>6){
					TRow+=1;
					TCol=4;
				}
			}else {
				TCol+=1;
				i-=1;
				if(TCol>6){
					TRow+=1;
					TCol=4;
				}
			}
		}else if(premoment_X<0&&premoment_Y>0)
		{
			if(seat[CRow][CCol]==0&&CRow!=13)
			{
				seat_row[i]=CRow;
				seat_column[i][0]=ABCDEF[CCol-1];
				seat[CRow][CCol]=2;
				premoment_X+=weight[i]*dist_X[CRow-1];
				premoment_Y+=weight[i]*dist_Y[CCol-1];
				CCol-=1;
				if(CCol<1){
					CRow+=1;
					CCol=3;
				}
			}else
			{	
				CCol-=1;
				i-=1;
				if(CCol<1){
					CRow+=1;
					CCol=3;
				}
			}
		}else if(premoment_X>0&&premoment_Y>0)
		{
			if(seat[ARow][ACol]==0&&ARow!=13)
			{
				seat_row[i]=ARow;
				seat_column[i][0]=ABCDEF[ACol-1];
				seat[ARow][ACol]=2;
				premoment_X+=weight[i]*dist_X[ARow-1];
				premoment_Y+=weight[i]*dist_Y[ACol-1];
				ACol-=1;
				if(ACol<1){
					ARow-=1;
					ACol=3;
				}
			}else
			{	
				ACol-=1;
				i-=1;
				if(ACol<1){
						ARow-=1;
						ACol=3;
					}
			}
		}
	}
	
	SeatAscending(name,IC,age,gender,seat_column,seat_row,weight);					//Function to sort seat ascending order
	
	for(i=0;i<lgtT;i++)					//to print all the data in sequence(Name,Gender,Ic,Age,Weight)
	{
		printf("%d\t%s\t%s\t%s\t%d\t%5.2fkg\t%d%s\n",i+1,name[i],gender[i],IC[i],age[i],weight[i],seat_row[i],seat_column[i]);
	}
	
	FILE *f3=fopen("PassengerList.csv","w");					//create and write a new csv file for passenger list
	fprintf(f3,"X-Moment:,%5.2f,kg-m\nY-Moment:,%5.2f,kg-m\n",premoment_X,premoment_Y);
	fprintf(f3,"No,Name,IC,Age,Gender,Seat Row,Seat Column\n");
	for(i=0;i<lgtT;i++)					//to write all the data in sequence
	{
		fprintf(f3,"%d,%s,%s,%d,%s,%d,%s\n",i+1,name[i],IC[i],age[i],gender[i],seat_row[i],seat_column[i]);
	}
}
