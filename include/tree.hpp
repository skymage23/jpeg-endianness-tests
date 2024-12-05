#include <memory>
#include <vector>


#include <error_handling/exceptions.hpp>

#ifndef CNN_PRACTICE_TREE
#define CNN_PRACTICE_TREE


namespace cnn_practice {
    namespace collections {

        class TreeNode {
            private:
            bool leaf;

            public:
            std::shared_ptr<std::vector<std::shared_ptr<TreeNode>>> children;
            std::shared_ptr<TreeNode> parent;

            //protected:
            public:
            TreeNode(bool leaf, const std::shared_ptr<TreeNode> parent){
                this -> parent = parent;
                this -> leaf = leaf;
            }
            
            bool is_leaf(){ return this -> leaf; }

            public:
            TreeNode(TreeNode&& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> leaf = input.leaf;
            }

            TreeNode(TreeNode& input){
                this -> parent = input.parent;
                this -> children = input.children;
                this -> leaf = input.leaf;
            }

            TreeNode() {
                this -> parent = nullptr;
                this -> children = nullptr;
                this -> leaf = false;
            }

            void addChild(std::shared_ptr<TreeNode> child){
                this -> children -> push_back(child);
            }
        };

        template <typename T> class DataStoreTreeNode : public TreeNode {
            private:
            T value;

            public:
            DataStoreTreeNode() : TreeNode() {}
            DataStoreTreeNode(DataStoreTreeNode<T>& input) : 
                TreeNode(std::static_pointer_cast<TreeNode>(input)) {
                this -> value = input.value;
            }
            DataStoreTreeNode(TreeNode& input) : TreeNode(input){}
            DataStoreTreeNode(
                bool is_leaf,
                const T& value,
                std::shared_ptr<collections::DataStoreTreeNode<T>> parent
            ) : TreeNode(is_leaf, parent){
                this -> value = value;
            }
            DataStoreTreeNode(DataStoreTreeNode&& input) : TreeNode(    
                static_cast<TreeNode&&>(input) 
            ){
                this -> value = input.value;
            }

            T getValue() {
                return value;
            }
        };

        // T = externally expected API type.
        // U = internal representation type.
        // The two are not always the same.
        template <typename T, typename U> class Tree {
            protected:
            std::shared_ptr<DataStoreTreeNode<U>> root;

            protected:
            Tree(const T& input) {
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


            virtual std::shared_ptr<TreeNode> walk(
                __attribute__((unused)) const T& input
            ){
                throw new cnn_practice::error_handling::NotImplementedException();
            }

            public:
            Tree() =  default;
            Tree(Tree&& input) {
                this -> root = input.root;
            }
            bool contains(const T& input) { return (this -> walk(input)) != nullptr; }

            virtual void add( __attribute__((unused)) const T& input){
                throw new cnn_practice::error_handling::NotImplementedException();
            }
            virtual std::vector<std::string> to_string(){
                throw new cnn_practice::error_handling::NotImplementedException();
            };
        };
    };
};
#endif