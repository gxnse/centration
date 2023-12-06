#ifndef DATACENTRATION_H
#define DATACENTRATION_H

#include <vector>
#include <string>

using namespace std;

class dataCentration {

public:
  // Constructor of the class
  dataCentration(int fingers, double diameter, double distance, int samples);

  // Function that extracts data from a text file and stores it into the vector of vectors
  vector<vector<double>> extractDataFromFile(const std::string& filename);

  // Function to calculate an offset pair (x,y)
  std::pair<double, double> calculateOffset(const vector<vector<double>>& originalLengths);

  // Function to centre the measurements
  std::vector<std::vector<double>> centerMeasurements(
    const std::vector<std::vector<double>>& measurementData,
      const std::pair<double, double>& offset);

  // Function to save the processed data
  void saveDataToFile(const vector<vector<double>>& data, const string& filename);

private:
  // Checks if the parameters provided in config are valid
  void validateSettings(int numFingersData, int numSamplesData);

  // Parameters used in measurements' centration
  int numOfFingers;       // Number of fingers
  int numOfSamples;       // Number of samples along pipe
  double pipeDiameter;    // Diameter of a pipe in [mm]
  double sampleDistance;  // Distance between samples along pipe in [mm]

};

#endif // DATACENTRATION_H
