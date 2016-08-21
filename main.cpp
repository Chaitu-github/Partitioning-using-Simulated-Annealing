#include <iostream>
#include<fstream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<math.h>
#include <algorithm>
using namespace std;

////global variables
int n;
int time1;
int initialcost;
int currentcost;
int bestcost;
int r1,r2; //random numbers generated for swapping
char *inputfilename[3];
char *outputfilename[3];



vector<vector<int> > rowindex; //for storing sparse connectivity matrix
vector<int> initialpartition; //for storing the initial partition

//function declarations
void readfile();
void initialsol();
void printsparsematrix();
int randomfun();
void SA();
void outputfile();


int main(int argc,char *argv[])
{

time1=(unsigned) time(0);

//time1= 1456160565;
srand(time1);
inputfilename[1]=argv[1];
outputfilename[1]=argv[2];
readfile();
initialsol();
currentcost=initialcost;
bestcost=initialcost;
SA();
outputfile();
}

//reading benchmark file and forming sparse connectivity matrix
void readfile()
{
  //  cout<<"reading the file"<<endl;
    //cout<<"------------"<<endl<<endl;

    int nodes;
    int edges;
    int n1,n2;
ifstream file(inputfilename[1]);
if(file.is_open())
    {
       file>>nodes>>edges;

        cout<<"no.of cells "<<nodes<<"\n"<<"no.of edges "<<edges<<endl;

     n=nodes;
     //cout<<"time "<<time1<<endl;
    rowindex.resize(n);//initializing the size of matrix

    while(file>>n1>>n2)
       {
         rowindex[n1-1].push_back(n2-1);
		 rowindex[n2-1].push_back(n1-1);
	   }
	} else cout<<"error opening the file"<<endl;
file.close();
}


//Generating initial random pattern and calculating initial cutset
void initialsol()
{
  for(int i=0;i<n/2;++i)
   {
	 initialpartition.push_back(1);
         initialpartition.push_back(0);
   }

random_shuffle(initialpartition.begin(),initialpartition.end());

int cost=0;
int SizeOfRowIndex;
int ElementInSetA;

for(int i=0;i<n;++i)
{
	SizeOfRowIndex=rowindex[i].size();
	  ElementInSetA=initialpartition.at(i);
 for(unsigned int j=0;j<SizeOfRowIndex;++j)
 {
    if( ElementInSetA!=initialpartition.at(rowindex[i][j]))
	  {
	  	++cost;
	  }
  }
}

initialcost=cost/2;
cout<<"\ninitial cost "<<initialcost<<endl;

cout<<endl;

}

//to print sparse connectivity matrix
void printsparsematrix()
{
  cout<<" printing Sparse matrix "<<endl;
    for(unsigned int i=0;i<n;++i)
     {
       unsigned int size1=rowindex[i].size();
        for(unsigned int j=0;j<size1;++j)
        {
            cout<<"row index "<<i<<"\nconnected column "<<rowindex[i][j]<<endl;
			cout<<"----------------"<<endl;
        }
    }
}


//simulated annealing function
void SA()
{
//cout<<"simulated annealing"<<endl;
     double k=1.38064852e-23;
	 double itemp=400000;
     double noOfMoves=30000;
     double ftemp=1;
     double TempDec=0.99;
     double noOfSaMoves=1;
     double MovesInc=10;
     double newcost=0;
     double exp1;
     double gain=0;


	for(int i=0;i<noOfSaMoves;++i)
	{
	  while(itemp>ftemp)
	 {
        for(int moves=0;moves<noOfMoves;++moves)
        {

          gain=randomfun();
          double r=(double)rand() / (double)RAND_MAX ;
           newcost=currentcost-(gain);
           exp1=(gain)/k*itemp;
		   //for storing the best cost
           if(newcost<bestcost)
		   {
		   	bestcost=newcost;
		   }

		   //Probabilistic condition for accepting move
          if(((gain)>0) || r<exp(exp1))
          {
             currentcost=newcost;

             swap(initialpartition.at(r1),initialpartition.at(r2)); //swapping nodes if move is accepted

		  }
        }
	 itemp*=TempDec;
	 }
	}
cout<<"final cost "<<currentcost<<endl;
  //  cout<<"seed value "<<time1<<endl;


}


//Generates two random numbers and calculates gain for swapping
int randomfun()
{
int gain=0;
int r1int=0;
int r1ext=0;
int r2int=0;
int r2ext=0;

r1= (rand()%n);
r2=(rand()%n);

while(initialpartition.at(r1)==initialpartition.at(r2))
{
	r1= (rand()%n);
    r2=(rand()%n);
}


int cr1r2=0;
int SizeOfVectorRandom=rowindex[r1].size();
int ElementInSetRandom=initialpartition.at(r1);
int ColumnIndex;
for(unsigned int i=0;i<SizeOfVectorRandom;++i)
{

	ColumnIndex=(rowindex[r1][i]);
 	if(ElementInSetRandom==initialpartition.at(ColumnIndex))
	{
		++r1int;
	}
	else ++r1ext;
}

SizeOfVectorRandom=rowindex[r2].size();
ElementInSetRandom=initialpartition.at(r2);

for(unsigned int i=0;i<SizeOfVectorRandom;++i)
{
	if(ElementInSetRandom==initialpartition.at(rowindex[r2][i]))
	{
		++r2int;
	} else ++r2ext;
}


if(r1int+r1ext<r2int+r2ext)
{
	for(unsigned int i=0;i<rowindex[r1].size();++i)
	{
		if(r2==rowindex[r1][i])
		{
          ++cr1r2;
		}
	}
}
else
{
	for(unsigned int i=0;i<rowindex[r2].size();++i)
	{
       if(r1==rowindex[r2][i])
		{
			++cr1r2;
		}
	}
}


(gain)+=r1ext;
(gain)+=r2ext;
(gain)-=r1int;
(gain)-=r2int;
(gain)-=2*cr1r2;

return gain;
}

//writing output to the file
void outputfile()
{
ofstream output(outputfilename[1]);
if(output.is_open())
{
    output<<"seed value "<<time1<<endl;
    output<<"final cut set size "<<currentcost<<endl;
    //output<<"best cut set size "<<bestcost<<endl;
   //output<<"\ntotal time taken "<<time(0)-time1<<" seconds"<<endl;

    output<<"\nNodes in set 0 "<<endl;
    for( int i=0;i<n;++i)
    {
     if(initialpartition.at(i)==0)
		{
		 output<<i+1<<' ';
		}

    }
    output<<"\nNodes in set 1 "<<endl;
    for( int i=0;i<n;++i)
    {
     if(initialpartition.at(i)!=0)
        {
          output<<i+1<<' ';
	}

    }
}
output.close();
}



