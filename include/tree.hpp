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
            TreeNode(bool is_root, bool is_leaf, std::shared_ptr<TreeNode> parent){
                this -> parent = parent;
                this -> is_root = is_root;
                this -> is_leaf = is_leaf;
            }

            TreeNode(TreeNode&& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> is_root = input.is_root;
                this -> is_leaf = input.is_leaf;
            }

            bool is_root(){ return this -> is_root; }
            bool is_leaf(){ return this -> is_leaf; }

            public:
            TreeNode() {
                this -> parent = nullptr;
                this -> children = nullptr;
                this -> is_root = false;
                this -> is_leaf = false;
            }
        };

        class RootTreeNode : TreeNode{
            protected:
            RootTreeNode() : TreeNode(true, false, nullptr){}
        };

        class LeafBearingTreeNode : TreeNode {
            protected:
            LeafBearingTreeNode(
                bool is_leaf,
                std::shared_ptr<TreeNode> parent
            ) : TreeNode(false, is_leaf, parent) {}
        };

        template <typename T> class DataStoreTreeNode : LeafBearingTreeNode{
            public:
            T value;

            protected:
            DataStoreTreeNode(
                bool is_leaf,
                T value,
                std::shared_ptr<TreeNode> parent,
            ) : LeafBearingTreeNode(is_leaf, parent){
                this -> value = value;
            }

            DataStoreTreeNode(DataStoreTreeNode&& input) : TreeNode(input) {
                this -> value = value;
            }

            public:
            DataStoreTreeNode() : TreeNode(){}
        };
    };

    template <typename T> class Tree : RootTreeNode {
        protected:
        Tree(const T& input) : RootTreeNode(){
            this -> add(T);
        }

        //Returns a reference to the final
        //TreeNode found when searching for
        //"input" in the tree. If "input"
        //is not found, returns "nullptr".

        virtual std::shared_ptr<TreeNode> walk(const T& input);

        public:
        Tree() : RootTreeNode(){};
        Tree(Tree&& input) : RootTreeNode(input){};


        bool contains(const T& input) { return (this -> walk(input)) != nullptr; }
        virtual void add(const T& input);
        virtual std::vector<std::string> to_string();
    };
};
#endif