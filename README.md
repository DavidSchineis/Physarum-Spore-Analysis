# Physarum Polycephalum Spore Analysis
>A project to assist in my brother's research that detects, measures, and analyzes *P. polycephalum* spores from microscopy images implemented in C++.

## Features
* Detection of spores using OpenCV’s SimpleBlobDetector.
* Measurement of spores calibrated to scale using marked nonionic polystyrene microspheres (beads) in the microscopy images.
* Ouputs a JPEG with annotated spores.
* Filters out smudges, spores in contact, and the beads used for scaling through manual parametrization.
* Customizable detection parameters for improved accuracy.

## Physarum Polycephalum
*P. polycephalum* is a unicellular protist slime mold that is commmonly used in biology research. The research this project assists in is focused on analyzing the rate of growth and spore size variance as a result of medias with varying salinity. *P. polycephalum* spores appear as small, nearly circular blobs, sometimes overlapping. 

Learn more about *P. polycephalum* [here](https://en.wikipedia.org/wiki/Physarum_polycephalum).

## Spore Detection
* Converts the image to grayscale for better contrast.
* Uses adaptive thresholding to separate the spores from background.
* Applies filtering based on area, circularity, convexity, and inertia ratio.
* Uses a bead with known dimensions as scale calibration to convert blob sizes to real-world microns.
* Draws red circles around detected spores and labels them with their diameter size in microns.


## How to Compile and Run
Ensure OpenCV4 is installed 
```bash
brew install opencv pkg-config
```

Compile the program
```bash
g++ -std=c++17 spore_detector.cpp -o spore_detector `pkg-config --cflags --libs opencv4`
```

Run the program
```bash
./spore_detector
```
