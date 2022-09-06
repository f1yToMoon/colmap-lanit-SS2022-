#include <iostream>
#include "base/database.h"
#include "util/misc.h"
#include "util/option_manager.h"
#include "feature/extraction.h"
#include "exe/database.h"
#include "exe/gui.h"
#include "feature/matching.h"

int main(int argc, char *argv[]) {

    ///create new database
    colmap::OptionManager options;
    options.AddDatabaseOptions();
    colmap::Database db1(argv[1]);

    ///reference database
    std::string path_to_database1(argv[2]);
    colmap::Database db(path_to_database1);

    ///read features
    colmap::Image im = db.ReadImageWithName(argv[3]);
    colmap::Camera camera = db.ReadCamera(im.CameraId());
    colmap::FeatureDescriptors descriptors = db.ReadDescriptors(im.ImageId());
    colmap::FeatureKeypoints keypoints = db.ReadKeypoints(im.ImageId());

    ///read bitmap
    colmap::Bitmap bp;
    colmap::BitmapColor <uint8_t> *color;
    bp.Read(argv[4], false);

    colmap::FeatureKeypoints kp;

    std::cout << keypoints.size() << "\n______\n";
    for(int i = 0; i < keypoints.size(); ++i) {
        int k_x = static_cast<int>(keypoints[i].x);
        int k_y = static_cast<int>(keypoints[i].y);
        bp.GetPixel(k_x, k_y, color);
        auto col = *color;
        if (col.r == 255) {
            kp.push_back(keypoints[i]);
        }
    }
    std::cout << kp.size() << "\n";


    colmap::FeatureDescriptors dp(kp.size(), 128);
    int k = 0;
    for(int i = 0; i < keypoints.size(); ++i) {
        int k_x = static_cast<int>(keypoints[i].x);
        int k_y = static_cast<int>(keypoints[i].y);
        bp.GetPixel(k_x, k_y, color);
        auto col = *color;
        if (col.r == 255) {
            for(int f = 0; f < 128; ++f) {
                dp(k, f) = descriptors(i, f);
            }
            k++;
        }
    }

    ///write features in new database
    db1.WriteCamera(camera, true);
    db1.WriteImage(im, true);
    db1.WriteKeypoints(im.ImageId(), kp);
    db1.WriteDescriptors(im.ImageId(), dp);

}
