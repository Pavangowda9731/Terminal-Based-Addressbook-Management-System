#include <stdio.h>
#include "contact.h"

/*
 * Program: Terminal Based  Address Book Management System
 * Author: Pavan Kumar AS
 * Date: July 2025
 * Description:
 *   This program provides a console-based address book management system
 *   that allows users to create, search, edit, delete, list, and save contacts.
 *   It features input validation for names, phone numbers, and email addresses,
 *   and stores contacts persistently in a file named "contacts.txt".
 *
 * Usage:
 *   Compile the program using a C compiler and run the executable.
 *   Follow the interactive menu-driven interface to manage contacts.
 *
 * This project is intended for learning C programming and file operations.
 */


int main() {
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    do {
        printf("\033[1;36m");
      printf("\n╔════════════════════════════════╗\n");
        printf("║        Address Book Menu       ║\n");
        printf("╠════════════════════════════════╣\n");
        printf("\033[0m");
        printf("\033[1;30m");
        printf("║ 1. CREATE CONTACT              ║\n");
        printf("║ 2. SEARCH CONTACT              ║\n");
        printf("║ 3. EDIT CONTACT                ║\n");
        printf("║ 4. DELETE CONTACT              ║\n");
        printf("║ 5. LIST ALL CONTACTS           ║\n");
        printf("║ 6. SAVE CONTACT                ║\n");
        printf("║ 7. EXIT                        ║\n");
        printf("╚════════════════════════════════╝\n");
         printf("\033[0m");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                createContact(&addressBook);
                break;
            case 2:
                searchContact(&addressBook);
                break;
            case 3:
                editContact(&addressBook);
                break;
            case 4:
                deleteContact(&addressBook);
                break;
            case 5:
                listContacts(&addressBook);
                break;
            case 6:
                
                save(&addressBook);
                break;
           
        }
    } while (choice != 7);
    
       return 0;
}
