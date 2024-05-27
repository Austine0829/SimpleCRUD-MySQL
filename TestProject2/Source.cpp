#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;

const string server = "tcp://127.0.0.1:3306";
const string username = "root";
const string password = "root";

class infoManagementSystem {
	private:
		string name{};
		string lastName{};
		string phoneNumber{};
		string birthDate{};
		int id{};
		int getID{};

	public:
		void meneFunc() {
			
			int choice{};

			cout << "[1]Create Data\n";
			cout << "[2]Read Data\n";
			cout << "[3]Update Data\n";
			cout << "[4]Delete Data\n";
			cout << "[5]Exit\n";
			cout << "Enter Choice: ";
			cin >> choice;

			switch (choice)
			{

			case 1:

				addStudentInfo();
				break;

			case 2:

				checkStudentInfo();
				break;

			case 3:

				updateStudentInfo();
				break;

			case 4:

				deleteStudentInfo();
				break;

			case 5:

				exit(1);
				break;

			default:

				cout << "Invalid Choice\n";
				meneFunc();
				break;
			}
		}

		void addStudentInfo() {

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* pstmt;

			try
			{
				driver = get_driver_instance();
				con = driver->connect(server, username, password);
			}
			catch (sql::SQLException e)
			{
				cout << "Could not connect to server. Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}

			con->setSchema("schooldb");
			pstmt = con->prepareStatement("INSERT INTO student_info(student_name, student_last_name, student_phone_number, student_birthdate) VALUES(?, ?, ?, ?);");
 			
			cout << "Enter Student Name: ";
			cin >> name;

			cout << "Enter Student Last Name: ";
			cin >> lastName;

			cout << "Enter Student Phone Number: ";
			cin >> phoneNumber;

			cout << "Enter Student Birth Date (YY//MM//DD): ";
			cin >> birthDate;

			pstmt->setString(1, name);
			pstmt->setString(2, lastName);
			pstmt->setString(3, phoneNumber);
			pstmt->setString(4, birthDate);
			
			pstmt->execute();
			cout << "Details Has Been Inserted In Database." << endl;

			delete pstmt;
			delete con;

			meneFunc();
		}
		
		//BUG//Student ID 1 NOT WORKING 
		void checkStudentInfo() {

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* pstmt;
			sql::ResultSet* result;

			try
			{
				driver = get_driver_instance();
				con = driver->connect(server, username, password);
			}
			catch (sql::SQLException e)
			{
				cout << "Could not connect to server. Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}

			con->setSchema("schooldb");

			pstmt = con->prepareStatement("SELECT * FROM student_info ;");
			result = pstmt->executeQuery();

			while (result->next())
			{
				cout << "Student ID: " << result->getInt(1) << "\n";
				cout << "Student Name: " << result->getString(2) << "\n";
				cout << "Student Phone Number: " << result->getString(3) << "\n";
				cout << "Student Birth Date: " << result->getString(4) << "\n";
			}
				
			delete con;
			delete pstmt;
			delete result;

			meneFunc();
		}

		void updateStudentInfo() {

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* pstmt;

			try
			{
				driver = get_driver_instance();
				con = driver->connect(server, username, password);
			}
			catch (sql::SQLException e)
			{
				cout << "Could not connect to server. Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}

			con->setSchema("schooldb");
			pstmt = con->prepareStatement("UPDATE student_info SET student_name = ?, student_last_name = ?, student_phone_number = ?, student_birthdate = ? WHERE student_id = ?");

			cout << "Enter New Student Name: ";
			cin >> name;

			cout << "Enter New Student Last Name: ";
			cin >> lastName;

			cout << "Enter New Student Phone Number: ";
			cin >> phoneNumber;

			cout << "Enter New Student Birth Date (YY//MM//DD): ";
			cin >> birthDate;

			cout << "Enter Student ID To Confirm Changes: ";
			cin >> id;

			pstmt->setString(1, name);
			pstmt->setString(2, lastName);
			pstmt->setString(3, phoneNumber);
			pstmt->setString(4, birthDate);
			pstmt->setInt(5, id);

			pstmt->executeQuery();

			cout << "Details Has Been Update In Database\n";

			delete con;
			delete pstmt;

			meneFunc();
		}

		void deleteStudentInfo() {

			sql::Driver* driver;
			sql::Connection* con;
			sql::PreparedStatement* pstmt;
			sql::ResultSet* result;

			char choice{};

			try
			{
				driver = get_driver_instance();
				//for demonstration only. never save password in the code!
				con = driver->connect(server, username, password);
			}
			catch (sql::SQLException e)
			{
				cout << "Could not connect to server. Error message: " << e.what() << endl;
				system("pause");
				exit(1);
			}

			con->setSchema("schooldb");
			pstmt = con->prepareStatement("DELETE FROM student_info WHERE student_id = ?");

			cout << "Enter Student ID To Delete Information: ";
			cin >> id;

			pstmt->setInt(1, id);
           
			result = pstmt->executeQuery();

			cout << "Details Has Been Deleted In Database\n";
			
			delete con;
			delete pstmt;
			delete result;
		    
			meneFunc();
		}
};

int main()
{
	infoManagementSystem out;
	out.meneFunc();

	return 0;
}