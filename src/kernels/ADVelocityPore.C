// the PDE is from the https://www.sciencedirect.com/science/article/pii/S0022311518302861
// Modeling porosity migration in LWR and fast reactor MOX fuel using the finite element method
#include "ADVelocityPore.h"

registerMooseObject("RestructedApp", ADVelocityPore);

InputParameters
ADVelocityPore::validParams()
{
	auto params = ADKernelGrad::validParams();

	params.addParam<MaterialPropertyName>("velocity_pore", 1., "the velocity of pore");
	params.addClassDescription("the kernel is to calcate the porosity convection");
	return params;
}

