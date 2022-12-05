#include "VelocityPorosityAux.h"

registerMooseObject("RestructeApp", VelocityPorosityAux);

InputParameters
VelocityPorosityAux::validParams()
{
	InputParameters params = AuxKernel::validParams();
	params.addCoupledVar("temp", "coupled temperature");
	params.addClassDescription("the restruction of Mox porosity velocity");
	return params;
}
