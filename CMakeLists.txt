
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





#find_package(MPFR REQUIRED)

add_executable(main  main.cpp   texturemanagement.cpp  newton.cpp universe.cpp fileuniverse.cpp Button.cpp  )
target_link_libraries(main  -lsfml-graphics -lsfml-window -lsfml-system -lmpfr )
# se il testing e' abilitato...
#   per disabilitare il testing, passare -DBUILD_TESTING=OFF a cmake durante la fase di configurazione
if (BUILD_TESTING)

  # aggiungi l'eseguibile statistics.t
  #add_executable(newton.t texturemanagement.cpp newton.test.cpp  newton.cpp universe.cpp fileuniverse.cpp)
  # aggiungi l'eseguibile statistics.t alla lista dei test
<<<<<<< HEAD
  add_test(NAME newton.t COMMAND newton.t)
  add_executable(distance distance.test.cpp  newton.cpp universe.cpp fileuniverse.cpp)
  add_test(NAME distance COMMAND distance.t)
  add_executable(nearest nearest.test.cpp  newton.cpp universe.cpp fileuniverse.cpp)
  add_test(NAME nearest COMMAND nearest.t)
  add_executable(energy energy.test.cpp  newton.cpp universe.cpp fileuniverse.cpp)
  add_test(NAME energy COMMAND energy.t)
  add_executable(collision collision.test.cpp  newton.cpp universe.cpp fileuniverse.cpp)
  add_test(NAME collision COMMAND collision.t)
=======
  #add_test(NAME newton.t COMMAND newton.t)

>>>>>>> 8fff33bc3f9d7b1c45bb78c19b499bae56baf825
endif()