#ifndef NON_GRAVITAR_IMPROVEMENTCRATE_HPP
#define NON_GRAVITAR_IMPROVEMENTCRATE_HPP

#include "CratePersistentData.hpp"

struct ImprovementCrate : public CratePersistentData {
    std::string get_content_smesh_path() override {
        return std::string("./res/models/crates/crate__asterisk.smesh");
    }
};

#endif //NON_GRAVITAR_IMPROVEMENTCRATE_HPP
