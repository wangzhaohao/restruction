[Mesh]
  coord_type = RZ
  [block]
    type = GeneratedMeshGenerator
    dim = 2
    nx = 100
    ny = 1
    xmax = 5e-3
    ymax = 1e-3
  []
[]

[Problem]
  solve = false
[]

[AuxVariables]
  [temp]
    family = LAGRANGE 
    order = FIRST
  []
  [velocity_porosity]
    family = MONOMIAL
    order = FIRST
  []
  [temp_test]
  []
[]

[AuxKernels] 
  [temp_function_aux]
    type = FunctionAux
    function = temp_function
    variable = temp
  []
  [velocity_poroperty_aux]
    type = MaterialRealAux
    property = velocity_porosity
    variable = velocity_porosity
  []
  [temp_test_aux]
    type = ParsedAux
    variable = temp_test
    function = 1500
  []
[]

[Functions]
  [temp_function]
    type = ParsedFunction
    value = -6190.60166*x-8.05175e7*x*x-8.10883e9*x*x*x+1.48088e12*x*x*x*x+2910.26613
  []
[]

[Materials]
  [velocity_poroperty_material]
    type = VelocityPorosityMaterial
    temp = temp
  []
[]

[Executioner]
  type = Steady 
  
  solve_type = 'PJFNK'
[]  
    
[Outputs]
  exodus = true
[]

