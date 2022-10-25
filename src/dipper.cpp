#include <fmt/core.h>

#include "diplib.h"
#include "diplib/histogram.h"
#include "diplib/lookup_table.h"
#include "diplib/segmentation.h"
#include "diplib/simple_file_io.h"
#include "dipviewer.h"

int main(int argc, char **argv) {
  std::string imgFileName;
  std::string outFileName;
  int nColorVectors = 8;

  if (argc < 3) {
    fmt::print("Please specify input and output filename(or path)\n");
    return 1;
  }

  if (argc == 4) nColorVectors = std::stoi(argv[3]);

  imgFileName = argv[1];
  outFileName = argv[2];

  dip::Image input = dip::ImageRead(imgFileName);
  input.SetColorSpace("Lab");  

  // Compute the color histogram.
  dip::Histogram hist(input, {},
                      {dip::Histogram::Configuration(0.0, 255.0, 64)});

  // Cluster the histogram, the output histogram has a label assigned to each
  // bin. Each label corresponds to one of the clusters.
  dip::uint nClusters = nColorVectors;
  dip::Image histImage = hist.GetImage();  // Copy with shared data
  dip::Image tmp;
  dip::CoordinateArray centers =
      dip::MinimumVariancePartitioning(histImage, tmp, nClusters);
  histImage.Copy(tmp);  // Copy 32-bit label image into 64-bit histogram image.

  // Find the cluster label for each pixel in the input image.
  dip::Image labels = hist.ReverseLookup(input);

  // The `centers` array contains histogram coordinates for each of the centers.
  // We need to convert these coordinates to RGB values by multiplying by 4
  // (=256/64). `centers[ii]` corresponds to label `ii+1`.
  dip::Image lutImage({nClusters + 1}, 3, dip::DT_UINT8);
  lutImage.At(0) = 0;  // label 0 doesn't exist
  for (dip::uint ii = 0; ii < nClusters; ++ii) {
    lutImage.At(ii + 1) = {centers[ii][0] * 4, centers[ii][1] * 4,
                           centers[ii][2] * 4};
  }

  // Finally, we apply our look-up table mapping, painting each label in the
  // image with its corresponding RGB color.
  dip::LookupTable lut(lutImage);
  dip::Image output = lut.Apply(labels);
//   output.SetColorSpace("RGB");

  dip::ImageWriteJPEG(output, outFileName);
}