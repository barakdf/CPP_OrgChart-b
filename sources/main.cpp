//#include <iostream>
//#include "OrgChart.hpp"
//int main() {
//    using namespace ariel;
////    OrgChart chart2;
////    chart2.add_root("Owner");
////    chart2.add_root("New_Owner");
//////    chart2.add_sub("Owner" , "General Manager");//Owner was replaced
//////    chart2.add_sub("Lebron James" , "General_Manager");//no such value
////    chart2.add_sub("New_Owner" , "General_Manager");
////    chart2.add_sub("New_Owner" , "Share_Holders");
////    chart2.add_sub("New_Owner" , "Head_of_operations");
////    chart2.add_sub("General_Manager" , "Head_Coach");
////    chart2.add_sub("General_Manager" , "Assistant_Coach");
////    chart2.add_sub("Head_of_operations" , "Team_Doctor");
////    chart2.add_sub("Head_of_operations" , "Head_Scout");
////    chart2.add_sub("Share_Holders" , "Sub_Share_Holder1");
////    chart2.add_sub("Share_Holders" , "Sub_Share_Holder2");
//////    chart2.add_sub("head_of_operations" , "Cheerleader");//Head not head
////    chart2.add_sub("Head_Coach" , "Captain");
////    chart2.add_sub("Team_Doctor" , "Team_Physiotherapist");
////    chart2.add_sub("Assistant_Coach" , "Water_Boy");
////////    auto it = org.begin_level_order();
////////    std::cout << (*it) << std::endl;
////////    std::cout << org.members.at("sapir").left << std::endl;
////////    std::cout << org.members.at("dan").left << std::endl;
////////    std::cout << org.members.at("tal").parent << std::endl;
////
////
////
//    /* create normal tree */
//
//    OrgChart org;
//
////    org.add_sub("tal", "renana");// "can't add sub before root"
//    org.add_root("dana");
//    org.add_root("shir");
//    org.add_sub("shir", "tal");
////    org.add_sub("adi", "sapir");// "employer doesn't exist"
//    org.add_sub("shir", "sapir");
//    org.add_sub("sapir", "dan");
//    org.add_sub("dan", "ziv");
//    org.add_sub("tal", "avi");
//    org.add_sub("tal", "yossi");
//    org.add_sub("shir", "ido");
//    org.add_sub("ziv", "shaked");
//    org.add_sub("ziv", "ofer");
//    for(auto it = org.begin_reverse_order(); it != org.reverse_order(); ++it){
//        std::cout << (*it) << " LEVEL : " << it->_level() << std::endl;
//    }
////
////    std::vector<char> arrow_test;
////    for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
////    {
////        arrow_test.push_back(it->at(0));
////    }
////
////    arrow_test.at(0);
////    arrow_test.at(1);
////    arrow_test.at(2);
////    arrow_test.at(3);
////    arrow_test.at(4);
////    arrow_test.at(5);
////    arrow_test.at(6);
////    arrow_test.at(7);
////    arrow_test.at(8);
////    arrow_test.at(9);
////    arrow_test.at(10);
////    arrow_test.at(11);
////    arrow_test.at(12);
////
////
////    std::vector<std::string> pre_order;
////    for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
////    {
////        pre_order.push_back(*it);
////    }
////    pre_order.at(0);
////    pre_order.at(1);
////    pre_order.at(2);
////    pre_order.at(3);
////    pre_order.at(4);
////    pre_order.at(5);
////    pre_order.at(6);
////    pre_order.at(7);
////    pre_order.at(8);
////    pre_order.at(9);
////    pre_order.at(10);
////    pre_order.at(11);
////    pre_order.at(12);
////
////    chart2.add_root("Stan_Kronke");
////
////
////    std::vector<std::string> rv_lvl_order;
////    for (auto it = chart2.begin_reverse_order(); it != chart2.reverse_order(); ++it)
////    {
////        std::cout << *it << std::endl;
//////        rv_lvl_order.push_back(*it);
////    }
////
//////    rv_lvl_order.at(0);
//////    rv_lvl_order.at(1);
//////    rv_lvl_order.at(2);
//////    rv_lvl_order.at(3);
//////    rv_lvl_order.at(4);
//////    rv_lvl_order.at(5);
//////    rv_lvl_order.at(6);
//////    rv_lvl_order.at(7);
//////    rv_lvl_order.at(8);
//////    rv_lvl_order.at(9);
//////    rv_lvl_order.at(10);
//////    rv_lvl_order.at(11);
//////    rv_lvl_order.at(12);
//}
