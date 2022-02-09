set(SRC_BUILD_FILES
    "App.cpp"
    "Pch/pch.h"
    "Pch/pch.cpp"
    "Engine/Engine.h"
    "Engine/Engine.cpp"
    )


add_executable(Sr_Core ${SRC_BUILD_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
         FILES ${SRC_BUILD_FILES})
         
target_include_directories(Sr_Core PUBLIC 
#   ${PROJECT_SOURCE_DIR}/Source/InceptionEngine 
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/camera
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/SrGui
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/SrGui/backends

    ${PROJECT_SOURCE_DIR}/Libraries/includes

#   ${PROJECT_SOURCE_DIR}/StandAloneResource
)

target_link_libraries(Sr_Core 
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glfw3.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/assimp-vc142-mt.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glew32.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glew32s.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/tinyxml2d.lib
)


#add_custom_command(TARGET Sr_Core POST_BUILD 
# COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        "${PROJECT_SOURCE_DIR}/ThirdParty/assimp_dll/assimp-vc140-mt.dll"
#        "${PROJECT_BINARY_DIR}/Source/SrBase")