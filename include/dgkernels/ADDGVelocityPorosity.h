#pragma once
#include "ADDGKernel.h"

class ADDGVelocityPorosity : public ADDGKernel
{
	public:
		static InputParameters validParams();

		ADDGVelocityPorosity(const InputParameters & parameters);

	protected:
		ADReal computeQpResidual(Moose::DGResidualType type) override;

		RealVectorValue _velocity;
	private:
		const MaterialProperty<Real> & _velocity_porosity;
};
