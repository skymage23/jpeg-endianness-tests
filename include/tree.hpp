#include <memory>
#include <vector>


#ifndef CNN_PRACTICE_TREE
#define CNN_PRACTICE_TREE

namespace cnn_practice {
    namespace collections {
        class TreeNode {
            private:
            bool is_root;
            bool is_leaf;

            protected:
            std::shared_ptr<TreeNode> parent;
            std::shared_ptr<std::vector<TreeNode>> children;


            protected:
            TreeNode(bool is_root, std::shared_ptr<TreeNode> parent){
                this -> parent = parent;
                this -> is_root = is_root;
            }

            TreeNode(TreeNode&& input){
                this -> parent = input.parent;
                this -> children = input.children;
            }

            bool is_root(){ return this -> is_root; }

            public:
            TreeNode() {
                this -> parent = nullptr;
                this -> children = nullptr;
                this -> is_root = false;
            }
        };

        class RootTreeNode : TreeNode{
            protected:
            RootTreeNode() : TreeNode(false, nullptr){}
        };

        class LeafableTree

        template <typename T> class DataStoreTreeNode : TreeNode{
            public:
            T value;

            protected:
            DataStoreTreeNode(T value,
                std::shared_ptr<TreeNode> parent,
            ) : TreeNode(parent){
                this -> value = value;
            }

            DataStoreTreeNode(DataStoreTreeNode&& input) : TreeNode(input) {
                this -> value = value;
            }

            public:
            DataStoreTreeNode() : TreeNode(){}
        };
    };
};
#endif