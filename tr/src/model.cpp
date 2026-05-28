#include "model.h"
#include <fstream>
#include <sstream>

Model::Model(const std::string filename) {
  std::ifstream in(filename);
  if (!in.is_open())
    return;

  std::string line;
  while (std::getline(in, line)) {
    std::istringstream iss(line);
    std::string tag;
    iss >> tag;
    if (tag == "v") {
      vec3 v;
      iss >> v.x >> v.y >> v.z;
      verts.push_back(v);
    } else if (tag == "f") {
      std::string tok;
      while (iss >> tok) {
        int vi = 0;
        std::sscanf(tok.c_str(), "%d", &vi);
        facet_vrt.push_back(vi - 1);
      }
    }
  }
}

int Model::nverts() const { return static_cast<int>(verts.size()); }
int Model::nfaces() const { return static_cast<int>(facet_vrt.size() / 3); }

vec3 Model::vert(const int i) const { return verts[i]; }
vec3 Model::vert(const int iface, const int nthvert) const {
  return verts[facet_vrt[iface * 3 + nthvert]];
}
