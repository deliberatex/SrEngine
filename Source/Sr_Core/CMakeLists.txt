set(SRC_BUILD_FILES
    "App.cpp"
    "Pch/pch.h"
    "Pch/pch.cpp"
    "Engine/Engine.h"
    "Engine/Engine.cpp"
    "Timer/Timer.h"
    "Timer/Timer.cpp"
    "Events/Event.h"
    
    "ECS/Systems.h"
    "ECS/Base/Types.h"
    "ECS/Base/BaseComponent.h"
    "ECS/Base/BaseSystem.h"
    "ECS/Base/CompList.h"
    "ECS/Base/EntityManager.h"
    "ECS/Base/ComponentFactory.h"
    "ECS/Components.h"
    "ECS/Base/Entity.h"
    "ECS/Components/Camera.h"
    "ECS/Components/CsScript.h"
    "ECS/Components/DirectionalLight.h"
    "ECS/Components/EntityName.h"
    "ECS/Components/Gizmo3D.h"
    "ECS/Components/KeyMotion.h"
    "Resource/Resource.h"
    "Resource/Resource.cpp"
    
    
    "Vendor/GUIZMO/ImGuizmo.cpp"
    "Vendor/GUIZMO/ImGuizmo.h"
    "Vendor/IMGUI/imconfig.h"
    "Vendor/IMGUI/imgui.cpp"
    "Vendor/IMGUI/imgui.h"
    "Vendor/IMGUI/imgui_demo.cpp"
    "Vendor/IMGUI/imgui_draw.cpp"
    "Vendor/IMGUI/imgui_impl_glfw.cpp"
    "Vendor/IMGUI/imgui_impl_glfw.h"
    "Vendor/IMGUI/imgui_impl_opengl3.cpp"
    "Vendor/IMGUI/imgui_impl_opengl3.h"
    "Vendor/IMGUI/imgui_internal.h"
    "Vendor/IMGUI/imgui_widgets.cpp"
    "Vendor/IMGUI/imstb_rectpack.h"
    "Vendor/IMGUI/imstb_textedit.h"
    "Vendor/IMGUI/imstb_truetype.h"
    "Vendor/STB/stb_image.cpp"
    "Vendor/STB/stb_image.h"

    
    
     "Errors/Errors.h"
     "Objects/Vertex.h"
     "Objects/VertexArray.h"
     "Objects/Shader.h"
     "ECS/Components/MeshRenderer.h"
     "ECS/Components/ModelRenderer.h"
     "Objects/ColorBuffer.h"
     "Objects/DepthBuffer.h"
     "Objects/GLMesh.h"
     "Objects/GLQuad.h"
     "Objects/Material.h"
     "Objects/Model.h"
     "Objects/SamplerBuffer.h"
     "ECS/Components/PointLight.h"
     "ECS/Components/RigidBody.h"
     "ECS/Components/SpotLight.h"
     "ECS/Components/SpriteRenderer.h"
     "ECS/Components/Transform.h"
     "ECS/Systems/CameraSystem.h"
     "ECS/Systems/CSharpScriptSystem.h"
     "ECS/Systems/DirectionalLightSystem.h"
     "ECS/Systems/EditorCameraSystem.h"
     "ECS/Systems/GridRendererSystem.h"
     "ECS/Systems/MeshRendererSystem.h"
     "ECS/Systems/ModelRendererSystem.h"
     "ECS/Systems/PhysicsSystem.h"
     "ECS/Systems/PointLightSystem.h"
     "ECS/Systems/SkyBoxRendererSystem.h"
     "ECS/Systems/SpotLightSystem.h"
     "ECS/Systems/SpriteRendererSystem.h"
     "Editor/CompUIs/CompUI.h"
     "Editor/CompUIs/DirectLightUI.h"
     "Editor/CompUIs/MeshUI.h"
     "Editor/CompUIs/NameTagUI.h"
     "Editor/CompUIs/PointLightUI.h"
     "Editor/CompUIs/TransformUI.h"
     "Editor/Controls/Widgets.h"
     "Editor/UiLayer.h"
     "Editor/UiLayer.cpp"
     "Events/AppEvents.h"
     "Events/Dispatcher.h"
     "Events/EventSystem.h"
     "Events/GLFWImp.h"
     "Events/GLFWImp.cpp"
     "Events/KeyEvents.h"
     "Events/MouseEvents.h"
     "Events/WindowEvents.h"
     "Serializer/XMLSerializer.h"
     "Serializer/XMLSerializer.cpp" "Engine/PathHelper.h" "Engine/PathHelper.cpp")



add_executable(Sr_Core ${SRC_BUILD_FILES})

source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}"
         FILES ${SRC_BUILD_FILES})
         
target_include_directories(Sr_Core PUBLIC 
#   ${PROJECT_SOURCE_DIR}/Source/InceptionEngine 
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/camera
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/SrGui
#    ${PROJECT_SOURCE_DIR}/Source/SrBase/SrGui/backends
    
    ${PROJECT_SOURCE_DIR}/Source/Sr_Core/
    ${PROJECT_SOURCE_DIR}/Source/Sr_Core/Engine
    ${PROJECT_SOURCE_DIR}/Source/Sr_Core/ECS
    ${PROJECT_SOURCE_DIR}/Libraries/includes

#   ${PROJECT_SOURCE_DIR}/StandAloneResource
)

target_link_libraries(Sr_Core 
    ${PROJECT_SOURCE_DIR}/Libraries/libs/OpenGL32.Lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glfw3.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glew32.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/glew32s.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/tinyxml2.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/freeglutd.lib
    ${PROJECT_SOURCE_DIR}/Libraries/libs/assimp-vc142-mtd.lib

)

#target_precompile_headers(Sr_Core
#    "${PROJECT_SOURCE_DIR}/Source/Sr_Core/Pch/pch.h"
#)

add_custom_command(TARGET Sr_Core POST_BUILD 
 COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Libraries/dlls/glew32.dll"
        "${PROJECT_BINARY_DIR}/Source/Sr_Core")

add_custom_command(TARGET Sr_Core POST_BUILD 
 COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Libraries/dlls/assimp-vc142-mtd.dll"
        "${PROJECT_BINARY_DIR}/Source/Sr_Core")

add_custom_command(TARGET Sr_Core POST_BUILD 
 COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${PROJECT_SOURCE_DIR}/Libraries/dlls/freeglutd.dll"
        "${PROJECT_BINARY_DIR}/Source/Sr_Core")
