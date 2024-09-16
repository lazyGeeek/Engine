#! /bin/bash
handle_error() {
  echo "An error occurred. Exiting..."
  rm -rf $ScriptDir/temp
  rm -rf $ScriptDir/../bins
  rm -rf $ScriptDir/../include 
  rm -rf $ScriptDir/../libs 
  exit 1
}

trap handle_error ERR

echo -e "\n============================================================================"
echo -e "Creating directories"
echo -e "============================================================================\n"

declare ScriptDir=$(dirname "$0")

mkdir -p $ScriptDir/../bins
mkdir -p $ScriptDir/../include
mkdir -p $ScriptDir/../include/imgui
mkdir -p $ScriptDir/../libs

echo -e "\n============================================================================"
echo -e "Start Building GLFW"
echo -e "============================================================================\n"

unzip -o $ScriptDir/glfw-3.3.8.zip -d $ScriptDir/temp > /dev/null

cmake $ScriptDir/temp/glfw-3.3.8 -B$ScriptDir/temp/glfw-3.3.8/build \
  -DSDL2_DISABLE_INSTALL=ON \
  -DSDL2_DISABLE_UNINSTALL=ON \
  -DSDL_TEST=OFF \
  -DSDL_SHARED=ON \
  -DSDL_STATIC=OFF \
  -DCMAKE_DEBUG_POSTFIX=""

cmake --build $ScriptDir/temp/glfw-3.3.8/build --config Release

cp -r $ScriptDir/temp/glfw-3.3.8/build/include/ $ScriptDir/../include
cp -r $ScriptDir/temp/glfw-3.3.8/build/include-config-/ $ScriptDir/../include
find $ScriptDir/temp/glfw-3.3.8/build \( -name '*.so' -o -name '*.dylib' -o \) -type f -exec cp '{}' $ScriptDir/../libs \;
find $ScriptDir/temp/glfw-3.3.8/build \( -name '*.a' \) -type f -exec cp '{}' $ScriptDir/../bins \;

echo -e "\n============================================================================"
echo -e "Finish Building GLFW"
echo -e "============================================================================\n"

echo -e "\n============================================================================"
echo -e "Start Building GLEW"
echo -e "============================================================================\n"

unzip -o $ScriptDir/glew-2.2.0.zip -d $ScriptDir/temp > /dev/null

cmake $ScriptDir/temp/glew-2.2.0/build/cmake -B$ScriptDir/temp/glew-2.2.0/new_build \
    -DBUILD_UTILS=OFF \
    -DBUILD_SHARED_LIBS=OFF

cmake --build $ScriptDir/temp/glew-2.2.0/new_build --config Release

cp -r $ScriptDir/temp/glew-2.2.0/include/ $ScriptDir/../include
find $ScriptDir/temp/glew-2.2.0/new_build \( -name '*.so' -o -name '*.dylib' \) -type f -exec cp '{}' $ScriptDir/../libs \;
find $ScriptDir/temp/glew-2.2.0/new_build \( -name '*.a' \) -type f -exec cp '{}' $ScriptDir/../bins \;

echo -e "\n============================================================================"
echo -e "Finish Building GLEW"
echo -e "============================================================================\n"

echo -e "\n============================================================================"
echo -e "Unpacking GLM"
echo -e "============================================================================\n"

unzip -o $ScriptDir/glm-0.9.9.8.zip -d $ScriptDir/temp > /dev/null
cp -r $ScriptDir/temp/glm/glm $ScriptDir/../include

echo -e "\n============================================================================"
echo -e "Unpacking ImGui"
echo -e "============================================================================\n"

unzip -o $ScriptDir/imgui-1.90.1.zip -d $ScriptDir/temp > /dev/null
find $ScriptDir/temp/imgui-1.90.1 \( -name '*.c*' -o -name '*.h*' \) -maxdepth 1 -type f -exec cp '{}' $ScriptDir/../include/imgui \;
cp -r $ScriptDir/temp/imgui-1.90.1/backends $ScriptDir/../include/imgui

echo -e "\n============================================================================"
echo -e "Finished"
echo -e "============================================================================"
