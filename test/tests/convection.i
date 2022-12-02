[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 20
  xmax = 5e-3 
[]

[Variables]
  [u]
    family = MONOMIAL
    order = CONSTANT
  []
[]

[Kernels]
  [time]
    type = TimeDerivative
    variable = u
  []
  [convection]
    type = VelocityPorosity
    variable = u
    velocity_porosity = 1e-7
  []
[]

[DGKernels]
  [convection]
    type = ADDGVelocityPorosity
    variable = u
    velocity = '1e-7 0 0'
  []
[]

[BCs]
  [left]
    type = PenaltyDirichletBC 
    value = 0.05
    boundary = 'right'
    variable = u
    penalty = 1e6
  []
[]

[Executioner]
  type = Transient
  solve_type = NEWTON
  num_steps = 10
  dt = 1
  dtmin = 1
[]

[Outputs]
  exodus = true
[]

