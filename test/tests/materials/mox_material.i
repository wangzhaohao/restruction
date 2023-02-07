#Test the MOXMaterial Kato et al
#Physical Properties and Irradiation Behavior Analysis of Np- and Am-Bearing MOX Fuels

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 100
[]

[Variables/temp]
  initial_condition = 400
[]

[BCs]
  [temp_left]
    type = DirichletBC
    variable = temp
    value = 500
    boundary = left
  []
  [temp_right]
    type = DirichletBC
    variable = temp
    value = 2300
    boundary = right
  []
[]

[Kernels/diff]
  type = Diffusion
  variable = temp
[]

[Materials]
  [mox_thermal]
    type = MOXThermal
    americium = 0.016
    neptunium = 0.016
    dev_O_M = 2
    temperature = temp
    porosity = 0
    outputs = all
  []
[]

[Executioner]
  type = Steady
  
  solve_type = PJFNK
[]

[Outputs]
  csv = true
  exodus = true
[]
