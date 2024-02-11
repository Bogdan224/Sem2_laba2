#include<iostream>
#include<ctime>
using namespace std;

struct Item {
    int value;
    Item* right;
    Item* left;
};


void Insert(int val, Item** q)
{
    if (*q == NULL)
    {
        *q = (Item*)malloc(sizeof(Item));
        (*q)->left = (*q)->right = NULL;
        (*q)->value = val;
        return; 
    }

    if (val < (*q)->value)
        Insert(val, &(*q)->left);
    if (val > (*q)->value)
        Insert(val, &(*q)->right);
    //���� �������� ����������� � ������, �� �������� �� ����������� � ������� ���������������
    if ((*q)->value == val)
        return;

}

void PrintVos(Item* head) {
    if (head == NULL) {
        return;
    }

    PrintVos(head->left);
    cout << head->value << " ";
    PrintVos(head->right);

}

void PrintUb(Item* head) {
    if (head == NULL) {
        return;
    }

    PrintUb(head->right);
    cout << head->value << " ";
    PrintUb(head->left);
}

int Delete(int key, Item** node) {
    Item* t, * up;
    if (*node == NULL) return 0; // ��� ������ �������� � ������

    if ((*node)->value == key) {
        // ���� �������� ��������� � �����, �� ������� ����
        if (((*node)->left == NULL) && ((*node)->right == NULL)) {
            free(*node);
            *node = NULL;
            return 1;
        }
        if ((*node)->left == NULL) {
            t = *node;
            *node = (*node)->right;
            free(t);
            return 1;
        }
        if ((*node)->right == NULL) {
            t = *node;
            *node = (*node)->left;
            free(t);
            return 1;
        }
        up = *node;
        t = (*node)->left; // ���� � ����� ���������
        //���������� �� �������� ������� ����
        while (t->right != NULL) {
            up = t;
            t = t->right;
        }
        //�������� �������� �� ������� ���� ������ ���������� ��������
        (*node)->value = t->value;
        if (up != (*node)) {
            // ���� ������� ������ �� ����, �� ������������ ��� �� ������
            if (t->left != NULL) up->right = t->left;
            else up->right = NULL; // ������� ����
        }
        // ���� ���� ���������� ���� �������, ������� ����
        else (*node)->left = t->left;
        // ����������� ������ � ������� ������� ������ �������
        free(t);
        return 1;
    }
    if ((*node)->value < key)
        return Delete(key, &(*node)->right);
    return Delete(key, &(*node)->left);
}

void DeleteAll(Item*& root) {
    if (root == NULL) {
        return;
    }
    DeleteAll(root->left);
    DeleteAll(root->right);
    Delete(root->value, &root);
    root = NULL;
}

int Size(Item* head) {
    if (head == NULL) {
        return 1;
    }
    int N_r = 0, N_l = 0;
    if (head->left != NULL) {
        N_l = Size(head->left);
    }
    if (head->right != NULL) {
        N_r = Size(head->right);
    }
    return N_r + N_l + 1;
}


int main() {
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    Item* it = (Item*)malloc(sizeof(Item));
    int size;
    cout << "������� ���-�� ����� � ������ -> ";
    cin >> size;

    int a = rand() % 100;
    it->value = a;
    it->left = NULL;
    it->right = NULL;

    for (int i = 0; i < size - 1; i++)
    {
        a = rand() % 100;
        Insert(a, &it);
    }
    PrintVos(it);
    cout << "\n" << "���-�� ���������: " << Size(it) << endl;

    cout << "������� �����, ������� ������ ������� -> ";
    cin >> a;
    Delete(a, &it);

    PrintUb(it);

    DeleteAll(it);

    PrintUb(it);

    return 0;
}