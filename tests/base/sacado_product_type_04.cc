// ---------------------------------------------------------------------
//
// Copyright (C) 2015 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------


// test ProductType with sacado

#include <iomanip>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <typeinfo>

#include <deal.II/base/tensor.h>
#include <deal.II/base/sacado_product_type.h>

#include "../tests.h"

template <typename T, typename U, typename CompareType>
void check()
{
  AssertThrow (typeid(typename ProductType<T,U>::type) == typeid(CompareType),
               ExcInternalError());
}


int main()
{
  typedef Sacado::Fad::DFad<double> Sdouble;
  typedef Sacado::Fad::DFad<Sdouble> SSdouble;
  std::ofstream logfile("output");
  deallog.attach(logfile);
  deallog.depth_console(0);
  deallog.threshold_double(1.e-10);


  // check product with Tensor<1,dim>
  check<Tensor<1,2,Sdouble>,Tensor<1,2,Sdouble>,Sdouble >();
  check<Tensor<1,2,SSdouble>,Tensor<1,2,SSdouble>,SSdouble  >();

  Tensor<1,2,SSdouble> t1;
  Tensor<1,2,SSdouble> t2;
  SSdouble a(2,0,7.0);
  SSdouble b(2,1,3.0);
  SSdouble c;
  a.val() = Sdouble(2,0,7.0);
  b.val() = Sdouble(2,1,3.0);

  for (unsigned int i=0; i<2; ++i)
    {
      t1[i] = 2.*a+i;
      t2[i] = 3.*b-i;
    }
  const Tensor<1,2,SSdouble> t3=t2;
  t1 *t2;

  t2 += a*t1;

  c = 0;
  c += (a*b + 0.5*(t3*t3 + t1*t2))*0.3;



  deallog << "OK" << std::endl;
}
