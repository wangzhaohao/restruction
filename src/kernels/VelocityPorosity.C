#include "VelocityPorosity.h"
#include "MooseMesh.h"

registerMooseObjectAliased("RestructeApp", VelocityPorosityKernel, "VelocityPorosity");

InputParameters
VelocityPorosityKernel::validParams()
{
  InputParameters params = Kernel::validParams();
	// params.addParam<MaterialPropertyName>("velocity_porosity", "velocity_porosity", "the porosity velociy");
	RealVectorValue vp(1, 0, 0);
	params.addParam<RealVectorValue>("vp", vp, "the velocity (default is (1, 0, 0))");
	params.addParam<MaterialPropertyName>("velocity_porosity", 1., "the velocity of porosity.");
  params.addClassDescription("the kernel is to calcate the porosity convection");

  return params;
}

VelocityPorosityKernel::VelocityPorosityKernel(const InputParameters & parameters)
  : Kernel(parameters),
	_velocity_porosity(getMaterialProperty<Real>("velocity_porosity")),
	_vp(getParam<RealVectorValue>("vp"))
{
}

Real
VelocityPorosityKernel::computeQpResidual()
{
	 // if (isParamValid("vp"))
	return -_grad_test[_i][_qp] * (_vp * _velocity_porosity[_qp] * _u[_qp]);
	 // else
	// return _velocity_porosity[_qp] * _grad_u[_qp](0) * _vp * _test[_i][_qp];
	// return _test[_i][_qp] * _grad_u[_qp](0);
}

Real
VelocityPorosityKernel::computeQpJacobian()
{
	// return (_velocity_porosity[_qp] * _grad_phi[_j][_qp](0)) * _test[_i][_qp];
	return -_grad_test[_i][_qp] * (_phi[_j][_qp] * _vp * _velocity_porosity[_qp]);
}

