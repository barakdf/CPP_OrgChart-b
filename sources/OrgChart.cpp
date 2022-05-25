//
// Created by barak on 16/05/2022.
//

#include "OrgChart.hpp"



using namespace ariel;

/** --------------------------------- OrgChart --------------------------------*/

/** add_root method is using to add a new root or to update the existing one,
 * check if root is null (does not initialized yet),
 * Case True -> create a new node, insert the node to the member map(main collection of nodes for quick pull)
 *              assign the root pointer to the stored place in the member map.
 *              insert the root to the level map. (for reverse/order iterators)
 * Case False -> insert the root in the map with new key_name.
 *               change the title of the node in the new place.
 *               assign the root pointer independent field to point on the new node stored in the map.
 *               erase the old node with old name from the member map.
 *               update the root to the level map. (for reverse/order iterators)*/
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
    /* make new node with basic data and defaults */
    Node *parent = &(members.at(curr_title));
    Node child{new_title, parent->_level() + 1, parent};


    /* Always happening */
    this->members.insert({new_title, child});

    if (child._level() > this->max_level) {
        this->levels.insert({child._level(), &(this->members.at(new_title))});
        this->max_level = child._level();
    }
    /* setting right node and left node if they are existed.
     * if no siblings then left node remain null
     * if there is no cousins on left then right node remain null*/
//    std::cout << "Parent num of childern " << parent->children.size() << "\n";
    if (!parent->children.empty()) {

        Node *temp = &this->members.at(new_title);
        /* in case there is siblings the new node will set his left pointer to the prev child,
         * new node will take the prev child right node pointer */
        this->members.at(new_title).left = parent->children.at(parent->get_num_children() - 1);
        this->members.at(new_title).right = parent->children.at(parent->get_num_children() - 1)->right;

        /* if the node to the right of the new node is not null, set the right node left pointer to the new node.
         * ELSE, the right node of the new node will remain nullptr */
        if (this->members.at(new_title).right != nullptr) {
            parent->right->children.at(0)->left = temp;
        }
        parent->children.at(parent->get_num_children() - 1)->right = temp;

    } else {
        /** create two temp parents,
         * left parent who will iterate all left nodes of the curr parent
         * right parent who will iterate all right nodes of the curr parent.
         * at each left/right node check if he has children,
         * Case True ->
         *              Left will be the last child of the left parent to and assign to left node of the curr node,
         *              and curr node will be the right of him
         *              Right will be the first child of the right parent and assign to the right node of the curr node,
         *              and curr node will be the left of him
         *              */

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

    /** add to parent children vec,
     * if the left node of the sub is nullptr, then it means he is the first node if hes level,
     * and will be assign in the level map
     * */
    this->members.at(curr_title).add_child(&this->members.at(new_title));
    if (this->members.at(new_title).left == nullptr) {
        this->levels.at(child._level()) = &(this->members.at(new_title));
    }

    return *this;
}

/** return the members map */
auto OrgChart::get_members() {
    return &(this->members);
}

/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> iterator with levels_map and pointer to the root */
LevelOrder OrgChart::begin_level_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return LevelOrder{&(this->levels), this->root};
}
/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> return iterator with nullptr value*/
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
/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> return reverse iterator assign with levels_map
 *                               and the last value of the levels_map*/
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


    return ReverseLevelOrder{&(this->levels), this->levels.at(max_level)};
}
/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> return iterator with nullptr value*/
ReverseLevelOrder OrgChart::reverse_order() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return ReverseLevelOrder{};
}
/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> iterator with the root */
PreOrder OrgChart::begin_preorder() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return PreOrder{this->root};
}
/** Check if the root is nullptr, Case True -> throw exception (chart is empty)
 *                               Case False -> return iterator with nullptr value */
PreOrder OrgChart::end_preorder() {
    if (this->root == nullptr) {
        throw std::invalid_argument("Chart is empty\n");
    }
    return PreOrder{nullptr};
}

/** cout operator for the whole chart */
std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart &orgChart) {

    for (auto iter = orgChart.levels.begin(); iter != orgChart.levels.end(); ++iter ) {
        OrgChart::Node *e = iter->second;
        size_t counter = 0;
        while (e != nullptr) {
            ostream << "  " <<e->_title() << "  ";
            counter++;

            e = e->right;

        }
        ostream << "\n";
        for (int i = 0; i < counter; ++i) {
            ostream << "----||----";
        }
        ostream << "\n";
    }
    return ostream;
}

/** ------------ Node Class ---------------*/

/** return the size of children-vector*/
size_t OrgChart::Node::get_num_children() const {
    return this->children.size();
}
/** cout operator for each node, print the title of the node.*/
std::ostream &ariel::operator<<(std::ostream &ostream, OrgChart::Node &node) {
    ostream << node.title << '\n';

    return ostream;
}

/** handle the appending of a new child to the Node*/
void OrgChart::Node::add_child(Node *child) {
    this->children.push_back(child);
}

/** title getters and setters */

/* title getter*/
std::string &OrgChart::Node::_title() {
    return this->title;
}

/* title setter */
void OrgChart::Node::set_title(std::string _title) {
    this->title = std::move(_title);

}
/** getters for the title length.
 * I made two of these in different name because of studentTests conflict..*/

/* return the length of the title (string.length)*/
int OrgChart::Node::size() {
    return (int) this->title.length();
}

/* return the length of the title (string.length)*/
size_t OrgChart::Node::length() {
    return this->title.length();
}

/** return the specific char in the name at index(param) place */
char OrgChart::Node::at(size_t i) {
    return this->title.at(i);
}

/* return the level of this node in the chart tree
 * used for reverse/level iterators */
size_t OrgChart::Node::_level() const {
    return this->level;
}


/** Basic Iterator Parent Class */

OrgChart::Iterator::Iterator(const OrgChart::Iterator &other):pointer_to_current_node(other.pointer_to_current_node) {};

/* assignment operator is defined as default,
 * no heap data need to be handled and no delete methods implemented.
 * */
OrgChart::Iterator &OrgChart::Iterator::operator=(const OrgChart::Iterator &other) = default;

const std::string &OrgChart::Iterator::operator*() const {
    /* check if the pointer is null,
     * Case True -> throw exception.
     * Otherwise, return the current node title.*/
    if (this->pointer_to_current_node == nullptr) {
        throw std::invalid_argument("NULL PTR\n");
    }

    return (this->pointer_to_current_node)->_title();
}

/* return the current node pointer */
OrgChart::Node *OrgChart::Iterator::operator->() const {
    return this->pointer_to_current_node;
}

/** Boolean */
/**check if the left node is nullptr,
     *      Case False -> check if the other node is nullptr,
     *                          Case True -> return false  otherwise return (left node title == right node title)
     *      Otherwise, return (left node == nullptr) */
bool OrgChart::Iterator::operator==(const OrgChart::Iterator &other) {


    if (this->pointer_to_current_node != nullptr) {
        if (other.pointer_to_current_node != nullptr) {
            return (this->pointer_to_current_node)->_title() == (other.pointer_to_current_node)->_title();
        }
        return false;
    }
    return other.pointer_to_current_node == nullptr;


}

bool OrgChart::Iterator::operator!=(const OrgChart::Iterator &other) {

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
    /**
     * check if the current node have a right node,
     * if true -> assign the current node to be he's right.
     * Otherwise -> if the chart has next level, assign to be the first of the next one (using levels_map),
     *              else return a nullptr.
     * */
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

    /**
     * check if the current node have a right node,
     * if true -> assign the current node to be he's right.
     * Otherwise -> if the chart has prev level, assign to be the first of the prev one (using levels_map),
     *              else return a nullptr.
     * */

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
/** same temp form of the iterator, increasing the original iterator, and returning the temp.*/
ReverseLevelOrder ReverseLevelOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}




/** PreOrder */


/* Prefix */
/** check if the parent is null, if true then its the root and the next node will be hes first child and return.
 *  if the current node does not have children, than he is a leaf, while the child is not the last child,
 *  the current node will be the right sibling,
 *  if the child is the last child then we move to the parent->right (if exist)
 *  if the same operation leads to the root, the current node is the last -> return nullptr.
 *  */
PreOrder &PreOrder::operator++() {
    if (this->pointer_to_current_node->parent == nullptr) {
        if (!this->pointer_to_current_node->children.empty()) {
            this->pointer_to_current_node = this->pointer_to_current_node->children.at(0);
        } else {
            this->pointer_to_current_node = nullptr;
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
            /* check if the "recursion" got up to the root - means that it is the last node.*/
            if (this->pointer_to_current_node->parent == nullptr) {
                this->pointer_to_current_node = nullptr;
                return *this;
            }
        }
        this->pointer_to_current_node = this->pointer_to_current_node->right;
    }
    return *this;
}

/* Postfix */
PreOrder PreOrder::operator++(int) {
    auto temp = *this;
    ++(*this);
    return temp;
}



