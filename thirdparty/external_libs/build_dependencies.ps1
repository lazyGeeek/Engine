Write-Output "============================================================================"
Write-Output "Creating directories"
Write-Output "============================================================================`n"

New-Item -Path "$PSScriptRoot/" -Name "../bins" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../include" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../include/imgui" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../include/nvapi" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../libs" -ItemType Directory -Force

try {
    Write-Output "`n============================================================================"
    Write-Output "Start Building GLFW"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/glfw-3.3.8.zip" -Force -DestinationPath "$PSScriptRoot/temp"

    cmake $PSScriptRoot/temp/glfw-3.3.8 -B"$PSScriptRoot/temp/glfw-3.3.8/build" `
        -DGLFW_BUILD_EXAMPLES=OFF `
        -DGLFW_BUILD_TESTS=OFF `
        -DGLFW_BUILD_DOCS=OFF `
        -DGLFW_INSTALL=OFF `
        -DGLFW_VULKAN_STATIC=OFF `
        -DBUILD_SHARED_LIBS=OFF `
        -DCMAKE_DEBUG_POSTFIX=""

    cmake --build "$PSScriptRoot/temp/glfw-3.3.8/build" --config Release

    Copy-Item -Path "$PSScriptRoot/temp/glfw-3.3.8/include/*" -Recurse -Destination "$PSScriptRoot/../include" -Container -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/glfw-3.3.8/build/*" -Include *.lib -Recurse | Copy-Item -Destination "$PSScriptRoot/../libs/" -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/glfw-3.3.8/build/*" -Include *.pdb,*.dll -Recurse | Copy-Item -Destination "$PSScriptRoot/../bins/" -Force

    Write-Output "`n============================================================================"
    Write-Output "Finish Building GLFW"
    Write-Output "============================================================================`n"

    Write-Output "`n============================================================================"
    Write-Output "Start Building GLEW"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/glew-2.2.0.zip" -Force -DestinationPath "$PSScriptRoot/temp"

    cmake $PSScriptRoot/temp/glew-2.2.0/build/cmake -B"$PSScriptRoot/temp/glew-2.2.0/new_build" `
        -DBUILD_UTILS=OFF `
        -DBUILD_SHARED_LIBS=OFF

    cmake --build "$PSScriptRoot/temp/glew-2.2.0/new_build" --config Release

    Copy-Item -Path "$PSScriptRoot/temp/glew-2.2.0/include/*" -Recurse -Destination "$PSScriptRoot/../include" -Container -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/glew-2.2.0/new_build/*" -Include *.lib -Recurse | Copy-Item -Destination "$PSScriptRoot/../libs/" -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/glew-2.2.0/new_build/*" -Include *.pdb,*.dll -Recurse | Copy-Item -Destination "$PSScriptRoot/../bins/" -Force

    Write-Output "`n============================================================================"
    Write-Output "Finish Building GLEW"
    Write-Output "============================================================================`n"

    Write-Output "`n============================================================================"
    Write-Output "Unpacking GLM"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/glm-0.9.9.8.zip" -Force -DestinationPath "$PSScriptRoot/temp"
    Copy-Item -Path "$PSScriptRoot/temp/glm/glm" -Recurse -Destination "$PSScriptRoot/../include" -Container -Force

    Write-Output "`n============================================================================"
    Write-Output "Unpacking ImGui"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/imgui-1.90.1.zip" -Force -DestinationPath "$PSScriptRoot/temp"
    Get-ChildItem -Path "$PSScriptRoot/temp/imgui-1.90.1/*" -Include *.c*,*.h* | Copy-Item -Destination "$PSScriptRoot/../include/imgui/" -Force
    Copy-Item -Path "$PSScriptRoot/temp/imgui-1.90.1/backends/" -Recurse -Destination "$PSScriptRoot/../include/imgui/" -Force

    Write-Output "`n============================================================================"
    Write-Output "Unpacking NvAPI"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/NvAPI.zip" -Force -DestinationPath "$PSScriptRoot/temp"
    Get-ChildItem -Path "$PSScriptRoot/temp/nvapi-main/*" -Include *.c*,*.h* | Copy-Item -Destination "$PSScriptRoot/../include/nvapi/" -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/nvapi-main/amd64/*" -Include *.lib -Recurse | Copy-Item -Destination "$PSScriptRoot/../libs/" -Force

} catch {
    $_
    Remove-Item -LiteralPath "$PSScriptRoot/temp" -Force -Recurse
    Remove-Item -LiteralPath "$PSScriptRoot/../bins" -Force -Recurse
    Remove-Item -LiteralPath "$PSScriptRoot/../include" -Force -Recurse
    Remove-Item -LiteralPath "$PSScriptRoot/../libs" -Force -Recurse
} finally {
    Write-Output "`n============================================================================"
    Write-Output "Finished"
    Write-Output "============================================================================"
}