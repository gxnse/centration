#include "dataCentration.h"
#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>

using namespace std;

// Constructor
dataCentration::dataCentration(int fingers, double diameter, double distance, int samples)
  : numOfFingers(fingers), pipeDiameter(diameter), sampleDistance(distance), numOfSamples(samples) {}

// Checks if the parameters provided in config are valid and in accordance with dataset
void dataCentration::validateSettings(int numFingersData, int numSamplesData) {
  if (numOfFingers != static_cast<int>(numFingersData) || numOfSamples != static_cast<int>(numSamplesData)) {
    throw std::invalid_argument("Invalid settings: Number of fingers or samples do not match dataset dimensions.");
  }
}

// Function to extract the sensor data
vector<vector<double>> dataCentration::extractDataFromFile(const string& filename) {
  vector<vector<double>> data;

  ifstream file("../data/" + filename);
  if (!file.is_open()) {
    cerr << "Error opening file: " << filename << endl;
    return data;
  }

  // Read each line from the file
  string line;
  while (getline(file, line)) {
    vector<double> row;
    istringstream iss(line);
    double value;

    // Read each value from the line and store it in the row vector
    while (iss >> value) {
      row.push_back(value);
    }

    // Add the row to the data vector
    data.push_back(row);
  }

  file.close();

  // Validates the settings with the dataset
  try {
    size_t actualNumOfFingers = data[0].size();
    size_t actualNumOfSamples = data.size();
    validateSettings(actualNumOfFingers, actualNumOfSamples);
    cout << "The parameters in the settings are set in accordance with the provided dataset." << endl;
  } catch (const std::exception& e) {
    std::cerr << "Warning! " << e.what() << std::endl;
  }

  return data;
}

// Function to calculate the offset
std::pair<double, double> dataCentration::calculateOffset(const vector<vector<double>>& measurementData) {

  // The measurements' first sample is at index 0
  const std::vector<double>& firstSampleData = measurementData[0];

  // Find the max and min fingers' lengths (the sum of which describes the diameter of the pipe)
  double maxFingersLength = *std::max_element(firstSampleData.begin(), firstSampleData.end());
  double minFingersLength = *std::min_element(firstSampleData.begin(), firstSampleData.end());

  // Find the index of the max and min fingers' lengths
  size_t maxFingersLengthIndex = std::distance(firstSampleData.begin(), std::max_element(firstSampleData.begin(), firstSampleData.end()));
  size_t minFingersLengthIndex = std::distance(firstSampleData.begin(), std::min_element(firstSampleData.begin(), firstSampleData.end()));

  // Tool's position calculation (converting from polar to Cartesian coordinates)
  double toolsTheta = (2 * M_PI * minFingersLengthIndex / numOfFingers);    // Angle (theta) in [rad]
  double toolsPositionX = minFingersLength * cos(toolsTheta);               // x=r*cos(theta)
  double toolsPositionY = minFingersLength * sin(toolsTheta);               // y=r*sin(theta)

  std::cout << "The position of the MIT Caliper: X = " << toolsPositionX << " Y = " << toolsPositionY << std::endl;

  // Offset's calculation
  double offsetX = ((maxFingersLength - minFingersLength) / 2) * cos(toolsTheta);
  double offsetY = ((maxFingersLength - minFingersLength) / 2) * sin(toolsTheta);

  std::cout << "The derived offset: X = " << offsetX << " Y = " << offsetY << std::endl;

  return std::make_pair(offsetX, offsetY);
}


// Function to centre the measurements
std::vector<std::vector<double>> dataCentration::centerMeasurements(
  const std::vector<std::vector<double>>& measurementData, const std::pair<double, double>& offset) {

  // Create a copy of the input data to avoid modifying the original
  std::vector<std::vector<double>> centeredMeasurements = measurementData;

  // Iteration through rows of fingers & columns of samples
  for (size_t sampleID = 0; sampleID < numOfSamples; sampleID++) {
    for (size_t fingerID = 0; fingerID < numOfFingers; fingerID++) {

      // Converting from polar to Cartesian coordinates & considering offset
      double lengthOfFinger = centeredMeasurements[sampleID][fingerID];
      double theta = (2 * M_PI * fingerID / numOfFingers);                        // Angle (theta) in [rad]
      double fingersCentralizedX = lengthOfFinger * cos(theta) + offset.first;   // x=r*cos(theta)+offsetX
      double fingersCentralizedY = lengthOfFinger * sin(theta) + offset.second;  // y=r*sin(theta)+offsetY

      // Updating a new vector of vectors with centralized measurements
      centeredMeasurements[sampleID][fingerID] = sqrt(pow(fingersCentralizedX, 2) + pow(fingersCentralizedY, 2));
    }
  }

  std::cout << "The measurements have been centralized." << std::endl;

  return centeredMeasurements;
}


// Function to save data to a file
void dataCentration::saveDataToFile(const vector<vector<double>>& data, const string& filename) {
  ofstream file("../data/" + filename);
  if (!file.is_open()) {
    cerr << "Error opening file for writing: " << filename << endl;
    return;
  }

  // Write each row to the file
  for (const auto& row : data) {
    for (double value : row) {
      file << value << " ";
    }
    file << endl;
  }

  file.close();

  std::cout << "The centralized measurements have been save to the ../data/" << filename << std::endl;
}