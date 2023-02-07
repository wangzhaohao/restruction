// the PDE is from the https://www.sciencedirect.com/science/article/pii/S0022311518302861
// Modeling porosity migration in LWR and fast reactor MOX fuel using the finite element method
#include "ADVelocityPore.h"

registerMooseObject("RestructeApp", ADVelocityPore);

InputParameters
ADVelocityPore::validParams()
{
  auto params = ADKernelGrad::validParams();

  params.addParam<MaterialPropertyName>("velocity_pore","velocity_pore", "the velocity of pore");
  params.addClassDescription("the kernel is to calcate the porosity convection");
  return params;
}

ADVelocityPore::ADVelocityPore(const InputParameters & parameters) : ADKernelGrad(parameters),
	_velocity_pore(getADMaterialProperty<Real>("velocity_pore"))
{}

ADRealVectorValue
ADVelocityPore::precomputeQpResidual()
{
  ADRealVectorValue coeff_vector(1, 0, 0); 
  return coeff_vector * std::abs(_velocity_pore[_qp]) * (1 - _u[_qp]) * _u[_qp];
}
