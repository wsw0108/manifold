# Copyright 2020 The Manifold Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

project(manifold_test)

add_subdirectory(third_party)
add_subdirectory(meshIO)

enable_testing()

set(SOURCE_FILES polygon_test.cpp mesh_test.cpp samples_test.cpp test_main.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} polygon GTest::GTest manifold meshIO samples)

target_compile_options(${PROJECT_NAME} PRIVATE ${MANIFOLD_FLAGS})
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_14)

add_test(test_all ${PROJECT_NAME})

file(COPY data DESTINATION . FILES_MATCHING PATTERN "*.ply")

if(EMSCRIPTEN)
  set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS
    "-s ASSERTIONS=1 -s DEMANGLE_SUPPORT=1 --preload-file data --bind")
else()
endif()

if(APPLE)
  # All executables that link to CUDA need this. If you ever get
  # "CUDA driver version is insufficient for CUDA runtime version",
  # this is probably what's missing.
  set_property(TARGET ${PROJECT_NAME}
    PROPERTY
    BUILD_RPATH ${CMAKE_CUDA_IMPLICIT_LINK_DIRECTORIES})
endif()
