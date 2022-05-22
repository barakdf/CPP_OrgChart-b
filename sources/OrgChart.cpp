//
// Created by barak on 16/05/2022.
//

#include "OrgChart.hpp"

#include <utility>

using namespace ariel;

OrgChart &OrgChart::add_root(const std::string& title) {
    if (this->root == nullptr) {
        Node e(title, 0);
        this->members.insert({title,e});
        this->root = &(this->members.at(title))    ;
    } else {
        this->root->set_title(title);
    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string& curr_title, const std::string& new_title) {
    if (this->members.find(curr_title) == this->members.end()) {
        throw std::invalid_argument("Parent Not Found\n");
    }

    Node *parent = &(members.at(curr_title));
    Node child{new_title, parent->get_num_childs()};
    this->members.insert({new_title, child});
    this->members.at(curr_title).add_child(&this->members.at(new_title));
    return *this;
}

auto OrgChart::get_members() {
    return &(this->members);
}

LevelOrder OrgChart::begin_level_order() {
    return LevelOrder{this->root};
}

LevelOrder OrgChart::end_level_order() {
    return LevelOrder{nullptr};
}

LevelOrder OrgChart::begin() {
    return this->begin_level_order();
}

LevelOrder OrgChart::end() {
    return this->end_level_order();
}

ReverseLevelOrder OrgChart::begin_reverse_order() {
    return ReverseLevelOrder{this->root};
}

ReverseLevelOrder OrgChart::reverse_order() {
    return ReverseLevelOrder{nullptr};
}

PreOrder OrgChart::begin_preorder() {
    return PreOrder{this->root};
}

PreOrder OrgChart::end_preorder() {
    return PreOrder{nullptr};
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart &orgChart) {
    ostream << "hi";
    return ostream;
}

/** ------------ Node Class */

size_t OrgChart::Node::get_num_childs() {

    return 0;
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart::Node &node) {
    ostream << node.title << '\n';

    return ostream;
}

void OrgChart::Node::add_child(Node *child) {

    this->childs.push_back(child);

}

const std::string &OrgChart::Node::_title() {
    return this->title;
}

void OrgChart::Node::set_title(std::string _title) {
    this->title = std::move(_title);

}

int OrgChart::Node::size() {
    return this->title.length();
}


/** Basic Iterator Parent Class */

OrgChart::Iterator &OrgChart::Iterator::operator=(const OrgChart::Iterator &other) = default;

const std::string &OrgChart::Iterator::operator*() const{
    if (this->pointer_to_current_node == nullptr) {
        throw std::invalid_argument("NULL PTR");
    }
    return (this->pointer_to_current_node)->_title();
}

OrgChart::Node *OrgChart::Iterator::operator->() const {
    return this->pointer_to_current_node;
}

/* Boolean */
//TODO
bool OrgChart::Iterator::operator==(const OrgChart::Iterator &other) {
    return false;
}
//TODO
bool OrgChart::Iterator::operator!=(const OrgChart::Iterator &other) {
    return false;
}


/** Level Order Class */




/* Prefix */
//TODO
const LevelOrder LevelOrder::operator++(int) {
    return *this;
}

/* Postfix */
//TODO
LevelOrder &LevelOrder::operator++() {
    return *this;
}



/** ReverseLevelOrder */


/* Prefix */
//TODO
ReverseLevelOrder &ReverseLevelOrder::operator++() {
    return *this;
}

/* Postfix */
//TODO
const ReverseLevelOrder ReverseLevelOrder::operator++(int) {
    return *this;
}




/** PreOrder */


/* Prefix */
//TODO
PreOrder &PreOrder::operator++() {
    return *this;
}

/* Postfix */
//TODO
const PreOrder PreOrder::operator++(int) {
    return *this;
}



