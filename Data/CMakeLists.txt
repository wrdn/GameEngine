macro(copy_file src dst_dir)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${src} ${dst_dir}/Data/${src} COPYONLY)
endmacro(copy_file)

###### File: "config.xml" ######
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/src/")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/VSM/VSM.vert" ######
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/VSM/VSM_StoreMoments.vert" ######
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/VSM/VSM_StoreMoments.frag" ######
copy_file("Shaders/VSM/VSM_StoreMoments.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM_StoreMoments.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM_StoreMoments.frag" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM_StoreMoments.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM_StoreMoments.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/VSM/VSM.frag" ######
copy_file("Shaders/VSM/VSM.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM.frag" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/PCF_ShadowMapping.vert" ######
copy_file("Shaders/PCF_ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/PCF_ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/PCF_ShadowMapping.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/PCF_ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/PCF_ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/ShadowMapping.frag" ######
copy_file("Shaders/ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/ShadowMapping.frag" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/PCF_ShadowMapping.frag" ######
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "Shaders/ShadowMapping.vert" ######
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza.obj" ######
copy_file("sponza/sponza.obj" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza.obj" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza.obj" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza.obj" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza.obj" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza.mtl" ######
copy_file("sponza/sponza.mtl" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza.mtl" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza.mtl" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza.mtl" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza.mtl" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_plant_spec.jpg" ######
copy_file("sponza/sponza_textures/vase_plant_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_plant_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_plant_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_plant_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_plant_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_thorn_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_thorn_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_thorn_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_thorn_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_thorn_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_thorn_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_b_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_b_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_b_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_b_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_b_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_b_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_curtain_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_curtain_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_curtain_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_curtain_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_curtain_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_curtain_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_ceiling_a_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_ceiling_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_ceiling_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_ceiling_a_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/lion_ddn.jpg" ######
copy_file("sponza/sponza_textures/lion_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/lion_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/lion_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/lion_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/lion_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_thorn_mask.jpg" ######
copy_file("sponza/sponza_textures/sponza_thorn_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_thorn_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_thorn_mask.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_thorn_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_thorn_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_details_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_details_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_details_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_details_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_details_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_details_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_details_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_details_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_details_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_details_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_details_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_details_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/background.jpg" ######
copy_file("sponza/sponza_textures/background.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/background.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/background.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/background.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/background.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_curtain_blue_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_curtain_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_curtain_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_curtain_blue_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_curtain_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_curtain_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/chain_texture.jpg" ######
copy_file("sponza/sponza_textures/chain_texture.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/chain_texture.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/chain_texture.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/chain_texture.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/chain_texture.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_fabric_green_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_fabric_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_fabric_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_fabric_green_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_fabric_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_fabric_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_hanging.jpg" ######
copy_file("sponza/sponza_textures/vase_hanging.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_hanging.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_hanging.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_hanging.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_hanging.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/spnza_bricks_a_spec.jpg" ######
copy_file("sponza/sponza_textures/spnza_bricks_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/spnza_bricks_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/spnza_bricks_a_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/spnza_bricks_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/spnza_bricks_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/chain_texture_ddn.jpg" ######
copy_file("sponza/sponza_textures/chain_texture_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/chain_texture_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/chain_texture_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/chain_texture_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/chain_texture_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_b_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_b_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_b_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_b_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_b_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_b_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_floor_a_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_floor_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_floor_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_floor_a_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_floor_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_floor_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_b_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_b_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_b_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_b_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_b_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_b_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_fabric_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_fabric_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_fabric_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_fabric_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_fabric_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_fabric_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/spnza_bricks_a_diff.jpg" ######
copy_file("sponza/sponza_textures/spnza_bricks_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/spnza_bricks_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/spnza_bricks_a_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/spnza_bricks_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/spnza_bricks_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_round_ddn.jpg" ######
copy_file("sponza/sponza_textures/vase_round_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_round_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_round_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_round_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_round_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_round.jpg" ######
copy_file("sponza/sponza_textures/vase_round.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_round.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_round.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_round.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_round.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/lion.jpg" ######
copy_file("sponza/sponza_textures/lion.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/lion.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/lion.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/lion.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/lion.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_thorn_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_thorn_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_thorn_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_thorn_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_thorn_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_thorn_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_arch_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_arch_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_arch_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_arch_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_arch_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_arch_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_thorn_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_thorn_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_thorn_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_thorn_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_thorn_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_thorn_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/spnza_bricks_a_ddn.jpg" ######
copy_file("sponza/sponza_textures/spnza_bricks_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/spnza_bricks_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/spnza_bricks_a_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/spnza_bricks_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/spnza_bricks_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_roof_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_roof_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_roof_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_roof_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_roof_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_roof_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_flagpole_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_flagpole_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_flagpole_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_flagpole_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_flagpole_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_flagpole_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_flagpole_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_flagpole_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_flagpole_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_flagpole_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_flagpole_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_flagpole_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_dif.jpg" ######
copy_file("sponza/sponza_textures/vase_dif.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_dif.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_dif.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_dif.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_dif.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_plant.jpg" ######
copy_file("sponza/sponza_textures/vase_plant.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_plant.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_plant.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_plant.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_plant.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_ddn.jpg" ######
copy_file("sponza/sponza_textures/vase_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_plant_mask.jpg" ######
copy_file("sponza/sponza_textures/vase_plant_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_plant_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_plant_mask.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_plant_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_plant_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_details_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_details_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_details_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_details_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_details_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_details_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_roof_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_roof_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_roof_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_roof_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_roof_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_roof_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_fabric_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_fabric_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_fabric_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_fabric_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_fabric_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_fabric_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_fabric_blue_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_fabric_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_fabric_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_fabric_blue_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_fabric_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_fabric_blue_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_c_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_c_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_c_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_c_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_c_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_c_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_floor_a_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_floor_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_floor_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_floor_a_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_floor_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_floor_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_a_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_a_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_ceiling_a_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_ceiling_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_ceiling_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_ceiling_a_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/background_ddn.jpg" ######
copy_file("sponza/sponza_textures/background_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/background_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/background_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/background_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/background_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_a_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_a_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_a_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/chain_texture_mask.jpg" ######
copy_file("sponza/sponza_textures/chain_texture_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/chain_texture_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/chain_texture_mask.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/chain_texture_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/chain_texture_mask.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_floor_a_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_floor_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_floor_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_floor_a_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_floor_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_floor_a_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_a_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_a_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/vase_round_spec.jpg" ######
copy_file("sponza/sponza_textures/vase_round_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/vase_round_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/vase_round_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/vase_round_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/vase_round_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_c_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_c_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_c_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_c_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_c_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_c_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_arch_spec.jpg" ######
copy_file("sponza/sponza_textures/sponza_arch_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_arch_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_arch_spec.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_arch_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_arch_spec.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_ceiling_a_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/lion2_ddn.jpg" ######
copy_file("sponza/sponza_textures/lion2_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/lion2_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/lion2_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/lion2_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/lion2_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_column_c_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_column_c_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_column_c_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_column_c_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_column_c_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_column_c_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_arch_ddn.jpg" ######
copy_file("sponza/sponza_textures/sponza_arch_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_arch_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_arch_ddn.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_arch_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_arch_ddn.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "sponza/sponza_textures/sponza_curtain_green_diff.jpg" ######
copy_file("sponza/sponza_textures/sponza_curtain_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("sponza/sponza_textures/sponza_curtain_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("sponza/sponza_textures/sponza_curtain_green_diff.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("sponza/sponza_textures/sponza_curtain_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("sponza/sponza_textures/sponza_curtain_green_diff.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "test.jpg" ######
copy_file("test.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("test.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("test.jpg" "${PROJECT_BINARY_DIR}/src/")
copy_file("test.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("test.jpg" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######
