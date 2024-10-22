#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

struct Image {
    std::vector<uint8_t> data;
    int width;
    int height;
    int pts; // Presentation Time Stamp

    Image(int w, int h, int pts) : width(w), height(h), pts(pts) {
        data.resize(w * h * 3); 
    }
};

class Watermark {
public:
    Watermark(const std::string& text) : text_(text), running_(false) {}

    void start() {
        if (!running_) {
            running_ = true;
            std::cout << "Watermark started.\n";
        }
    }

    void stop() {
        if (running_) {
            running_ = false;
            std::cout << "Watermark stopped.\n";
        }
    }

    Image processImage(const Image& inputImage) {
        if (!running_) {
            std::cerr << "Watermark is not running!\n";
            return inputImage;
        }

        Image outputImage = inputImage;

        std::cout << "Processing image with PTS: " << inputImage.pts << "\n";
        std::cout << "Adding watermark: " << text_ << "\n";

        return outputImage;
    }

private:
    std::string text_;
    bool running_;
};

class WatermarkFactory {
public:
    static Watermark* createWatermark(const std::string& text) {
        return new Watermark(text);
    }

    static void deleteWatermark(Watermark* watermark) {
        delete watermark;
    }
};

int main() {
    Watermark* wm = WatermarkFactory::createWatermark("Sample Watermark");

    wm->start();

    Image img(1920, 1080, 12345);

    Image outputImage = wm->processImage(img);

    wm->stop();

    WatermarkFactory::deleteWatermark(wm);

    return 0;
}
