#pragma once

#include "Function.h"
#include "Kernel.h"

class VelocityPorosityKernel;


class VelocityPorosityKernel : public Kernel
{
public:
  static InputParameters validParams();

  VelocityPorosityKernel(const InputParameters & parameters);
protected:
  virtual Real computeQpResidual() override;
	virtual Real computeQpJacobian() override;

private:
	const MaterialProperty<Real> & _velocity_porosity;
	const RealVectorValue _vp;
};
