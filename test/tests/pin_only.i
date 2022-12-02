[Mesh]
  [rmp]
    type = ReactorMeshParams
    dim = 3 
    geom = "Hex"
    assembly_pitch = 7.10315
    axial_regions = '1.0 2.0'
    axial_mesh_intervals = '1 3'
    top_boundary_id = 201
    bottom_boundary_id = 202
  []

  [pin1]
    type = PinMeshGenerator
    reactor_params = rmp
    pin_type = 12
    pitch = 1.42063
    num_sectors = 4
    region_ids='1;
                2'
#    region_ids='1 2 3 4'

#    ring_radii = '0.2 0.4 0.5'
    mesh_intervals = '5'
    quad_center_elements = true#false
    extrude = true
    show_info = true
  []
[]

[AuxVariables]
  [region_id]
    family = MONOMIAL
    order = CONSTANT
  []
[]

[AuxKernels]
  [region_id]
    type = ExtraElementIDAux
    variable = region_id
    extra_id_name = region_id
  []
[]

[Problem]
  solve = false
[]

[Outputs]
  exodus = true
  execute_on = timestep_end
[]

[Executioner]
  type = Steady
[]
