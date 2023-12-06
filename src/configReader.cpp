#include "configReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

configReader::configReader(const std::string& filename) {
  if (!loadConfigFromFile(filename)) {
    std::cerr << "Error: Unable to load " << filename << " !" << std::endl;
  } else {
    std::cout << "The settings have been loaded from ../settings/" << filename << std::endl;
  }
}


bool configReader::loadConfigFromFile(const std::string& filename) {
  std::ifstream configFile("../settings/" + filename);

  std::string line;
  while (std::getline(configFile, line)) {
    std::istringstream iss(line);
    std::string key, value;

    if (!(iss >> key >> value)) {
      // Failed to extract key and config parameter from the line
      std::cerr << "Error: Unable to parse a line: " << line << " !" << std::endl;
      continue;
    }

    // Process key and value
    if (key == "Number_of_fingers") {
      numOfFingers = std::stoi(value);
    }
    else if (key == "Diameter_of_a_pipe") {
      pipeDiameter = std::stod(value);
    }
    else if (key == "Distance_between_samples_along_pipe") {
      sampleDistance = std::stod(value);
    }
    else if (key == "Number_of_samples_along_pipe") {
      numOfSamples = std::stoi(value);
    }
    else if (key == "Flag_activating_plotting_function") {
      generateGraph = static_cast<bool>(std::stoi(value));
    }
    else if (key == "ID_of_the_sample_to_be_plotted") {
      sampleToGenerate = std::stoi(value);
    }
  }

  configFile.close();
  return true;
}

int configReader::getNumOfFingers() const {
  return numOfFingers;
}

double configReader::getPipeDiameter() const {
  return pipeDiameter;
}

double configReader::getSampleDistance() const {
  return sampleDistance;
}

int configReader::getNumOfSamples() const {
  return numOfSamples;
}

bool configReader::isGraphGenerationEnabled() const {
  return generateGraph;
}

int configReader::getSampleToGenerate() const {
  return sampleToGenerate;
}