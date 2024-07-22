#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

class Worker {
public:
    string education;
    double salary;
    int vacation;
    double extra;

    Worker(const string& education, double salary, int vacation, double extra) :
        education(education), salary(salary), vacation(vacation), extra(extra) {}

    virtual void duty() {
        cout << "Um die Kinder zu kuemmern." << endl;
    }

    void display() {
        ifstream inputFile(education);

        if (inputFile.is_open()) {
            string line;
            while (getline(inputFile, line)) {
                cout << line << endl;
            }

            inputFile.close();
        }
        else {
            cout << "Failed to open the file." << endl;
        }

        cout << "Die Bezahlung ist " << salary << endl;
        cout << "Der Urlaub ist " << vacation << endl;
        cout << "Die Auszeichnung ist " << salary * extra / 100 << endl;
    }
};

class Leiter : public Worker {
public:
    Leiter(const string& education, double salary, int vacation, double extra) :
        Worker(education, salary, vacation, extra) {}

    void duty() override {
        cout << "Den anderen Arbeitern zu schreien." << endl;
    }

};

class Teacher : public Worker {
public:
    Teacher(const string& education, double salary, int vacation, double extra) :
        Worker(education, salary, vacation, extra) {}

    void duty() override {
        cout << "Den Kindern zu schreien." << endl;
    }
};

class Nurse : public Worker {
private:
    int experience;

public:
    Nurse(const string& education, double salary, int vacation, double extra, int experience) :
        Worker(education, salary, vacation, extra), experience(experience) {}

    void duty() override {
        cout << "Die Kinder zu heilen." << endl;
    }
};

template <typename T>
class BST {
private:
    struct node {
        T data;
        struct node* left;
        struct node* right;
    };
    node* root;

public:
    BST() {
        root = NULL;
    }

    bool isEmpty() const { return root == NULL; }

    ~BST() {

    }

    void insert(T d) {
        node* t = new node;
        node* parent;
        t->data = d;
        t->left = NULL;
        t->right = NULL;
        parent = NULL;

        if (isEmpty()) root = t;
        else {
            node* current;
            current = root;
            while (current)
            {
                parent = current;
                if (t->data > current->data) current = current->right;
                else current = current->left;
            }
            if (t->data < parent->data)
                parent->left = t;
            else
                parent->right = t;
        }
    }

    void display(node* p, std::ostream& os) const {
        if (p != NULL) {
            if (p->left)
                display(p->left, os);
            os << " " << p->data << " ";
            if (p->right)
                display(p->right, os);
        }
    }

    template <typename U>
    friend std::ostream& operator<<(std::ostream& os, const BST<U>& obj) {
        obj.display(obj.root, os);
        return os;
    }
};

void insertionSort(vector<Worker*>& urlaub) {
    int n = urlaub.size();
    for (int i = 1; i < n; ++i) {
        Worker* key = urlaub[i];
        int j = i - 1;
        while (j >= 0 && urlaub[j]->vacation < key->vacation) {
            urlaub[j + 1] = urlaub[j];
            --j;
        }
        urlaub[j + 1] = key;
    }
}

int main() {
    Leiter leiter("C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\project\\leiter.txt", 2000.00, 35, 20.00);
    Teacher teacher("C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\project\\teacher.txt", 1900.00, 50, 30.98);
    Nurse nurse("C:\\Users\\dobri\\OneDrive\\Desktop\\FDS\\project\\nurse.txt", 1400.00, 30, 15.87, 30);

    BST<double> s;
    s.insert(leiter.salary);
    s.insert(teacher.salary);
    s.insert(nurse.salary);

    cout << s << endl;
    cout<<endl;

    vector<Worker*> urlaub;
    urlaub.push_back(&leiter);
    urlaub.push_back(&teacher);
    urlaub.push_back(&nurse);

    insertionSort(urlaub);

    for (const auto& worker : urlaub) {
        worker->display();
        cout<<endl;
    }

    return 0;
}
