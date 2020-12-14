/*@Author
Student me : <EdCAPA KIZILTAS>
Student ID: <504192517>
Date:<08.12.2020>*/

#include <iostream> 
#include <fstream>
#include <stdlib.h>
#include <string.h>


using namespace std;

struct Resistor_identity{
    char* group;
    double value;
};


struct Resistor{
    //char* group;
    //double value;
    Resistor_identity* r_identity;
    int quantity;
    Resistor *next;
    void build(Resistor_identity&);
};


void Resistor::build(Resistor_identity& res){
    r_identity = new Resistor_identity; 
    r_identity->group = new char[strlen(res.group) +1];
    r_identity->value = res.value;
    strcpy(r_identity->group, res.group);
    quantity = 1;
    next = NULL;
}

struct Circuit{
    Resistor *head;
    void create();
    void add (char*, double);
    void remove (char*, double);
    void terminate (Resistor*);
    void circuitInfoDisplay();
    void clear();
    double circuitInfoCalculation();
};

void Circuit::create(){
	head = NULL;
};

void Circuit::add(char* group_t, double value_t ){
	Resistor* traverse;
	Resistor_identity newrecord;
	Resistor* newnode;
	newnode = new Resistor; 
	
	newrecord.group = new char[sizeof(group_t)];
	strcpy(newrecord.group, group_t);
        newrecord.value = value_t;
	newnode->build(newrecord);

	traverse = head;

	if (head == NULL){
		head = newnode;
		return;
	}
	while (traverse)
	{
		if (!(strcmp(traverse->r_identity->group,newnode->r_identity->group))){
			traverse->quantity++;
            return;
		}
		traverse = traverse->next;
	}
	if(head->r_identity->value > newnode->r_identity->value){
		newnode->next = head;
		head = newnode;
		return;
	}
    traverse = head;
    while(traverse->next){
		if(traverse->next->r_identity->value > newnode->r_identity->value) {
			newnode->next = traverse->next;
			traverse->next = newnode;
			return;
		}
		traverse = traverse->next;
	}
	traverse->next = newnode;
	delete [] newrecord.group;
	//delete newrecord;
}


 void Circuit::remove (char* group_t, double value_t){
    Resistor* traverse;
	traverse = head;
     if (head == NULL){ 
		cout<< "NO_RESISTOR"<<endl;
		return;
	}
	if (!(strcmp(head->r_identity->group, group_t))){
		if (head->r_identity->value != (0-value_t)){
			cout<< "NO RESISTOR"<< endl;
			return;
		}
		if(head->quantity == 1){
			head = head->next;
			delete[] traverse->r_identity->group;
	 		delete traverse->r_identity;
     		delete traverse;
		}
		else
		{
			head->quantity--;
		}
		return;
		
	}
	while(traverse->next){
		if (!(strcmp(traverse->next->r_identity->group,group_t))){
			if (traverse->next->r_identity->value != (0-value_t))
				break;
			if (traverse->next->quantity == 1) 
				terminate(traverse);
			else 
				traverse->next->quantity--;
            return;
		}
		traverse = traverse->next;
	}
	cout<< "NO_RESISTOR"<< endl;
 }

 void Circuit::terminate(Resistor* resistor){
	 Resistor* newnode;
	 newnode = new Resistor;
	 newnode->next = resistor->next->next;
	 delete[] resistor->next->r_identity->group;
	 delete resistor->next->r_identity;
	 delete resistor->next;
	 resistor->next = newnode->next;
	 delete newnode;
 }

void Circuit::clear(){
    Resistor* traverse;
    while (head)
    {
        traverse = head;
        head = head->next;
		delete[] traverse->r_identity->group;
		//delete traverse->r_identity->value
		delete traverse->r_identity;
		//delete traverse->quantity;
        delete traverse;
     }
 }

 void Circuit::circuitInfoDisplay(){
     double resistor_equivalence;
     Resistor* traverse;
     traverse = head;
    if (head == NULL){ 
		cout<< "NO_RESISTOR"<<endl;
        return;
	}
    int total_quantity = traverse->quantity ;
    while(traverse->next){
		if ((traverse->r_identity->value) == traverse->next->r_identity->value)
			total_quantity =total_quantity + traverse->next->quantity; 
        else {
            cout<<traverse->r_identity->value<<':'<<total_quantity<<"\n";
            total_quantity = traverse->next->quantity;
        }
		traverse = traverse->next;
	}
    cout<<traverse->r_identity->value<<':'<<total_quantity<<"\n";
    resistor_equivalence = circuitInfoCalculation();
    cout<<"Total resistance="<< resistor_equivalence << " ohm" <<endl;

 }

 double Circuit::circuitInfoCalculation(){
    double resistor_equivalence = 0.0;
    Resistor* traverse;
    traverse = head;
    while(traverse){
		resistor_equivalence = resistor_equivalence + (traverse->r_identity->value / traverse->quantity);
		traverse = traverse->next;
	}
    return resistor_equivalence;
 }




Circuit  drawing;

int main(int argc, char* argv[]){

	char *group_t= new char;
	double value_t;
	//const char filename[] = "input.txt";
	drawing.create();
	fstream f;
	f.open(argv[1], fstream::in | fstream::binary);
	if (!f.is_open()) exit(1);
	else{
		f>> *group_t>>value_t;
		while(!f.eof()){
			if (value_t > 0) drawing.add(group_t, value_t);
			else if (value_t < 0) drawing.remove(group_t, value_t);
			else drawing.circuitInfoDisplay();
			f>> group_t>>value_t;
		}		
	drawing.clear();
	return EXIT_SUCCESS;
	}	
}
