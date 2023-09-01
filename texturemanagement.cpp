#include "Graphic.hpp"

gr::TM::TM(const std::string& str, U::FileUniverse* u) : u_{u}, s_{str} {
  loadAndAssignTextures(s_, u_);
}

void gr::TM::tm(const std::string& str, U::FileUniverse* u) {
  loadAndAssignTextures(str, u);
}

std::string gr::TM::showAllNameImages() {
  std::string s;
  for (const auto& img : texture_name_) {
    s += img + "\n";
  }
  s += ("size of vector_txe" + std::to_string(texture_vector_.size()) + "\n");
  return s;
}

void gr::TM::loadAndAssignTextures(std::string folder, U::Universe* universe) {
  /////CREATING TEXTURES' VECTOR
  if (texture_name_.size() == 0) {  ////creating the vector with the textures'
                                    /// name and loading textures only one time

    assert(texture_name_.size() == 0);
    if (std::filesystem::is_directory(folder)) {
      for (const auto& entry : std::filesystem::directory_iterator(folder)) {
        if (entry.is_regular_file() && (entry.path().extension() == ".png")) {
          texture_name_.push_back(entry.path().filename().string());
        }
      }
    } else {
      throw std::runtime_error("Not find the folder");
    }

    for (const auto& textureName : texture_name_) {
      sf::Texture texture;
      if (!texture.loadFromFile(folder + "/" + textureName)) {
        throw std::runtime_error(
            "Failed to load  a texture from the folder " +
            folder);  // Throw an exception to handle the error.
      }

      texture_vector_.push_back(texture);
    }
  }

  /////CHECKING IF ALL TEXTURES ARE LOADED
  if (texture_vector_.size() != texture_name_.size()) {
    throw std::runtime_error(
        "Not all textures are loaded");  // Throw an exception to handle the
                                         // error.
  }

  ////ASSIGNING TEXTURES TO THE PLANETS

  assert(texture_vector_.size() != 0);
  for (unsigned int i = 0; i < (universe->size()); ++i) {
    auto it = std::find(texture_name_.begin(), texture_name_.end(),
                        (*universe)[i].stringtexture);
    unsigned int idx = std::distance(texture_name_.begin(), it);

    if (idx < texture_name_.size()) {
      (*universe)[i].texture = &texture_vector_[idx];
    } else {  ////if the string chosen by the user is wrong

      std::string standardimage = "standard.png";
      ////I create a string and don't repeat the string name of the standard
      /// image / in order to have more control (no digit error)
      assert((*universe)[i].stringtexture != standardimage);
      (*universe)[i].stringtexture = standardimage;

      i--;
    }
  }
}
