
#cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

cmake_minimum_required(VERSION 3.16)
project(planets VERSION 0.1.0)

# abilita il supporto per i test, tra cui l'opzione BUILD_TESTING usata sotto
include(CTest)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# richiedi l'uso di C++17, senza estensioni non-standard offerte dal compilatore usato 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

# abilita warning
string(APPEND CMAKE_CXX_FLAGS " -Wall -Wextra")

# abilita l'address sanitizer e l'undefined-behaviour sanitizer in debug mode
string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")
string(APPEND CMAKE_EXE_LINKER_FLAGS_DEBUG " -fsanitize=address,undefined -fno-omit-frame-pointer")



add_executable(main  main.cpp  drawing.cpp texturemanagement.cpp  newton.cpp universe.cpp fileuniverse.cpp Button.cpp  )
target_link_libraries(main  -lsfml-graphics -lsfml-window -lsfml-system mpfr )

# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione

if (BUILD_TESTING)

add_executable(all.t tests/all.test.cpp tests/distance.test.cpp tests/newton.test.cpp tests/nearest.test.cpp tests/file.test.cpp tests/energy.test.cpp tests/collision.test.cpp drawing.cpp texturemanagement.cpp  newton.cpp universe.cpp fileuniverse.cpp Button.cpp )

#add_executable(all.t tests/all.test.cpp  tests/distance.test.cpp tests/newton.test.cpp tests/nearest.test.cpp tests/file.test.cpp tests/energy.test.cpp tests/collision.test.cpp drawing.cpp texturemanagement.cpp  newton.cpp universe.cpp fileuniverse.cpp Button.cpp )
#add_executable(all.t tests/all.test.cpp  tests/distance.test.cpp  drawing.cpp texturemanagement.cpp  newton.cpp universe.cpp fileuniverse.cpp Button.cpp )

target_link_libraries(all.t  -lsfml-graphics -lsfml-window -lsfml-system mpfr)
add_test(NAME all.t COMMAND all.t)

endif()