//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "BodyForce.h"

// Forward Declarations

class MOXHeatSource : public BodyForce
{
protected:
  virtual Real computeQpResidual() override;

  virtual Real computeQpJacobian() override;

public:
  static InputParameters validParams();

  const VariableValue & _porosity;
  const Real & _porosity_initial;
  MOXHeatSource(const InputParameters & parameters);
};
