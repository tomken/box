
#include "nlohmann/json.hpp"

static void test_json() {
    nlohmann::json json;
    json['a'] = 1.0;
    exit(0);
}