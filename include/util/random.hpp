#ifndef UTIL_RANDOM_HPP
#define UTIL_RANDOM_HPP

#include <cstdlib>
#include <raylib.h>
#include <vector>

// Random functions

inline int randomInt(int min, int max) {
   return min + (rand() % (max - min + 1));
}

inline float randomFloat(float min, float max) {
   return min + (float)rand() / float(RAND_MAX / (max - min));
}

inline bool chance(int percent) {
   return randomInt(0, 100) <= percent;
}

inline Color randomColor(unsigned char min, unsigned char max) {
   return {
      (unsigned char)randomInt(min, max),
      (unsigned char)randomInt(min, max),
      (unsigned char)randomInt(min, max),
      255
   };
}

// Random vector access functions

template<class T>
inline T& randomVectorElement(std::vector<T> &vector) {
   return vector[randomInt(0, vector.size() - 1)];
}

template<class T>
inline const T& randomVectorElement(const std::vector<T> &vector) {
   return vector.at(randomInt(0, vector.size() - 1));
}

template<class T>
inline T& randomVectorElement(std::vector<T> &&vector) {
   return vector[randomInt(0, vector.size() - 1)];
}

#endif
