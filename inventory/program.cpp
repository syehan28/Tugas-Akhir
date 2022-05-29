/*
    Algoritma dan Struktur Data
    Tugas Akhir
    Inventaris Barang
*/

#include <iostream>
#include <fstream>

using namespace std;

struct Barang
{
    string name;
    int serial;
    int stock;

    Barang *next;
};

Barang *head, *tail, *newNode, *temp, *temp2;

void addData(string name, int serial, int stock)
{
    newNode = new Barang();
    newNode->name = name;
    newNode->serial = serial;
    newNode->stock = stock;
    newNode->next = NULL;

    if (head == NULL)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        tail = newNode;
    }
}

void deleteNodeBySerial(int serial)
{
    temp = head;
    temp2 = head;
    while (temp != NULL)
    {
        if (temp->serial == serial)
        {
            if (temp == head)
            {
                head = head->next;
                delete temp;
                break;
            }
            else if (temp == tail)
            {
                tail = temp2;
                tail->next = NULL;
                delete temp;
                break;
            }
            else
            {
                temp2->next = temp->next;
                delete temp;
                break;
            }
        }
        temp2 = temp;
        temp = temp->next;
    }
}

void saveFile()
{
    ofstream file;
    file.open("invet.txt");
    temp = head;

    while (temp != NULL)
    {
        file << temp->name << endl;
        file << temp->serial << endl;
        file << temp->stock << endl;

        temp = temp->next;
    }
    file.close();
}

void readFile()
{
    ifstream file;
    file.open("invet.txt");
    string name;
    int serial, stock;

    while (file >> name >> serial >> stock)
    {
        addData(name, serial, stock);
    }
    file.close();
}

void printList()
{

    temp = head;
    while (temp != NULL)
    {
        cout << endl;
        if (temp == head)
        {
            cout << "=====================================" << endl;
            cout << "|Serial   |   Stock  |  Nama Barang |" << endl;
            cout << "=====================================" << endl;
        }

        cout << "  " << temp->serial << "\t\t" << temp->stock << "\t" << temp->name  << endl;

        temp = temp->next;

        if (temp == NULL)
        {
            cout << "=====================================" << endl;
        }
        continue;
    }
}

int main()
{
    string name;
    int serial, stock, menu;
    readFile();
    while (true)
    {
        cout << "===========================" << endl;
        cout << "|     Inventaris Barang   |" << endl;
        cout << "===========================" << endl;

        cout << "|   1. Tambah Barang"
             << "      |" << endl;
        cout << "|   2. Hapus Barang"
             << "       |" << endl;
        cout << "|   3. Tampilkan Barang"
             << "   |" << endl;
        cout << "|   4. Keluar"
             << "             |" << endl;
        cout << "===========================" << endl;
        cout << "Pilih Menu: ";
        cin >> menu;

        switch (menu)
        {
        case 1:

            cout << "Masukkan nama barang: ";
            getline(cin.ignore(), name);
            cout << "Masukkan serial barang: ";
            cin >> serial;
            cout << "Masukkan stock barang: ";
            cin >> stock;

            addData(name, serial, stock);
            cout << endl;
            cout << "Data berhasil ditambahkan" << endl
                 << endl;
            saveFile();
            break;

        case 2:
            cout << "Serial Barang: ";
            cin >> serial;
            deleteNodeBySerial(serial);

            cout << "Data berhasil dihapus" << endl;

            saveFile();
            break;

        case 3:
            printList();

            cout << endl;
            break;

        case 4:
            exit(1);
            break;

        default:
            cout << "Menu tidak ada" << endl;
            break;
        }
    }
}