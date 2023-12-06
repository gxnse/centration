#ifndef GRAPHHANDLER_H
#define GRAPHHANDLER_H

#include <vector>

class graphHandler {
public:
  graphHandler(bool generateGraph, int sampleToGenerate);
  ~graphHandler();

  void plotOriginalDataGraph(const std::vector<std::vector<double>>& dataToPlot);
  void plotProcessedDataGraph(const std::vector<std::vector<double>>& dataToPlot);

private:
  bool generateGraph_;
  int sampleToGenerate_;
};

#endif // GRAPHHANDLER_H