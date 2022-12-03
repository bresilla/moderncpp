#include <fmt/core.h>

#include <chrono>
#include <iostream>
#include <map>
#include <opencv2/opencv.hpp>
#include <random>
#include <vector>

class Pixel {
public:
  uchar b, g, r; // 8 bit, 0-255
  Pixel(uchar b, uchar g, uchar r) {
    this->b = b;
    this->g = g;
    this->r = r;
  }
};

template <> struct fmt::formatter<Pixel> {
  formatter<int> int_formatter;
  template <typename ParseContext> constexpr auto parse(ParseContext &ctx) {
    return ctx.begin();
  }
  template <typename FormatContext>
  auto format(const Pixel &pixel, FormatContext &ctx) {
    return format_to(ctx.out(), "rgb({},{},{})", pixel.r, pixel.g, pixel.b);
  }
};

class KMeans {
private:
  std::vector<Pixel> clusterCentres;
  std::vector<int> clusterCentres_int;
  std::map<Pixel, int> clusterCount;
  cv::Mat image;
  int K;

public:
  cv::Mat labels;
  // Intialise cluster centres as random pixels from the image
  KMeans(cv::Mat image, int K) {
    this->image = image;
    this->K = K;
    labels = cv::Mat::zeros(cv::Size(image.cols, image.rows), CV_8UC1);
    for (int i = 0; i < K; i++) {
      int randRow = random(image.rows - 1);
      int randCol = random(image.cols - 1);
      cv::Vec3b bgr_pixel = image.at<cv::Vec3b>(randRow, randCol);
      uchar b = bgr_pixel[0];
      uchar g = bgr_pixel[1];
      uchar r = bgr_pixel[2];
      clusterCentres.push_back(Pixel(b, g, r));
    }
    assignNewClusterCentres();
  }
  void train(int iterations) {
    // fmt::print("Training...\n");
    for (int i = 0; i < iterations; i++) {
      computeCentroids();
      assignNewClusterCentres();
      // fmt::print("Training step {} done\n", i);
    }
  }

  void convert() {
    for (int r = 0; r < image.rows; r++) {
      for (int c = 0; c < image.cols; c++) {
        Pixel p = clusterCentres.at(labels.at<uchar>(r, c));
        cv::Vec3b bgr_pixel(p.b, p.g, p.r);
        // cv::Vec3b curr_pix = image.at<cv::Vec3b>(r, c);
        image.at<cv::Vec3b>(r, c) = bgr_pixel;
        auto curr_pix = Pixel(bgr_pixel[0], bgr_pixel[1], bgr_pixel[2]);
        for (int i = 0; i < clusterCentres.size(); i++) {
          fmt::print("KEY");
          fmt::print("KEY");
          // if(clusterCount.find(curr_pix) != clusterCount.end()){
          //   fmt::print("KEY EXISTS");
          // } else {
          //   fmt::print("KEY DOES NOT EXISTS");
          // }
        }
        fmt::print("{}", bgr_pixel[0]);
      }
    }
  }
  void get_colors() {
    for (Pixel p : clusterCentres) {
      fmt::print("{}\n", p);
    }
  }

private:
  void assignNewClusterCentres() {
    for (int r = 0; r < image.rows; r++) {
      for (int c = 0; c < image.cols; c++) {
        int centroidLabel = 0;
        uchar b, g, r1;
        cv::Vec3b bgr_pixel = image.at<cv::Vec3b>(r, c);
        b = bgr_pixel[0];
        g = bgr_pixel[1];
        r1 = bgr_pixel[2];
        double distance, min_dist;
        min_dist = euclideanDistance(clusterCentres[0].b, clusterCentres[0].g,
                                     clusterCentres[0].r, b, g, r1);
        for (int i = 1; i < K; i++) {
          distance = euclideanDistance(clusterCentres[i].b, clusterCentres[i].g,
                                       clusterCentres[i].r, b, g, r1);
          if (distance < min_dist) {
            min_dist = distance;
            centroidLabel = i;
            labels.at<uchar>(r, c) = (uchar)centroidLabel;
          }
        }
      }
    }
  }

private:
  void computeCentroids() {
    for (int i = 0; i < K; i++) {
      double mean_b = 0.0, mean_g = 0.0, mean_r = 0.0;
      int n = 0;
      for (int r = 0; r < image.rows; r++) {
        for (int c = 0; c < image.cols; c++) {
          if (labels.at<uchar>(r, c) == i) {
            cv::Vec3b bgr_pixel = image.at<cv::Vec3b>(r, c);
            mean_b += bgr_pixel[0];
            mean_g += bgr_pixel[1];
            mean_r += bgr_pixel[2];
            n++;
          }
        }
      }
      mean_b /= n;
      mean_g /= n;
      mean_r /= n;
      clusterCentres.at(i) = Pixel(mean_b, mean_g, mean_r);
    }
  }

  static double euclideanDistance(int x1, int y1, int c1, int x2, int y2,
                                  int c2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2) + pow(c1 - c2, 2));
  }

  static int random(int lim) {
    std::default_random_engine dre(std::chrono::steady_clock::now()
                                       .time_since_epoch()
                                       .count()); // provide seed
    std::uniform_int_distribution<int> uid{
        0, lim};     // help dre to generate nos from 0 to lim (lim included);
    return uid(dre); // pass dre as an argument to uid to generate the random no
  }
};

int main(int argc, char **argv) {
  std::string imgFileName;
  std::string outFileName;
  int nColorVectors = 64;

  if (argc < 3) {
    fmt::print("Please specify input and output filename(or path)\n");
    return 1;
  }

  if (argc == 4)
    nColorVectors = std::stoi(argv[3]);

  imgFileName = argv[1];
  outFileName = argv[2];
  cv::Mat image;
  image = cv::imread(imgFileName);

  if (image.empty())
    return -1;

  KMeans kmeans(image, nColorVectors);
  kmeans.train(10);
  kmeans.convert();
  kmeans.get_colors();
  cv::imwrite(outFileName, image);

  return 0;
}