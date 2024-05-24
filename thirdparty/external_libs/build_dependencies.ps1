Write-Output "============================================================================"
Write-Output "Creating directories"
Write-Output "============================================================================`n"

New-Item -Path "$PSScriptRoot/" -Name "../bins" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../include" -ItemType Directory -Force
New-Item -Path "$PSScriptRoot/" -Name "../libs" -ItemType Directory -Force

try {
    Write-Output "`n============================================================================"
    Write-Output "Start Building SDL2"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/SDL2-2.28.5.zip" -Force -DestinationPath "$PSScriptRoot/temp"

    cmake $PSScriptRoot/temp/SDL2-2.28.5 -B"$PSScriptRoot/temp/SDL2-2.28.5/build" `
        -DSDL2_DISABLE_INSTALL=ON `
        -DSDL2_DISABLE_UNINSTALL=ON `
        -DSDL_TEST=OFF `
        -DSDL_SHARED=ON `
        -DSDL_STATIC=OFF `
        -DCMAKE_DEBUG_POSTFIX=""

    cmake --build "$PSScriptRoot/temp/SDL2-2.28.5/build" --config Release

    Copy-Item -Path "$PSScriptRoot/temp/SDL2-2.28.5/build/include/*" -Recurse -Destination "$PSScriptRoot/../include/" -Container -Force
    Copy-Item -Path "$PSScriptRoot/temp/SDL2-2.28.5/build/include-config-release/*" -Recurse -Destination "$PSScriptRoot/../include/" -Container -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/SDL2-2.28.5/build/*" -Include *.lib -Recurse | Copy-Item -Destination "$PSScriptRoot/../libs/" -Force
    Get-ChildItem -Path "$PSScriptRoot/temp/SDL2-2.28.5/build/*" -Include *.pdb,*.dll -Recurse | Copy-Item -Destination "$PSScriptRoot/../bins/" -Force

    Write-Output "`n============================================================================"
    Write-Output "Finish Building SDL2"
    Write-Output "============================================================================`n"

    Write-Output "`n============================================================================"
    Write-Output "Unpacking GLM"
    Write-Output "============================================================================`n"

    Expand-Archive "$PSScriptRoot/glm-0.9.9.8.zip" -Force -DestinationPath "$PSScriptRoot/temp"
    Copy-Item -Path "$PSScriptRoot/temp/glm/glm" -Recurse -Destination "$PSScriptRoot/../include" -Container -Force

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