//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Material.h"

class VelocityPorosityMaterial : public Material
{
public:
  VelocityPorosityMaterial(const InputParameters & parameters);

  static InputParameters validParams();

protected:
  virtual void computeProperties() override;

private:

  ADMaterialProperty<Real> & _velocity_pore;
  const VariableValue & _temperature;
  const VariableGradient & _grad_temperature;
};
