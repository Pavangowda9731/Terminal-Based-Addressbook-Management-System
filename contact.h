#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[MAX_CONTACTS];
    int contactCount;
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void save(AddressBook *AddressBook);
int is_valid_name(char*);
int is_valid_phone(char*);
int is_valid_email(char*);
int searchData(AddressBook *addressBook, int );
int isPhoneDuplicate(AddressBook *addressBook, const char *);


#endif


    
