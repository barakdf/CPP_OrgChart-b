//
// Created by shaul on 09/05/2022.
//
#include "doctest.h"
#include "sources/OrgChart.hpp"
#include "string"
using namespace ariel;
using namespace std;
TEST_CASE ("Case 1 Objects - Family tree")
{
    //create object person for this test
    class Person {
    public:
        string name;
        int age;

        Person(string Name, int Age) : name(Name), age(Age) {}

        bool operator==(Person &p1) {
            return this->name == p1.name;
        }
    };
    //instantiate People
    Person Great_GrandFather("Great_GrandFather", 85);
    Person Grandfather("GrandFather", 65);
    Person Father("Father", 45);
    Person Uncle("Uncle", 43);
    Person Aunt("Aunt", 43);
    Person Son("Son", 20);
    Person Daughter("Daughter", 18);
    Person Cousin("Cousin", 15);

    OrgChart<Person> chart1;
            CHECK_THROWS(chart1.add_sub(Aunt, Son));//no root
            CHECK_NOTHROW(chart1.add_root(Aunt));
            CHECK_NOTHROW(chart1.add_root(Great_GrandFather));
            CHECK_THROWS(chart1.add_sub(Aunt, Son));//root was replaced
            CHECK_THROWS(chart1.add_sub(Son, Uncle));//no such value
            CHECK_NOTHROW(chart1.add_sub(Great_GrandFather, Grandfather));
            CHECK_NOTHROW(chart1.add_sub(Grandfather, Father));
            CHECK_NOTHROW(chart1.add_sub(Grandfather, Uncle));
            CHECK_NOTHROW(chart1.add_sub(Grandfather, Aunt));
            CHECK_THROWS(chart1.add_sub(Cousin, Father));//cousin not added yet
            CHECK_NOTHROW(chart1.add_sub(Father, Son));
            CHECK_NOTHROW(chart1.add_sub(Father, Daughter));
            CHECK_NOTHROW(chart1.add_sub(Uncle, Cousin));

    // test level order
    vector<Person> lvl_order;
    for (auto it = chart1.begin_level_order(); it != chart1.end_level_order(); ++it) {
        lvl_order.push_back(*it);
    }
            CHECK_EQ(lvl_order.at(0).name, Great_GrandFather.name);
            CHECK_EQ(lvl_order.at(1).name, Grandfather.name);
            CHECK_EQ(lvl_order.at(2).name, Father.name);
            CHECK_EQ(lvl_order.at(3).name, Uncle.name);
            CHECK_EQ(lvl_order.at(4).name, Aunt.name);
            CHECK_EQ(lvl_order.at(5).name, Son.name);
            CHECK_EQ(lvl_order.at(6).name, Daughter.name);
            CHECK_EQ(lvl_order.at(7).name, Cousin.name);


    lvl_order.clear();
    //add another field and check that it works
    Person Cousin2("Cousin2", 14);
            CHECK_NOTHROW(chart1.add_sub(Aunt, Cousin2));

    //check default iterator
    for (auto person: chart1) {
        lvl_order.push_back(person);
    }
            CHECK_EQ(lvl_order.at(0).name, Great_GrandFather.name);
            CHECK_EQ(lvl_order.at(1).name, Grandfather.name);
            CHECK_EQ(lvl_order.at(2).name, Father.name);
            CHECK_EQ(lvl_order.at(3).name, Uncle.name);
            CHECK_EQ(lvl_order.at(4).name, Aunt.name);
            CHECK_EQ(lvl_order.at(5).name, Son.name);
            CHECK_EQ(lvl_order.at(6).name, Daughter.name);
            CHECK_EQ(lvl_order.at(7).name, Cousin.name);
            CHECK_EQ(lvl_order.at(8).name, Cousin2.name);


    //add another field and check that it works
    Person GreatUncle("GreatUncle", 62);
            CHECK_NOTHROW(chart1.add_sub(Great_GrandFather, GreatUncle));

    // test reverse level order
    vector<Person> rv_lvl_order;
    for (auto it = chart1.begin_reverse_order(); it != chart1.reverse_order(); ++it) {
        rv_lvl_order.push_back(*it);
    }
            CHECK_EQ(rv_lvl_order.at(0).name, Son.name);
            CHECK_EQ(rv_lvl_order.at(1).name, Daughter.name);
            CHECK_EQ(rv_lvl_order.at(2).name, Cousin.name);
            CHECK_EQ(rv_lvl_order.at(3).name, Cousin2.name);
            CHECK_EQ(rv_lvl_order.at(4).name, Father.name);
            CHECK_EQ(rv_lvl_order.at(5).name, Uncle.name);
            CHECK_EQ(rv_lvl_order.at(6).name, Aunt.name);
            CHECK_EQ(rv_lvl_order.at(7).name, Grandfather.name);
            CHECK_EQ(rv_lvl_order.at(8).name, GreatUncle.name);
            CHECK_EQ(rv_lvl_order.at(9).name, Great_GrandFather.name);

    // Change root check that still works
    Person GreatGrandma("GreatGrandma", 84);
            CHECK_NOTHROW(chart1.add_root(GreatGrandma));

    //test preorder
    vector<Person> pre_order;
    for (auto it = chart1.begin_preorder(); it != chart1.end_preorder(); ++it) {
        pre_order.push_back(*it);
    }
            CHECK_EQ(pre_order.at(0).name, GreatGrandma.name);
            CHECK_EQ(pre_order.at(1).name, Grandfather.name);
            CHECK_EQ(pre_order.at(2).name, Father.name);
            CHECK_EQ(pre_order.at(3).name, Son.name);
            CHECK_EQ(pre_order.at(4).name, Daughter.name);
            CHECK_EQ(pre_order.at(5).name, Uncle.name);
            CHECK_EQ(pre_order.at(6).name, Cousin.name);
            CHECK_EQ(pre_order.at(7).name, Aunt.name);
            CHECK_EQ(pre_order.at(8).name, Cousin2.name);
            CHECK_EQ(pre_order.at(9).name, GreatUncle.name);

    //test arrow operator
    vector<int> arrow_test;
    for (auto it = chart1.begin_preorder(); it != chart1.end_preorder(); ++it) {
        arrow_test.push_back(it->age);
    }
            CHECK_EQ(arrow_test.at(0), 84);
            CHECK_EQ(arrow_test.at(1), 65);
            CHECK_EQ(arrow_test.at(2), 45);
            CHECK_EQ(arrow_test.at(3), 20);
            CHECK_EQ(arrow_test.at(4), 18);
            CHECK_EQ(arrow_test.at(5), 43);
            CHECK_EQ(arrow_test.at(6), 15);
            CHECK_EQ(arrow_test.at(7), 43);
            CHECK_EQ(arrow_test.at(8), 14);
            CHECK_EQ(arrow_test.at(9), 62);
}
TEST_CASE ("Case 2 Football Team")
{
    //checking string
    OrgChart<string> chart2;
            CHECK_NOTHROW(chart2.add_root("Owner"));
            CHECK_NOTHROW(chart2.add_root("New_Owner"));
            CHECK_THROWS(chart2.add_sub("Owner" , "General Manager"));//Owner was replaced
            CHECK_THROWS(chart2.add_sub("Lebron James" , "General_Manager"));//no such value
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "General_Manager"));
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "Share_Holders"));
            CHECK_NOTHROW(chart2.add_sub("New_Owner" , "Head_of_operations"));
            CHECK_NOTHROW(chart2.add_sub("General_Manager" , "Head_Coach"));
            CHECK_NOTHROW(chart2.add_sub("General_Manager" , "Assistant_Coach"));
            CHECK_NOTHROW(chart2.add_sub("Head_of_operations" , "Team_Doctor"));
            CHECK_NOTHROW(chart2.add_sub("Head_of_operations" , "Head_Scout"));
            CHECK_NOTHROW(chart2.add_sub("Share_Holders" , "Sub_Share_Holder1"));
            CHECK_NOTHROW(chart2.add_sub("Share_Holders" , "Sub_Share_Holder2"));
            CHECK_THROWS(chart2.add_sub("head_of_operations" , "Cheerleader"));//Head not head
            CHECK_NOTHROW(chart2.add_sub("Head_Coach" , "Captain"));
            CHECK_NOTHROW(chart2.add_sub("Team_Doctor" , "Team_Physiotherapist"));
            // test level order
            vector<string> lvl_order;
            for (auto it = chart2.begin_level_order(); it != chart2.end_level_order(); ++it)
            {
               lvl_order.push_back(*it);
            }
            CHECK_EQ(lvl_order.at(0),"New_Owner");
            CHECK_EQ(lvl_order.at(1),"General_Manager");
            CHECK_EQ(lvl_order.at(2),"Share_Holders");
            CHECK_EQ(lvl_order.at(3),"Head_of_operations");
            CHECK_EQ(lvl_order.at(4),"Head_Coach");
            CHECK_EQ(lvl_order.at(5),"Assistant_Coach");
            CHECK_EQ(lvl_order.at(6),"Sub_Share_Holder1");
            CHECK_EQ(lvl_order.at(7),"Sub_Share_Holder2");
            CHECK_EQ(lvl_order.at(8),"Team_Doctor");
            CHECK_EQ(lvl_order.at(9),"Head_Scout");
            CHECK_EQ(lvl_order.at(10),"Captain");
            CHECK_EQ(lvl_order.at(11),"Team_Physiotherapist");
            lvl_order.clear();

            //add another field and check that it works
            CHECK_NOTHROW(chart2.add_sub("Assistant_Coach" , "Water_Boy"));
             cout << chart2 << endl;
            //check default iterator
            for (auto name:chart2)
            {
                lvl_order.push_back(name);
            }
            CHECK_EQ(lvl_order.at(0),"New_Owner");
            CHECK_EQ(lvl_order.at(1),"General_Manager");
            CHECK_EQ(lvl_order.at(2),"Share_Holders");
            CHECK_EQ(lvl_order.at(3),"Head_of_operations");
            CHECK_EQ(lvl_order.at(4),"Head_Coach");
            CHECK_EQ(lvl_order.at(5),"Assistant_Coach");
            CHECK_EQ(lvl_order.at(6),"Sub_Share_Holder1");
            CHECK_EQ(lvl_order.at(7),"Sub_Share_Holder2");
            CHECK_EQ(lvl_order.at(8),"Team_Doctor");
            CHECK_EQ(lvl_order.at(9),"Head_Scout");
            CHECK_EQ(lvl_order.at(10),"Captain");
            CHECK_EQ(lvl_order.at(11),"Water_Boy");
            CHECK_EQ(lvl_order.at(12),"Team_Physiotherapist");

            // test reverse level order
            vector<string> rv_lvl_order;
            for (auto it = chart2.begin_reverse_order(); it != chart2.reverse_order(); ++it)
            {
                rv_lvl_order.push_back(*it);
            }
            CHECK_EQ(rv_lvl_order.at(0),"Captain");
            CHECK_EQ(rv_lvl_order.at(1),"Water_Boy");
            CHECK_EQ(rv_lvl_order.at(2),"Team_Physiotherapist");
            CHECK_EQ(rv_lvl_order.at(3),"Head_Coach");
            CHECK_EQ(rv_lvl_order.at(4),"Assistant_Coach");
            CHECK_EQ(rv_lvl_order.at(5),"Sub_Share_Holder1");
            CHECK_EQ(rv_lvl_order.at(6),"Sub_Share_Holder2");
            CHECK_EQ(rv_lvl_order.at(7),"Team_Doctor");
            CHECK_EQ(rv_lvl_order.at(8),"Head_Scout");
            CHECK_EQ(rv_lvl_order.at(9),"General_Manager");
            CHECK_EQ(rv_lvl_order.at(10),"Share_Holders");
            CHECK_EQ(rv_lvl_order.at(11),"Head_of_operations");
            CHECK_EQ(rv_lvl_order.at(12),"New_Owner");

            // Change root check that still works
            CHECK_NOTHROW(chart2.add_root("Stan_Kronke"));

            //test preorder
            vector<string> pre_order;
            for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
            {
                pre_order.push_back(*it);
            }
            CHECK_EQ(pre_order.at(0),"Stan_Kronke");
            CHECK_EQ(pre_order.at(1),"General_Manager");
            CHECK_EQ(pre_order.at(2),"Head_Coach");
            CHECK_EQ(pre_order.at(3),"Captain");
            CHECK_EQ(pre_order.at(4),"Assistant_Coach");
            CHECK_EQ(pre_order.at(5),"Water_Boy");
            CHECK_EQ(pre_order.at(6),"Share_Holders");
            CHECK_EQ(pre_order.at(7),"Sub_Share_Holder1");
            CHECK_EQ(pre_order.at(8),"Sub_Share_Holder2");
            CHECK_EQ(pre_order.at(9),"Head_of_operations");
            CHECK_EQ(pre_order.at(10),"Team_Doctor");
            CHECK_EQ(pre_order.at(11),"Team_Physiotherapist");
            CHECK_EQ(pre_order.at(12),"Head_Scout");

            //test arrow operator
            vector<char> arrow_test;
            for (auto it = chart2.begin_preorder(); it != chart2.end_preorder(); ++it)
            {
                arrow_test.push_back(it->at(0));
            }
            CHECK_EQ(arrow_test.at(0),'S');
            CHECK_EQ(arrow_test.at(1),'G');
            CHECK_EQ(arrow_test.at(2),'H');
            CHECK_EQ(arrow_test.at(3),'C');
            CHECK_EQ(arrow_test.at(4),'A');
            CHECK_EQ(arrow_test.at(5),'W');
            CHECK_EQ(arrow_test.at(6),'S');
            CHECK_EQ(arrow_test.at(7),'S');
            CHECK_EQ(arrow_test.at(8),'S');
            CHECK_EQ(arrow_test.at(9),'H');
            CHECK_EQ(arrow_test.at(10),'T');
            CHECK_EQ(arrow_test.at(11),'T');
            CHECK_EQ(arrow_test.at(12),'H');
}
// Testing integers , each son is a product of father*x for some x
TEST_CASE ("Case 2 Integers")
{
    OrgChart<int> chart3;
            CHECK_THROWS(chart3.add_sub(1,10));//trying to add sub before root for new org
            CHECK_NOTHROW(chart3.add_root(5));
            CHECK_NOTHROW(chart3.add_root(1));
            CHECK_THROWS(chart3.add_sub(5, 2));//5 was replaced
            CHECK_THROWS(chart3.add_sub(2 , 7));//no such value
            CHECK_NOTHROW(chart3.add_sub(1 , 2));
            CHECK_NOTHROW(chart3.add_sub(1 , 3));
            CHECK_NOTHROW(chart3.add_sub(2 , 4));
            CHECK_NOTHROW(chart3.add_sub(1 ,5));
            CHECK_NOTHROW(chart3.add_sub(5 , 25));
            CHECK_NOTHROW(chart3.add_sub(25 , 250));
            CHECK_NOTHROW(chart3.add_sub(4 , 8));
            CHECK_NOTHROW(chart3.add_sub(1, 7));
            CHECK_THROWS(chart3.add_sub(6 , 8));//no such value

    // test level order
    vector<int> lvl_order;
    for (auto it = chart3.begin_level_order(); it != chart3.end_level_order(); ++it)
    {
       lvl_order.push_back(*it);
    }
            CHECK_EQ(lvl_order.at(0),1);
            CHECK_EQ(lvl_order.at(1),2);
            CHECK_EQ(lvl_order.at(2),3);
            CHECK_EQ(lvl_order.at(3),5);
            CHECK_EQ(lvl_order.at(4),7);
            CHECK_EQ(lvl_order.at(5),4);
            CHECK_EQ(lvl_order.at(6),25);
            CHECK_EQ(lvl_order.at(7),8);
            CHECK_EQ(lvl_order.at(8),250);


    lvl_order.clear();

    //add another field and check that it works
            CHECK_NOTHROW(chart3.add_sub(250, 10000));

            CHECK_THROWS(chart3.add_sub(100000, 111111));//no node that fits father
    //check default iterator
    for (auto number:chart3)
    {
        lvl_order.push_back(number);
    }
            CHECK_EQ(lvl_order.at(0),1);
            CHECK_EQ(lvl_order.at(1),2);
            CHECK_EQ(lvl_order.at(2),3);
            CHECK_EQ(lvl_order.at(3),5);
            CHECK_EQ(lvl_order.at(4),7);
            CHECK_EQ(lvl_order.at(5),4);
            CHECK_EQ(lvl_order.at(6),25);
            CHECK_EQ(lvl_order.at(7),8);
            CHECK_EQ(lvl_order.at(8),250);
            CHECK_EQ(lvl_order.at(9),10000);

    // test reverse level order
    vector<int> rv_lvl_order;
    for (auto it = chart3.begin_reverse_order(); it != chart3.reverse_order(); ++it)
    {
        rv_lvl_order.push_back(*it);
    }
            CHECK_EQ(rv_lvl_order.at(0),10000);
            CHECK_EQ(rv_lvl_order.at(1),8);
            CHECK_EQ(rv_lvl_order.at(2),250);
            CHECK_EQ(rv_lvl_order.at(3),4);
            CHECK_EQ(rv_lvl_order.at(4),25);
            CHECK_EQ(rv_lvl_order.at(5),2);
            CHECK_EQ(rv_lvl_order.at(6),3);
            CHECK_EQ(rv_lvl_order.at(7),5);
            CHECK_EQ(rv_lvl_order.at(8),7);
            CHECK_EQ(rv_lvl_order.at(9),1);

    // Change root check that still works
            CHECK_NOTHROW(chart3.add_root(int(1.2)));

    //test preorder
    vector<int> pre_order;
    for (auto it = chart3.begin_preorder(); it != chart3.end_preorder(); ++it)
    {
        pre_order.push_back(*it);
    }
            CHECK_EQ(pre_order.at(0),1);
            CHECK_EQ(pre_order.at(1),2);
            CHECK_EQ(pre_order.at(2),4);
            CHECK_EQ(pre_order.at(3),8);
            CHECK_EQ(pre_order.at(4),3);
            CHECK_EQ(pre_order.at(5),5);
            CHECK_EQ(pre_order.at(6),25);
            CHECK_EQ(pre_order.at(7),250);
            CHECK_EQ(pre_order.at(8),10000);
            CHECK_EQ(pre_order.at(9),7);


}

