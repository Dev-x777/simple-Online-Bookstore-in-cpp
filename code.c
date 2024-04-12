
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for a book
typedef struct Book {
    char title[100];
    char author[100];
    int year;
    float price;
    struct Book* left;
    struct Book* right;
} Book;

// Function to create a new book node
Book* createBookNode(char title[], char author[], int year, float price) {
    Book* newBook = (Book*)malloc(sizeof(Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->year = year;
    newBook->price = price;
    newBook->left = NULL;
    newBook->right = NULL;
    return newBook;
}

// Function to insert a book into the BST
Book* insertBook(Book* root, char title[], char author[], int year, float price) {
    if (root == NULL) {
        return createBookNode(title, author, year, price);
    }
    int cmp = strcmp(title, root->title);
    if (cmp < 0) {
        root->left = insertBook(root->left, title, author, year, price);
    } else if (cmp > 0) {
        root->right = insertBook(root->right, title, author, year, price);
    } else {
        printf("\nError: Book with title '%s' already exists!\n", title);
    }
    return root;
}

// Function to search for a book by title
Book* searchBook(Book* root, char title[]) {
    if (root == NULL || strcmp(root->title, title) == 0) {
        return root;
    }
    if (strcmp(title, root->title) < 0) {
        return searchBook(root->left, title);
    }
    return searchBook(root->right, title);
}

// Function to delete a book from the BST
Book* deleteBook(Book* root, char title[]) {
    if (root == NULL) {
        return root;
    }
    int cmp = strcmp(title, root->title);
    if (cmp < 0) {
        root->left = deleteBook(root->left, title);
    } else if (cmp > 0) {
        root->right = deleteBook(root->right, title);
    } else {
        if (root->left == NULL) {
            Book* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Book* temp = root->left;
            free(root);
            return temp;
        }
        Book* temp = root->right;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        strcpy(root->title, temp->title);
        strcpy(root->author, temp->author);
        root->year = temp->year;
        root->price = temp->price;
        root->right = deleteBook(root->right, temp->title);
    }
    return root;
}

// Function to print all books in the BST (inorder traversal)
void printBooks(Book* root) {
    if (root != NULL) {
        printBooks(root->left);
        printf("\nTitle: %s\n", root->title);
        printf("Author: %s\n", root->author);
        printf("Year: %d\n", root->year);
        printf("Price: $%.2f\n", root->price);
        printf("------------------------------------\n");
        printBooks(root->right);
    }
}

int main() {
    Book* root = NULL;
    char title[100];
    char author[100];
    int year;
    float price;
    char choice;

    do {
        printf("\nWelcome to the Online Bookstore\n");
        printf("====================================\n");
        printf("Menu:\n");
        printf("1. Insert a book                   |\n");
        printf("2. Search for a book               |\n");
        printf("3. Delete a book                   |\n");
        printf("4. Print all books                 |\n");
        printf("5. Exit                            |\n");
        printf("====================================\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                printf("\nEnter title of the book: ");
                scanf(" %[^\n]", title);
                printf("Enter author of the book: ");
                scanf(" %[^\n]", author);
                printf("Enter publication year of the book: ");
                scanf("%d", &year);
                printf("Enter price of the book: ");
                scanf("%f", &price);
                root = insertBook(root, title, author, year, price);
                printf("\nBook inserted successfully!\n");
                break;
            case '2':
                printf("\nEnter title of the book to search: ");
                scanf(" %[^\n]", title);
                Book* searchedBook = searchBook(root, title);
                if (searchedBook != NULL) {
                    printf("\nBook Found:\n");
                    printf("Title: %s\n", searchedBook->title);
                    printf("Author: %s\n", searchedBook->author);
                    printf("Year: %d\n", searchedBook->year);
                    printf("Price: $%.2f\n", searchedBook->price);
                } else {
                    printf("\nBook not found!\n");
                }
                break;
            case '3':
                printf("\nEnter title of the book to delete: ");
                scanf(" %[^\n]", title);
                root = deleteBook(root, title);
                printf("\nBook deleted successfully!\n");
                break;
            case '4':
                printf("\nAll Books:\n");
                if (root == NULL) {
                    printf("No books found!\n");
                } else {
                    printBooks(root);
                }
                break;
            case '5':
                printf("\nExiting...\n");
                break;
            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    } while (choice != '5');
    // Made by DEV

    return 0;
}
