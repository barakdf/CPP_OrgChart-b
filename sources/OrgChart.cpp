//
// Created by barak on 16/05/2022.
//

#include "OrgChart.hpp"

#include <utility>




using namespace ariel;

OrgChart &OrgChart::add_root(const std::string &title) {
    int ROOT_INIT = 0;
    if (this->root == nullptr) {
        Node e(title, ROOT_INIT, ROOT_INIT);
        this->members.insert({title, e});
        this->root = &(this->members.at(title));
    } else {
//        auto itr = this->members.find(this->root->right)
        std::string name = (this->root)->_title();
        this->members.insert({title, *(this->root)});
        this->members.at(title).set_title(title);
        this->root = &(this->members.at(title));
//        this->root->set_title(title);
        this->members.erase(name);

    }
    return *this;
}

OrgChart &OrgChart::add_sub(const std::string &curr_title, const std::string &new_title) {
    /** CHECK If the parent exist in the chart. Case FALSE -> Throw Exception */
    if (this->members.find(curr_title) == this->members.end()) {
        throw std::invalid_argument("Parent Not Found\n");
    }
    if (curr_title == new_title) {
        return *this;
    }
    /*make new node with basic data and defaults*/
    Node *parent = &(members.at(curr_title));
    Node child{new_title, parent->get_num_children(), parent->_level(), parent};

    /* Always happening */
    this->members.insert({new_title, child});

    /* setting right node and left node if exist.
     * if no siblings then left node remain null
     * if there is no cousins on left then right node remain null*/
    std::cout << "Parent num of childern " << parent->children.size() << "\n";
    if (!parent->children.empty()) {
        Node *temp = &this->members.at(new_title);
        this->members.at(new_title).left = parent->children.at(parent->get_num_children() - 1);
        this->members.at(new_title).right = parent->children.at(parent->get_num_children() - 1)->right;


        if (this->members.at(new_title).right != nullptr) {
            parent->right->children.at(0)->left = temp;
        }
        parent->children.at(parent->get_num_children() - 1)->right = temp;

    } else {
        Node *p_r = parent;
        Node *p_l = parent;
        while (p_l->left != nullptr) {
            if (!(p_l->left->children.empty())) {
                this->members.at(new_title).left = p_l->left->children.at(p_l->left->get_num_children() - 1);
                p_l->left->children.at(p_l->left->get_num_children() - 1)->right = &(this->members.at(new_title));
                break;
            }
            p_l = p_l->left;
        }

        while (p_r->right != nullptr) {
            if (!(p_r->right->children.empty())) {
                this->members.at(new_title).right = p_r->right->children.at(0);
                p_r->right->children.at(0)->left = &(this->members.at(new_title));
                break;
            }
            p_r = p_r->right;
        }
    }

    this->members.at(curr_title).add_child(&this->members.at(new_title));


//    if (parent->right != nullptr ) {
//        if (parent->right->children[0] != nullptr) {
//            this->members.at(new_title).right = (parent->right->children.at(0));
//            parent->right->children.at(0)->left = &this->members.at(new_title);
//        }
//    }







    return *this;
}

auto OrgChart::get_members() {
    return &(this->members);
}

LevelOrder OrgChart::begin_level_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return LevelOrder{this->root};
}

LevelOrder OrgChart::end_level_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return LevelOrder{nullptr};
}

LevelOrder OrgChart::begin() {
    return this->begin_level_order();
}

LevelOrder OrgChart::end() {
    return this->end_level_order();
}

ReverseLevelOrder OrgChart::begin_reverse_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    Node *temp = this->root;

    while (!temp->children.empty()) {
        temp = temp->children.at(0);
        if (temp->children.empty()) {
            Node *temp2 = temp->right;
            while (temp2 != nullptr) {
                if (!(temp2->children.empty())) {
                    temp = temp2;
                    break;
                }
                temp2 = temp2->right;

            }
        }
    }

//    while (true) {
//        if (!temp->children.empty()) {
//            temp = temp->children.at(0);
//        } else if (temp->right != nullptr) {
//            temp = temp->right;
//        } else {
//            break;
//        }
//    }


    return ReverseLevelOrder{temp};
}

ReverseLevelOrder OrgChart::reverse_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return ReverseLevelOrder{nullptr};
}

PreOrder OrgChart::begin_preorder() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return PreOrder{this->root};
}

PreOrder OrgChart::end_preorder() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return PreOrder{nullptr};
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart &orgChart) {
    ostream << "hi";
    return ostream;
}

/** ------------ Node Class */

size_t OrgChart::Node::get_num_children() const {
    return this->children.size();
}

std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart::Node &node) {
    ostream << node.title << '\n';

    return ostream;
}

void OrgChart::Node::add_child(Node *child) {

    this->children.push_back(child);

}

std::string &OrgChart::Node::_title() {
    return this->title;
}

void OrgChart::Node::set_title(std::string _title) {
    this->title = std::move(_title);

}

int OrgChart::Node::size() {
    return (int) this->title.length();
}

size_t OrgChart::Node::_level() const {
    return this->level;
}

size_t OrgChart::Node::length() {
    return this->title.length();
}


/** Basic Iterator Parent Class */

OrgChart::Iterator::Iterator(const OrgChart::Iterator &other) : pointer_to_current_node(
        other.pointer_to_current_node) {}

OrgChart::Iterator &OrgChart::Iterator::operator=(const OrgChart::Iterator &other) {
    this->pointer_to_current_node = other.pointer_to_current_node;
    return *this;
}

const std::string &OrgChart::Iterator::operator*() const {
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
    if (this->pointer_to_current_node != nullptr) {
        if (other.pointer_to_current_node != nullptr) {
            return (this->pointer_to_current_node)->_title() == (other.pointer_to_current_node)->_title();
        }
        return false;
    } else {
        if (other.pointer_to_current_node == nullptr) {
            return true;
        }
        return false;
    }

}

//TODO
bool OrgChart::Iterator::operator!=(const OrgChart::Iterator &other) {
    if (this->pointer_to_current_node == nullptr && other.pointer_to_current_node == nullptr) {
        return false;
    }
    return !(*this == other);
}






/** Level Order Class */




/* Postfix */
//TODO
const ariel::LevelOrder LevelOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}


/* Prefix */
//TODO
LevelOrder &LevelOrder::operator++() {
//    std::cout<< (this->pointer_to_current_node)->_title() << std::endl;
    if (pointer_to_current_node->right == nullptr) {
        while (pointer_to_current_node->left != nullptr) {
            pointer_to_current_node = pointer_to_current_node->left;
        }
        while (pointer_to_current_node->children.empty()) {
            pointer_to_current_node = pointer_to_current_node->right;
            if (pointer_to_current_node == nullptr) {
                return *this;
            }
        }
        pointer_to_current_node = pointer_to_current_node->children.at(0);

    } else {
        pointer_to_current_node = pointer_to_current_node->right;
    }
    return *this;
}



/** ReverseLevelOrder */


/* Prefix */
//TODO
ReverseLevelOrder &ReverseLevelOrder::operator++() {
    std::string s = (pointer_to_current_node)->_title();
    if (pointer_to_current_node->right == nullptr) {

        pointer_to_current_node = pointer_to_current_node->parent;
        if (pointer_to_current_node == nullptr) {
            return *this;
        }
        while (pointer_to_current_node->left != nullptr) {
            pointer_to_current_node = pointer_to_current_node->left;
        }


    } else {
        pointer_to_current_node = pointer_to_current_node->right;
    }
    return *this;
}

/* Postfix */
//TODO
const ReverseLevelOrder ReverseLevelOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}




/** PreOrder */


/* Prefix */
//TODO
PreOrder &PreOrder::operator++() {
    if (this->pointer_to_current_node->parent == nullptr) {
        if (!this->pointer_to_current_node->children.empty()) {
            this->pointer_to_current_node = this->pointer_to_current_node->children.at(0);
        } else {
            this->pointer_to_current_node = this->pointer_to_current_node->parent;
        }
        return *this;
    }
    if (!this->pointer_to_current_node->children.empty()) {
        this->pointer_to_current_node = this->pointer_to_current_node->children.at(0);
    } else {
        while (this->pointer_to_current_node ==
               this->pointer_to_current_node->parent->children.at(
                       this->pointer_to_current_node->parent->get_num_children() - 1)) {

            this->pointer_to_current_node = this->pointer_to_current_node->parent;
            if (this->pointer_to_current_node->parent == nullptr) {
                this->pointer_to_current_node = this->pointer_to_current_node->parent;
                return *this;
            }
        }
        this->pointer_to_current_node = this->pointer_to_current_node->right;
    }
    return *this;
}

/* Postfix */
//TODO
const PreOrder PreOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}



