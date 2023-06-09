cmake_minimum_required(VERSION 3.16)
project(IsoRPG VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra ")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")

#set base code files
set(CODE )

#set files to be compiled
add_executable(game.bin src/main.cpp src/gameInterface/gameInterface.cpp src/gameInterface/gameScreens.cpp src/gameInterface/widgets/widgets.cpp src/resourceLoader.cpp)

#set dependencies
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

#set link libraries 
target_link_libraries(game.bin PRIVATE sfml-graphics)

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
#
if (BUILD_TESTING)

  # aggiungi l'eseguibile gane,t
  add_executable(game.t src/test/game.test.cpp src/gameInterface/gameInterface.cpp src/gameInterface/gameScreens.cpp src/gameInterface/widgets/widgets.cpp)
  
  target_link_libraries(game.t PRIVATE sfml-graphics)
  # aggiungi l'eseguibile statistics.t alla lista dei test
  add_test(NAME game.t COMMAND game.t)

endif()

