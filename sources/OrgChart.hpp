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
        friend class LevelOrder;
        friend class ReverseLevelOrder;
        friend class PreOrder;
        class Node {
        private:
            std::string title;
            Node* parent;
            std::vector<Node*> childs;
            int _size;
            size_t index;

        public:
            Node(std::string  title, size_t _index):title(std::move(title)), parent(nullptr), _size(0), index(_index){}

            void add_child(Node* child);

            const std::string & _title();

            void set_title(std::string _title);

            size_t get_num_childs();

            int size();

            friend std::ostream & operator<< (std::ostream &ostream, Node& node);
        };

    private:
        Node *root;
        /* map of members for O(1) search of a member node */
        std::unordered_map<std::string, Node> members;


    public:
        OrgChart() : root(nullptr) {}

        OrgChart &add_root(const std::string& title);

        OrgChart &add_sub(const std::string& curr_title, const std::string& new_title);

        auto get_members();




        /** -------------- Iterator Classes */


        /** Basic Iterator Parent Class
         * this class will contain all the common implementation of tha sub behave iterators.*/

        class Iterator {
        private:
            Node *pointer_to_current_node;
        public:
            Iterator(Node *ptr = nullptr): pointer_to_current_node(ptr){}

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
    public:
        explicit LevelOrder(OrgChart::Node *ptr = nullptr)
                : Iterator(ptr) {}

        LevelOrder& operator++();
        const LevelOrder operator++(int );

    };


    /* REVERSE LEVEL ORDER CLASS */
    class ReverseLevelOrder:public OrgChart::Iterator {
    public:
        explicit ReverseLevelOrder(OrgChart::Node *ptr = nullptr)
                : Iterator(ptr) {}

        ReverseLevelOrder& operator++();
        const ReverseLevelOrder operator++(int );


    };


    /* PRE ORDER CLASS */
    class PreOrder:public OrgChart::Iterator {

    public:
        explicit PreOrder(OrgChart::Node *ptr = nullptr)
                : Iterator(ptr) {}

        PreOrder& operator++();
        const PreOrder operator++(int );



    };

}


#endif //CPP_ORGCHART_A_ORGCHART_HPP
