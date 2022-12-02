[Mesh]
  type = GeneratedMesh
  dim = 2
  nx = 10
  ny = 2
[]

[Variables]
  [u][]
[]

[Kernels]
  [diff]
    type = Diffusion
    variable = u
  []
  [rxn]
    type = Reaction
    variable = u
    rate = -1.0
  []
[]

[BCs]
  [right]
    type = DirichletBC
    variable = u
    value = 1
    boundary = right
  []
[]

[Executioner]
  type = Steady
[]

[Outputs]
  exodus = true
[]
