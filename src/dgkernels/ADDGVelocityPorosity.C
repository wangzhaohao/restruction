#include "ADDGVelocityPorosity.h"

registerMooseObject("RestructeApp", ADDGVelocityPorosity);

InputParameters
ADDGVelocityPorosity::validParams()
{
	InputParameters params = ADDGKernel::validParams();
	params.addRequiredParam<RealVectorValue>("velocity", "Velocity vector");
	params.addClassDescription("DG upwinding for the porosity velocity");
	return params;
}

ADDGVelocityPorosity::ADDGVelocityPorosity(const InputParameters & parameters)
	: ADDGKernel(parameters),
	_velocity_porosity(getMaterialProperty<Real>("velocity_porosity")),
	_velocity(getParam<RealVectorValue>("velocity"))
{
}

ADReal
ADDGVelocityPorosity::computeQpResidual(Moose::DGResidualType type)
{
	ADReal r = 0;

	Real vdotn = _velocity_porosity[_qp] * _velocity * _normals[_qp];

	switch(type)
	{
		case Moose::Element:
			if (vdotn >= 0)
				r += vdotn * _u[_qp] *_test[_i][_qp];
			else
				r += vdotn * _u_neighbor[_qp] * _test[_i][_qp];
			break;

		case Moose::Neighbor:
			if (vdotn >= 0)
				r -= vdotn * _u[_qp] * _test_neighbor[_i][_qp];
			else
				r -= vdotn * _u_neighbor[_qp] * _test_neighbor[_i][_qp];
			break;

	}
	
	return r;
}
