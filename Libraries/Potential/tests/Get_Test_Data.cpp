//
// Created by Keiwan Jamaly on 04.11.22.
//

#include "Get_Test_Data.h"
#include "simdjson.h"

namespace phy {

    using namespace simdjson; // optional

    void get_test_data(std::string filename, dbl_vec &sigma, std::vector<dbl_vec> &u_vector, dbl_vec &t_vector) {
        ondemand::parser parser;
        dbl_vec u;
        double t;

        auto json = padded_string::load(filename);
        ondemand::document doc = parser.iterate(json); // position a pointer at the beginning of the JSON data

        auto graphs = doc.find_field("graphs").get_array();

        for (auto element: graphs) {
            sigma.clear();
            sigma.clear();
            u.clear();
            // get t value
            std::string_view t_string = element.find_field("label").get_string();
            std::string t_value(t_string);
            t_value.replace(0, 2, "");
            t = std::stod(t_value);
            // store sigma values

            for (auto x_val: element.find_field("x").get_array()) {
                sigma.push_back(x_val.get_double());
            }
            // store u values
            for (auto y_val: element.find_field("y").get_array()) {
                u.push_back(y_val.get_double());
            }
            u_vector.push_back(u);
            t_vector.push_back(t);
        }
    }

} // phy