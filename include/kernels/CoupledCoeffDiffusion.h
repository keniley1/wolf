#ifndef COUPLEDCOEFFDIFFUSION_H
#define COUPLEDCOEFFDIFFUSION_H

#include "Kernel.h"

class CoupledCoeffDiffusion;

template <>
InputParameters validParams<CoupledCoeffDiffusion>();

/**
 *
 */
class CoupledCoeffDiffusion : public Kernel
{
public:
  CoupledCoeffDiffusion(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;
  virtual Real computeQpOffDiagJacobian(unsigned int jvar) override;

private:
  const VariableGradient & _coupled_grad;

  Real _diffusivity;

  unsigned int _coupled_id;
};

#endif // COUPLEDCOEFFDIFFUSION_H
