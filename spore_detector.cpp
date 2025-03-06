// P. polycephalum Spore Detection

// Import libraries
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/features2d.hpp>

// Constants for scaling
const double BEAD_DIAMETER_UM = 9.7;
double um_per_px = 0.182; 

// Loads image
cv::Mat loadImage(const std::string& filename) {
    cv::Mat image = cv::imread(filename, cv::IMREAD_COLOR);
    if (image.empty()) {
        std::cerr << "Error: Could not load image " << filename << std::endl;
    }
    return image;
}

// Detects physarum blobs and ignore beads or blobs touching or on border
std::vector<cv::KeyPoint> detectBlobs(const cv::Mat& image) {
    
    // Grayscale conversion
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Parameters
    cv::SimpleBlobDetector::Params params;
    params.filterByArea = true;
    params.minArea = 250;   //100
    params.maxArea = 15000; // 
    params.filterByCircularity = true;
    params.minCircularity = 0.6;    //0.75
    params.filterByConvexity = true;
    params.minConvexity = 0.8;  //0.8
    params.filterByInertia = true;
    params.minInertiaRatio = 0.6;   // 0.6

    // Create vector of points
    cv::Ptr<cv::SimpleBlobDetector> detector = cv::SimpleBlobDetector::create(params);
    std::vector<cv::KeyPoint> keypoints;
    detector->detect(gray, keypoints);
    return keypoints;
}

// Draw detected blobs with diameter labels
void annotateBlobs(cv::Mat& image, std::vector<cv::KeyPoint> keypoints) {
    for (const auto& kp : keypoints) {
        cv::Point center(static_cast<int>(kp.pt.x), static_cast<int>(kp.pt.y));
        double size_um = kp.size * um_per_px;
        
        // Draw red circle around blob
        cv::circle(image, center, static_cast<int>(kp.size / 2), cv::Scalar(0, 0, 255), 2);
        
        // Label diameter in microns
        std::string text = std::to_string(size_um).substr(0, 4) + " microns";
        cv::putText(image, text, cv::Point(center.x + 5, center.y - 5), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 0), 2);
    }
}

// Work in progress
// Manually define the bead's location for scale calibration
double calibrateScale(cv::Mat& image, cv::Point beadCenter) {
    int beadRadius = 0;
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    // Create mask around bead
    cv::Mat mask = cv::Mat::zeros(gray.size(), CV_8UC1);
    cv::circle(mask, beadCenter, 10, cv::Scalar(255), -1);

    // Find contours to get bead size
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(mask, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    if (!contours.empty()) {
        cv::Point2f center;
        float radius;
        cv::minEnclosingCircle(contours[0], center, radius);
        beadRadius = static_cast<int>(radius);
    }

    double beadDiameterPx = beadRadius * 2.0;
    return BEAD_DIAMETER_UM / beadDiameterPx;
}

// Main function
int main() {
    std::string fileName = "image1.jpg"; 
    cv::Mat image = loadImage(fileName);
    if (image.empty()) return -1;

    // Work in progress
    // Compute scale in μm/px from manually defining the bead's location
    /* cv::Point beadCenter(750, 300);
    um_per_px = calibrateScale(image, beadCenter);
    std::cout << "Scale: " << um_per_px << " μm/px" << std::endl; */

    // Detect blobs
    std::vector<cv::KeyPoint> keypoints = detectBlobs(image);

    // Annotate blobs
    annotateBlobs(image, keypoints);

    // Show and save output image
    cv::imshow("Physarum Spores", image);
    cv::imwrite("Physarum.jpg", image);

    // Press 'Q' or 'ESC' to quit program
    while (true) {
        char key = cv::waitKey(0);
        if (key == 'q' || key == 27) { 
            break;
        }
    }
    cv::destroyAllWindows(); 

    return 0;
}
