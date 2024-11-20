#include<iostream>
#include <stdio.h>
#include <string.h>
using namespace std;

void szyfruj(int klucz, char tab[])
{
 int dl = strlen(tab); 
	

 if(!(klucz >= -26 && klucz <= 26)) return;
	
 if(klucz >= 0)
  for(int i=0;i<dl;i++)
  if(tab[i] + klucz+i <= 'Z')
   tab[i] += klucz+i;
  else
   tab[i] = tab[i] + klucz+i - 26; 
 else
  for(int i=0;i<dl;i++)
  if(tab[i] + klucz-i >= 'A')
   tab[i] += klucz-i;
  else
   tab[i] = tab[i] + klucz-i+ 26;
}

int main()
{
 char tab[1001];
	
 int klucz;
	
 cin>>tab;
	
 cin>>klucz;
	
 szyfruj(klucz,tab); //szyfrowanie
	
 cout<<"Po zaszyfrowaniu: "<<tab<<endl;
	
 szyfruj(-klucz,tab); //deszyfrowanie
	
 cout<<"Po rozszyfrowaniu: "<<tab<<endl;

 return 0;
}
