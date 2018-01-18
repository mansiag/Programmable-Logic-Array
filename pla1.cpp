#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<stdio.h>
#include<algorithm>
#include<cstring>
#include<set>
using namespace std;
//converts decimal to binary and stores it in a string
string to_binary(int n,int m)
{
 string a;
  for(int i=0;i<m;i++)
  {
   if(n%2==0)
  	a.push_back('0');
   else 
  	a.push_back('1');
   n=n/2;
  }
 reverse(a.begin(),a.end());
 return a;
}
//compare two binary numbers to check if their is 1 bit difference or they are alike
int compare(string a,string b)
{
int n=a.length();
int c=0,d=0,k;
  for(int i=0;i<n;i++)
   {
      if(a[i]!=b[i])
  	{
  	 c++;
  	 k=i;
  	}
      else if(a[i]==b[i])
      d++;
   }
if(c==1) return k;               //returns the position of the string where the difference is 1 bit
else if(d==n) return -2;         //returns -2 if the two binary numbers are alike
else return -1;                  //returns -1 if their is no 1 bit difference neither they are alike
} 
//change the bit to _ at the position where their is 1 bit difference
string change(string a,int l)    
{ 
 a[l]='_';
 return a;
}
//checks if a binary number is already present in vector containing prime implicants
void check_like(string a,vector<string>&b)
{
 int flag=0,n=b.size();
  for(int i=0;i<n;i++)
  {
    if(compare(a,b[i])==-2)return;
    else flag++;
  }
 if(flag==n)
 b.push_back(a);
 return;
}
//calculates the power 
/*long int pow(int base,int power)
{long int res=1;
 while(power--)
 res*=base;
 return res;
}*/
int main() 
{
 int i2,j2,k2,min,t,i;
 vector<vector<string> >f;                            //vector containing all the functions.
                                                     // Minterms of functions are stored i2 the form of their binary equivalent
 vector<vector<string> >fc;                           //vector containing complement of all the functions
 set<string>final;                                   //final set to contain the union of functions
 set<string>temp2;                                   //temporary set to contain the union of functions
 string s,result;
 vector<vector<int> >mint;                           //stores the minterms of all the functions and their complement  
 int fn,m;
 cout<<"Enter the no. of variables: ";
 cin>>m;
 if(m<=0){cout<<"Invalid Input ";return 0;}
 cout<<"Enter the no. of function: ";
 cin>>fn;
 if(fn<=0){cout<<"Invalid Input ";return 0;}
for(i2=0;i2<fn;i2++)
 {
   vector<int>temp;
   int nm;
   cout<<"Enter Function F"<<i2+1<<":\n";
   cout<<"Enter the no. of minterms: ";
   cin>>nm;
   if(nm<=0)
   {cout<<"Invalid input ";return 0;}
   cout<<"Enter the minterms between 0 to "<<pow(2,m)-1<<" ";
   for(j2=0;j2<nm;j2++)
    {
      int a;
      cin>>a;
      if(a<0 || a>pow(2,m))
       { cout<<"Invalid Input.minterm should be between 0 and "<<pow(2,m)-1;return 0;}
      temp.push_back(a);
    }
   mint.push_back(temp);
}
for(i2=0;i2<fn;i2++)
{
   int d=0;
   vector<int>temp;
	for(j2=0;j2<pow(2,m);j2++)
	{
	  if(mint[i2][d]!=j2)
		temp.push_back(j2);
	  else
	        d++;
	}
   mint.push_back(temp);
}
//This loop finds the minimized function by tabulation method
for(int i1=0;i1<(2*fn);i1++)
{
    int i,j,k,n,l,row,col,count;
    n=mint[i1].size();
    vector<string>temps;
    vector<string>terms;
    vector<string>vect;
    vector<string>prime;
    vector<string>temp1;
    vector<string>ep;
    vector<int>temp2;
    vector<pair<int,int> >temp3;
    int *a=new int[n];
    for(int j=0;j<n;j++)
	a[j]=mint[i1][j];
    for(int i=0;i<n;i++)
	vect.push_back(to_binary(a[i],m));
    for(int i=0;i<vect.size();i++)
	 terms.push_back(vect[i]);
         //This loop find the prime implicants of a particular function and store them in prime vector
    while(!vect.empty())
      {
        for(i=0;i<vect.size()-1;i++)
	{
	  int c=0;
          for(j=i+1;j<vect.size();j++)
	  {
	     l=compare(vect[i],vect[j]);
	     if(l!=-1 && l!=-2)
	      {
	        temp1.push_back(change(vect[i],l));
	        temp2.push_back(j);
	      }
             else c++;
          }
          if(c==j-i-1)
           { int d=0;
             for(int k=0;k<temp2.size();k++)
		{
		    if(i==(temp2[k]))
		     	{d=1;break;}
		}
	     if(d==0) check_like(vect[i],prime);
	   }
         }
         int d=0;
         for(int k=0;k<temp2.size();k++)
		  {
		  	if(i==(temp2[k]))
		  		{d=1;break;}
		  }
         if(d==0)check_like(vect[i],prime);
	 vect.clear();
	 for(int i=0;i<temp1.size();i++)
	   {
	      vect.push_back(temp1[i]);
           }
		   temp1.clear();
		   temp2.clear();
       }
       //Selection of prime implicants 
	vector<string>().swap(temp1);   //deallocate temp1 vector
	vector<int>().swap(temp2);      //deallocate temp2 vector
	vector<string>().swap(vect);    //deallocate vect vector
	row=prime.size();                //stores no. of rows in prime implicant chart
	col=n;                           //stores no.of column in prime implicant chart
	int**t = new int*[row+1];        //matrix corresponding to prime implicant chart.one extra row for ticks
	for(int i=0;i<row+1;i++)
	{  t[i]=new int[col];
	}

	for(int i=0;i<row+1;i++)        //initializing 0 to all the elements of prime implicant chart 
	{for(int j=0;j<col;j++)
	  t[i][j]=0;
	}
        //crossing(storing as 1)to indicate minterm contained in the prime implicant of that row
	for(int i=0;i<row;i++)
	{int c;
	 int n1=terms.size();
	 int m1=prime[i].length();
	 for(int j=0;j<n1;j++)
	 { c=1;
	   for(int k=0;k<m1;k++)
	   { if(prime[i][k]!='_'){if(prime[i][k]!=terms[j][k]){c=0;break;}}}
	   if(c==1)t[i][j]=1;
	 }
	 }
        //counting number of one's in each column. if number of ones's is equal to 1 then storing the indices of that cell
	for(j=0;j<col;j++)
	 {count=0;
	   for(i=0;i<row;i++)
	    { if(t[i][j]==1) {count++;k=i;}}
	   if(count==1){temp3.push_back(make_pair(j,k));}
	 }
        /*ticking of minterms (in which their is only 1 one) and minterms covered by those selected prime implicant and
         storing that selected prime implicant as essential prime implicant.*/
	for(i=0;i<temp3.size();i++)
	{ if(t[row][temp3[i].first]!=1)  //check that if a minterm(column with 1 one's) is already covered by a prime implicant
	   { ep.push_back(prime[temp3[i].second]);
	     t[temp3[i].second][temp3[i].first]=-1;
	     t[row][temp3[i].first]=1;
	     for(j=0;j<col;j++)
		{ if(t[temp3[i].second][j]==1)
		    {for(k=0;k<row;k++)
		      { if(t[k][j]==1)
		         t[k][j]=-1;
		      }
		     t[row][j]=1;        //putting ticks
		    }
		 }
	     }
	}
	temp3.clear();
        //counting number of ones(indicating minterms still not covered) in each row.if count is greater than 0 than store the count and row_index
	for(i=0;i<row;i++)
	{ count=0;
	  for(j=0;j<col;j++)
	  { if(t[i][j]==1)
	    count++;
	  }
	  if(count>0){temp3.push_back(make_pair(count,i));}
	}
        //final selection of prime implicants to cover the remaining minterms
	sort(temp3.begin(),temp3.end());
      if(!temp3.empty())
	{i=temp3.size()-1;
		{ ep.push_back(prime[temp3[i].second]);
		  for(j=0;j<col;j++)
		    { if(t[temp3[i].second][j]==1)
			{ for(k=0;k<row;k++)
			  { if(t[k][j]==1)
			     {t[k][j]=-1;}
			  }
			}
		    }
		}

		while(1)
		{ k=1;
		   for(i=0;(i<temp3.size()-k && i>=0);i++)
		   {count=0;
		   for(j=0;j<col;j++)
		      { if(t[temp3[i].second][j]==1)
			count++;
		      }
		   if(count>0)
		    {temp3[i].first=count;}else temp3[i].first=0;}
		   sort(temp3.begin(),temp3.end()-k);
		   i=temp3.size()-1-k;
		   if(temp3[i].first>0)
		   {ep.push_back(prime[temp3[i].second]);
		     for(j=0;j<col;j++)
		      { if(t[temp3[i].second][j]==1)
			 { for(k=0;k<row;k++)
			    { if(t[k][j]==1)
			     {t[k][j]=-1;}
			    }
			 }
		      }
		   }  
		  else 
		  break;
		k++;
		}
		for(int i=0;i<ep.size();i++)
		{ temps.push_back(ep[i]); }
         }
	else
	{
	    for(int i=0;i<prime.size();i++)
	     {
	        temps.push_back(prime[i]);
	     }
	}
if(i1<fn)
f.push_back(temps);                       //storing minimized function 
else
fc.push_back(temps);                      //storing minimized complement function
}
cout<<"The functions are: \n";
for(int j=0;j<f.size();j++)
{ cout<<"F"<<j+1<<"= ";
  for(int k=0;k<f[j].size();k++)
  { 
    for(int l=0;l<f[j][k].size();l++)
    { if(f[j][k][l]=='0'){cout<<char(l+65)<<"'";}
      else if(f[j][k][l]=='1'){cout<<char(l+65);}
  } 
 if(k!=f[j].size()-1)cout<<'+';
}
  cout<<endl;
}
for(int j=0;j<fc.size();j++)
{ cout<<"F"<<j+1<<"'= ";
  for(int k=0;k<fc[j].size();k++)
  {  
    for(int l=0;l<fc[j][k].size();l++)
    { if(fc[j][k][l]=='0'){cout<<char(l+65)<<"'";}
      else if(fc[j][k][l]=='1'){cout<<char(l+65);}
  } 
  if(k!=fc[j].size()-1)cout<<'+';
}cout<<endl;}
/*here we find the union of a possible arrangement of functions by using set and the size of the set gives the number of terms in union.
the arrangement with the minimum size gives the functions for pla*/
t=pow(2,fn);                              //stores the total number of possible arrangements
 i=0;
  s=to_binary(i,fn);                    //each binary string correspond to a particular arrangement.0 bit corresponds to F' and 1 bit corresponds to F
   for(int j=0;j<fn;j++)                            
   {if(s[j]=='0'){for(int k=0;k<fc[j].size();k++)
                 final.insert(fc[j][k]);                    
                }
    else{for(int k=0;k<f[j].size();k++)
                 final.insert(f[j][k]);
                }
   }
   min=final.size();
   result=s;                             
   for(int i=1;i<t;i++)                     
   {temp2.clear();  
    s=to_binary(i,fn);
   for(int j=0;j<fn;j++)
    {if(s[j]=='0'){for(int k=0;k<fc[j].size();k++)
                 temp2.insert(fc[j][k]);
                }
    else{for(int k=0;k<f[j].size();k++)
                 temp2.insert(f[j][k]);
                }
     
    }
    
    
    if(min>temp2.size())
    {min=temp2.size();
     final.clear();
     final.insert(temp2.begin(), temp2.end());
     result=s;
     temp2.clear();
    }
   }
cout<<"\nThe functions selected for pla are: ";
   for(i=0;i<fn;i++)
   { if(result[i]=='0')cout<<"F"<<i+1<<"'";           //priniting final arrangemnet
     else cout<<"F"<<i+1;
     cout<<" ";
   }
 return 0;
}





