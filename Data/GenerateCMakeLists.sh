#!/bin/bash

echo -e "macro(copy_file src dst_dir)\nconfigure_file(\${CMAKE_CURRENT_SOURCE_DIR}/\${src} \${dst_dir}/Data/\${src} COPYONLY)\nendmacro(copy_file)\n" > CMakeLists.txt

find * -print0 | while read -d $'\0' f
do
if [[ ! -d "$f" && "$f" != "$0" && "$f" != *CMakeLists* && "$f" != *~ ]]
then
#echo -e "copy_file(\"$f\" \"\${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\")" >> CMakeLists.txt
echo -e "copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/Debug\")" >> CMakeLists.txt # copy to Debug
echo -e "copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/Release\")" >> CMakeLists.txt # copy to Release

echo -e "IF(\${CMAKE_SYSTEM_NAME} MATCHES \"Windows\")\ncopy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/src/\")\nENDIF(\${CMAKE_SYSTEM_NAME} MATCHES \"Windows\")" >> CMakeLists.txt # copy for visual studio to build/src directory

fi
done
