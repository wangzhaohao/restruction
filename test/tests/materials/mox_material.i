#Test the MOXMaterial Kato et al
#the O/M ratio is 2(x = 0) Am = Np = 0

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
    value = 300
    boundary = left
  []
  [temp_right]
    type = DirichletBC
    variable = temp
    value = 2000
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
    americium = 0
    neptunium = 0
    dev_O_M = 2
    temperature = temp
 #   pososity = 0.15
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
