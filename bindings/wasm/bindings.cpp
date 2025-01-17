// Copyright 2022 The Manifold Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <emscripten/bind.h>

using namespace emscripten;

#include <manifold.h>

using namespace manifold;

Manifold Union(Manifold& a, Manifold& b) { return a + b; }
void Add(Manifold& a, Manifold& b) { a += b; }

Manifold Difference(Manifold& a, Manifold& b) { return a - b; }
void Subtract(Manifold& a, Manifold& b) { a -= b; }

Manifold Intersection(Manifold& a, Manifold& b) { return a ^ b; }
void Intersect(Manifold& a, Manifold& b) { a ^= b; }

EMSCRIPTEN_BINDINGS(whatever) {
  value_object<glm::ivec3>("ivec3")
      .field("0", &glm::ivec3::x)
      .field("1", &glm::ivec3::y)
      .field("2", &glm::ivec3::z);

  register_vector<glm::ivec3>("Vector_ivec3");

  value_object<glm::vec3>("vec3")
      .field("x", &glm::vec3::x)
      .field("y", &glm::vec3::y)
      .field("z", &glm::vec3::z);

  register_vector<glm::vec3>("Vector_vec3");

  value_object<glm::vec4>("vec4")
      .field("x", &glm::vec4::x)
      .field("y", &glm::vec4::y)
      .field("z", &glm::vec4::z)
      .field("w", &glm::vec4::w);

  register_vector<glm::vec4>("Vector_vec4");

  value_object<Mesh>("Mesh")
      .field("vertPos", &Mesh::vertPos)
      .field("triVerts", &Mesh::triVerts)
      .field("vertNormal", &Mesh::vertNormal)
      .field("halfedgeTangent", &Mesh::halfedgeTangent);

  class_<Manifold>("Manifold")
      .constructor<Mesh>()
      .function("Add", &Add)
      .function("Subtract", &Subtract)
      .function("Intersect", &Intersect)
      .function("GetMesh", &Manifold::GetMesh);

  function("Union", &Union);
  function("Difference", &Difference);
  function("Intersection", &Intersection);
}
