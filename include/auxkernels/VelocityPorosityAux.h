//2022.12.5认为辅助变量会放进去求导.
#pragma once

#include "AuxKernel.h"

class VelocityPorosityAux : public AuxKernel
{
	public:
		VelocityPorosityAux(const InputParameters & parameters);
		static InputParameters validParams();
	protected:
		virtual Real computeValue() override;
		const VariableValue & _temperature;
		const VariableGradient & _grad_temperature;
}
