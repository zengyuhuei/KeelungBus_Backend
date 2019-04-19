//00557018 3A 曾毓惠 
#include <iostream>     

using namespace std; 

 
class aaa
{
	private:
		int _counter;
		int * _memory;
	public:
		int_array_cell(int *cell_ptr)  //constructor 
		{
			_counter = 1;
			_memory = cell_ptr;
			cout << "int_array_cell is allocated" << endl;
		}
		~int_array_cell(void) //destructor
		{ 
			 
			delete [] _memory; 
			cout<<"int_array_cell counter "<<_counter<<": deleted"<<endl;
		} 
		int get_counter() const
		{
			return _counter;
		}
		void decrease_counter() 
		{
			if(_counter == 0 )
			{
				return;
			}
			_counter--;
		}
		void increase_counter()
		{
			_counter++;
		}
	
		int& operator[](const int n) //overloading (*_memory)[n] 
		{
			return _memory[n];
		}
};

class counter_ptr
{
	private:
		char * _name;
		int_array_cell * _cell_ptr;
	public:
		//constructor when  newing object of counter_ptr incoming two parameters,char pointer and int pointer int main function
		counter_ptr(char *name,int *cell_ptr){ 
			_name = name; 
			_cell_ptr = new int_array_cell(cell_ptr); 
			cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
		} 
		//constructor when  newing object of counter_ptr incoming one parameter,char pointer int main function
		counter_ptr(char *name){
			_name = name;
			_cell_ptr = NULL; 
			cout << "counter_ptr " << _name <<" is not assigned to an int_array_cell" << endl;
		}
		//destructor
		~counter_ptr()
		{
			//delete the memory of _cell_ptr
			cout << "counter_ptr " <<_name <<" is deleted" << endl;
			//the pointer  points to other memory 
			if(_cell_ptr != NULL)
			{
				
				_cell_ptr -> decrease_counter();
				//there is only one object in the array
				//so free the memory of that object
				//and make the pointer back to the begining
				if(_cell_ptr->get_counter() == 0)
				{
					delete _cell_ptr;
					_cell_ptr = NULL;
				}
			}
			//print the meaasage after freeing  the memory 
			if(_cell_ptr != NULL && _cell_ptr->get_counter() > 0)
			{
				cout<<"int_array_cell counter is decreased: counter " <<_cell_ptr->get_counter()<<endl;
			}
		}
			
		//clean the object
		void release()
		{	
			_cell_ptr -> decrease_counter();
			cout << "int_array_cell counter is decreased: counter " <<_cell_ptr->get_counter() << endl;
			_cell_ptr = NULL;
			cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
		}
		
		//overloading that function like object = new int [] calls
		counter_ptr& operator=(int *mem)  
		{
			_cell_ptr -> decrease_counter();
			delete _cell_ptr;
			_cell_ptr = new int_array_cell(mem);
			cout<<"counter_ptr "<<_name<<" is assigned to an int_array_cell: counter "<<_cell_ptr->get_counter()<<endl;
			return *this;
		}
		
		//overloading that function like object = object(has assigned to an int_array_cell) calls
		counter_ptr& operator=(const counter_ptr& index)
		{
			if(NULL!=index._cell_ptr)
			{
				if(_cell_ptr != NULL)
				{
					_cell_ptr->decrease_counter();
				}
				//make the pointer to assign to the index
				_cell_ptr = index._cell_ptr;
				_cell_ptr -> increase_counter();
				
				cout << "int_array_cell counter is increased: counter " << _cell_ptr->get_counter() << endl;
				cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
			}
			return *this;
		}
     	////overloading (*_cell_ptr)[n] 
		int& operator[](const int n)
		{
			return (*_cell_ptr)[n];
		}
};


int main()
{

 //PART 一  (30分)
    counter_ptr b("b", new int[10]); 

	{

		b = new int[100]; 
    	counter_ptr a("a");
		a = b;

	}
	// PART 二  (30分)
	//set the data to the object	
	for(int i=0; i<10; i++)
		b[i] = i;
		
	//print all data in the object
	for(int i=0; i<10; i++)      
		cout << b[i] << ' ';    
		cout << endl;    

    counter_ptr c("c");

	c = b;
	//clean the object
	b.release();	
}





/*
//PART 三 (20分)
#include <iostream>     
using namespace std; 

 
class int_array_cell
{
	private:
		int _counter;
		int * _memory;
	public:
		int_array_cell(int *cell_ptr)  //constructor 
		{
			_counter = 1;
			_memory = cell_ptr;
			cout << "int_array_cell is allocated" << endl;
		}
		~int_array_cell(void) //destructor
		{ 
			 
			delete [] _memory; 
			cout<<"int_array_cell counter "<<_counter<<": deleted"<<endl;
		} 
		int get_counter() const
		{
			return _counter;
		}
		void decrease_counter() 
		{
			if(_counter == 0 )
			{
				return;
			}
			_counter--;
		}
		void increase_counter()
		{
			_counter++;
		}
	
		int& operator[](const int n) //overloading (*_memory)[n] 
		{
			return _memory[n];
		}
};
//template
template<typename T,typename Q>
class counter_ptr
{
	private:
		char * _name;
		T * _cell_ptr;
	public:
		//constructor when  newing object of counter_ptr incoming two parameters,char pointer and int pointer int main function
		counter_ptr(char *name,Q *cell_ptr){ 
			_name = name; 
			_cell_ptr = new T(cell_ptr); 
			cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
		} 
		//constructor when  newing object of counter_ptr incoming one parameter,char pointer int main function
		counter_ptr(char *name){
			_name = name;
			_cell_ptr = NULL; 
			cout << "counter_ptr " << _name <<" is not assigned to an int_array_cell" << endl;
		}
		//destructor
		~counter_ptr()
		{
			//delete the memory of _cell_ptr
			cout << "counter_ptr " <<_name <<" is deleted" << endl;
			//the pointer  points to other memory 
			if(_cell_ptr != NULL)
			{
				
				_cell_ptr -> decrease_counter();
				//there is only one object in the array
				//so free the memory of that object
				//and make the pointer back to the begining
				if(_cell_ptr->get_counter() == 0)
				{
					delete _cell_ptr;
					_cell_ptr = NULL;
				}
			}
			//print the meaasage after freeing  the memory 
			if(_cell_ptr != NULL && _cell_ptr->get_counter() > 0)
			{
				cout<<"int_array_cell counter is decreased: counter " <<_cell_ptr->get_counter()<<endl;
			}
		}
			
		//clean the object
		void release()
		{	
			_cell_ptr -> decrease_counter();
			cout << "int_array_cell counter is decreased: counter " <<_cell_ptr->get_counter() << endl;
			_cell_ptr = NULL;
			cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
		}
		
		//overloading that function like object = new int [] calls
		counter_ptr& operator=(Q *mem)  
		{
			_cell_ptr -> decrease_counter();
			delete _cell_ptr;
			_cell_ptr = new int_array_cell(mem);
			cout<<"counter_ptr "<<_name<<" is assigned to an int_array_cell: counter "<<_cell_ptr->get_counter()<<endl;
			return *this;
		}
		
		//overloading that function like object = object(has assigned to an int_array_cell) calls
		counter_ptr& operator=(const counter_ptr& index)
		{
			if(NULL!=index._cell_ptr)
			{
				if(_cell_ptr != NULL)
				{
					_cell_ptr->decrease_counter();
				}
				//make the pointer to assign to the index
				_cell_ptr = index._cell_ptr;
				_cell_ptr -> increase_counter();
				
				cout << "int_array_cell counter is increased: counter " << _cell_ptr->get_counter() << endl;
				cout << "counter_ptr " << _name << " is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
			}
			return *this;
		}
     	//overloading (*_cell_ptr)[n] 
		Q& operator[](const Q n)
		{
			return (*_cell_ptr)[n];
		}
};


int main()
{


    counter_ptr<int_array_cell,int> b("b", new int[10]);

	{

		b = new int[100]; 
        counter_ptr <int_array_cell,int> a("a");
		a = b;


	}
	//set the data to the object	
	for(int i=0; i<10; i++)
		b[i] = i;
		
	//print all data in the object
	for(int i=0; i<10; i++)      
		cout << b[i] << ' ';    
		cout << endl;    

    counter_ptr <int_array_cell,int> c("c");

	c = b;
	//clean the object
	b.release();	
	
		
		

}
*/

/* 
//PART 四 (20分)
//用 template counter_ptr 寫 stack
#include <fstream>
#include <iostream>    
#include <string>
using namespace std; 


class int_array_cell
{
	private:
		int _counter;
		int * _memory;
	public:
		int_array_cell(int *cell_ptr)
		{
			// like stack's top
			_counter = -1; 
			_memory = cell_ptr;
			cout << "int_array_cell is allocated" << endl;
		}
		~int_array_cell(void) 
		{ 
			delete [] _memory; 
			cout << "int_array_cell counter " << _counter << ": deleted" << endl;
		} 
		int get_counter() const
		{
			return _counter;
		}
		void decrease_counter()
		{
			if(_counter<-1)
			{
				return;
			}
			_counter--;
		}
		void increase_counter()
		{
			_counter++;
		}
		//overloading (*_memory)[n] 
		int& operator[](const int n)
		{
			return _memory[n];
		}
};
template<typename T,typename Q>
class counter_ptr
{
	private:
		char * _name;
		T * _cell_ptr;
		
	public:
		//constructor when  newing object of counter_ptr incoming two parameters,char pointer and int pointer int main function
	 	counter_ptr(char *name, Q* cell_ptr)
		{
			_name = name; 
			_cell_ptr = new T(cell_ptr); 
			cout << "counter_ptr "<< _name <<" is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
		} 
		//constructor when  newing object of counter_ptr incoming one parameter,char pointer int main function
		counter_ptr(char *b)
		{
			_name = b;
			_cell_ptr = NULL;
			cout << "counter_ptr " << _name <<" is not assigned to an int_array_cell" << endl;
		}
		//destructor
		~counter_ptr()
		{
			cout<<"counter_ptr "<<_name<<" is deleted"<<endl;
			//delete the memory of _cell_ptr
			if(_cell_ptr != NULL)
			{
				_cell_ptr->decrease_counter();
				//there is only one object in the array
				//so free the memory of that object
				//and make the pointer back to the begining
				if(_cell_ptr->get_counter() == -1)
				{
					delete _cell_ptr;
					_cell_ptr = NULL;
				}
			}
			//print the meaasage after freeing  the memory 
			if(_cell_ptr != NULL && _cell_ptr->get_counter() > 0)
			{
				cout << "int_array_cell counter is decreased: counter " << _cell_ptr->get_counter() << endl;
			}
		}
			
		//clean the object
		void release()
		{
			_cell_ptr->decrease_counter();
			cout << "int_array_cell counter is decreased: counter " << _cell_ptr->get_counter() << endl;
			_cell_ptr=NULL;
			cout << "counter_ptr " << _name << " is not assigned to an int_array_cell" << endl;
		}
		//overloading that function like object = new Q [] calls
		counter_ptr& operator=(Q *mem)  
		{
			_cell_ptr->decrease_counter();
			delete _cell_ptr;
			_cell_ptr = new int_array_cell(mem);
			cout << "counter_ptr "<< _name <<" is assigned to an int_array_cell: counter "<< _cell_ptr->get_counter() << endl;
			return *this;
		}
		//overloading that function like object = object(has assigned to an int_array_cell) calls
		counter_ptr& operator=(const counter_ptr& index)
		{
			if(index._cell_ptr != NULL)
			{
				if(_cell_ptr != NULL)
				{
					_cell_ptr->decrease_counter();
				}
				//make the pointer to assign to the index
				_cell_ptr=index._cell_ptr;
				_cell_ptr->increase_counter();
				cout <<"int_array_cell counter is increased: counter " << _cell_ptr->get_counter() << endl;
				cout << "counter_ptr "<< _name <<" is assigned to an int_array_cell: counter " << _cell_ptr->get_counter() << endl;
			}
			return *this;
		}
		//overloading (*_cell_ptr)[n] 
		Q& operator[](const int n)
		{
			return (*_cell_ptr)[n];
		}
		
		int size(); //return the size of the stack
		bool isEmpty();  //check the stack is empty or not  
		void printCoding();  //print the coding of data in the stack
		void printData();  //print the data in the stack
		void push(Q); //add data to the stack
		Q& pop(); //take the data from the stack
		void clean(); //clean the stack
		//if the input is in the stack return true , or return fasle
		bool check(int a, int b) 
		{
	
			for(int i = 0; i<=_cell_ptr->get_counter();i++)
			{
				if(((*_cell_ptr)[i] == a) && (*_cell_ptr)[i+1] == b &&  (i%2)==0) return true;
			}
			return false;
		
		}

};


// function to add an element x in the stack
template <typename T,typename Q>
void counter_ptr<T,Q>::push(Q x)
{
	_cell_ptr->increase_counter();
	(*_cell_ptr)[_cell_ptr->get_counter()] = x;
}
// Utility function to return the size of the stack
template <typename T,typename Q>
int counter_ptr<T,Q>::size()
{
	return _cell_ptr->get_counter() + 1;
}

// Utility function to check if the stack is empty or not
template <typename T,typename Q>
bool counter_ptr<T,Q>::isEmpty()
{
	return _cell_ptr->get_counter() == -1;	// or return size() == 0;
}


// Utility function to print all of the coding of items in the stack
template <typename T,typename Q>
void counter_ptr<T,Q>::printCoding()
{
	int i;
	for(i = 0; i<=_cell_ptr->get_counter();i+=2)
	{
		cout << "("<< (*_cell_ptr)[i]<<" "<<(*_cell_ptr)[i+1]<<") "; 
	}
	cout << endl;
}

// Utility function to print all data of items in the stack
template <typename T,typename Q>
void counter_ptr<T,Q>::printData()
{
	int i;
	for(i = 0; i<=_cell_ptr->get_counter();i+=2)
	{
		int my1 = (*_cell_ptr)[i];
		int my2 =(*_cell_ptr)[i+1];
		char c2[3];
		c2[0] = my1;
		c2[1] = my2;
		c2[2] = '\0';
		cout<< c2;
		
	}
	cout << endl;
}
// function to pop top element from the stack
template <typename T,typename Q>
Q& counter_ptr<T,Q>::pop()
{
	// check for stack underflow
	if (isEmpty())
	{
		cout << "UnderFlow\nProgram Terminated\n";
		exit(1);
	}
	
	_cell_ptr->decrease_counter();
	return (*_cell_ptr)[_cell_ptr->get_counter()+1];
	
	
}
// function to clean all items in the stack
template <typename T,typename Q>
void counter_ptr<T,Q>::clean()
{
	while(!isEmpty()) pop();
	
}

int main()
{
	ifstream inputFile("input.txt");
	counter_ptr<int_array_cell,int> b("b", new int[1000]);
    while(!inputFile.eof())
    {
        string a,data;
		inputFile >> a;
		
		if(a =="I") //input data
		{
			inputFile >> data;
			 cout<<"I 資料輸入: "<<endl;
			
			for(int i =0; i<data.size(); i++)
			{
				b.push((int)data.at(i));
			}
		}
		if(a == "P") //print the data in the stack
		{
			cout<<"P 資料輸出: ";
			b.printData();
		}
		if(a == "B")  //print the coding of the datain the stack
		{
			
			cout<<"B 資料內碼輸出: ";
			b.printCoding();
		}
		if(a == "R") 
		{
			//拿一個資料
			cout<<"R 拿一個資料: ";
			 int my1 = b.pop();;
			 int my2 = b.pop();
			 char c2[3];
			 c2[0] = my2;
			 c2[1] = my1;
			 c2[2] = '\0';
			 printf("%s\n",c2);
		}
		if(a == "C") //clean the stack
		{
			cout <<"C 清空"<<endl;
			b.clean();
		}
		if(a == "?") //check the input is in the stack or not
		{
			cout<<"? 查詢: ";
			inputFile >> data;
			cout <<data<<" 是否在stack中?";
			if(b.check((int) data.at(0), (int) data.at(1)))
				cout <<"是"<<endl;
			else
				cout<<"否"<<endl;	 
			 
		}

        

    }

}
*/ 
