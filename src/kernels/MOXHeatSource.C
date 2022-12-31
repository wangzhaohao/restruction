//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MOXHeatSource.h"

registerMooseObject("RestructeApp", MOXHeatSource);

InputParameters
MOXHeatSource::validParams()
{
  InputParameters params = BodyForce::validParams();

  // Override defaults and documentation, weak form is identical to BodyForce in MOOSE
  params.addParam<Real>("value", 1.0, "Value of heat source. Multiplied by function if present.");
  params.addParam<FunctionName>("function", "1", "Function describing the volumetric heat source");
  params.addCoupledVar("porosity", 0, "Coupled porosity");
  params.addParam<Real>("porosity_initial", 0.05, "the initial porosity");

  return params;
}

MOXHeatSource::MOXHeatSource(const InputParameters & parameters) : BodyForce(parameters),
  _porosity(coupledValue("porosity")),
  _porosity_initial(getParam<Real>("porosity_initial"))
{}

Real
MOXHeatSource::computeQpResidual()
{
  return (1 - _porosity[_qp])/(1 - _porosity_initial) * BodyForce::computeQpResidual();
}

Real
MOXHeatSource::computeQpJacobian()
{
  return (1 - _porosity[_qp])/(1 - _porosity_initial) * BodyForce::computeQpJacobian();
}
