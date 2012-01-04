#!/bin/bash

echo -e "macro(copy_file src dst_dir)
configure_file(\${CMAKE_CURRENT_SOURCE_DIR}/\${src} \${dst_dir}/Data/\${src} COPYONLY)
endmacro(copy_file)" > CMakeLists.txt

find * -print0 | while read -d $'\0' f
do
if [[ ! -d "$f" && "$f" != "$0" && "$f" != *CMakeLists* && "$f" != *~ ]]
then

# copy to Debug and Release
echo -e "\n###### File: \"$f\"\ncopy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/Debug\")
copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/Release\")\n" >> CMakeLists.txt

# copy to src/ and all the directories VS can create builds for: Debug, Release (above), plus MinSizeRel and RelWithDebInfo
echo -e "IF(\${CMAKE_SYSTEM_NAME} MATCHES \"Windows\")
copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/src/\")
copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/MinSizeRel/\")
copy_file(\"$f\" \"\${PROJECT_BINARY_DIR}/\${PROJECT_NAME}/RelWithDebInfo/\")
ENDIF(\${CMAKE_SYSTEM_NAME} MATCHES \"Windows\")\n######" >> CMakeLists.txt

#echo -e "copy_file(\"$f\" \"\${CMAKE_RUNTIME_OUTPUT_DIRECTORY}\")" >> CMakeLists.txt # OLD

fi
done
