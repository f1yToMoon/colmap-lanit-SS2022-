#include <iostream>
#include "base/database.h"
#include "util/misc.h"
#include "util/option_manager.h"
#include "feature/extraction.h"
#include "exe/database.h"
#include "exe/gui.h"
#include "feature/matching.h"


int main() {
    std::string path_to_database("/home/nick/project/TEST.db");
    colmap::Database db_track(path_to_database);

    colmap::SiftMatchingOptions sift_m_opt;
    colmap::ExhaustiveMatchingOptions ex_opt;
    ex_opt.block_size = db_track.NumImages();
    colmap::ExhaustiveFeatureMatcher ex_matcher(ex_opt, sift_m_opt, path_to_database);
    ex_matcher.Start();

}
