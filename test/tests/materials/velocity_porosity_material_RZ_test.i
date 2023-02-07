# test the VelocityPorosityMaterial 
# the Outputs is **velocity_pore**
# the data from Phase-fielf simulations of pore migration and morphology change in thermal gradient
# parabolic profile with centerline value 2800K and outer value 900K

[Mesh]
  type = GeneratedMesh
  dim = 1
  nx = 1000
  xmin = 0
  xmax = 5e-3
  coord_type = RZ
[]

[Variables/temp]
  initial_condition = 400
[]

[Kernels]
  [diff]
    type = Diffusion
    variable = temp
  []

  [bodyforce]
    type = BodyForce
    variable = temp
    value = 3.04e8
  []
[]

[BCs]
  [temp_left]
    type = NeumannBC
    variable = temp
    value = 0
    boundary = left
  []
  [temp_right]
    type = DirichletBC
    variable = temp
    value = 900
    boundary = right
  []
[]

[Materials/velocity_pore]
  type = VelocityPorosityMaterial
  temp = temp
  outputs = all
[]

[Executioner]
  type = Steady
  
  solve_type = 'PJFNK'
[]

[Outputs]
  csv = true
  exodus = true
[]
