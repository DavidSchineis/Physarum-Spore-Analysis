# Physarum Polycephalum Spore Analysis
>A project to assist in my brother's research that detects, measures, and analyzes *P. polycephalum* spores from microscopy images implemented in C++.

## Features
* Automatic detection of spores using OpenCV’s SimpleBlobDetector.
* Measurement of spores calibrated to scale using marked nonionic polystyrene microspheres (beads) in the microscopy images.
* Annotated image output as a JPEG with labeled spore diameter sizes.
* Filters out smudges, spores in contact, and beads through manual parametrization.
* Customizable detection parameters for improved accuracy.

## How Blob Detection Works
Physarum spores appear as **small, nearly circular blobs**, sometimes touching. This program:
1. Converts the image to **grayscale** for better contrast.
2. Applies **blob detection**, filtering based on:
   - **Size**
   - **Circularity**
   - **Convexity** (to merge touching spores)
3. Uses a **9.7μm bead as scale calibration** to convert blob sizes to real-world microns.
4. Draws **red circles** around detected spores and labels them with their **size in μm**.

### 

---

## How to Run
### **1️⃣ Install Dependencies**
#### **MacOS (via Homebrew)**
```bash
brew install opencv pkg-config
