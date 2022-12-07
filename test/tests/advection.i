[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 10
  xmin = 0.5
[]

[Variables]
  [u][]
[]

[Kernels]
  [advection]
    type = ConservativePorosity
    upwinding_type = full
    variable = u
    velocity_porosity = velocity_porosity
  []
[]

[BCs]
  [u_right]
    type = DirichletBC
    variable = u
    value = 1
    boundary = right
  []
  [u_left]
    type = DirichletBC
    value = 1.5
    variable = u
    boundary = left
  []
[]

[Materials]
  [velocity_porosity_material]
    type = GenericFunctionMaterial
    prop_names = 'velocity_porosity'
    prop_values = velocity_porosity_function
  []
[]

[Functions]
  [velocity_porosity_function]
    type = ParsedFunction
    value = 2*x+1
  []
[]

[Executioner]
  type = Steady
  solve_type = PJFNK
[]

[Outputs]
  exodus = true
[]
