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
            friend class OrgChart;
            friend class LevelOrder;
            friend class ReverseLevelOrder;
            friend class PreOrder;
        private:
            std::string title;


            size_t level;

            size_t index;
            Node* parent;
            Node* left;
            Node* right;

            std::vector<Node*> children;
        public:
            Node(std::string  title, size_t _level, Node* _parent = nullptr, Node* _left = nullptr, Node* _right = nullptr):
            title(std::move(title)), level(_level), parent(_parent), left(_left), right(_right), index(0){}

            size_t length();
            size_t _level() const;

            char at(size_t i);

            Node * get_right() {
                return right;
            }

            bool if_null() {
                return this->right == nullptr;
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
        /* store the max level of the tree, for fast assign reverseOrder begin node */
        size_t max_level;
        /* map of members for O(1) search of a member node */
        std::unordered_map<size_t,Node *> levels;

        /* map that store the nodes in the tree by <title,Node>
         * this data structure is use to store all data
         * and for fast pull node object for the add_sub and add_root methods.*/
        std::unordered_map<std::string, Node> members;
    public:


        OrgChart() : root(nullptr), max_level(0) {}

        OrgChart &add_root(const std::string& title);

        OrgChart &add_sub(const std::string& curr_title, const std::string& new_title);

        auto get_members();




        /** -------------- Iterator Classes */


        /** Basic Iterator Parent Class
         * this class will contain all the common implementation of tha sub behave iterators.*/

        class Iterator {
        private:
            Node *Ppointer_to_current_node;
        public:
            Iterator(Node *ptr): Ppointer_to_current_node(ptr){}

            void set_pointer(Node *node) {
                this->Ppointer_to_current_node = node;
            }
//            Iterator(const Iterator &other);

//            Iterator &operator=(const Iterator &);

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
        OrgChart::Node *pointer_to_current_node;
    public:
        LevelOrder(std::unordered_map<size_t, OrgChart::Node *>* levels = nullptr, OrgChart::Node *ptr = nullptr)
                :level(levels),pointer_to_current_node(ptr), Iterator(ptr) {}

        LevelOrder& operator++();
        LevelOrder operator++(int );

    };


    /* REVERSE LEVEL ORDER CLASS */
    class ReverseLevelOrder:public OrgChart::Iterator {
        std::unordered_map<size_t, OrgChart::Node *>* level;
        OrgChart::Node *pointer_to_current_node;
    public:
        ReverseLevelOrder(std::unordered_map<size_t, OrgChart::Node *> * levels  = nullptr, OrgChart::Node *ptr = nullptr)
                : level(levels),pointer_to_current_node(ptr),Iterator(ptr) {}

        ReverseLevelOrder& operator++();
        ReverseLevelOrder operator++(int );


    };


    /* PRE ORDER CLASS */
    class PreOrder:public OrgChart::Iterator {
        OrgChart::Node *pointer_to_current_node;
    public:
        PreOrder(OrgChart::Node *ptr)
                : pointer_to_current_node(ptr),Iterator(ptr) {}

        PreOrder& operator++();
        PreOrder operator++(int );



    };

}


#endif //CPP_ORGCHART_A_ORGCHART_HPP
