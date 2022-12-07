//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "OutflowBC.h"
#include "Function.h"

registerMooseObject("RestructeApp", OutflowBC);

InputParameters
OutflowBC::validParams()
{
  InputParameters params = IntegratedBC::validParams();
  params.addRequiredParam<Real>("outlet_conc", "the outlet concentration");
  return params;
}

OutflowBC::OutflowBC(const InputParameters & parameters)
  : IntegratedBC(parameters),
	_velocity_porosity(getMaterialProperty<Real>("velocity_porosity")),
  _outlet_conc(getParam<Real>("outlet_conc"))
{
}

Real
OutflowBC::computeQpResidual()
{
	RealVectorValue velocity(1, 0, 0);
  return _test[_i][_qp] * _u[_qp] * _outlet_conc * _velocity_porosity[_qp] * _normals[_qp] * velocity;
}

Real
OutflowBC::computeQpJacobian()
{
  RealVectorValue velocity(1, 0, 0);
  return _test[_i][_qp] * _phi[_j][_qp] *_outlet_conc *  _velocity_porosity[_qp] * _normals[_qp] * velocity;
}
