// FILE  H1DEGPHI.CC: program to output deg(phi) table
//////////////////////////////////////////////////////////////////////////
//
// Copyright 1990-2012 John Cremona
// 
// This file is part of the mwrank/g0n package.
// 
// mwrank is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2 of the License, or (at your
// option) any later version.
// 
// mwrank is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// for more details.
// 
// You should have received a copy of the GNU General Public License
// along with mwrank; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
// 
//////////////////////////////////////////////////////////////////////////

#include <fstream>

#include <eclib/marith.h>
#include <eclib/moddata.h>
#include <eclib/symb.h>
#include <eclib/cusp.h>
#include <eclib/homspace.h>
#include <eclib/oldforms.h>
#include <eclib/curve.h>
#include <eclib/cperiods.h>
#include <eclib/newforms.h>
#include <eclib/periods.h>

#define AUTOLOOP
#define BOOKORDER       // if defined, sorts newforms/curves into order
                        // in the Book (relevant up to 500 only)

//#SHOW_FACTORIZATION

#include <eclib/curvesort.h>

int main(void)
{
  set_precision("Enter number of decimal places");
 int limit,n=1; 
#ifdef AUTOLOOP
 cerr<<"Enter first and last N: ";
cin>>n>>limit; 
 n--; 
 cerr<<endl;
// cout << "Table of curves with deg(phi) (and its prime divisors) for N from "<<(n+1)<<" to "<<limit<<endl;
#ifdef BOOKORDER
// cout<<"(reordered to agree with Book for levels up to 500)"<<endl;
#endif
// cout << "\nN \t# \tdeg(phi) {primes} \t";
// cout<<"[a1,a2,a3,a4,a6]";
 //cout<<"{c4,c6}";
// cout<<endl<<endl;
 while (n<limit) { n++;
#else
 while (cout<<"Enter level: ", cin>>n, n>0) {
   cout<<endl;  
#endif
 newforms nf(n,1);
 for(int xi=0; xi<nf.n1ds; xi++)
   { int i = xi;
#ifdef BOOKORDER
     i=booknumber0(n,i);
#endif
     long degphi = nf.nflist[i].degphi;
     vector<long> pdphi=pdivs(degphi);
     long ip, npdphi=pdphi.size();
     bigfloat rperiod;
     Curve C = nf.getcurve(i, -1, rperiod);
     Curvedata CD(C,1);  // The 1 causes minimalization
     cout << n << "\t" << codeletter(xi) << "\t1\t" << degphi << " \t{";
     for(ip=0; ip<npdphi; ip++)
       {
	 long p=pdphi[ip];
#ifdef SHOW_FACTORIZATION
	 if(ip)cout<<"\\cdot ";
#else
	 if(ip)cout<<",";
#endif
	 cout<<p;
#ifdef SHOW_FACTORIZATION
	 long v=val(p,degphi);
	 if(v>1) {cout<<"^"; if(v>9)cout<<"{"<<v<<"}"; else cout<<v;}
#endif
       }
     cout << "} \t";
     cout << (Curve)CD << endl;
   }
}       // end of while()
// cout<<endl;
}       // end of main()


