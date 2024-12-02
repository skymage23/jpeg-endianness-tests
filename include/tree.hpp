#include <memory>
#include <vector>


#include <error_handling/exceptions.hpp>
#include <collections.hpp>

#ifndef CNN_PRACTICE_TREE
#define CNN_PRACTICE_TREE


namespace cnn_practice {
    namespace collections {

        class TreeNode {
            private:
            bool root;
            bool leaf;

            protected:
            std::shared_ptr<TreeNode> parent;
            std::shared_ptr<std::vector<TreeNode>> children;

            //protected:
            public:
            TreeNode(bool root, bool leaf, std::shared_ptr<TreeNode> parent){
                this -> parent = parent;
                this -> root = root;
                this -> leaf = leaf;
            }

            
            bool is_root(){ return this -> root; }
            bool is_leaf(){ return this -> leaf; }

            public:
            TreeNode(TreeNode&& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> root = input.root;
                this -> leaf = input.leaf;
            }

            TreeNode(TreeNode& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> root = input.root;
                this -> leaf = input.leaf;
            }

            TreeNode() {
                this -> parent = nullptr;
                this -> children = nullptr;
                this -> root = false;
                this -> leaf = false;
            }

            void addChild(std::shared_ptr<TreeNode> child){
                this -> children -> push_back(child);
            }
        };

        class RootTreeNode : TreeNode {
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
                std::shared_ptr<TreeNode> parent
            ) : LeafBearingTreeNode(is_leaf, parent){
                this -> value = value;
            }

            DataStoreTreeNode(DataStoreTreeNode&& input) : TreeNode(input) {
                this -> value = value;
            }

            public:
            DataStoreTreeNode() : TreeNode(){}
        };

        template <typename T> class Tree : RootTreeNode {

            
            private:

            protected:
            Tree(const T& input) : RootTreeNode(){
                this -> add(input);
            }

            //Returns a reference to the final
            //TreeNode found when searching for
            //"input" in the tree. If "input"
            //is not found, returns "nullptr".

            //namespacing required probably due to how virtuals
            //are handled in the implementation.

            //allow_prefix_match: Match as many characters
            //    as possible in the input string, but
            //    stop and return a reference to the last
            //    matching character.


            virtual std::shared_ptr<
                CN_COLL_NS(TreeNode)
            > walk(const T& input){
                throw new cnn_practice::error_handling::NotImplementedException();
            }

            public:
            Tree() : RootTreeNode(){}
            Tree(Tree&& input) : RootTreeNode(input){}

            bool contains(const T& input) { return (this -> walk(input)) != nullptr; }

            virtual void add(const T& input){
                throw new cnn_practice::error_handling::NotImplementedException();
            }
            virtual std::vector<std::string> to_string(){
                throw new cnn_practice::error_handling::NotImplementedException();
            };
        };
    };
};
#endif