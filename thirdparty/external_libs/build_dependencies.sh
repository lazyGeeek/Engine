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
mkdir -p $ScriptDir/../libs

echo -e "\n============================================================================"
echo -e "Start Building SDL2"
echo -e "============================================================================\n"

unzip -o $ScriptDir/SDL2-2.28.5.zip -d $ScriptDir/temp > /dev/null

cmake $ScriptDir/temp/SDL2-2.28.5 -B$ScriptDir/temp/SDL2-2.28.5/build \
  -DSDL2_DISABLE_INSTALL=ON \
  -DSDL2_DISABLE_UNINSTALL=ON \
  -DSDL_TEST=OFF \
  -DSDL_SHARED=ON \
  -DSDL_STATIC=OFF \
  -DCMAKE_DEBUG_POSTFIX=""

cmake --build $ScriptDir/temp/SDL2-2.28.5/build --config Release

cp -r $ScriptDir/temp/SDL2-2.28.5/build/include/ $ScriptDir/../include
cp -r $ScriptDir/temp/SDL2-2.28.5/build/include-config-/ $ScriptDir/../include
find $ScriptDir/temp/SDL2-2.28.5/build \( -name '*.lib' -o -name '*.dylib' \) -type f -exec cp '{}' $ScriptDir/../libs \;
find $ScriptDir/temp/SDL2-2.28.5/build \( -name '*.pdb' -o -name '*.a' \) -type f -exec cp '{}' $ScriptDir/../bins \;

echo -e "\n============================================================================"
echo -e "Finish Building SDL2"
echo -e "============================================================================\n"

echo -e "\n============================================================================"
echo -e "Unpacking GLM"
echo -e "============================================================================\n"

unzip -o $ScriptDir/glm-0.9.9.8.zip -d $ScriptDir/temp > /dev/null
cp -r $ScriptDir/temp/glm/glm $ScriptDir/../include

echo -e "\n============================================================================"
echo -e "Finished"
echo -e "============================================================================"
