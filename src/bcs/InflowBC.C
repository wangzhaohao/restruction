//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "InflowBC.h"

registerMooseObject("RestructeApp", InflowBC);

InputParameters
InflowBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<Real>("inlet_conc", "The inlet concentration");
  return params;
}

InflowBC::InflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
    _velocity_porosity(getMaterialProperty<Real>("velocity_porosity")),
    _inlet_conc(getParam<Real>("inlet_conc"))
{
}

Real
InflowBC::computeQpResidual()
{
	RealVectorValue velocity(1, 0, 0);
  return _test[_i][_qp] * _inlet_conc * _velocity_porosity[_qp] * _normals[_qp] * velocity;
}

Real
InflowBC::computeQpJacobian()
{
  return 0.;
}
