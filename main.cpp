#include <iostream.h>
#include <cstring>
#include <stdio.h>
#include <sqlca.h>
#include <stdlib.h>

void sql_error(char *msg)
{
    cout<<msg<<endl;
    return;
}

void print_notfound()
{
    cout<<"NOT FOUND";
}
void next()
{
    char m;
    cout<<endl<<"- Press any key to continue -";
    cin.ignore();
    cin.get(m);
    fflush(stdin);
    system("cls");
}

int main()
{
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<"-------------------1914641 Class Student Directory-------------------"<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    
    int t,n;
    char m;
    bool loop = true;
    
    //make the declaration of its elements
    EXEC SQL BEGIN DECLARE SECTION;
    char username[20];
    char password[20];
    char server[10];
    char sno[10];
    char sname[30];
    char sgender[10];
    char sage[3];
    char sdept[30];
    char cno[3];
    char grade[4];
    char cname[50];
    char cpno[3];
    char ccredit[2];
    char temp[20];
    char temp1[20];
    EXEC SQL END DECLARE SECTION;
    
    //implement username, password, and server to connect with the database
    cout<<"Insert Username:";
    cin>>username;
    cout<<endl<<"Insert Password:";
    cin>>password;
    cout<<endl<<"Insert Server Name:";
    cin>>server;
    
    // connecting to the database
    EXEC SQL CONNECT:username IDENTIFIED BY :password USING :server;
    
    if(sqlca.sqlcode==0)
        cout<<"Connecting success. \nConnected to ORACLE as user "<<username<<" CONGRATULATION!"<<endl;
    else
    {
        printf("%.*s\n",sqlca.sqlerrm.sqlerrml,sqlca.sqlerrm.sqlerrmc);
        return 0;
    }
    
    next();
    
    // creating TABLE S
    EXEC SQL CREATE TABLE S
    (
     sno NUMBER(10) PRIMARY KEY,
     sname VARCHAR(30),
     sgender CHAR(6),
     sage NUMBER(2),
     sdept VARCHAR(30)
     );
    
    // creating TABLE SC
    EXEC SQL CREATE TABLE SC
    (
     sno NUMBER(9) PRIMARY KEY,
     cno NUMBER(2),
     grade NUMBER(2),
     );
    
    // creating TABLE C
    EXEC SQL CREATE TABLE C
    (
     cno NUMBER(2) PRIMARY KEY,
     cname CHAR(30),
     cpno NUMBER(2),
     ccredit NUMBER(2),
     );
    
    // creating the main menu
    while(1)
    {
    start:
        system("cls");
        cout<<"-------------------------------------------------------------------------------"<<endl;
        cout<<"                     ~ MAIN MENU ~"<<endl;
        cout<<"               Please Choose the Option You Need!"<<endl;
        cout<<"                     0:Display the Table"<<endl;
        cout<<"                     1:Add New Data"<<endl;
        cout<<"                     2:Delete the Data"<<endl;
        cout<<"                     3:Update Data"<<endl;
        cout<<"                     4:Show Information"<<endl;
        cout<<"                     5: Exit"<<endl;
        cout<<"-------------------------------------------------------------------------------"<<endl;
        do
        {
            cout<<"Your option? "; 	cin>>t;
        } while (t>5||t<0);
        
        switch (t)
        {
            case 0:
            {
                while (loop)
                {
                    system("cls");
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"Select the Table to Display: "<<endl;
                    cout<<"0: Student Table"<<endl;
                    cout<<"1: Student-Course Table"<<endl;
                    cout<<"2: Course Table"<<endl;
                    cout<<"3: Return to main menu"<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    cout<<"Your option? "; cin>>n;
                    
                    
                    EXEC SQL WHENEVER NOT FOUND DO break;
                    
                    switch (n)
                    {
                        case 0:// show Student Table include: sno,sname,sgender,sage,sdept
                            system("cls");
                            cout<<"----------------------------------------------------------"<<endl;
                            cout<<"            Display the Student Table"<<endl;
                            cout<<"----------------------------------------------------------"<<endl;
                            
                            EXEC SQL DECLARE tmp0 CURSOR FOR
                            SELECT sno, sname, sgender, sage, sdept FROM S;
                            EXEC SQL OPEN tmp0;
                            for (;;)
                            {
                                EXEC SQL FETCH tmp0 INTO :sno, :sname, :sgender, :sage, :sdept;
                                cout<<"Student's number="<<sno<<endl;
                                cout<<"Student's name="<<sname<<endl;
                                cout<<"Student's gender="<<sgender<<endl;
                                cout<<"Student's age="<<sage<<endl;
                                cout<<"Student's department="<<sdept<<endl;
                                cout<<"*****************************"<<endl;
                            }
                            EXEC SQL CLOSE tmp0;
                            next();
                            break;
                        case 1:// show Student-Course table include: sno, cno, grade
                            system("cls");
                            cout<<"----------------------------------------------------------"<<endl;
                            cout<<"           Display the Student-Course Table"<<endl;
                            cout<<"----------------------------------------------------------"<<endl;
                            
                            EXEC SQL DECLARE tmp1 CURSOR FOR
                            SELECT sno, cno, grade FROM SC;
                            EXEC SQL OPEN tmp1;
                            for (;;)
                            {
                                EXEC SQL FETCH tmp1 INTO :sno, :cno, :grade;
                                cout<<"Student's number="<<sno<<endl;
                                cout<<"Course number="<<cno<<endl;
                                cout<<"Student's Grade="<<grade<<endl;
                                cout<<"*****************************"<<endl;
                            }
                            EXEC SQL CLOSE tmp1;
                            next();
                            break;
                        case 2://show Course table include: cno, cname, cpno, ccredit
                            system("cls");
                            cout<<"----------------------------------------------------------"<<endl;
                            cout<<"                Display the Course Table"<<endl;
                            cout<<"----------------------------------------------------------"<<endl;
                            
                            EXEC SQL DECLARE tmp2 CURSOR FOR
                            SELECT cno, cname, cpno, ccredit FROM C;
                            EXEC SQL OPEN tmp2;
                            for (;;)
                            {
                                EXEC SQL FETCH tmp2 INTO :cno, :cname, :cpno, :ccredit;
                                cout<<"Course number="<<cno<<endl;
                                cout<<"Course name="<<cname<<endl;
                                cout<<"Prerequisite Course number="<<cpno<<endl;
                                cout<<"Course credit="<<ccredit<<endl;
                                cout<<"*****************************"<<endl;
                            }
                            EXEC SQL CLOSE tmp2;
                            next();
                            break;
                        case 3:
                            goto start;
                    }; //close the switch
                } // end while statement of case 0
                break;
                
            case 1:
                while (loop)
                {
                    system("cls");
                    cout<<"-------------------------------------------------------"<<endl;
                    cout<<"Select the Table to be added a new data"<<endl;
                    cout<<"0: Student Table"<<endl;
                    cout<<"1: Student-Course Table"<<endl;
                    cout<<"2: Course Table"<<endl;
                    cout<<"3. Return to main menu"<<endl;
                    cout<<"-------------------------------------------------------"<<endl;
                    cout<<"Your option? "; cin>>t;
                    
                    switch (t)
                    {
                        case 0:  // Adding new data to S which include: sno, sname, sgender, sage, sdept
                            system("cls");
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<"         Add New Data to Student Table"<<endl;
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<endl<<"Please enter the Student's number: ";			cin>>sno;
                            cout<<endl<<"Please enter the Student's name: ";			cin>>sname;
                            cout<<endl<<"Please enter the Student's gender: ";			cin>>sgender;
                            cout<<endl<<"Please enter the Student's age: ";				cin>>sage;
                            cout<<endl<<"Please enter the Student's department: ";		cin>>sdept;
                            
                            EXEC SQL INSERT INTO S(sno, sname, sgender, sage, sdept)
                            values(:sno, :sname, :sgender, :sage, :sdept);
                            
                            
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data has been successfully added to Student Table."<<endl;
                            
                            next();
                            break;
                            
                            
                        case 1:  // Adding new data to SC which include: sno, cno, grade
                            system("cls");
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<"         Add New Data to Student-Course Table"<<endl;
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<endl<<"Please enter the Student's number: ";			cin>>sno;
                            cout<<endl<<"Please enter the Course that the student took: ";	cin>>cno;
                            cout<<endl<<"Please enter the Grade: ";					cin>>grade;
                            
                            EXEC SQL INSERT INTO SC(sno, cno, grade)
                            values(:sno, :cno, :grade);
                            
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data has been successfully added to Student-Course Table."<<endl;
                            
                            next();
                            break;
                            
                            
                        case 2: // Adding new data to C which include:cno, cname, cpno, ccredit
                            system("cls");
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<"           Add New Data to Course Table"<<endl;
                            cout<<"--------------------------------------------------------------"<<endl;
                            cout<<endl<<"Enter the Course number:";				cin>>cno;
                            cout<<endl<<"Enter the Course name:";				cin>>cname;
                            cout<<endl<<"Enter the cpno:";						cin>>cpno;
                            cout<<endl<<"Enter the Course credit:";				cin>>ccredit;
                            
                            EXEC SQL INSERT INTO C(cno, cname, cpno, ccredit)
                            values(:cno, :cname, :cpno, :ccredit);
                            
                            
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data has been successfully added to Course Table."<<endl;
                            
                            next();
                            break;
                            
                            
                        case 3:
                            goto start;
                    }; // closing switch
                }//end while statement of case 1
                break;
                
            case 2:
                while (loop)
                {
                    system("cls");
                    cout<<"-----------------------------------------------------------"<<endl;
                    cout<<"Select the Table to be deleted the data"<<endl;
                    cout<<"0: Student Table"<<endl;
                    cout<<"1: Student-Course Table"<<endl;
                    cout<<"2: Course Table"<<endl;
                    cout<<"3: Return to Main Menu"<<endl;
                    cout<<"----------------------------------------------------------"<<endl;
                    cin>>t;
                    
                    EXEC SQL WHENEVER NOT FOUND DO print_notfound();
                    
                    switch (t)
                    {
                        case 0: //delete data from S Table include: sno, sname, sgender ,sage, sdept
                            system("cls");
                            do
                            {
                                cout<<"-----------------------------------------------------------"<<endl;
                                cout<<"        Delete data from Student Table"<<endl;
                                cout<<"----------------------------------------------------------"<<endl;
                                cout<<"Choose to delete data with: "<<endl;
                                cout<<"1: Student number"<<endl;
                                cout<<"2: Student name"<<endl;
                                cin>>n;
                            } while (n < 1 || n > 2);
                            
                            if (n == 1)
                            {
                                cout<<"Please enter the Student's number:"<<endl;
                                cin>>sno;
                                EXEC SQL DELETE FROM S
                                WHERE sno=:sno;
                            }
                            else
                            {
                                cout<<"Please enter the student's name:"<<endl;
                                cin>>sname;
                                EXEC SQL DELETE FROM S
                                WHERE sname=:sname;
                            }
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data in Student Table has been deleted successfully."<<endl;
                            next();
                            break;
                            
                        case 1: //delete data from SC Table include: sno, cno, grade
                            system("cls");
                            cout<<"----------------------------------------------------------------"<<endl;
                            cout<<"         Delete data from Student-Course Table"<<endl;
                            cout<<"----------------------------------------------------------------"<<endl;
                            cout<<"Please enter the student's number:"<<endl;   cin>>sno;
                            cout<<"Please enter the course number:"<<endl;  	cin>>cno;
                            EXEC SQL DELETE FROM SC
                            WHERE sno=:sno AND cno=:cno;
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data in Student-Course Table has been deleted successfully."<<endl;
                            next();
                            break;
                        case 2: //delete data from C Table include: cno, cname, cpno, ccredit
                            system("cls");
                            do
                            {
                                cout<<"-----------------------------------------------------------"<<endl;
                                cout<<"         Delete data from Course Table"<<endl;
                                cout<<"----------------------------------------------------------"<<endl;
                                cout<<"Choose to delete data with: "<<endl;
                                cout<<"1: Course number "<<endl;
                                cout<<"2: Course name"<<endl;
                                cout<<"Your option? ";  cin>>n;
                            } while (n < 1 || n > 2);
                            
                            if (n == 1)
                            {
                                cout<<"Please enter the course number:"<<endl;
                                cin>>cno;
                                EXEC SQL DELETE FROM C
                                WHERE cno=:cno;
                            }
                            else
                            {
                                cout<<"Please enter the course name:"<<endl;
                                cin>>cname;
                                EXEC SQL DELETE FROM C
                                WHERE cname=:cname;
                            }
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"The data in Course Table has been deleted successfully."<<endl;
                            next();
                            break;
                            
                        case 3:
                            goto start;
                    }; // close the switch
                } // end while statement of case 2
                break;
                
            case 3:
                while (loop)
                {
                    system("cls");
                    cout<<"-----------------------------------------------------"<<endl;
                    cout<<"Select the Table to be updated the data: "<<endl;
                    cout<<"0: Student Table"<<endl;
                    cout<<"1: Student-CourseTable"<<endl;
                    cout<<"2: Course Table"<<endl;
                    cout<<"3: Back"<<endl;
                    cout<<"-----------------------------------------------------"<<endl;
                    cout<< "Your option? ";  cin>>t;
                    
                    EXEC SQL WHENEVER NOT FOUND DO continue;
                    
                    switch (t)
                    {
                        case 0: // update data from S Table: choose sno,then update; sname, sgender, sage, sdept
                            system("cls");
                            cout<<"-----------------------------------------------------"<<endl;
                            cout<<"    Update the Data in Student Table"<<endl;
                            cout<<"-----------------------------------------------------"<<endl;
                            cout<<"Please enter the Student's number to update:"<<endl;   cin>>temp;
                            cout<<"Enter the new data:"<<endl;
                            
                            cout<<endl<<"Student's name:";		    cin>>sname;
                            cout<<endl<<"Student's gender:";		cin>>sgender;
                            cout<<endl<<"Student's age:";			cin>>sage;
                            cout<<endl<<"Student's department:";	cin>>sdept;
                            
                            EXEC SQL UPDATE S
                            SET sname= :sname,
                            sgender= :sgender,
                            sage= :sage,
                            sdept= :sdept
                            WHERE sno=:temp; EXEC SQL COMMIT;
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"Data in Student Table has been updated."<<endl;
                            next();
                            break;
                            
                            
                        case 1: // update data from SC Table: Choose sno and cno,then update grade
                            system("cls");
                            cout<<"-----------------------------------------------------------"<<endl;
                            cout<<"   Update the Data in Student-Course Table"<<endl;
                            cout<<"----------------------------------------------------------"<<endl;
                            cout<<"Please enter the Student number you want to edit:"<<endl;
                            cin>>temp;
                            cout<<"Please enter the Course number you want to edit:"<<endl;
                            cin>>temp1;
                            cout<<"Enter the new data:"<<endl;
                            cout<<endl<<"Grade:";				cin>>grade;
                            
                            EXEC SQL UPDATE SC
                            SET grade= :grade
                            WHERE sno=:temp AND cno=:temp1; EXEC SQL COMMIT;
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else
                                cout<<endl<<"Data in Student-Course Table has been updated."<<endl;
                            next();
                            break;
                        case 2: // update data from C Table: Choose cno,then update; cname, cpno, ccredit
                            system("cls");
                            cout<<"-----------------------------------------------------------"<<endl;
                            cout<<"     Update the Data in Course Table"<<endl;
                            cout<<"----------------------------------------------------------"<<endl;
                            cout<<"Please enter the Course number to update:"<<endl;
                            cin>>temp;
                            cout<<"Enter the new data:"<<endl;
                            
                            cout<<endl<<"Course name:";				cin>>cname;
                            cout<<endl<<"Prerequisite number:";		cin>>cpno;
                            cout<<endl<<"Course credit:";			cin>>ccredit;
                            
                            EXEC SQL UPDATE C
                            SET cname= :cname,
                            cpno= :cpno,
                            ccredit= :ccredit
                            WHERE cno= :temp; EXEC SQL COMMIT;
                            if (sqlca.sqlcode != 0)
                                printf("ERROR!\n");
                            else 
                                cout<<endl<<"Data in Course Table has been updated."<<endl;
                            next();
                            break;		
                            
                        case 3:
                            goto start;
                    }; // closing switch
                }// end which statement of case 3
                break;
                
            case 4:
                while (loop)
                {
                    system("cls");
                    cout<<"------------------------------------------------------"<<endl;
                    cout<<"Select the Table to show information"<<endl;
                    cout<<"0: Student table"<<endl;
                    cout<<"1: Student-Course table"<<endl;
                    cout<<"2: Course table"<<endl;
                    cout<<"3: Return to Main Menu"<<endl;
                    cout<<"------------------------------------------------------"<<endl;
                    cout<<"Your option? "; cin>>t;
                    
                    EXEC SQL WHENEVER NOT FOUND DO print_notfound();
                    switch (t)
                    {
                        case 0: // Show information in S Table include : sno, sname, sgender, sage, sdept
                            system("cls");
                            do
                            {
                                cout<<"--------------------------------------------------------------"<<endl;
                                cout<<"     Showing information in Student Table"<<endl;
                                cout<<"--------------------------------------------------------------"<<endl;
                                cout<<"Choose number to show information from S table with : " <<endl;
                                cout<<"1: Student number"<<endl;
                                cout<<"2: Student name"<<endl;
                                cout<<"3: Student gender"<<endl;
                                cout<<"4: Student department"<<endl;
                                cout<<"Your option? "; cin>>n;
                            } while (n<1 || n>4);
                            
                            if (n == 1)
                            {
                                cout<<"Please enter the Student's number"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp3 CURSOR FOR
                                SELECT sno, sname, sgender, sage, sdept FROM S
                                WHERE sno=:temp;
                                EXEC SQL OPEN tmp3;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp3 INTO :sno, :sname, :sgender, :sage, :sdept;
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Student's name="<<sname<<endl;
                                    cout<<"Student's gender="<<sgender<<endl;
                                    cout<<"Student's age="<<sage<<endl;
                                    cout<<"Student's department="<<sdept<<endl;
                                }
                                EXEC SQL CLOSE tmp3;
                            }
                            else if (n == 2)
                            {
                                cout<<"Please enter the Student's name (don't forget the capital letter): "<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp4 CURSOR FOR
                                SELECT sno, sname, sgender, sage, sdept FROM S
                                WHERE sname=:temp;
                                EXEC SQL OPEN tmp4;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp4 INTO :sno, :sname, :sgender, :sage, :sdept;
                                    
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Student's name="<<sname<<endl;
                                    cout<<"Student's gender="<<sgender<<endl;
                                    cout<<"Student's age="<<sage<<endl;
                                    cout<<"Student's department="<<sdept<<endl;
                                }
                                EXEC SQL CLOSE tmp4;
                            }
                            else if (n == 3)
                            {
                                cout<<"Please enter the Student's gender (don't forget the capital letter):"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp5 CURSOR FOR
                                SELECT sno, sname, sgender, sage, sdept FROM S
                                WHERE sgender=:temp;
                                EXEC SQL OPEN tmp5;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp5 INTO :sno, :sname, :sgender, :sage, :sdept;
                                    
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Student's name="<<sname<<endl;
                                    cout<<"Student's gender="<<sgender<<endl;
                                    cout<<"Student's age="<<sage<<endl;
                                    cout<<"Student's department="<<sdept<<endl;
                                    cout<<"------------------------------------"<< endl;
                                }
                                EXEC SQL CLOSE tmp5;
                            }
                            else if (n == 4)
                            {
                                cout<<"Please enter the Student's Department (don't forget the capital letter):"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp6 CURSOR FOR
                                SELECT sno, sname, sgender, sage, sdept FROM S
                                WHERE sdept=:temp;
                                EXEC SQL OPEN tmp6;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp6 INTO :sno, :sname, :sgender, :sage, :sdept;
                                    
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Student's name="<<sname<<endl;
                                    cout<<"Student's gender="<<sgender<<endl;
                                    cout<<"Student's age="<<sage<<endl;
                                    cout<<"Student's department="<<sdept<<endl;
                                    cout<<"------------------------------------"<< endl;
                                }
                                EXEC SQL CLOSE tmp6;
                            }
                            next();
                            break;
                        case 1: // Show information in SC Table include : sno, cno, grade
                            system("cls");
                            do
                            {
                                cout<<"-------------------------------------------------------------------"<<endl;
                                cout<<"   Showing information in Student-Course Table"<<endl;
                                cout<<"-------------------------------------------------------------------"<<endl;
                                cout<<"Choose number to show information from SC table with : " <<endl;
                                cout<<"1: Student number"<<endl;
                                cout<<"2: Course number"<<endl;
                                cout<<"Your option? "; cin>>n;
                            } while (n < 1 || n > 2);
                            
                            if (n == 1)
                            {
                                cout<<"Please enter the Student's number"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp7 CURSOR FOR
                                SELECT sno, cno, grade FROM SC
                                WHERE sno=:temp;
                                EXEC SQL OPEN tmp7;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp7 INTO :sno, :cno, :grade;
                                    
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Course number="<<cno<<endl;
                                    cout<<"Grade="<<grade<<endl;
                                }
                                EXEC SQL CLOSE tmp7;
                            }
                            else
                            {
                                cout<<"Please enter the Course number"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp8 CURSOR FOR
                                SELECT sno, cno, grade FROM SC
                                WHERE cno=:temp;
                                EXEC SQL OPEN tmp8;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp8 INTO :sno, :cno, :grade;
                                    
                                    cout<<"Student's number="<<sno<<endl;
                                    cout<<"Course number="<<cno<<endl;
                                    cout<<"Grade="<<grade<<endl;
                                }
                                EXEC SQL CLOSE tmp8;
                            }
                            next();
                            break;
                        case 2: // Show information in C Table include : cno, cname, cpno, ccredit
                            system("cls");
                            do
                            {
                                cout<<"-----------------------------------------------------------"<<endl;
                                cout<<"     Showing information in Course Table"<<endl;
                                cout<<"-----------------------------------------------------------"<<endl;
                                cout<<"Choose number to show information from table C : "<<endl;
                                cout<<"1: Course number "<<endl;
                                cout<<"2: Course name "<<endl;
                                cout<<"Your option? "; cin>>n;
                            } while (n < 1 || n > 2);
                            
                            if (n == 1)
                            {
                                cout<<"Please enter the Course number:"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp9 CURSOR FOR
                                SELECT cno, cname, cpno, ccredit FROM C
                                WHERE cno=:temp;
                                EXEC SQL OPEN tmp9;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp9 INTO :cno, :cname, :cpno, :ccredit;
                                    
                                    cout<<"Course number="<<cno<<endl;
                                    cout<<"Course name="<<cname<<endl;
                                    cout<<"Course prequisite no="<<cpno<<endl;
                                    cout<<"Course credit="<<ccredit<<endl;
                                }
                                EXEC SQL CLOSE tmp9;
                            }
                            else
                            {
                                cout<<"Please enter the Course name"<<endl;
                                cin>>temp;
                                EXEC SQL DECLARE tmp10 CURSOR FOR
                                SELECT cno, cname, cpno, ccredit FROM C
                                WHERE cname=:temp;
                                EXEC SQL OPEN tmp10;
                                EXEC SQL WHENEVER NOT FOUND DO break;
                                for (;;)
                                {
                                    EXEC SQL FETCH tmp10 INTO :cno, :cname, :cpno, :ccredit;
                                    
                                    cout<<"Course number="<<cno<<endl;
                                    cout<<"Course name="<<cname<<endl;
                                    cout<<"Cpno="<<cpno<<endl;
                                    cout<<"Course credit="<<ccredit<<endl;
                                }
                                EXEC SQL CLOSE tmp10;
                            }
                            next();
                            break;
                        case 3:
                            goto start;
                    }; // close the switch
                }// end while statement of case 4
                break;
            case 5:
                cout<<endl<<endl<<"Save the changes?(Y - save the changes) ";
                cout<<endl<<endl<<"Save the changes?(C - Back to Main Menu) "<<endl;	
                cin>>m;
                if (m == 'Y' || m == 'y')
                {
                    EXEC SQL COMMIT WORK RELEASE; cout<<"Changes Has Been Save."<<endl;
                }
                else 
                    goto start;
                return 0;
                
            };
        }
        
        return 0;
    }
    
}




