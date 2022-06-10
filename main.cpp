#include<iostream>
#include<stdlib.h>
#include<fstream>
#include<string.h>
#include<cstring>

using namespace std;

class Users
{
	private:
		char userName[30];
		char userRole[10];
		char userPassword[20];
	
	public:
		int userID;
		Users()
		{
			userID = 0;
			string s = "user";
		    int n = s.length();
		 
		    strcpy(userRole, s.c_str());
		}
		void getUserData();
		void displayUserData();
		void saveUserData();
		void editUserData();
		int compareUser(Users user);
		int getRole(Users user);
		int operator == (char Nm[20]); 
};

void Users::getUserData()
{
	cout<<"Enter User Name : ";
	cin.ignore();
	cin.getline(userName,30);
	cout<<"Enter User Password : ";
	cin.getline(userPassword,20);
}

void Users::displayUserData()
{
	cout<<"User ID is "<<userID<<endl;
	cout<<"User Name is "<<userName<<endl;
	cout<<"User Role is "<<userRole<<endl;
	cout<<"User Password is "<<userPassword<<endl;
}

void Users::saveUserData()
{
	fstream f1, f2;
	f1.open("files/users.dat",ios::app);
	f2.open("files/userRec.txt",ios::app);
	f1.write((char *)this, sizeof(*this));
	f2<<userID<<"\n";
	f2.close();
	f1.close();
}

void Users::editUserData()
{
	cout<<"Enter User Role : ";
	cin.getline(userRole, 10);
}

int Users::compareUser(Users u)
{
	if(strcmp(userName,u.userName) == 0 && strcmp(userPassword,u.userPassword) == 0)
	{
		return 1;	
	}
	else
	{
		return 0;
	}
}

int Users::operator ==(char Nm[20])
{
	if(strcmp(userName,Nm) == 0)
	{
		return 1;	
	}	
	else
	{
		return 0;
	}
}

int Users::getRole(Users user)
{
	if(strcmp(user.userRole,"Admin") == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

class Inventory
{
	private:
		char itemName[50];
		char itemCategory[10];
		double itemWeight;
		
	public:
		int itemId;
		Inventory()
		{
			itemId = 0;
			itemWeight = 0;
		}
		void getItem();
		void displayItem();
		void saveItem();
		friend double getGoldPrice(Inventory itm, double goldPrice, double silverPrice);
		void updateItem();
		int operator == (char itemNm[20]);
};

void Inventory::getItem()
{
	cin.ignore();
	cout<<"Enter item name : ";
	cin.getline(itemName,50);
	cout<<"Enter item Category : ";
	cin.getline(itemCategory,10);
	cout<<"Enter item Weight in Grams :";
	cin>>itemWeight;
	cin.ignore();
}

void Inventory::displayItem()
{
	cout<<"Item Name : "<<itemName<<endl;
	cout<<"Item Category : "<<itemCategory<<endl;	
	cout<<"Item Weight : "<<itemWeight<<endl;
}

void Inventory::saveItem()
{
	fstream f1, f2;
	f1.open("files/inventory.dat",ios::app);
	f2.open("files/inventoryRec.txt",ios::app);
	f1.write((char *)this, sizeof(Inventory));
	f2<<itemId<<"\n";
	f2.close();
	f1.close();
}

int findTotalUsers()
{
	string flg;
	int num=0;
	fstream targetFile;
	targetFile.open("files/userRec.txt",ios::in);
	while(getline(targetFile, flg))
	{
		num++;
	}
	targetFile.close();
	return num;
}

void adminPanel()
{
	cout<<"Enter 1 to Check Inventory\n";
	cout<<"Enter 2 to Edit Inventory\n";
	cout<<"Enter 3 to update Price\n";
	cout<<"Enter 4 to change role of any user\n";
	cout<<"Enter 5 to add new item to Inventory\n";
	cout<<"Enter 6 to exit\n";
}

void userPanel()
{
	cout<<"Enter 1 to see Designs\n";
	cout<<"Enter 2 to check price of Gold and Silver\n";
	cout<<"Enter 3 to exit\n";
}

void updateUser(Users *frs, int num)
{
	//Code to edit the previous users list to file
	fstream newlist;
	newlist.open("files/users.dat",ios::out);
	for(int i=0; i<num;i++)
	{
		newlist.write((char *)(frs+i), sizeof(Users));
	}
	newlist.close();
}

int findInventory()
{
	string flg;
	int num=0;
	fstream targetFile;
	targetFile.open("files/inventoryRec.txt",ios::in);
	while(getline(targetFile, flg))
	{
		num++;
	}
	targetFile.close();
	return num;
}

void upDatePrice()
{
	ofstream price;
	int pri[2],i=0;
	string fl;
	price.open("files/price.txt");
	cout<<"Enter Price of Gold(10g) in INR  : ";
	cin>>pri[0];
	cout<<"Enter Price of Silver(1kg) in INR : ";
	cin>>pri[1];
	price<<pri[0]<<"\n";
	price<<pri[1]<<"\n";
	price.close();
}

double getGoldPrice(Inventory itm, double goldPrice, double silverPrice)
{
	double price;
	double weightInTola,weightInKilo;
	if(strcmp(itm.itemCategory,"Gold") == 0)
	{
		weightInTola = itm.itemWeight / 10;
		price =  ((goldPrice*0.92)*weightInTola) + (itm.itemWeight*800);
	}
	else if(strcmp(itm.itemCategory,"Silver") == 0)
	{
		weightInKilo = itm.itemWeight / 1000;
		price = (weightInKilo*silverPrice) + (itm.itemWeight*20);
	}
	return price;
}

int Inventory::operator ==(char itemNm[20])
{
	if(strcmp(itemName,itemNm) == 0)
	{
		return 1;	
	}	
	else
	{
		return 0;
	}
}

void Inventory::updateItem()
{
	cin.ignore();
	cout<<"Enter new Item Name : ";
	cin.getline(itemName,50);
	cout<<"Enter item Weight in Grams :";
	cin>>itemWeight;
}

void updateInventory(Inventory *frs, int num)
{
	//Code to edit the previous users list to file
	fstream newlist;
	newlist.open("files/inventory.dat",ios::out);
	for(int i=0; i<num;i++)
	{
		newlist.write((char *)(frs+i), sizeof(*frs));
	}
	newlist.close();
}


int main()
{
	int num, i,inven;
	num = findTotalUsers();
	inven = findInventory();
	
	//Code to read the data of users from users.dat file to the array of object of class Users
	fstream usersData;
	usersData.open("files/users.dat",ios::app | ios::in | ios::binary);
	usersData.seekg(0);
	Users u[num+10];
	for(i=0;i<num;i++)
	{
		usersData.read((char *)&u[i],sizeof(Users));
	}
	usersData.close();
	
	Inventory invent[inven+5];
	fstream inventoryData;
	inventoryData.open("files/inventory.dat",ios::app | ios::in | ios::binary);
	inventoryData.seekg(0);
	Inventory item[inven+10];
	for(i=0;i<inven;i++)
	{
		inventoryData.read((char *)&item[i],sizeof(Inventory));
	}
	inventoryData.close();
	
	int e,auth,inventoryflag,rol,roleId;
	int newId;
	inventoryflag = 0;
	cout<<"Enter 1 to create a new User"<<endl;
	cout<<"Enter 2 to log in as an existing user"<<endl;
	cin>>e;
	
	double goldPrice, silverPrice, price;
	ifstream prices;
	prices.open("files/price.txt");
	prices>>goldPrice;
	prices>>silverPrice;
	prices.close();
	switch(e)
	{
		case 1:
			u[num].getUserData();
			u[num].userID = num+1;
			u[num].saveUserData();
			cout<<"User Successfully Created"<<endl;
			num++;
			auth = 2;
			roleId = 2;
			break;
		case 2:
			Users currentUser;
			currentUser.getUserData();
			auth=0;
			for(i=0;i<num;i++)
			{
				auth = currentUser.compareUser(u[i]);
				if(auth == 1)
				{
					rol = currentUser.getRole(u[i]);
					if(rol==1)
					{
						roleId=1;
					}
					else if(rol==0)
					{
						roleId=2;
					}
					break;
				}
			}
	}
	if(roleId == 1)
	{
		system("CLS");
		cout<<"Welcome\n\n";
		while(e != 6)
		{
			system("CLS");
			cout<<"Welcome\n\n";
			adminPanel();
			cout<<"Gold price is "<<goldPrice<<" Silver price is "<<silverPrice<<endl;
			cin>>e;
			switch(e)
			{
				case 1:
					for(i=0;i<inven;i++)
					{
						item[i].displayItem();
						price = getGoldPrice(item[i],goldPrice, silverPrice);
						cout<<"Price is "<<price<<endl;
					}
					cout<<"Press any key\n";
					cin.ignore();
					break;
				case 2:
					cin.ignore();
					char itemName[20];
					cout<<"Enter item Name : ";
					cin.getline(itemName,20);
					for(i=0;i<inven;i++)
					{
						if(item[i] == itemName)
						{
							item[i].displayItem();
							item[i].updateItem();
							item[i].displayItem();
						}
					}
					updateInventory(&item[0],inven);
					break;
				case 3:
					upDatePrice();
					break;
				case 4:
					cin.ignore();
					char usName[20];
					cout<<"Enter User Name : ";
					cin.getline(usName,20);
					for(i = 0;i<num;i++)
					{
						if(u[i] == usName)
						{
							u[i].displayUserData();
							u[i].editUserData();
							cout<<"Enter\n";
							u[i].displayUserData();
						}
					}
					updateUser(&u[0],num);
					break;
				case 5:
					newId = inven+inventoryflag;
					item[newId].itemId = newId+1;
					item[newId].getItem();
					item[newId].displayItem();
					item[newId].saveItem();
					inventoryflag++;
					inven = findInventory();
					updateInventory(&item[0],inven);
					break;
				case 6:
					break;
				default:
					cout<<"Enter a valid choice ";
					break;
			}
			cout<<"Press enter key to continue\n";
			cin.ignore();	
		}
	}
	else if(roleId==2)
	{
		system("CLS");
		cout<<"Welcome\n\n";
		while(e != 3)
		{
			system("CLS");
			cout<<"Welcome\n\n";
			userPanel();
			cin>>e;
			switch(e)
			{
				case 1 :
					for(i=0;i<inven;i++)
					{
						item[i].displayItem();
						price = getGoldPrice(item[i],goldPrice, silverPrice);
						cout<<"Price is "<<price<<endl;
					}
					cout<<"Press enter key to continue";
					cin.ignore();
					break;
				case 2 :
					cout<<"Price of Gold(10Grams) : "<<goldPrice<<endl;
					cout<<"Price of Silver(1kg) : "<<silverPrice<<endl;
					cout<<"Press enter key to continue";
					cin.ignore();
					break;
				case 3:
					break;
				default:
					cout<<"Enter a valid choice";
			}
			cin.ignore();
		}
	}
	else
	{
		cout<<"Invalid User\n";
	}
	
	return 0;
}
