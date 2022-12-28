#pragma once

#include "Material.h"

// class Function;

class VelocityPorosityMaterial : public Material
{
  public:
    static InputParameters validParams();

    VelocityPorosityMaterial(const InputParameters & parameters);
  protected:
    virtual void computeProperties();

    ADMaterialProperty<Real> & _velocity_pore;
    const VariableValue & _temperature;
    const VariableGradient & _grad_temperature;
};
