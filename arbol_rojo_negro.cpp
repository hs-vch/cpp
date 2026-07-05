

template<typename T>
class RBTree {
private:
    enum Color { RED = 0, BLACK = 1 };

    struct Node {
        T key;
        Color color;
        Node* left;
        Node* right;
        Node* parent;
        Node(const T& k, Color c, Node* l, Node* r, Node* p)
            : key(k), color(c), left(l), right(r), parent(p) {}
    };

    Node* root;
    Node* NIL; // nodo sentinela (hojas)
    bool (*cmp)(const T&, const T&); // comparador: true si a < b

    // Helpers
    bool less_than(const T& a, const T& b) const {
        if (cmp) return cmp(a,b);
        // Si no hay cmp, asumimos que T define operator<
        return a < b;
    }
    bool equal_to(const T& a, const T& b) const {
        return (!less_than(a,b) && !less_than(b,a));
    }

    void left_rotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != NIL) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void right_rotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != NIL) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == NIL) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insert_fixup(Node* z) {
        while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node* y = z->parent->parent->right; // uncle
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                // mirror
                Node* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == NIL) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    Node* tree_minimum(Node* x) {
        while (x->left != NIL) x = x->left;
        return x;
    }

    void delete_fixup(Node* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    left_rotate(x->parent);
                    x = root;
                }
            } else {
                // mirror
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    right_rotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    // recursion helper para liberar nodos
    void free_subtree(Node* x) {
        if (x == NIL) return;
        free_subtree(x->left);
        free_subtree(x->right);
        delete x;
    }

public:
    // Constructor: si cmp == nullptr, se usa operator< del tipo T
    RBTree(bool (*compare)(const T&, const T&) = 0) : cmp(compare) {
        // crear NIL sentinel
        NIL = (Node*) operator new(sizeof(Node));
        // Colocar valores seguros en NIL (no usar constructor normal que espera key)
        // inicializamos campos manualmente
        new (NIL) Node(T(), BLACK, nullptr, nullptr, nullptr); // placement new para inicializar
        NIL->left = NIL->right = NIL->parent = NIL;
        root = NIL;
    }

    // Destructor
    ~RBTree() {
        free_subtree(root);
        // destruir y liberar NIL
        NIL->~Node();
        operator delete(NIL);
    }

    // Prohibir copia por defecto (evitar inconsistencias)
    RBTree(const RBTree&) = delete;
    RBTree& operator=(const RBTree&) = delete;

    // Buscar: devuelve puntero al nodo (o NIL si no existe)
    Node* search(const T& key) const {
        Node* x = root;
        while (x != NIL) {
            if (equal_to(key, x->key)) return x;
            if (less_than(key, x->key)) x = x->left;
            else x = x->right;
        }
        return NIL;
    }

    // Insert: retorna true si inserta, false si key ya existe
    bool insert(const T& key) {
        Node* z = new Node(key, RED, NIL, NIL, NIL);
        Node* y = NIL;
        Node* x = root;
        while (x != NIL) {
            y = x;
            if (equal_to(z->key, x->key)) {
                delete z;
                return false; // no insertamos duplicados por diseño
            }
            if (less_than(z->key, x->key)) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == NIL) root = z;
        else if (less_than(z->key, y->key)) y->left = z;
        else y->right = z;
        z->left = NIL;
        z->right = NIL;
        z->color = RED;
        insert_fixup(z);
        return true;
    }

    // Remove: retorna true si eliminó, false si no existía
    bool remove(const T& key) {
        Node* z = search(key);
        if (z == NIL) return false;
        Node* y = z;
        Color y_original_color = y->color;
        Node* x;
        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = tree_minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == BLACK) delete_fixup(x);
        return true;
    }

    // Recorrido in-order con callback. visit recibe const T&
    void inorder_traversal(void (*visit)(const T&)) const {
        Node* cur = root;
        // usare recursion simple (depth = O(h))
        inorder_recursive(cur, visit);
    }

private:
    void inorder_recursive(Node* x, void (*visit)(const T&)) const {
        if (x == NIL) return;
        inorder_recursive(x->left, visit);
        visit(x->key);
        inorder_recursive(x->right, visit);
    }
};
