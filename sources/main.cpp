//#include <iostream>
//#include "OrgChart.hpp"
//
//int main() {
//    using namespace ariel;
//    OrgChart Konoha_Shinobi_Ranks;
//
//    Konoha_Shinobi_Ranks.add_root("Hokage");
//    Konoha_Shinobi_Ranks.add_sub(
//                    "Hokage", "Medical")
//            .add_sub("Hokage", "SP_Jounin")
//            .add_sub("Hokage", "Anbu")
//            .add_sub("Hokage", "Sannin");
//    Konoha_Shinobi_Ranks.add_sub(
//                    "SP_Jounin", "Jounin")
//            .add_sub("Jounin", "Chounin")
//            .add_sub("Chounin", "Genin")
//            .add_sub("Genin", "Academy Student");
//    Konoha_Shinobi_Ranks.add_sub(
//                    "Anbu", "Ibki")
//            .add_sub("Ibki", "Torture");
//    Konoha_Shinobi_Ranks.add_sub(
//            "Anbu", "Danzo").
//            add_sub("Danzo", "Root");
//
//    std::cout << Konoha_Shinobi_Ranks << std::endl;
//
//    std::cout << "~~Level Order Ranks\n" << std::endl;
//    for (auto ninja: Konoha_Shinobi_Ranks) {
//        std::cout << (ninja) << std::endl;
//    }
//    std::cout <<"\n";
//
//    std::cout << "~~Reverse Level Order Ranks\n" << std::endl;
//    for (auto iter = Konoha_Shinobi_Ranks.begin_reverse_order(); iter != Konoha_Shinobi_Ranks.reverse_order(); ++iter) {
//        std::cout << *iter << std::endl;
//    }
//    std::cout <<"\n";
//
//    std::cout << "~~Pre Order Ranks\n" << std::endl;
//    for (auto iter = Konoha_Shinobi_Ranks.begin_preorder(); iter != Konoha_Shinobi_Ranks.end_preorder(); ++iter) {
//        std::cout << *iter << std::endl;
//    }
//
//}