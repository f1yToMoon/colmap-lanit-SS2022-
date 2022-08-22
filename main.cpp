#include <iostream>
#include "base/database.h"
#include "util/misc.h"
#include "util/option_manager.h"
#include "feature/extraction.h"
//#include "exe/feature.h"
#include "exe/database.h"
//#include "base/camera_models.h"
//#include "base/image_reader.h"
#include "exe/gui.h"
#include "feature/matching.h"
//#include "util/opengl_utils.h"
//#include "base/reconstruction.h"



int main() {

    //TODO extract features
    /*colmap::FeatureKeypoints *kp;
    colmap::FeatureDescriptors *dp;
    colmap::ImageReaderOptions im_options;
    colmap::SiftExtractionOptions sift_options;
    im_options.Check();
    sift_options.Check();
    colmap::ExtractSiftFeaturesCPU(sift_options, bp, kp, dp);*/


    //create new database
    colmap::OptionManager options;
    options.AddDatabaseOptions();
    colmap::Database db1("/home/nick/project/1.db");

    //reference database
    std::string path_to_database("/home/nick/Downloads/gerrard-hall/database.db");
    colmap::Database db(path_to_database);

    //read features
    colmap::Image im = db.ReadImageWithName("IMG_2331.JPG");
    //std::cout << im.ImageId() << "\n";
    colmap::Camera camera = db.ReadCamera(1);
    colmap::FeatureDescriptors descriptors = db.ReadDescriptors(im.ImageId());
    colmap::FeatureKeypoints keypoints = db.ReadKeypoints(im.ImageId());

    //read bitmap
    colmap::Bitmap bp;
    colmap::BitmapColor<uint8_t>* color;
    bp.Read("/home/nick/project/masks/0000000391.tiff.png", false);

    colmap::FeatureKeypoints kp;
    colmap::FeatureDescriptors dp(keypoints.size(), 128);

    /*std::cout << keypoints.size() << "\n";
    for(auto & keypoint : keypoints) {
        int k_x = static_cast<int>(keypoint.x);
        int k_y = static_cast<int>(keypoint.y);
        if (bp.GetPixel(k_x, k_y, color)) {
            kp.push_back(keypoint);
            dp() = descriptors(i);
        }
    }*/

    std::cout << keypoints.size() << "\n____________\n";
    for(int i = 0; i < keypoints.size(); ++i) {
        int k_x = static_cast<int>(keypoints[i].x);
        int k_y = static_cast<int>(keypoints[i].y);
        auto pi = bp.GetPixel(k_x, k_y, color);
        if(pi) {
            kp.push_back(keypoints[i]);
            dp(i) = descriptors(i);
        }
    }

    std::cout << kp.size() <<"\n";
    std::cout << bp.IsRGB();

    /*std::cout << "db1_image : " << db1.ExistsImage(im.ImageId()) << "\n";
    std::cout << "db1_camera : " << db1.ExistsCamera(1) << "\n";
    std::cout << "db1_descriptors : " << db1.ExistsDescriptors(im.ImageId()) << "\n";
    std::cout << "db1_keypoints : " << db1.ExistsKeypoints(im.ImageId()) << "\n" << "________________\n";*/

    //write features in new database
    db1.WriteCamera(camera);
    db1.WriteImage(im, true);
    db1.WriteKeypoints(im.ImageId(), kp);
    db1.WriteDescriptors(im.ImageId(), dp);

    /*std::cout << "db1_image : " << db1.ExistsImage(im.ImageId()) << "\n";
    std::cout << "db1_camera : " << db1.ExistsCamera(1) << "\n";
    std::cout << "db1_descriptors : " << db1.ExistsDescriptors(im.ImageId()) << "\n";
    std::cout << "db1_keypoints : " << db1.ExistsKeypoints(im.ImageId()) << "\n";*/

}