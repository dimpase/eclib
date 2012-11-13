// torsion.cc: program to find & display torsion points
//////////////////////////////////////////////////////////////////////////
//
// Copyright 1990-2012 John Cremona
// 
// This file is part of the mwrank package.
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
 
#include <eclib/points.h>
#include <eclib/getcurve.h>


int main(){
  cerr<<"Program to find and/or count torsion on a curve.\n\n";
  set_precision("Enter number of decimal places");

  cerr<<"Enter 0 for short output (#torsion only)\n";
  cerr<<"   or 1 for long  output (list of the torsion points): ";
  int showpoints; cin >> showpoints;
  initprimes("PRIMES",0);
  vector<bigrational> ai(5);
  vector<Point> tor; int ntor, n2;
  bigint u, r, s, t, v;
  int verb=1;

  while (getcurve(ai,verb))
    {
      Curvedata E0(ai,v);
      Curvedata E1 = E0.minimalize(u,r,s,t);
      cout<<"Curve ["<<ai[0]<<","<<ai[1]<<","<<ai[2]<<","<<ai[3]<<","<<ai[4]<<"]"<<flush;
      tor = torsion_points(E1); 
      ntor = tor.size();
      n2=0;
      cout<<" \t has " << ntor << " torsion point(s)\n";
      if(showpoints)
	{
	  for(int i=0; i<ntor; i++)
	    {
	      Point P = transform(tor[i],&E0,u,r,s,t,1);
	      cout << scale(P,v,0) << "\t";
	      if(!P.isvalid()) cout << " --warning: NOT on curve!\n";
	      else
		{
		  int ord = order(P);
		  if(ord==2) n2++;
		  cout << "(order " << ord << ")\n";
		}
	    }
	  if(n2>2) cout<<"Non-cyclic: C2 x C"<<(ntor/2)<<"\n"; 
	  else cout << "Cyclic: C"<<ntor<<"\n";
	}
    }
} //ends main

	

