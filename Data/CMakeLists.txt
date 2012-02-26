macro(copy_file src dst_dir)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${src} ${dst_dir}/Data/${src} COPYONLY)
endmacro(copy_file)

###### File: "Shaders/PCF_ShadowMapping.frag" ######
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/PCF_ShadowMapping.frag" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
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

###### File: "Shaders/ShadowMapping.vert" ######
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/ShadowMapping.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
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

###### File: "Shaders/VSM/VSM.vert" ######
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
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

###### File: "Shaders/VSM/VSM_StoreMoments.vert" ######
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/src/")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("Shaders/VSM/VSM_StoreMoments.vert" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
######

###### File: "config.xml" ######
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Debug")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/Release")

IF(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/src/")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/MinSizeRel/")
copy_file("config.xml" "${PROJECT_BINARY_DIR}/${PROJECT_NAME}/RelWithDebInfo/")
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
