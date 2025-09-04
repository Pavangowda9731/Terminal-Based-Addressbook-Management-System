#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include<unistd.h>
 


void listContacts(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
          printf("\033[1;31m");
        printf("No contacts to display.\n\n");
          printf("\033[0m");
        return;
    }
   
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if (strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }

    printf("\033[1;36m");
    printf("\n╔══════╦════════════════════╦════════════════╦════════════════════════════════════════╗\n");

     
    printf("║ %-4s ║ %-18s ║ %-14s ║ %-38s ║\n", "No.", "Name", "Phone", "Email");
      

  
    printf("╠══════╬════════════════════╬════════════════╬════════════════════════════════════════╣\n");
    printf("\033[0m");

    
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("\033[1;30m");
        printf("║ %-4d ║ %-18s ║ %-14s ║ %-38s ║\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
               printf("\033[0m");

    }

   printf("\033[1;30m");
    printf("╚══════╩════════════════════╩════════════════╩════════════════════════════════════════╝\n\n");
    printf("\033[0m");


   
}
    


void initialize(AddressBook *addressBook)
 {
 


    FILE* fptr = fopen("contacts.txt", "r");  
    if (fptr == NULL)
    {
          printf("\033[1;31m");
        printf("Unable to open file\n");
          printf("\033[0m");
        return;
    }

    char name[50], phone[20], email[50] ;
    addressBook->contactCount = 0;

  

   
    while (fscanf(fptr, "%[^,],%[^,],%[^\n]\n", name, phone, email) == 3)
    {
       
        int i = addressBook->contactCount;
        strcpy(addressBook->contacts[i].name, name);
        strcpy(addressBook->contacts[i].phone, phone);
        strcpy(addressBook->contacts[i].email, email);
      

        addressBook->contactCount++;
    }

    fclose(fptr);  // Step 5: close file

    // printf("Contacts loaded successfully. Total: %d\n", addressBook->contactCount);
}

 
  


void save(AddressBook *addressBook) 
{
   
    

 FILE* fptr = fopen("contacts.txt", "w"); 
    if (fptr == NULL)
    {
          printf("\033[1;31m");
        printf("Unable to open file\n");
          printf("\033[0m");
        return;
    }

    int count = addressBook->contactCount;

    for (int i = 0; i < count; i++) 
    {
       
        fprintf(fptr, "%s", addressBook->contacts[i].name);
        fputc(',', fptr);

        
        fprintf(fptr, "%s", addressBook->contacts[i].phone);
        fputc(',', fptr);

        
        fprintf(fptr, "%s", addressBook->contacts[i].email);
        fputc('\n', fptr);

    }

    fclose(fptr); 
     char buffer[25];
            for (int i = 0; i <= 100; i++)
            {
                 printf("\033[1;37m");    
                printf("[ Saving the Contact........ %3d%%]\r", i);
                 printf("\033[0m");    
                fflush(stdout);
                usleep(100000);
            }
    printf("\033[1;32m");
    printf("Contacts saved successfully.\n");
    printf("\033[0m");
}


void createContact(AddressBook *addressBook)
{
    
    if (addressBook->contactCount >= MAX_CONTACTS) 
    {
        printf("\033[1;31m");
        printf("Address book is full. Cannot add more contacts.\n");
        printf("\033[0m");
        return;
    }

	char temp[100];
    Contact *newContact = &addressBook->contacts[addressBook->contactCount];//is just a shortcut pointer to the next available contact slot in the array, so you can fill it easily

    //For user entering a name 
    while(1)
    {
        printf("Enter the Name :");
        scanf(" %[^\n]", temp);
       

        if(is_valid_name(temp))
        {
            strcpy(newContact->name,temp);
            break;
        }
        else
        {
            printf("\033[1;31m");
            printf("Invalid Name! Only characters are allowed\n");
              printf("\033[0m");
           
        }

    }
    
    //For user entering a phone number 
    while(1)
    {
        printf("Enter a Mobile number : ");
        scanf(" %s", temp);
        getchar();

        if (!is_valid_phone(temp))
        {
            printf("\033[1;31m");
            printf("Invalid Phone number! Only digits allowed and must be 10 digits.\n");
              printf("\033[0m");
            continue;
        }

        if(isPhoneDuplicate(addressBook, temp))
        {
             printf("\033[1;31m");
            printf("This number is already stored. Please enter a different phone number.\n");
            printf("\033[0m");
            continue;
        }

        strcpy(newContact->phone, temp);
        break;

        
    }

    while(1)
    {
        printf("Enter a Email-ID : ");
        scanf(" %s", temp);

        if(is_valid_email(temp))
        {
            strcpy(newContact->email,temp);
            break;
        }
        else
        {
            printf("\033[1;31m");
           printf("Invalid E-Mail!\n");
            printf("\033[0m");
        }

    }
           char buffer[25];
            for (int i = 0; i <= 100; i++)
            {
                 printf("\033[1;37m");    
                printf("[Creating your Contact....... %3d%%]\r", i);
                 printf("\033[0m");    
                fflush(stdout);
                usleep(100000);
            }
     addressBook->contactCount++;
     printf("\033[1;32m");
    printf("\n Contact created successfully!!\n");
     printf("\033[0m");
	
    

    
}

void searchContact(AddressBook *addressBook) 
{
    

    int choice;
    char search[50];
    char again;
    

    while(1)
    {

        printf("\nSearch Menu\n");
        printf("1.NAME\n");
        printf("2.PHONE NUMBER\n");
        printf("3.EMAIL\n");
        printf("4.EXIT FROM SEARCH MENU\n");
        printf("Enter your choice : ");
        scanf("%d",&choice);

        int found = 0;

        switch(choice)
        {
           
            case 1:
                printf("Enter name to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_name(search)) 
                {
                      printf("\033[1;31m");
                    printf("Invalid name format.\n");
                      printf("\033[0m");
                    break;
                }
                 printf("\033[1;35m");
                printf("\n----> Search Results <----\n");
                 printf("\033[0m");
                
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strncasecmp(addressBook->contacts[i].name,search, strlen(search)) == 0) //comparision 
                    {
                        printf("Name   : %s\n", addressBook->contacts[i].name);
                        printf("Phone  : %s\n", addressBook->contacts[i].phone);
                        printf("Email  : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("\033[1;31m");
                    printf("No contact found with the name '%s'.\n", search);
                    printf("\033[0m");
                }
                break;

            case 2:
                printf("Enter Phone Number to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_phone(search)) 
                {
                      printf("\033[1;31m");
                    printf("Invalid Phone Number  format.\n");
                      printf("\033[0m");
                    break;
                }
                 printf("\033[1;35m");
                printf("\n----> Search Results <----\n");
                 printf("\033[0m");
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].phone, search) == 0)
                    {
                        printf("Name   : %s\n", addressBook->contacts[i].name);
                        printf("Phone  : %s\n", addressBook->contacts[i].phone);
                        printf("Email  : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                    printf("\033[1;31m");
                    printf("No contact found with the Phone Number '%s'.\n", search);
                    printf("\033[0m");
                }
                break;

            case 3:
            
                printf("Enter EMAIL - ID to search: ");
                scanf(" %[^\n]",search);
                if (!is_valid_email(search)) 
                {
                      printf("\033[1;31m");
                    printf("Invalid Email  format.\n");
                      printf("\033[0m");
                    break;
                }
                 printf("\033[1;35m");
                printf("\n----> Search Results <----\n");
                 printf("\033[0m");
                for (int i = 0; i < addressBook->contactCount; i++)
                {
                    if (strcmp(addressBook->contacts[i].email, search) == 0)
                    {
                        printf("Name   : %s\n", addressBook->contacts[i].name);
                        printf("Phone  : %s\n", addressBook->contacts[i].phone);
                        printf("Email  : %s\n", addressBook->contacts[i].email);
                        printf("\n");
                        found = 1;
                    }
                }
                if (found == 0)
                {
                      printf("\033[1;31m");
                    printf("No contact found with the EMAIL-ID '%s'.\n", search);
                      printf("\033[0m");
                }
                break;
            
            case 4:
               printf("\033[1;31m");
               printf("Exiting search menu...\n");
              printf("\033[0m");
                return;
            
            default:
              printf("\033[1;31m");
                printf("Please enter a valid choice (1-4).\n");
                  printf("\033[0m");
                break;


        }
        printf("\n");
          printf("\033[1;32m");
        printf("Do you want to search again? (y/n): ");
          printf("\033[0m");
        scanf(" %c", &again);
        getchar(); 

        if (again != 'y' && again != 'Y') 
        {
            break; 
        }
    }


}

void editContact(AddressBook *addressBook)
{
	

    int index, choice;
    char again = 'y';
    char phone[15];
    char email[50];
    char name[20];

    while (again == 'y' || again == 'Y')
    {
        printf("\nEdit Menu:\n");
        printf("1. Edit Name\n");
        printf("2. Edit Phone Number\n");
        printf("3. Edit Email-ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
 

        index = searchData( addressBook,choice);

        if (index >= 0 && index < addressBook->contactCount)
        {
            switch (choice)
            {
                case 1:
                    while (1)
                    {
                        printf("Enter new name:");
                        scanf(" %[^\n]", name);
                        getchar();

                        if (is_valid_name(name))
                            {
                                strcpy(addressBook->contacts[index].name, name);
                                break;
                            }
                            else
                            {
                                  printf("\033[1;31m");
                                printf("Enter valid name.\n");
                                  printf("\033[0m");
                            }
                    }
                        break;

                case 2:
                    while (1)
                    {
                        printf("Enter new phone number: ");
                        scanf(" %14[^\n]", phone);
                        getchar();

                        if (is_valid_phone(phone))
                        {
                            strcpy(addressBook->contacts[index].phone, phone);
                            break;
                        }
                        else
                        {
                              printf("\033[1;31m");
                            printf("Invalid phone number! Enter a 10-digit numeric phone number.\n");
                              printf("\033[0m");
                        }
                    }
                    break;

                case 3:
                    while (1)
                    {
                        printf("Enter new Email-ID: ");
                        scanf(" %49[^\n]", email);  
                        getchar();

                        if (is_valid_email(email))
                        {
                            strcpy(addressBook->contacts[index].email, email);
                            break;
                        }
                        else
                        {
                              printf("\033[1;31m");
                            printf("Invalid Email-ID format! Please try again.\n");
                              printf("\033[0m");
                        }
                    }
                    break;

                default:
                  printf("\033[1;31m");
                    printf("Invalid choice! Please enter 1-4.\n");
                      printf("\033[0m");
                    continue;
            }
             char buffer[25];
            for (int i = 0; i <= 100; i++)
            {
                 printf("\033[1;37m");    
                printf("[Editing your Contact ....... %3d%%]\r", i);
                 printf("\033[0m");    
                fflush(stdout);
                usleep(100000);
            }
            addressBook->contactCount++;
            printf("\033[1;32m");
            printf("\n Contact created successfully!!\n");
            printf("\033[0m");
            printf("\033[1;92m");
            printf("Edit Successful.\n");
             printf("\033[0m");
        }
        else
        {
              printf("\033[1;31m");
            printf("Contact not found.\n");
              printf("\033[0m");
        }

        printf("Do you want to edit another contact? (y/n): ");
        scanf(" %c", &again);
    
    }

    printf("Exiting edit menu.\n");


    
}

void deleteContact(AddressBook *addressBook)
{
    int index, i, choice;
    char again = 'y';

    do
    {
        printf("\nDelete Menu:\n");
        printf("1. Delete by name\n");
        printf("2. Delete by phone number\n");
        printf("3. Delete by Email-ID\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  

        index = searchData( addressBook,choice);

        if (index >= 0 && index < addressBook->contactCount)//checking whether the index returned by your search function is valid. 
        {
            char confirm;//store whether the user wants to proceed with deletion 
              printf("\033[1;31m");
            printf("Are you sure you want to delete '%s'? [Y/N]: ", addressBook->contacts[index].name);
              printf("\033[0m");
            scanf(" %c", &confirm);
            getchar();

            if (confirm != 'y' && confirm != 'Y')
            {
                  printf("\033[1;33m");
                printf("Deletion cancelled.\n");//skip deletion
                  printf("\033[0m");
                printf("Do you want to delete another contact? (y/n): ");
                scanf(" %c", &again);
                getchar();
                continue;//skip rest of iteration and show the delete menu again 
            }

           
            Contact deletedContact = addressBook->contacts[index];//Copies the contact to be deleted into a local variable deletedContact

            for (i = index; i < addressBook->contactCount - 1; i++)//shifts all contacts after the deleted one to the left by one position.
            {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }

            addressBook->contactCount--;  
             char buffer[25];
            for (int i = 0; i <= 100; i++)
            {
                 printf("\033[1;37m");    
                printf("[Deleting  your Contact....... %3d%%]\r", i);
                 printf("\033[0m");    
                fflush(stdout);
                usleep(100000);
            }
                addressBook->contactCount++;
                printf("\033[1;32m");
                printf("\n Contact created successfully!!\n");
                printf("\033[0m");

            printf("\033[1;92m");
            printf("Contact deleted successfully! (Press 'U' to undo)\n");
            printf("\033[0m");
          
            
            char undo;
            scanf(" %c", &undo);
            getchar(); 

            if (undo == 'u' || undo == 'U')
            {
                
                for (i = addressBook->contactCount; i > index; i--)//loop runs starting from the last contact currently in the address book 
                {
                    addressBook->contacts[i] = addressBook->contacts[i - 1];//means the contact at position i-1 moves to position i
                }
                addressBook->contacts[index] = deletedContact;// inserting the previously deleted contact back into the array at its original position index.
                addressBook->contactCount++;
                 char buffer[25];
            for (int i = 0; i <= 100; i++)
            {
                 printf("\033[1;37m");    
                printf("[ Contact restoring........ %3d%%]\r", i);
                 printf("\033[0m");    
                fflush(stdout);
                usleep(100000);
            }
                addressBook->contactCount++;
                printf("\033[1;32m");
                printf("\n Contact created successfully!!\n");
                printf("\033[0m");
                  printf("\033[1;33m");
                printf("Contact restored Sucessfully!\n");
                  printf("\033[0m");
            }
        }
        else
        {
              printf("\033[1;31m");
            printf("Contact not found.\n");
              printf("\033[0m");
        }

        
        printf("Do you want to delete another contact? (y/n): ");
        scanf(" %c", &again);
        getchar();  

    } while (again == 'y' || again == 'Y');

    printf("Exiting delete menu.\n");
}

int is_valid_name(char *name)
{
    for (int i = 0; name[i] != '\0'; i++) 
    {
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ')) 
        {
            return 0;
        }
    }
    return 1;
}

int is_valid_phone(char *phone) 
{
    int len = 0;

    for (int i = 0; phone[i] != '\0'; i++) 
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            return 0; 
        }
        len++;
    }

    if (len != 10) 
    {
        return 0; 
    }

    return 1;
}

int is_valid_email(char *email)
{
    int len = strlen(email);

    if (len < 6) // Minimum length for a@b.com
        return 0;

    int at_count = 0;
    int at_pos = -1;//@ character has not been found yet in the email string
    for (int i = 0; i < len; i++) {
        if (email[i] == '@')
        {
            at_count++;
            at_pos = i;
        }
    }

    
    if (at_count != 1)
        return 0;


    if (at_pos == 0 || at_pos == len - 1) //cannot be 1st or last charater
        return 0;

    
    char *dot = strchr(email + at_pos + 1, '.');//return ADDRESS
    if (!dot)
        return 0;

    
    if (dot == email + len - 1)// dot cannot be the very last character in the email.
        return 0;


    if (strcmp(email + len - 4, ".com") != 0)//comparision for last 4 character
        return 0;

    
    if (dot - (email + at_pos) < 2)
        return 0;

    
    if (at_pos < 1)
        return 0;

    if (len > 8)
     { 
        if (strcmp(email + len - 8, ".com.com") == 0)
            return 0;
    }


    return 1;

}

int searchData(AddressBook *addressBook, int choice)
{
    char search[100];
    int flag = 0;

    switch(choice)
    {
        case 1:  
            printf("Enter name to search: ");
            scanf("%[^\n]", search);

            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strncasecmp(addressBook->contacts[i].name, search,strlen(search)) == 0) //when both same return 0
                                                                                           //strlen(search) to search upto user type
                {
                     printf("\033[1;32m");
                    printf("------------------------------------------------------\n");
                     printf("\033[0m");
                    printf("%s\n",addressBook->contacts[i].name);
                    printf("%s\n",addressBook->contacts[i].phone);
                    printf("%s\n",addressBook->contacts[i].email);
                    printf("\033[1;32m");
                    printf("------------------------------------------------------\n");
                     printf("\033[0m");
                    return i; 
                }
            }
              printf("\033[1;31m");
            printf("Name not found!\n");
              printf("\033[0m");
            return -1;

        case 2:  
            while(1)
            {
                printf("Enter phone number to search: ");
                scanf("%s", search);

                
                if (!is_valid_phone(search)) 
                {
                      printf("\033[1;31m");
                    printf("Invalid phone number format. Try again.\n");
                      printf("\033[0m");
                    continue;  
                }

                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].phone, search) == 0)
                    {
                       printf("\033[1;32m");
                       printf("------------------------------------------------------\n");
                       printf("\033[0m");

                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);

                        printf("\033[1;32m");
                        printf("------------------------------------------------------\n");
                        printf("\033[0m");
                        return i;
                    }
                }
                  printf("\033[1;31m");
                printf("Phone number not found!\n");
                  printf("\033[0m");
                return -1;
            }

        case 3:  
            while(1)
            {
                printf("Enter email to search: ");
                scanf("%s", search);

              
                if (!is_valid_email(search))
                {
                      printf("\033[1;31m");
                    printf("Invalid email format. Try again.\n");
                      printf("\033[0m");
                    continue; 
                }

                for(int i = 0; i < addressBook->contactCount; i++)
                {
                    if(strcmp(addressBook->contacts[i].email, search) == 0)
                    {
                        printf("\033[1;32m");
                        printf("------------------------------------------------------\n");
                        printf("\033[0m");
                        printf("%s\n",addressBook->contacts[i].name);
                        printf("%s\n",addressBook->contacts[i].phone);
                        printf("%s\n",addressBook->contacts[i].email);
                        printf("\033[1;32m");
                        printf("------------------------------------------------------\n");
                        printf("\033[0m");
                        return i;
                    }
                }
                  printf("\033[1;31m");
                printf("Email not found!\n");
                  printf("\033[0m");
                return -1;
            }

        

        default:
          printf("\033[1;31m");
            printf("Invalid choice for search!\n");
              printf("\033[0m");
            return -1;
    }
}
int isPhoneDuplicate(AddressBook *addressBook, const char *phone)
{
    for (int i = 0; i < addressBook->contactCount; i++) 
    {
        if (strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 1;  // Duplicate found
        }
    }
    return 0;  // No duplicate
}
