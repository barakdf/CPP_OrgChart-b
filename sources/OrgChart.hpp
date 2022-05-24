//
// Created by barak on 16/05/2022.
//

#ifndef CPP_ORGCHART_A_ORGCHART_HPP
#define CPP_ORGCHART_A_ORGCHART_HPP

#include <iostream>
#include <iterator>
#include <utility>
#include <vector>
#include <unordered_map>

/** */


namespace ariel {
   class LevelOrder;
   class ReverseLevelOrder;
   class PreOrder;

    class OrgChart {

    public:
        class Node {
        private:
            std::string title;


            size_t index;

            size_t level;
        public:

            Node* parent;
            Node* left;
            Node* right;
            std::vector<Node*> children;
            Node(std::string  title, size_t _level, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr):
            title(std::move(title)), level(_level), parent(_parent), left(_left), right(_right){}

            size_t length();
            size_t _level() const;

            char at(size_t i) {
                return this->title.at(i);
            }



            void add_child(Node* child);

            std::string & _title();

            void set_title(std::string _title);

            size_t get_num_children() const;

            int size();

            friend std::ostream & operator<< (std::ostream &ostream, Node& node);
        };

    private:
        Node *root;
        size_t max_level;
        /* map of members for O(1) search of a member node */
        std::unordered_map<size_t,Node *> levels;


    public:
        std::unordered_map<std::string, Node> members;

        OrgChart() : root(nullptr), max_level(0) {}

        OrgChart &add_root(const std::string& title);

        OrgChart &add_sub(const std::string& curr_title, const std::string& new_title);

        auto get_members();




        /** -------------- Iterator Classes */


        /** Basic Iterator Parent Class
         * this class will contain all the common implementation of tha sub behave iterators.*/

        class Iterator {
        protected:
            Node *pointer_to_current_node;
        public:
            Iterator(Node *ptr): pointer_to_current_node(ptr){}
            Iterator(const Iterator &other);

            Iterator &operator=(const Iterator &);

            //            Node & operator&() const;
            Node * operator->() const;
            const std::string& operator*() const;

            bool operator==(const Iterator& other);
            bool operator!=(const Iterator& other);
        };






        /** Iterator Methods */

        /* LEVEL ORDER */
        LevelOrder begin_level_order();

        LevelOrder end_level_order();

        LevelOrder begin();
        LevelOrder end();

        /* REVERSE LEVEL ORDER */
        ReverseLevelOrder begin_reverse_order();

        ReverseLevelOrder reverse_order();

        /* PRE ORDER */
        PreOrder begin_preorder();

        PreOrder end_preorder();


        friend std::ostream & operator<< (std::ostream &ostream, OrgChart& orgChart);

    };

    /* LEVEL ORDER CLASS */
    class LevelOrder: public OrgChart::Iterator {
        std::unordered_map<size_t, OrgChart::Node *> *level;
    public:
        LevelOrder(std::unordered_map<size_t, OrgChart::Node *>* levels = nullptr, OrgChart::Node *ptr = nullptr)
                :level(levels), Iterator(ptr) {}

        LevelOrder& operator++();
        LevelOrder operator++(int );

    };


    /* REVERSE LEVEL ORDER CLASS */
    class ReverseLevelOrder:public OrgChart::Iterator {
        std::unordered_map<size_t, OrgChart::Node *>* level;
    public:
        ReverseLevelOrder(std::unordered_map<size_t, OrgChart::Node *> * levels  = nullptr, OrgChart::Node *ptr = nullptr)
                : level(levels),Iterator(ptr) {}

        ReverseLevelOrder& operator++();
        ReverseLevelOrder operator++(int );


    };


    /* PRE ORDER CLASS */
    class PreOrder:public OrgChart::Iterator {
    public:
        PreOrder(OrgChart::Node *ptr)
                : Iterator(ptr) {}

        PreOrder& operator++();
        PreOrder operator++(int );



    };

}


#endif //CPP_ORGCHART_A_ORGCHART_HPP
