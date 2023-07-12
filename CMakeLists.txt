# CMakeList.txt : projet CMake pour dofus-image-breaking-enhancement, incluez la source et définissez
# la logique spécifique au projet ici.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()


set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "Vcpkg toolchain file")

project ("dofus-image-breaking-enhancement")

# Ajoutez une source à l'exécutable de ce projet.
add_executable (dofus-image-breaking-enhancement "main.cpp" "main.h" "PngEditor.cpp" "PngEditor.h" "models/images/AtelierImg.h" "utils/FileSystemUtil.h" "utils/FileSystemUtil.cpp" "TextWriter.cpp" "TextWriter.h" "models/images/FenetreBrisageImg.h" "LabelCreator.cpp" "LabelCreator.h" "models/labeling/dataset/DatasetLabel.h"  "models/labeling/images/RuneLabel.h" "models/labeling/images/Label.h" "models/labeling/images/FenetreBrisageLabel.h" "models/labeling/images/ObjetLabel.h" "models/labeling/dataset/DatasetType.h" "models/labeling/images/CoefficientLabel.h" "models/labeling/images/NormalizedLabel.h" "models/text/TextDimensions.h" "mappers/LabelMapper.h" "mappers/LabelMapper.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET dofus-image-breaking-enhancement PROPERTY CXX_STANDARD 20)
endif()

# PACKAGES
find_package(PNG REQUIRED)
target_link_libraries(dofus-image-breaking-enhancement PRIVATE PNG::PNG)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
target_link_libraries(dofus-image-breaking-enhancement PRIVATE Freetype::Freetype) # since CMake 3.10