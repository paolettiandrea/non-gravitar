#ifndef NON_GRAVITAR_SOLARSYSTEM_CONSTRUCTIONDATA_HPP
#define NON_GRAVITAR_SOLARSYSTEM_CONSTRUCTIONDATA_HPP


struct SolarSystem_ConstructionData {
    unsigned int planetoid_number = 5;

    unsigned int min_planetoid_size = 50;
    unsigned int max_planetoid_size = 500;

    float min_difficulty_factor = 0.5;
    float max_difficulty_factor = 4.0;

    std::string to_string() const {
        std::stringstream ss;
        ss << "Solar System Contruction Data:\n"
            << "Size\tMin:" << min_planetoid_size << "\tMax: " << max_planetoid_size <<"\n"
            << "Difficulty\tMin:" << min_difficulty_factor << "\tMax : " << max_difficulty_factor;
        return ss.str();
    }
};


#endif //NON_GRAVITAR_SOLARSYSTEM_CONSTRUCTIONDATA_HPP
