#include "graphHandler.h"
#include <Python.h>
#include <sstream>
#include <iostream>
#include <cmath>

graphHandler::graphHandler(bool generateGraph, int sampleToGenerate)
  : generateGraph_(generateGraph), sampleToGenerate_(sampleToGenerate) {
  if (generateGraph_) {
    Py_Initialize();
  }
}

graphHandler::~graphHandler() {
  if (generateGraph_) {
    Py_Finalize();
  }
}

void graphHandler::plotOriginalDataGraph(const std::vector<std::vector<double>>& dataToPlot) {
  if (generateGraph_) {
    std::cout << "The graph with original data has been plotteed. Generated sample number: " << sampleToGenerate_ << std::endl;

    // Ensure sampleToGenerate_ is a valid index
    if (sampleToGenerate_ < 0 || sampleToGenerate_ >= dataToPlot.size()) {
      std::cerr << "Invalid sampleToGenerate_ index." << std::endl;
      return;
    }

    const std::vector<double>& lengths = dataToPlot[sampleToGenerate_];

    // Check if there are enough values in the selected row
    if (lengths.size() < 40) {
      std::cerr << "Insufficient data for plotting." << std::endl;
      return;
    }

    // Calculate Cartesian coordinates from polar coordinates with an offset
    std::vector<double> x, y;
    for (int i = 0; i < 40; ++i) {
      double angle = 2.0 * M_PI * i / 40.0;
      double x_coord = lengths[i] * std::cos(angle);
      double y_coord = lengths[i] * std::sin(angle);

      x.push_back(x_coord);
      y.push_back(y_coord);
    }

    // Construct the Python code for plotting
    std::string pythonCode = "import matplotlib.pyplot as plt\n"
      "import numpy as np\n"
      "theta = np.linspace(0, 2*np.pi, 40, endpoint=False)\n"
      "x = np.array([";

    for (int i = 0; i < 40; ++i) {
      pythonCode += std::to_string(x[i]);
      if (i < 39) pythonCode += ", ";
    }

    pythonCode += "])\n"
      "y = np.array([";

    for (int i = 0; i < 40; ++i) {
      pythonCode += std::to_string(y[i]);
      if (i < 39) pythonCode += ", ";
    }

    pythonCode += "])\n"
      "plt.plot(x, y, marker='o')\n"
      "plt.scatter(0, 0, color='red')  # Plot the center point\n";

    // Draw lines from the center point to each blue point
    for (int i = 0; i < 40; ++i) {
      pythonCode += "plt.plot([0, " + std::to_string(x[i]) + "], [0, " + std::to_string(y[i]) + "], color='gray', linestyle='--')\n";
    }

    pythonCode += "plt.xlabel('X-axis')\n"
      "plt.ylabel('Y-axis')\n"
      "plt.title('Plot of the original dataset')\n"
      "plt.show()";

    // Convert the C++ string to a C-style string for PyRun_SimpleString
    const char* cPythonCode = pythonCode.c_str();

    // Execute the Python code
    PyRun_SimpleString(cPythonCode);
  }
}


void graphHandler::plotProcessedDataGraph(const std::vector<std::vector<double>>& dataToPlot) {
  if (generateGraph_) {
    std::cout << "The graph with centered data has been plotteed. Generated sample number: " << sampleToGenerate_ << std::endl;

    // Ensure sampleToGenerate_ is a valid index
    if (sampleToGenerate_ < 0 || sampleToGenerate_ >= dataToPlot.size()) {
      std::cerr << "Invalid sampleToGenerate_ index." << std::endl;
      return;
    }

    const std::vector<double>& lengths = dataToPlot[sampleToGenerate_];

    // Check if there are enough values in the selected row
    if (lengths.size() < 40) {
      std::cerr << "Insufficient data for plotting." << std::endl;
      return;
    }

    // Calculate Cartesian coordinates from polar coordinates with an offset
    std::vector<double> x, y;
    for (int i = 0; i < 40; ++i) {
      double angle = 2.0 * M_PI * i / 40.0;
      double x_coord = lengths[i] * std::cos(angle);
      double y_coord = lengths[i] * std::sin(angle);

      x.push_back(x_coord);
      y.push_back(y_coord);
    }

    // Construct the Python code for plotting
    std::string pythonCode = "import matplotlib.pyplot as plt\n"
      "import numpy as np\n"
      "theta = np.linspace(0, 2*np.pi, 40, endpoint=False)\n"
      "x = np.array([";

    for (int i = 0; i < 40; ++i) {
      pythonCode += std::to_string(x[i]);
      if (i < 39) pythonCode += ", ";
    }

    pythonCode += "])\n"
      "y = np.array([";

    for (int i = 0; i < 40; ++i) {
      pythonCode += std::to_string(y[i]);
      if (i < 39) pythonCode += ", ";
    }

    pythonCode += "])\n"
      "plt.plot(x, y, marker='o')\n"
      "plt.scatter(0, 0, color='red')  # Plot the center point\n";

    // Draw lines from the center point to each blue point
    for (int i = 0; i < 40; ++i) {
      pythonCode += "plt.plot([0, " + std::to_string(x[i]) + "], [0, " + std::to_string(y[i]) + "], color='gray', linestyle='--')\n";
    }

    pythonCode += "plt.xlabel('X-axis')\n"
      "plt.ylabel('Y-axis')\n"
      "plt.title('Plot of the processed dataset')\n"
      "plt.show()";

    // Convert the C++ string to a C-style string for PyRun_SimpleString
    const char* cPythonCode = pythonCode.c_str();

    // Execute the Python code
    PyRun_SimpleString(cPythonCode);
  }
}
