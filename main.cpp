//
// Created by masuarez on 20/10/22.
//
#include <opencv2/opencv.hpp>
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace cv;
using namespace std;

using namespace std;

void PrintMatValues(Mat &mat, int size, String msg = "Check values") {
    cout << msg << endl;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Point pt(i, j);
            cout << pt << ", " << mat.at<float>(pt) << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

Mat FilterCreation(int size)
{
    // initialising standard deviation to 1.0
    double sigma = 1.0;
    double r, s = 2.0 * sigma * sigma;

    // sum is for normalization
    double sum = 0.0;

    // result
    Mat result = Mat::zeros(size, size, CV_32F);
    //PrintMatValues(result, size, "Check values 0");

    // generating size x size kernel
    for (int x = -size/2; x <= size/2; x++) {
        for (int y = -size/2; y <= size/2; y++) {
            r = sqrt(x * x + y * y);
            Point pt(x + size/2, y + size/2);
            result.at<float>(pt) = (exp(-(r * r) / s)) / (M_PI * s);
            sum += result.at<float>(pt);
        }
    }

    //PrintMatValues(result, size, "Check values 1");

    // normalization
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            Point pt = Point(i, j);
            result.at<float>(pt) = result.at<float>(pt) / sum;
        }
    }

    //PrintMatValues(result, size, "Check values 2");
    return result.clone();
}

void ApplyGaussianBlur(const Mat& mat, Mat& dest, const Mat& kernel, int size)
{
    cout << "Apply gaussian blur size: " << size << endl;
    dest = Mat::ones(mat.size[0], mat.size[1], mat.type());
    for (int x = 0; x < mat.size[0]; x++) {

    }

    /*Vec3b intensity = img.at<Vec3b>(y, x);
    uchar blue = intensity.val[0];
    uchar green = intensity.val[1];
    uchar red = intensity.val[2];*/
}

int main()
{
    //PrintMatValues(kernel_3x3, size, "Check values main");

    // Read image file
    Mat image = imread("../Blue-Lotus.jpg");

    // Check for failure
    if (image.empty())
    {
        cout << "Could not open or find the image" << endl;
        cin.get(); // wait for any key press
        return -1;
    }

    cout << "Image channels: " << image.channels() << endl;
    cout << "Image dimensions: " << image.dims << endl;
    cout << "Image type: " << image.type() << endl;
    cout << "Image size: " << image.size << endl;
    double min, max;
    cv::minMaxLoc(image, &min, &max);
    cout << "Min value: " << min << endl;
    cout << "Max value: " << max << endl;

    // Blur the image with 3x3 Gaussian kernel
    Mat image_blurred_with_3x3_kernel;
    Mat kernel_3x3 = FilterCreation(3);
    ApplyGaussianBlur(image, image_blurred_with_3x3_kernel, kernel_3x3, 3);
    //GaussianBlur(image, image_blurred_with_3x3_kernel, Size(3, 3), 0);

    // Blur the image with 5x5 Gaussian kernel
    Mat image_blurred_with_5x5_kernel;
    Mat kernel_5x5 = FilterCreation(5);
    ApplyGaussianBlur(image, image_blurred_with_5x5_kernel, kernel_5x5, 5);
    //GaussianBlur(image, image_blurred_with_5x5_kernel, Size(5, 5), 0);

    // Window's names
    String window_name = "Lotus";
    String window_name_blurred_with_3x3_kernel = "Lotus Blurred with 3 x 3 Gaussian Kernel";
    String window_name_blurred_with_5x5_kernel = "Lotus Blurred with 5 x 5 Gaussian Kernel";

    // Create windows with above names
    namedWindow(window_name);
    namedWindow(window_name_blurred_with_3x3_kernel);
    namedWindow(window_name_blurred_with_5x5_kernel);

    // Show our images inside the created windows.
    imshow(window_name, image);
    imshow(window_name_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel);
    imshow(window_name_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);

    waitKey(0); // Wait stroke
    destroyAllWindows();

    return 0;
}