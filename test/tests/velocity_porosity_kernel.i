[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 50
[]

[Variables]
  [u][]
[]

[Kernels]
#  [u_diff]
#    type = Diffusion
#    variable = u
#  []
  [u_velocity]
    type = VelocityPorosity
    variable = u
    velocity_porosity = -1e-3
  []
  [time]
    type = TimeDerivative
    variable = u
  []
#  [u_body]
#    type = BodyForce
#    variable = u
#    value = 1
#   []
[]

[BCs]
  [u_left]
    type = DirichletBC
    variable = u
    value = 1
    boundary  = right 
  []
[]

[Executioner]
  type = Transient 

  solve_type = PJFNK

  nl_rel_tol = 1.0e-9
  nl_abs_tol = 1.0e-10

  num_steps = 10
  dt = 1
#  solve_type = NEWTON 
[]

#[Preconditioning]
#  [./smp]
#    type = SMP
#    full = true
#  [../]
#[]

[Outputs]
  exodus = true
[]
