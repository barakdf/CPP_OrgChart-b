//
// Created by barak on 16/05/2022.
//

#include "OrgChart.hpp"

#include <utility>


using namespace ariel;

OrgChart &OrgChart::add_root(const std::string &title) {
    size_t ROOT_INIT = 0;
    if (this->root == nullptr) {
        Node e(title, ROOT_INIT);
        this->members.insert({title, e});
        this->root = &(this->members.at(title));
        this->levels.insert({ROOT_INIT, &this->members.at(title)});
    } else {
        std::string name = (this->root)->_title();
        this->members.insert({title, *(this->root)});
        this->members.at(title).set_title(title);
        this->root = &(this->members.at(title));
        this->members.erase(name);
        this->levels.at(ROOT_INIT) = &(this->members.at(title));

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
    Node child{new_title, parent->_level()+1, parent};


    /* Always happening */
    this->members.insert({new_title, child});

    if (child._level() > this->max_level) {
        this->levels.insert({child._level(), &(this->members.at(new_title))});
        this->max_level = child._level();
    }
    /* setting right node and left node if exist.
     * if no siblings then left node remain null
     * if there is no cousins on left then right node remain null*/
    std::cout << "Parent num of childern " << parent->children.size() << "\n";
    if (!parent->children.empty()) {

        Node *temp = &this->members.at(new_title);
        /* in case there is siblings the new node will set his left pointer to the prev child,
         * new node will take the prev child right node pointer*/
        this->members.at(new_title).left = parent->children.at(parent->get_num_children() - 1);
        this->members.at(new_title).right = parent->children.at(parent->get_num_children() - 1)->right;

        /* if the node to the right of the new node is not null, set the right node left pointer to the new node.
         * ELSE, the right node of the new node will remain nullptr */
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
    if (this->members.at(new_title).left == nullptr) {
        this->levels.at(child._level()) = &(this->members.at(new_title));
    }

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
    return LevelOrder{&(this->levels),this->root};
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
//    Node *temp = this->root;


//    while (!temp->children.empty()) {
//        temp = temp->children.at(0);
//        if (temp->children.empty()) {
//            Node *temp2 = temp->right;
//            while (temp2 != nullptr) {
//                if (!(temp2->children.empty())) {
//                    temp = temp2;
//                    break;
//                }
//                temp2 = temp2->right;
//
//            }
//        }
//    }

//    while (true) {
//        if (!temp->children.empty()) {
//            temp = temp->children.at(0);
//        } else if (temp->right != nullptr) {
//            temp = temp->right;
//        } else {
//            break;
//        }
//    }


    return ReverseLevelOrder{&(this->levels),this->levels.at(max_level)};
}

ReverseLevelOrder OrgChart::reverse_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return ReverseLevelOrder{};
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

OrgChart::Iterator &OrgChart::Iterator::operator=(const OrgChart::Iterator &other) = default;

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
    }
    return other.pointer_to_current_node == nullptr;



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
ariel::LevelOrder LevelOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}


/* Prefix */
//TODO
LevelOrder &LevelOrder::operator++() {
    /** handling only by node fields , Less Performance */
//    if (pointer_to_current_node->right == nullptr) {
//        while (pointer_to_current_node->left != nullptr) {
//            pointer_to_current_node = pointer_to_current_node->left;
//        }
//        while (pointer_to_current_node->children.empty()) {
//            pointer_to_current_node = pointer_to_current_node->right;
//            if (pointer_to_current_node == nullptr) {
//                return *this;
//            }
//        }
//        pointer_to_current_node = pointer_to_current_node->children.at(0);
//
//    } else {
//        pointer_to_current_node = pointer_to_current_node->right;
//    }

    /** store ONLY pointer to map, increasing performance.*/
    if (pointer_to_current_node->right == nullptr) {
        size_t curr_lvl = pointer_to_current_node->_level();
        if (this->level->find(curr_lvl + 1) == this->level->end()) {
            pointer_to_current_node = nullptr;
            return *this;
        }
        this->pointer_to_current_node = this->level->at(curr_lvl + 1);
    } else {
        this->pointer_to_current_node = this->pointer_to_current_node->right;
    }
    return *this;
}



/** ReverseLevelOrder */


/* Prefix */
//TODO
ReverseLevelOrder &ReverseLevelOrder::operator++() {

    /** handling only by node fields , Less Performance */

//    std::string s = (pointer_to_current_node)->_title();
//    if (pointer_to_current_node->right == nullptr) {
//
//        pointer_to_current_node = pointer_to_current_node->parent;
//        if (pointer_to_current_node == nullptr) {
//            return *this;
//        }
//        while (pointer_to_current_node->left != nullptr) {
//            pointer_to_current_node = pointer_to_current_node->left;
//        }
//
//
//    } else {
//        pointer_to_current_node = pointer_to_current_node->right;
//    }
//    if (pointer_to_current_node->right == nullptr) {
//        pointer_to_current_node =
//    }

    /** store ONLY pointer to map, increasing performance.*/

    if (pointer_to_current_node->right == nullptr) {
        size_t curr_lvl = pointer_to_current_node->_level();
        if (curr_lvl == 0) {
            pointer_to_current_node = nullptr;
            return *this;
        }
        this->pointer_to_current_node = this->level->at(curr_lvl - 1);
    } else {
        this->pointer_to_current_node = this->pointer_to_current_node->right;
    }
    return *this;
}

/* Postfix */
//TODO
ReverseLevelOrder ReverseLevelOrder::operator++(int) {
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
PreOrder PreOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}



