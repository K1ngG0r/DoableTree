#include <iostream>
#include <string>

template<typename T>
class BinTree {
private:
    class Node {
    public:
        T value;
        Node* parent;
        Node* left;
        Node* right;
        Node(T value) : value{ value }, parent{ nullptr },
            left{ nullptr }, right{ nullptr } {}
        
        void Print(int indent, std::string name) {
            for (int i = 0; i < indent - 1; i++)
            {
                std::cout << '\t';
            }
            std::cout << name << (indent > 0 ? "\t" : "");

            std::cout << value << std::endl;
        }

    };
    Node* root;
public:
    BinTree() :root{ nullptr } {}
    
    ~BinTree()
    {
        DeleteNode(root);
    }

    bool IsEmpty() {
        return root == nullptr;
    }

    BinTree& Push(T value) {
        Node* node = new Node(value);
        if (IsEmpty()) {
            root = node;
            return *this;
        }

        Node* current = root;

        while (current != nullptr) {
            node->parent = current;
            current =   node->value > current->value ?
                        current = current->right : current = current->left;
        }

        if (node->value > node->parent->value)
            node->parent->right = node;
        else
            node->parent->left = node;

        return *this;
    }

    bool ElementCheck(T element) {
        Node* current = root;

        while (current != nullptr) {
            if (current->value == element)
                return true;
            current = element > current->value ?
                current = current->right : current = current->left;

        }
        return false;
    }

    void Print() {
        PrintNode(root, 0, "");
    }

    BinTree& DeleteElement(T element) {
        Node* current = root;

        while (current != nullptr) {
            if (current->value == element)
                break;
            current = element > current->value ?
                current = current->right : current = current->left;
        }

        if(current == nullptr){
            std::cout << "None" << std::endl;
            return *this;
        }

        Node* tmp = current;


        tmp->left != nullptr ? tmp = tmp->left : ;

        while (tmp->right != nullptr)
            tmp = tmp->right;

        if (current < tmp->parent->parent)
            tmp->parent->parent->left = tmp;
        else
            tmp->parent->parent->right = tmp;

        current->parent != nullptr ?  tmp->parent = current->parent;
        current->left != nullptr ? tmp->left = current->left;
        current->right != nullptr ? tmp->right = current->right;

        current->Print(0, ":");

        return *this;
    }
private:
    void DeleteNode(Node* node) {
        if (node->left)
            DeleteNode(node->left);
        if (node->right)
            DeleteNode(node->right);
        delete node;
    }

    void PrintNode(Node* node, int indent, std::string name) {
        node->Print(indent, name);
        if (node->left)
            PrintNode(node->left, indent + 1, "left");
        if (node->right)
            PrintNode(node->right, indent + 1, "right");
    }

};


int main()
{
    srand(time(nullptr));
    BinTree<int> tree;
    for (size_t i = 0; i < 10; i++)
    {
        tree.Push(rand() % 10 + 1);
    }
    tree.Print();
    tree.DeleteElement(3);
    tree.Print();
}
