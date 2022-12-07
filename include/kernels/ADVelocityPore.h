#pragma once

#include "ADKernelGrad.h"

class ADVelocityPore: public ADKernelGrad
{
	public:
		static InputParameters validParams();

		ADvelocityPore(const InputParameters & parameters);
	protected:
		virtual ADRealVectorValue precomputeQpREsidual() override;
		const MaterialPorosity<Real> _velocity_pore;
}
