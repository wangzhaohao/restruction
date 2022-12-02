#pragma once
#include "Material.h"

class Function;

class VelocityPorosityMaterial : public Material
{
  public:
    static InputParameters validParams();

    VelocityPorosityMaterial(const InputParameters & parameters);
  protected:
    virtual void computeProperties();

    MaterialProperty<Real> & _velocity_porosity;
    const VariableValue & _temperature;
    const VariableGradient & _grad_temperature;
};
