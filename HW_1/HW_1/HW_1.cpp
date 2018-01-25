//HW1  Polynomial Operations using linked lists

//Due 11:59 pm, 1/31 (Wednesday)
//
//A polynomial is implemented using a linked list.  Only non-zero coefficients are included in linked list.
//Implment member functions operator+ , operator* , and add term
//
//You have to use the main function and print_linked_list provided to you.

#include <iostream>

using namespace std;

class term {
public:
	int power;
	int coef;
	term * next;
	term() { next = nullptr; }
	term(int c, int p) { power = p; coef = c; next = nullptr; }
};

class polynomial {
public:
	int num_terms;
	term * head;
	polynomial() { num_terms = 0; head = nullptr; }

	void add_term(int p, int c);
	//If the polynomial does not contain a term with power p, 
	//then add this new term.
	//If the polynomial contains a term with power p,
	//then add c to the existing coef.

	polynomial operator+(polynomial P);
	polynomial operator*(polynomial P);
	void print_polynomial();
};


void polynomial::print_polynomial() {
	cout << endl;
	term * p = head;
	while (p != nullptr) {
		cout << p->coef << " " << p->power << "   ";
		p = p->next;
	}
}

void polynomial::add_term(int c, int p) // make a term node containing power and coeff here and point it to the next one
{
	term *t1 = new term(c, p);   //constructor defined in 'term' class takes care of initialization.
	t1->next = nullptr;
	if (head == nullptr) { head = t1; return; }
	term *temp = head;
	while (temp->next != nullptr) { temp = temp->next; }
	temp->next = t1;
	//cout << "done" << endl;
} 


polynomial polynomial::operator+(polynomial P) // p1 and P 
{ 
	polynomial ans; //create a new linked list which is the sum of both p and P. Direct access to p1's elements. for p2's elements use P->
	term *t1 = head, *t2, *cur=P.head; // p1's head.
	int sum_coef=0;

	while (t1!= nullptr) //transverse through p1's nodes
	{
		t2 = cur;
		sum_coef = t1->coef;
		while (t2!= nullptr) // program fails if t2 has greater powers than t1;
		{
			if (t1->power < t2->power) //move t2 pointer but not t1
			{
				ans.add_term(t2->coef, t2->power);	
				cur = t2->next; 
				break;
			}
			else if (t1->power == t2->power) // move both t1 and t2 pointers
			{
				sum_coef += t2->coef;
				ans.add_term(sum_coef, t1->power);
				cur = t2->next;
				t1 = t1->next;
				break;
			}
			ans.add_term(sum_coef, t1->power);//if it comes here without satisfying any of the if conditions then t1 pow > t2 pow, move t1 pointer only.
			t1 = t1->next;
			break;
		}
		if (t2 == nullptr) { ans.add_term(sum_coef, t1->power); t1 = t1->next; } 
		
	}

	if (t1 == nullptr)
	{
		while (cur != nullptr)
		{
			ans.add_term(cur->coef, cur->power);
			cur = cur->next;
		}
	}
	
	return ans; 
}

polynomial polynomial::operator*(polynomial P) { return P; }


int main() {
	polynomial p1, p2, p3, p4, p5, p6;
	int num_t;
	cout << "Enter numer of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { //You don't need to check for input error
		int c, p;
		cin >> c >> p;
		p1.add_term(c, p);
	}
	p1.print_polynomial();
	cout << endl;
	cout << "Enter numer of terms" << endl;
	cin >> num_t;
	cout << "Enter all terms" << endl;
	for (int i = 0; i < num_t; i++) { //You don't need to check for input error
		int c, p;
		cin >> c >> p;
		p2.add_term(c, p);
	}
	p2.print_polynomial();
	p3 = p1 + p2;
	p3.print_polynomial();/*
	p4 = p1 * p2;
	p4.print_polynomial();*/
	getchar();
	getchar();
	return 0;
}
/*
//An example screenshot is given below:
//Different cases may be used during grading

Enter numer of terms
3
Enter all terms
2 2 1 1 4 0

2 2   1 1   4 0
Enter numer of terms
2
Enter all terms
-6 1 3 0

-6 1   3 0
2 2   -5 1   7 0
-12 3   -21 1   12 0

*/