#!/bin/bash

echo -e "macro(copy_file param)\nconfigure_file(\${CMAKE_CURRENT_SOURCE_DIR}/\${param} \${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Data/\${param} COPYONLY)\nendmacro(copy_file)\n" > CMakeLists.txt

find * -print0 | while read -d $'\0' f
do
if [[ ! -d "$f" && "$f" != "$0" && "$f" != *CMakeLists* && "$f" != *~ ]]
then
echo -e "copy_file(\"$f\")" >> CMakeLists.txt
fi
done
