#include <iostream>
using namespace std;

struct node {
int info;
struct node *next;
} *beginning, *listend;

void insert(int x) { 	
struct node *p = new node; 	
p->info = x; 	
p->next = NULL; 	
if (beginning == NULL) { 	
beginning = p;
listend = p;
} else { 	
listend->next = p;
listend = p; 	
}}


void output() { 	
struct node *p = beginning;
cout << "The list: ";
while (p != NULL) {
cout << p->info << " ";
p = p->next;}
cout << endl; }


struct node * search(int x) {
struct node *p = beginning;
while (p != NULL) {
if (p->info == x) return p;
else p = p->next;}
return NULL;}


void listdelete(struct node *p) {
struct node *p1 = beginning;
if (p == beginning) {
beginning = beginning->next;
return;}
while (p1->next != p)
p1 = p1->next; 	
p1->next = p->next;
delete p;}

		
int main() {
beginning = listend = NULL;
int input = 0;
do {cout << "Please enter an integer value (negative value = quit): ";
cin >> input;
if (input >= 0) insert(input);
} while (input >= 0);
output();
cout << "Integer to be deleted: ";
cin >> input;
struct node *p = search(input);
if (p != NULL) listdelete(p);
else cout << input << " is not in the list!" << endl;
output();
return 0;}
