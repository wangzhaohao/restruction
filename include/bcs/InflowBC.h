//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "IntegratedBC.h"

class InflowBC : public IntegratedBC
{
public:
  static InputParameters validParams();

  InflowBC(const InputParameters & parameters);

protected:
	const MaterialProperty<Real> & _velocity_porosity;
  Real _inlet_conc;
  virtual Real computeQpResidual();
  virtual Real computeQpJacobian();
};
