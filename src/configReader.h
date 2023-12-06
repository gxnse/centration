#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>

class configReader {
public:
  configReader(const std::string& filename);              // Constructor for config processing
  bool loadConfigFromFile(const std::string& filename);   // Function processing settings config

  // Getters for data processing returning settings parameters
  int getNumOfFingers() const;
  double getPipeDiameter() const;
  double getSampleDistance() const;
  int getNumOfSamples() const;

  // Getters for graph handler returning settings parameters
  bool isGraphGenerationEnabled() const;
  int getSampleToGenerate() const;

private:
  // For configuration of data processing algorithm
  int numOfFingers;       // Number of fingers
  double pipeDiameter;    // Diameter of a pipe in [mm]
  double sampleDistance;  // Distance between samples along pipe in [mm]
  int numOfSamples;       // Number of samples along pipe

  // For configuration of results plotting method
  bool generateGraph;     // Flag activating results graph plotting function
  int sampleToGenerate;   // ID of sample to be plotted
};

#endif // CONFIGREADER_H