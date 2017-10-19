//C++ Program implementation of MAFIA - MAximal Frequent Itemsets Algorithm
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <ctype.h>
#include <math.h>
#define MAXITEM 10
#define MAXTRANSACTION 100
using namespace std;


void readItems(string I[], int& m);
void readTransactions(string D[], int& n);
void generateItemset(string I[], string X[], int m);
void generateFrequentItemset(string X[], int m, string D[], int n, string FI[], int& l, int min_sup);
void generateMaximalFrequentItemset(string FI[], int n, string MFI[], int& k);
char getLastChar(string ch);
int getIndex(string ch[], int n, string str);
void DisplayItemset(string ch[], int n);

int main()
{   string Item[MAXITEM], Database[MAXTRANSACTION];
    int M, N, L = 0, Min_Sup, K = 0;
    cout<<"Welcome to C++ implementation of MAFIA - MAximal Frequent Itemsets Algorithm";
    cout<<"\n............................................................................"; 
    readItems(Item, M);
    readTransactions(Database, N);
    int P = (int) (pow(2, M));
    string XItemset[P], FrequentItemset[P];
    generateItemset(Item, XItemset, M);
    cout<<"\n ******The Itemset X generated is: \n";
    DisplayItemset(XItemset, P);
    cout<<"Read in the threshold minimum support of Itemset X: "; cin>>Min_Sup;
    generateFrequentItemset(XItemset, M, Database, N, FrequentItemset, L, Min_Sup);
    cout<<"\n ******The Frequent Itemset X generated is: \n";
    DisplayItemset(FrequentItemset, L);
    string MaximalFrequentItemset[L];
    generateMaximalFrequentItemset(FrequentItemset, L, MaximalFrequentItemset, K);
    cout<<"\n ******The Maximal Frequent Itemset X generated is: \n";
    DisplayItemset(MaximalFrequentItemset, K);
    system("PAUSE");
    return EXIT_SUCCESS;
}

void readItems(string I[], int& m)
{
  int j;
  cout<<"\nRead in the number of distinct items: "; cin>>m;
  cout<<"Read in "<<m<<" distinct items into set I: "<<endl;
  for (j = 0; j < m; j++)
  { cout<<"Read item: "<<j+1<<" : "; cin>>I[j]; }  
}

void readTransactions(string D[], int& n)
{
  int j;
  cout<<"\nRead in the number of Transactions: "; cin>>n;
  cout<<"Read in "<<n<<" transaction into a Database D:"<<endl;
  for (j = 0; j < n; j++)
  { cout<<"Read transation: "<<j+1<<" : "; cin>>D[j]; }  
}

void generateItemset(string I[], string X[], int m)
{
  int k, l, start, end, j, p, f;
  string w, y; char ch;
  for(k = 1; k <= m; k++)
  {
        if(k ==1)
        {
             for( l = 0; l < m; l++) 
             {//ch = I[l];
             X[l] = I[l]; //strcpy(X[l], I[l]);
             }start = 0; end = m-1;
        }
        else
        {
            for(j = start; j <= end; j++)
            {
                  w = X[j];
                  if(w.length() > 1) y = getLastChar(w);
                  else
                      y = w;
                  p = getIndex(I, m, y);
                  for(f = p+1; f < m; f++) X[l++] = w + I[f];
            }//end for j 
            start = end + 1; end = l - 1;
        }//end else
  }//end for k
}

void generateFrequentItemset(string X[], int m, string D[], int n, string FI[], int& k, int min_sup)
{
  int l, noOfFreq, i, j;
  int p = (int)pow(2, m);
  string itemI, itemJ, itemsetI[m], itemsetT[p];
  for(i = 0; i < p; i++)
  {
        noOfFreq = 0; itemI = X[i];
        for(j = 0; j < n; j++)
        {
              itemJ = D[j];
              for(l = 0; l < itemJ.length(); l++)
                    itemsetI[l] = itemJ[l];
              generateItemset(itemsetI, itemsetT, itemJ.length());
              for(l = 0; l < (int)pow(2, itemJ.length()); l++)
              {   //cout<<itemsetT[l]<<"   ";
                  if(itemI == itemsetT[l]) 
                    {   noOfFreq += 1; break; }
              }//end for l
        } //end for j         
        if(noOfFreq >= min_sup)
            FI[k++] = itemI;
  }//end for i         
}

void generateMaximalFrequentItemset(string FI[], int n, string MFI[], int& k)
{
  int l, noOfFreq, i, j;
  string itemI, itemJ, itemsetI[n]; 
  for(i = n-1; i >= 0; i--)
  {
        noOfFreq = 0; itemI = FI[i]; 
        for(j = n-1; j >= i+1; j--)
        {
              itemJ = FI[j];
              if(itemJ.length() == itemI.length())break;
              if(itemJ.length() > itemI.length())
              {
                   for(l = 0; l < itemJ.length(); l++)
                         itemsetI[l] = itemJ[l];
                      int p = (int)pow(2, l);   
                      string itemsetT[p];
                   generateItemset(itemsetI, itemsetT, itemJ.length());
                   for(l = 0; l < (int)pow(2, itemJ.length()); l++)
                   {   
                       if(itemI == itemsetT[l]) 
                         {   noOfFreq += 1; break; }
                   }//end for l
              }//end if
              if(noOfFreq > 0)break;
        } //end for j         
        if(noOfFreq == 0)
            MFI[k++] = itemI; 
  }//end for i         
}

char getLastChar(string ch)
{
     return  ch[ch.length()-1];
}

int getIndex(string ch[], int n, string str)
{
    int i;
    for(i = 0; i < n; i++)
    {
     if(str == ch[i]) return i;
    }     
}

void DisplayItemset(string ch[], int n)
{
    int i;
    for(i = 0; i < n; i++)
    {
     cout<<ch[i]<<", ";
    }
    cout<<"\n";
}
