# Physarum Polycephalum Spore Analysis
>A project to assist in my brother's research that detects, measures, and analyzes *P. polycephalum* spores from microscopy images implemented in C++.

## Features
* Automatic detection of spores using OpenCV’s SimpleBlobDetector.
* Measurement of spores calibrated to scale using marked nonionic polystyrene microspheres (beads) in the microscopy images.
* Annotated image output as a JPEG with labeled spore diameter sizes.
* Filters out smudges, spores in contact, and beads through manual parametrization.
* Customizable detection parameters for improved accuracy.

## Physarum Polycephalum
*P. polycephalum* is a slime mold that is commmonly referred to as the blob. 

## Blob Detection
*P. polycephalum* spores appear as small, nearly circular blobs, sometimes touching. This program:
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
