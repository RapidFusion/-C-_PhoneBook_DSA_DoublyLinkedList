#include<iostream>
using namespace std;
class node{
	public:
node* next;
node* prev;
char name[30];
char ph_no[30];
	node(char nam[],char no[]){
		next=NULL;
		prev=NULL;
		for(int i=0;i<30;i++){
			name[i]=nam[i];
			ph_no[i]=no[i];
		}
	}
};

void search(node* & head,node *&tail);
void edit_contact(node* &head,node *&tail);
bool similar_name(char srcnam[],char svdnam[]);
bool same_number(char contact1[],char contact2[]);
int find_req_pos(char nam[],node * &temp);
void addcontact(node * &head,node* &tail);
void search(node* & head,node*&tail);
void delete_contact(node *& head,node *& tail,int id);
void display(node * head);


void edit_contact(node* &head,node *&tail){
	node *temp= head;

	start:
	int id,i=1;
	cout<<"Enter Contact Id:";
	cin>>id;
	

	for (i=1; temp!=NULL  && i!=id; i++ ){//Traversing tto the required id
		temp=temp->next;
	//	cout<<i;
	}
	
	
	
	
//	cout<<i<<endl;
	if(i==id){
	//	system("cls");
		cout<<"Editing Contact...\n\n";
		cout<<"Previous Contact Details\n";
		cout<<temp->name<<endl;
		cout<<temp->ph_no<<endl<<endl;
		
		delete_contact(head,tail,id);
		
		addcontact(head,tail);
		
		
		return;
	}
	else{
		cout<<"Contact Id Not Found!\n";
		cout<<"1 To Enter Another Id\n2 To Find Id\n3 To Cancel\nEnter:";
		cin>>id;
		if(id==1){goto start;}
		else if(id==3){return;}
		else{search(head,tail);goto start;}
		
		}
	
}

bool similar_name(char srcnam[],char svdnam[]){
	int length=0;
	int equal=0;
	
	while(srcnam[length]!=0){
	length++;
	}

	for(int i=0 ; svdnam[i]!=0  && equal<length;i++){
		int src=srcnam[equal];
		int svd=svdnam[i];
		
		
		if(src>=65 && src<91){ //converting to lower case
			src=src+32;
		}
		if(svd>=65 && svd<91){ //converting to lower case
			svd=svd+32;
		}
		if((src== svd)){
			equal++;
			
		}
		
		else{
			equal=0;
		}
		
	//	cout<<equal<<endl;
	
	}
	if(equal==length){
	//	cout<<"Similar By Name";
		return 1;
	}

	
	else{
	//	cout<<"Not Similar";
		return 0;
	}
}

bool same_number(char contact1[],char contact2[]){ //check if phone numbers are same
	bool is_same=0;
	int i=0;
	int j=0;	
	
	if((contact1[0]=='+' && contact1[1]=='9' && contact1[2]=='2') && (contact2[0]=='+' && contact2[1]=='9' && contact2[2]=='2')){//do nothing
	}
	
	else{	//ignore +92
		if(contact1[0]=='+' && contact1[1]=='9' && contact1[2]=='2'){
			i=3;
			j=1;	
		}
		if(contact2[0]=='+' && contact2[1]=='9' && contact2[2]=='2'){

			i=1;
			j=3;
		}
	}
	
	for(i,j ; i <30 && j<30 ; i++ , j++){
		if(contact1[i]==0 || contact2[j]==0){
			i=30;
			j=30;
			is_same=0;
		}

		
		if (contact1[i] == ' '){
			i++;
		}
		if (contact2[j]== ' '){
			j++;
		}
		
		if(contact1[i] != contact2[j]){
		//	cout<<"loop breaked";
			i=30;j=30; //breaking loop
			is_same=0;
		}
		else{
		
			is_same=1;
		}
		
	}
//	cout<<"Same By Number";
	return is_same;

}

int find_req_pos(char nam[],node * &temp){  //find apropriate position to insert the new contact also traverse through linked list

	char name[30];
	while(temp!=NULL){
		bool is_larger=0;
		for(int i=0;i<30;i++)
		name[i]=temp->name[i];
		int lp=0;
	
		while (lp<30 && !is_larger){
			int a=nam[lp];
			int b=name[lp];
		
		//	cout<<a<<","<<b<<endl;		
			if(b==a+32 || a==b+32)
			{}
			
			
			else{
				if(b>64 && b<97){
					b=b+32;}
					if(a>64 && a<97){
					a=a+32;
					}
			}
		
		//	cout<<a<<","<<b<<endl;
			if(a<b){
		//		cout<<nam<<"<"<<name;
				return 1;
			}
			else if(a>b){
		//		cout<<nam<<">"<<name;
				is_larger=1;
			}
			lp++;
		}
		temp=temp->next;
	}
	return 0;
}

void addcontact(node * & head,node* &tail){  //add a new contact at apropriate position
	char nam[30];
	char no[30];
	cout<<"Enter Name:";
	cin.ignore(100,'\n');
	cin.getline(nam,30);
	
	cout<<"Enter Number:";
	cin.getline(no,30);
	node* new_node=new node(nam,no);
	if (head==NULL){
		head=new_node;
		tail=new_node;
	}
	
	else{
		node *temp=head;
		int similar=0;
		int id=1;
		while(temp!=NULL){
		
			if(similar_name(nam,temp->name)){
				if(similar==0){
				cout<<"Following Similar Contacts Have Been Found...\n";
				similar=1;
				}
				cout<<"\nContact ID:"<<id;
				cout<<endl<<temp->name<<endl;
				cout<<temp->ph_no<<endl<<endl;
		//		cout<<similar;
		//		found=1;
			}
			else if(same_number(no,temp->ph_no)){
				if(similar==0){
				cout<<"Following Similar Contacts Have Been Found...\n";
				similar=1;
				}
				cout<<"\nContact ID:"<<id;
				cout<<endl<<temp->name<<endl;
				cout<<temp->ph_no<<endl<<endl;
		//		found=1;
			}
		temp=temp->next;
		id++;
		}
		int opt=1;
		if(similar!=0){
			
			cout<<endl<<"Do You Want to Enter a New Contact?"<<"\n1 For New Contact\n2 To Edit Previous Contact\n Enter:";
			cin>>opt;
		}
		
		if(opt==1){
	
		
		temp=head;
		int result=find_req_pos(nam,temp);
		//cout<<endl<<endl<<result<<endl<<endl;

		if(result==1){   //old_name>new_name      
			if(temp->prev!=NULL)
				{temp->prev->next=new_node;}
			else{head=new_node;}
				new_node->prev=temp->prev;
				new_node->next=temp;
				temp->prev=new_node;
			}
		else if(result==0){ //new_name>all_old_names
		
			tail->next=new_node;
			new_node->prev=tail;
			new_node->next=NULL;
			tail=new_node;	
		}
		return;
		}
		else{
		edit_contact(head,tail);
		return;
		}
		
	}
}

void search(node* & head,node*&tail){     //check if two contacts are same
	node* temp=head;
	char nam_src[30];
	char no_src[30] ;
	bool found=0;
	double opt=0;
	char tmp[30];
	re:
	cout<<"1 To Search By Name\n2 To Search By Contact\nEnter:";
	cin>>opt;
	if (opt==1){
		cout<<"Enter Name To Search:";
		cin.ignore(100,'\n');
		cin.getline(nam_src,30);
	}
	else if(opt==2){
		cout<<"Enter Number To Search:";
		cin.ignore(100,'\n');	
		cin.getline(tmp,30);
		for(int i=0; tmp[i]!=0 && tmp[i]!='\n'; i++){
			no_src[i]=tmp[i];
		}	
	}
	else{
		goto re;
	}
	
	cout<<"Showing Results...\n\n";
	int id=1;
	while(temp!=NULL){
		if(opt==1){
			
			
			if(similar_name(nam_src,temp->name)){
				cout<<"Contact ID:"<<id;
				cout<<endl<<temp->name<<endl;
				cout<<temp->ph_no<<endl<<endl;
				found=1;
			}

			
		}
		else if(opt==2){
		
			if(same_number(no_src,temp->ph_no)){
				cout<<"Contact ID:"<<id<<endl;
				cout<<temp->name<<endl;
				cout<<temp->ph_no<<endl;
				found=1;
			}	
		}
		temp=temp->next;
		id++;
		
	}
	if (!found){
		cout<<"Oops, no such contact found!\n";
	}
}

void delete_contact(node *& head,node *& tail,int id){

	node *temp= head;
	start:

	int i=1;
	while (i!=id && temp!=NULL)
	{temp=temp->next;
	i++;
	}
	
	
	
//	cout<<i<<endl;
	if(i==id){
		

		if(id==1){
			if(head==tail){
				head=NULL;
				tail=NULL;
			}
			else{
			head=head->next;
			head->prev=NULL;
			}
		}
		
		else if(temp->next==NULL){
			tail=temp->prev;
			tail->next=NULL;
			;
		
		}
		
		else{
			temp->prev->next= temp->next;
			temp->next->prev=temp->prev;
		}
		
		
		delete temp;
		return;
	}
	else{
		cout<<"Contact Id Not Found!\n";
		cout<<"1 To Enter Another Id\n2 To Find Id\n3 To Cancel\nEnter:";
		cin>>id;
		if(id==1){goto start;}
		else if(id==3){return;}
		else{search(head,tail);goto start;}
		
		}
	
}

void display(node * head){
	node * temp = head;
	int id=1;
	while(temp!=NULL){
		cout<<"Contact ID:"<<id<<endl;
		cout<<temp->name<<endl;
		cout<<temp->ph_no<<endl<<endl;
		temp=temp->next;
		id++;
	}
	cout<<endl;
}

int main(){

	node * head=NULL;
	node * tail=NULL;
start:
	int opt=0;
	
	
	cout<<"1 To Add a Contact\n2 To Show Contacts\n3 To Search a Contact\n4 To Edit Contact\n5 To Remove a Contact\nEnter:";
	cin>>opt;
	switch(opt)
	{
	case 1:
		//system("cls");
		addcontact(head,tail);
		goto start;
	case 2:
	//	system("cls");
		display(head);
		goto start;
	case 3:
      //system("cls");
		search(head,tail);
		goto start;
	case 4:
	//	system("cls");
		edit_contact(head,tail);
		goto start;
	case 5:
	//	system("cls");
		cout<<"Enter Contact ID:";
		cin>>opt;
		delete_contact(head,tail,opt);
		goto start;
	}	
	}
