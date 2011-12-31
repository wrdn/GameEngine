#!/bin/bash

echo -e "macro(copy_file param)\nconfigure_file(\${CMAKE_CURRENT_SOURCE_DIR}/\${param} \${PROJECT_BINARY_DIR}/GameEngine/\${CMAKE_BUILD_TYPE}/Data/\${param} COPYONLY)\nendmacro(copy_file)\n" > CMakeLists.txt

find * -print0 | while read -d $'\0' f
do
if [[ ! -d "$f" && "$f" != "$0" && "$f" != *CMakeLists* ]]
then
echo -e "copy_file(\"$f\")" >> CMakeLists.txt
fi
done
