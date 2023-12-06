#include "configReader.h"       // Method for reading the program's settings
#include "dataCentration.h"     // Method for processing the data
#include "graphHandler.h"       // Method for graph building for result's evaluation

int main(int argc, char* argv[]) {

  // Create an instance of config processing class and pass the config's name
  configReader config("settings.cfg");

  // Create an instance of data processing class and pass the settings parameters
  dataCentration MITdata(config.getNumOfFingers(), config.getPipeDiameter(),
    config.getSampleDistance(), config.getNumOfSamples());

  // Derive the sensor's data from the provided file
  auto unprocessedData = MITdata.extractDataFromFile("data.txt");

  // Calculate offset pair (x,y)
  auto offsetPair = MITdata.calculateOffset(unprocessedData);

  // Derive the centered measurements
  auto processedData = MITdata.centerMeasurements(unprocessedData, offsetPair);

  // Save the centered measurements to the new .txt file
  MITdata.saveDataToFile(processedData, "new.txt");

  // Create an instance of data visualization class and pass the settings parameters
  graphHandler handler(config.isGraphGenerationEnabled(), config.getSampleToGenerate());

  // Pass the original dataset to the graph plotting function
  handler.plotOriginalDataGraph(unprocessedData);

  // Pass processed (centered) data to the graph plotting function
  handler.plotProcessedDataGraph(processedData);


  return 0;
}