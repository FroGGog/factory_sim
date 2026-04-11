#include "mngr/sound.hpp"
#include "util/random.hpp"
#include <filesystem>
#include <unordered_map>

// Constants

constexpr float soundPitchMin = 0.95f;
constexpr float soundPitchMax = 1.05f;

// Globals

static std::unordered_map<std::string, std::vector<std::string>> savedSounds;
static std::unordered_map<std::string, Sound> sounds;

// Load functions

void loadSound(const std::string &name, const std::string &path) {
   Sound newSound = LoadSound(path.c_str());
   sounds[name] = newSound;
}

void saveSound(const std::string &name, const std::vector<std::string> &soundList) {
   savedSounds[name] = soundList;
}

void loadSounds() {
   std::filesystem::create_directories("assets/sounds/"); // Create if not exists
   for (const auto &file: std::filesystem::recursive_directory_iterator("assets/sounds/")) {
      if (file.is_regular_file()) {
         std::string name = file.path().stem().string();
         std::string path = file.path().string();
         loadSound(name, path);
      }
   }
}

void loadSavedSounds() {
   // Save sounds that use multiple random sounds in one here
}

// Play functions

void playSound(const std::string &name, float volume) {
   if (!savedSounds.count(name) && !sounds.count(name)) {
      printf("Sound '%s' does not exist.\n", name.c_str());
      return; // Do not crash the program because of a sound!
   }

   Sound sound;
   if (savedSounds.count(name)) {
      std::vector<std::string> &pool = savedSounds[name];
      std::string &randomName = randomVectorElement(pool);
      sound = sounds[randomName];
   } else {
      sound = sounds[name];
   }

   float pitch = randomFloat(soundPitchMin, soundPitchMax);
   SetSoundPitch(sound, pitch);
   SetSoundVolume(sound, volume);
   PlaySound(sound);
}
