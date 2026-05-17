#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"



void listContacts(AddressBook *addressBook) 
{
    // Sort contacts based on the chosen criteria

    int i, order,sortCriteria ;
    
    printf("Choose how would you want to display the contacts :\n1.Name\n2.Phone No\n3.Email ID\n4.list as it is\n");
    scanf("%d",  &sortCriteria);
    

    if(sortCriteria >= 1 && sortCriteria <= 3)
    {
        printf("1.ascending\n2.descending\n");
        scanf("%d", &order);

        if(order != 1 && order != 2)
        {
            printf("Invalid order\n");
            return;
        }

        sort(addressBook, sortCriteria, order);
    }
    
    else if(sortCriteria != 4) 
    {
        printf("Invalid input");
        return;
    }

    printTableHeader();

    for(i = 0; i < addressBook->contactCount; i++ )
    {
        printf("| %-2d | %-22s | %-12s | %-26s |\n",
                    i + 1,
                    addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,
                    addressBook->contacts[i].email);                        
    } 
    // Print table footer
    printf("+----+------------------------+--------------+----------------------------+");

}
           
        

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    
    //Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
    
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
  
    char name_valid[50];
    char phone_valid[20];
    char email_valid[50];
    int result;

	/* Define the logic to create a Contacts */
    if(addressBook->contactCount < MAX_CONTACTS)
    {
        // Index where new contact will be stored
        int i = addressBook->contactCount ;

         // Loop until a valid name is entered
        do
        {
            printf("\nEnter the name : ");
            scanf(" %[^\n]", name_valid);

            // Validate the entered name
            result = validation_name(name_valid);

            if(result)
               strcpy( addressBook->contacts[i].name, name_valid);
            else 
               printf("\n\t\t\tEnter Proper Name\n");

        }while(result == 0);

        // Loop until a valid and unique phone number is entered
        do
        {
            printf("\nEnter the Phone No :");
            scanf(" %s", phone_valid);

            // Validate phone number and check for duplicates
            result = validation_PhoneNo(addressBook, phone_valid);

            if(result == 1) 
               strcpy( addressBook->contacts[i].phone, phone_valid);
            else if(result == -1)  
               printf("\n\t\t\tPhone No already exist\n");
            else 
               printf("\n\t\t\tEnter Proper Phone No\n");

        }while(result == 0 || result == -1);


         // Loop until a valid and unique email ID is entered
        do
        {
            printf("\nEnter the Email ID :");
            scanf(" %s", email_valid);

            // Validate email format and check for duplicates
            result = validation_Email(addressBook, email_valid);

            if(result == 1)
               strcpy( addressBook->contacts[i].email, email_valid);
            else if(result == -1)
               printf("\n\t\t\tEmail id already exists\n");
            else
               printf("\n\t\t\tInvalid Email id Format\n");

        }while(result == 0 || result == -1);

        // Increment total number of contacts
        addressBook->contactCount++;

        printf("+------------------------------------------+\n");
        printf("| Contact Added Successfully               |\n");
        printf("+------------------------------------------+\n");
        printf("| Name  : %-32s |\n", addressBook->contacts[i].name);
        printf("| Phone : %-32s |\n", addressBook->contacts[i].phone);
        printf("| Email : %-32s |\n", addressBook->contacts[i].email);
        printf("+------------------------------------------+\n");
        
    }
    else 
    {
        printf("Address book is full. Cannot add more contacts.\n");
    }
}


void searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int choice, i, found = 0;
    char search[50];

    printf("\nEnter what you want to search:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &choice);


    switch(choice)
    {
        case 1:
            found = 0;
            printf("Enter the name : ");
            scanf(" %[^\n]", search);

            
            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Case-insensitive substring match for name
                if( strcasestr(addressBook->contacts[i].name, search)  )
                {
                    if(found == 0)
                       printTableHeader();
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            i + 1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    found = 1;    
                }
            }

            if(found)
                printf("+----+------------------------+--------------+----------------------------+");
            
            // If no match found
            else
            {
               printf("Contact not found\n");
            }
            
            break;


        case 2:
            found = 0;
            printf("Enter the Phone number: ");
            scanf(" %s", search);


            for(i = 0; i < addressBook->contactCount; i++)
            {
                //compare phone number
                if((strcmp(search, addressBook->contacts[i].phone)== 0) )
                {
                    if(found == 0)
                       printTableHeader();
                    
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            i + 1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    found = 1;
                    break;    
                }
            }

            if(found)
               printf("+----+------------------------+--------------+----------------------------+");

            // If no match found
            else
            {
                printf("Contact not found\n");
            }
            break;

        case 3:
            found = 0;
            printf("Enter the Email: ");
            scanf(" %s", search);

            
            for(i = 0; i < addressBook->contactCount; i++)
            {

                if((strcmp(search, addressBook->contacts[i].email)== 0) )
                {
                    if(found == 0)
                       printTableHeader();
                    //compare email
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            i + 1,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    found = 1; 
                    break;   
                }
            }

            if(found)
               printf("+----+------------------------+--------------+----------------------------+");

            // If no match found
            else
            {
                printf("Contact not found\n");
            }
            break;
        
            
        default:
            printf("Invalid Input"); 
            break;   
            
    }


}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int choice, choice_1, i, position;
    int serial_no = 0 , edit_index = -1, result;
    char edited_newone[50];
    char search[50];
    int match_index[100];
    printf("\nEnter what you want to search:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &choice);

    switch(choice)
    {
        case 1:

            // Search contact by name (partial match)
            serial_no = 0; 
            printf("Enter the name : ");
            scanf(" %[^\n]", search);

            

            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Case-insensitive substring match
                if(strcasestr(addressBook->contacts[i].name, search) )
                {
                    if(serial_no == 0)
                       printTableHeader();
                    serial_no++;                         // Count matches
                    match_index[ serial_no - 1] = i;     // Store index


                    // Display matched contact   
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            serial_no,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    
                     
                }
            }
            if(serial_no)
                printf("+----+------------------------+--------------+----------------------------+\n");
            
            break;


        case 2:
            // Search contact by phone number
            serial_no = 0; 
            printf("Enter the Phone number: ");
            scanf(" %s", search);
            

            

            for(i = 0; i < addressBook->contactCount; i++)
            {
                if((strcmp(search, addressBook->contacts[i].phone)== 0) )
                {
                    if(serial_no == 0)
                       printTableHeader();
                    serial_no = 1;
                    match_index[0] = i;
                    
                    
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            serial_no,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    printf("+----+------------------------+--------------+----------------------------+\n");    
                    break;    
                }
            }
            
            
            break;

        case 3:
            // Search contact by email
            serial_no = 0; 
            printf("Enter the Email: ");
            scanf(" %s", search);
            
            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Exact email match
                if((strcmp(search, addressBook->contacts[i].email)== 0) )
                {
                    if(serial_no == 0)
                       printTableHeader(); 
                    serial_no = 1;
                    match_index[0] = i;
                   
                    
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            serial_no,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                           addressBook->contacts[i].email);
                    printf("+----+------------------------+--------------+----------------------------+\n");       
                    break;   
                }
            }
            
            
            break;
        
            
        default:
            printf("Invalid Input"); 
            return;   
            
    }


    // If no contact found
    if(serial_no == 0)
    {       
        printf("Contact not found\n"); 
        return;  
    }

    // If only one contact matched
    if(serial_no == 1)
    {
        edit_index = match_index[0];    
    }

    // If multiple contacts matched
    else if(serial_no > 1)
    {
        printf("Which position do you want to edit : ");
        scanf("%d", &position);

        // Validate position
        if(position < 1 || position > serial_no)
        {
            printf("Invalid input");
            return;
        }
        edit_index = match_index[position - 1];

    }

    // Ask user what field to edit
    printf("\nEnter what you want to edit:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &choice_1);

    switch(choice_1)
    {
        case 1:
            // Edit name
            do
            {
                printf("Enter the new name :");
                scanf(" %[^\n]", edited_newone);
                result = validation_name(edited_newone);

                if(result)
                   strcpy( addressBook->contacts[edit_index].name, edited_newone);
                else
                   printf("\n\t\t\tEnter Proper Name\n");
                
            }while(!result);

            break;

        
        case 2:
            // Edit phone number
            do
            {
                printf("Enter the new phone no :");
                scanf(" %s", edited_newone);
                result = validation_PhoneNo(addressBook, edited_newone);
                if(result == 1)
                   strcpy( addressBook->contacts[edit_index].phone, edited_newone); 
                else if(result == -1)
                   printf("\n\t\t\tPhone No already exist\n");
                else
                   printf("\n\t\t\tEnter Proper Phone No\n");
            }while(result == 0 || result == -1);
                
            break; 
            
        
        case 3:
            // Edit email ID
            do
            {
                printf("Enter the new email id : ");
                scanf(" %s", edited_newone);
                result = validation_Email(addressBook, edited_newone);
                if(result == 1)
                   strcpy(addressBook->contacts[edit_index].email, edited_newone); 
                 else if(result == -1)
                   printf("\n\t\t\tEmail id already exists\n");
                else
                   printf("\n\t\t\tInvalid Email id Format\n");
            }while(result == 0 || result == -1);
                
            break;
            
        default:
            printf("Invalid");   
            return; 
    }
    // Display updated contact
    printf("+------------------------------------------+\n");
    printf("| Updated Contact                          |\n");
    printf("+------------------------------------------+\n");
    printf("| Name  : %-32s |\n", addressBook->contacts[edit_index].name);
    printf("| Phone : %-32s |\n", addressBook->contacts[edit_index].phone);
    printf("| Email : %-32s |\n", addressBook->contacts[edit_index].email);
    printf("+------------------------------------------+\n");
                     
    
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int choice, i, position;
    int serial_no = 0 ;
    int edit_index = -1;
    char Y_or_N;
    char search[50];
    int match_index[100];
    printf("\nEnter what you want to search:\n1.Name\n2.Phone\n3.Email\n");
    scanf("%d", &choice);
    serial_no = 0;
    edit_index = -1;
    switch(choice)
    {
        case 1:
            // Search contact by name (partial match)
            serial_no = 0; 
            printf("Enter the name : ");
            scanf(" %[^\n]", search);

            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Case-insensitive substring match
                if( strcasestr(addressBook->contacts[i].name, search) )
                {
                    if(serial_no == 0)
                       printTableHeader(); 
                    serial_no++;                          // Increase match count
                    match_index[ serial_no - 1] = i;      // Store index

                    
                    // Display matched contact  
                    printf("| %-2d | %-22s | %-12s | %-26s |\n",
                            serial_no,
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email); 
                    
                    
                     
                }
            }
            if(serial_no)
               printf("+----+------------------------+--------------+----------------------------+");
            break;


        case 2:
            serial_no = 0; 
            printf("Enter the Phone number : ");
            scanf(" %s", search);

            

            
            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Exact phone match
                if((strcmp(search, addressBook->contacts[i].phone)== 0) )
                {
                    if(serial_no == 0)
                       printTableHeader(); 
                    serial_no = 1;
                    match_index[0] = i;
                    printf("Matching contacts: \n");
                    

                    printf("| 1  | %-22s | %-12s | %-26s |\n",
                            
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                    printf("+----+------------------------+--------------+----------------------------+\n");
                    break;
                        
                }
            }
            
            break;

        case 3:
            serial_no = 0; 
            printf("Enter the Email: ");
            scanf(" %s", search);
            
            
            for(i = 0; i < addressBook->contactCount; i++)
            {
                // Exact email match
                if((strcmp(search, addressBook->contacts[i].email)== 0) )
                {
                    if(serial_no == 0)
                       printTableHeader();  
                    serial_no = 1;
                    match_index[0] = i;
                    printf("Matching contacts: \n");
                    
                    printf("| 1  | %-22s | %-12s | %-26s |\n",
                            
                            addressBook->contacts[i].name,
                            addressBook->contacts[i].phone,
                            addressBook->contacts[i].email);
                   printf("+----+------------------------+--------------+----------------------------+\n");
                   break;
                       
                }
            }
            
            break;
        
            
        default:
            printf("Invalid Input"); 
            return;   
            
    }

    // If no contact found
    if(serial_no == 0)
    {       
        printf("Contact not found\n");
        return;
        
    }
   

    // Ask user for confirmation before deletion
    printf("Do you want to delete this contact : (Y/N)\nEnter:\nY---->Yes\nN---->No ");
    scanf(" %c", &Y_or_N);

    // If user does not confirm, exit
    if(Y_or_N != 'Y' && Y_or_N != 'y')
        return;
    
    // If only one contact matched    
    if(serial_no == 1)
    {
        edit_index = match_index[0];    
    }


    // If multiple contacts matched
    else if(serial_no > 1)
    {
        printf("Which position do you want to delete : ");
        scanf("%d", &position);

        // Validate position
        if(position < 1 || position > serial_no)
        {
            printf("Invalid position\n");
            return;
        }
        edit_index = match_index[position - 1];
    }
     
    
    // Shift contacts to overwrite the deleted contact
    for(i = edit_index; i < addressBook->contactCount - 1; i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i + 1]; 
    }

    // Decrease contact count
    addressBook->contactCount --;


    
    printTableHeader();
    for(i = 0; i < addressBook->contactCount; i++)
   {
        printf("| %-2d | %-22s | %-12s | %-26s |\n",
            i + 1,
            addressBook->contacts[i].name,
            addressBook->contacts[i].phone,
            addressBook->contacts[i].email);
   }

    printf("+----+------------------------+--------------+----------------------------+");


    
}
                              
   



int validation_name(char *name)
{
    int i = 0, dot_count = 0;
    
    while(name[i])
    {
        // alphabet
        if( (name[i] >= 'a' && name[i] <= 'z')||
            ( name[i] >= 'A' && name[i] <= 'Z') )  
        {
                i++;               
                
        }

        // space
        else if( name[i] == ' ' )
        {
            // staring space, trailing space
            if( i == 0 || name[i + 1] == ' ' || name[i + 1] == '\0')
               return 0;
            i++;
                
        }

        //dot
        else if( name[i] == '.')
        {
            dot_count++;
            
            // max 2 dots
            if(dot_count > 2)
                return 0;
                
            // dot cannot be first or last
            if (i == 0 || name[i + 1] == '\0')
               return 0;

            // continues dot
            if( name[i - 1] == '.' || name[i + 1] == '.')
               return 0;

            //dot must between 2 letter   
            if(! (( name[i - 1] >= 'a' && name[i - 1] <= 'z') ||
                  ( name[i - 1] >= 'A' && name[i - 1] <= 'Z')))
                return 0;  

            if(! (( name[i + 1] >= 'a' && name[i + 1] <= 'z') ||
                  ( name[i + 1] >= 'A' && name[i + 1] <= 'Z')))
                return 0;      
            i++;       

        }
        
        else
          return 0; 

    }
    
    return 1;   
}
int validation_PhoneNo(AddressBook *addressBook, char *phone)
{
    int i = 0, j = 0;

    // Check each character to ensure it is a digit
    while( phone[i] )
    {
        if(phone[i] >= '0' && phone[i] <= '9')// Valid digit check
           i++;
        else
           return 0;            // Invalid character found
    }

    // Phone number must contain exactly 10 digits
    if(i != 10)
       return 0;

    // Check whether the phone number already exists
    for(j = 0; j < addressBook->contactCount; j++)
    {
        if(strcmp(phone, addressBook->contacts[j].phone)== 0)
        return -1;    // Duplicate phone number found
    }
       
      return 1;  // Valid and unique phone number
    
}
int validation_Email(AddressBook *addressBook, char *email)
{
    int i = 0,  at_count = 0, dot_after_at = 0;

    if (email[0] == '@' || email[0] == '.')   // Email should not start with '@' or '.'
       return 0;

    while( email[i] )
    {
        // Allow lowercase letters, digits, underscore and hyphen
        if( (email[i] >= 'a' && email[i] <= 'z') || 
            (email[i] >= '0' && email[i] <= '9') ||
            (email[i] == '_' || email[i] == '-') )
        {
            i++;
        }

        // Handle '@' character
        else if(email[i] == '@')
        {
            if(at_count == 1)    // More than one '@' not allowed
               return 0;
            if(i == 0 || email[i + 1] == '\0')   // '@' cannot be first or last
               return 0;
           
            at_count++;
            i++;

        }

        // Handle '.' character
        else if(email[i] == '.')
        {
            if(i == 0 || email[i + 1] == '\0' )   // '.' cannot be first or last
               return 0;
            if(email[i - 1] == '.' || email[i - 1] == '@' || email[i + 1] == '@')   // Invalid dot placement
               return 0;
            if(at_count  == 1)
               dot_after_at = 1;    // Dot must appear after '@'
            i++;
            

        }
        else 
           return 0;   // Invalid character found
         
    }
    

    // Must contain exactly one '@' and at least one dot after it
    if(at_count != 1 || dot_after_at == 0)
       return 0;

    // Email must end with ".com"   
    int len = strlen(email);
    if (len < 4 || strcmp(email + len - 4, ".com") != 0)
        return 0;   

    // Check for duplicate email in address book    
    for(int j = 0; j < addressBook->contactCount; j++)
    {
        if(strcmp(email, addressBook->contacts[j].email)== 0)
        return -1;    // Email already exists
    }  

    return 1;   // Valid and unique email 

}

void sort(AddressBook *addressBook, int sortCriteria, int order)
{
    Contact temp;  // temp is contact datatype 
    int i, j;
    
    // outer loop---> number of contact
    for(i = 0; i < addressBook->contactCount - 1; i++)
    {
        //inner loop---> comparing adjacent contacts
        for(j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            // to store 0 or 1 or -1
            int compare = 0; 

            switch(sortCriteria)
            {
                case 1:
                    compare = strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name);
                    break;

                case 2:
                    compare = strcasecmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone);
                    break; 
                    
                case 3:
                    compare = strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email);
                    break;
                default:
                    return;    

            }

            // Swap contacts based on ascending or descending order
            if((order == 1 && compare > 0) || 
               (order == 2 && compare < 0))
            {
                temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}


void printTableHeader()
{
    printf("+----+------------------------+--------------+----------------------------+\n");
    printf("| No | Name                   | Phone        | Email                      |\n");
    printf("+----+------------------------+--------------+----------------------------+\n");
}

         