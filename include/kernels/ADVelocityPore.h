#pragma once

#include "ADKernelGrad.h"

class ADVelocityPore: public ADKernelGrad
{
	public:
		static InputParameters validParams();

		ADVelocityPore(const InputParameters & parameters);
	protected:
		virtual ADRealVectorValue precomputeQpResidual() override;
		const ADMaterialProperty<Real> & _velocity_pore;
};
