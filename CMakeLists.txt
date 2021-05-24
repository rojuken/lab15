cmake_minimum_required(VERSION 2.8) #Проверка версии CMake.

set(PROJECT_NAME Lab_15) #Создаем обычную локальную переменную с именем проекта
project(${PROJECT_NAME}) # Название проекта

set(TMapTree TMapTree)
set(TMapTreeIterator TMapIterator) 
set(TNode TNode)
set(TNodeTree TNodeTree)
set(main main)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE) #Создается переменная CMAKE_CONFIGURATION_TYPES со значением "Debug;Release" и меткой/разделом Configs, переменная сохраниется в специальном файле доступном из всех файлов,
if(NOT CMAKE_BUILD_TYPE) # проверка имеющихся у компилятора вариантов сборки
  set(CMAKE_BUILD_TYPE Release) #Если нет то устанавливаем Release
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/TMapTree 
${CMAKE_CURRENT_SOURCE_DIR}/TMapTreeIterator 
${CMAKE_CURRENT_SOURCE_DIR}/TNode
${CMAKE_CURRENT_SOURCE_DIR}/TNodeTree) #Добавляем директорию "${CMAKE_CURRENT_SOURCE_DIR}/vectorlib" в дополняемые каталоги включаемых файлов
#${CMAKE_CURRENT_SOURCE_DIR} - стандартная переменная с адресом рабочей директории

add_subdirectory(gtest) #Добавляем директорию с под-CMakeList-ом, и выполняем под-CMakeList
add_subdirectory(TMapTree)
add_subdirectory(TMapTreeIterator)
add_subdirectory(TNode)
add_subdirectory(TNodeTree)
add_subdirectory(main)
add_subdirectory(test)


