#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG 1
//debug 1 when programmer need to check the file information

typedef struct{
    //creating user structure

    char userName[30];//User name must be unique
    char firstName[30];
    char lastName[30];
    char userPassword[30];//user password needed to log in

}UserType;

typedef struct{
    //creating book structure

    char title[30];//a book has a name which is called title
    char author[30];// a book is written by an author
    int progressPercentage;// this variable is to indicate the percentage of complete by user
    int rating;// a user will rate a book from 0 to 5
    char userName[30];// a book will have a userName so that we can indicate the user using a book

}BookType;

void showUserMenu(){
    //this menu will show for registration , log in or deleting user
    // This menu will appear at the start of the project

    printf("1.New user register \n");
    printf("2.User log in \n");
    printf("3.Delete user\n");
    printf("4. Exit\n");
}

void newUser(){

    UserType newUser;// this structure is used to create a new user
    UserType user;// this structure will read user from file

    FILE* fp;

    while(1){
        //here we are taking user name from the user and determining the size of user name

        fflush(stdin);//this is to clear the input buffer from new lines
        printf("User Name : ");
        gets(newUser.userName);

        if(strlen(newUser.userName)>4&&strlen(newUser.userName)<30){ //strlen to determine the size of userName

            break;
        }
        printf("Username size must be between 5 and 30 \n");
    }

    fp= fopen("userInfo.txt", "r");//opening user file in reading mode

    while(fread(&user, sizeof(UserType), 1, fp)){

        if(strcmp(user.userName,newUser.userName)==0){ //comparing strings of new user and existing user from file

            printf("User name not available. Please enter another user name \n");
            fclose(fp);
            return;// this return will return the user to user menu
        }
    }

    fclose(fp);

    fflush(stdin);
    printf("First Name : ");
    gets(newUser.firstName);

    fflush(stdin);
    printf("Last Name : ");
    gets(newUser.lastName);

    while(1){
        //taking password input and making sure that is has appropriate size

        fflush(stdin);
        printf("Password : ");
        gets(newUser.userPassword);

        if(strlen(newUser.userPassword)>3&&strlen(newUser.userPassword)<30){ //determining the size of password

            break;
        }
        printf("Password size must be between 4 and 30 \n");
    }

    fp= fopen("userInfo.txt", "a");//opening file in append mode

    if(fp==NULL){ //if there is no file

        printf("File could not be opened");
    }

    fwrite(&newUser, sizeof(UserType), 1, fp); //writing about new user in the file

    fclose(fp);
}

int countUsers(){
    // this function will count the number of users in the user file

    int count=0; //variable used to count users
    UserType user;//user structure

    FILE *fp;

    fp= fopen("userInfo.txt", "r");

    while(fread(&user, sizeof(UserType), 1, fp)){
        //here we are reading from the file one by one and counting the number of users

        count++;
    }

    fclose(fp);

    return count;//here we return the number of users

}

UserType userLogIn(){
    //this function tries to log in and returns the user

    char userName[30];//log in username
    char pass[30];//if the password is correct user will log in

    UserType user;// creating a structure

    fflush(stdin);
    printf("Enter user name : \n");
    gets(userName);// log in username

    printf("Enter password : \n");
    gets(pass);// log in user password

    FILE* fp;

    fp= fopen("userInfo.txt", "r");

    while(fread(&user, sizeof(UserType), 1, fp)){

        if(strcmp(user.userName,userName)==0&&strcmp(user.userPassword,pass)==0){ //comparing string for user and password from user input and file

            return user;
        }
    }

    strcpy(user.userName,"NULL");// here the user is null when log in is unsuccessful

    return user;// returning null user

}

void deleteUser(){
    //here we will delete a user

    int index= -1;//if index does not change it means the user is not found
    int i=0;
    int count= countUsers();//counting the number of users
    char userName[30];
    char userPass[30];

    UserType *users=(UserType*) malloc(count * sizeof(UserType));
    //creating an array of dynamic size for UserType users[count];

    fflush(stdin);
    printf("Enter user name to delete : ");
    gets(userName);

    fflush(stdin);
    printf("Enter user pass : ");
    gets(userPass);

    FILE* fp;
    fp= fopen("userInfo.txt", "r");

    while(fread(&users[i], sizeof(UserType), 1, fp)){

        if(strcmp(users[i].userName,userName)==0&&strcmp(users[i].userPassword,userPass)==0 ){
            //if we find the user to delete from the string compare then we will get the index of the user to delete

            index =i;
        }

        i++;
    }

    fclose(fp);

    if(index== -1){
        // if we do not get the user, the index will remain unchanged

        printf("The user was not found \n");
        return; //this will return the user to user menu
    }

    for(i=index;i<count-1;i++){
        //this loop is used to delete the user by bringing all the users at the right 1 place left

        users[i]= users[i+1]; //here we are taking the user to the rightmost array
    }

    fp= fopen("userInfo.txt", "w");

    printf("\nUser deleted \n");

    fwrite(users, sizeof(UserType), count-1, fp); //we are writing the file except the rightmost array . so the user will be deleted

    fclose(fp);
}

void showBookMenu(){
    //book menu after log in

    printf("1. Add a book\n");
    printf("2. Remove a book\n");
    printf("3. List of books\n");
    printf("4. Update a book\n");
    printf("5. Log Out\n");
}

void addBook(UserType currentUser){
    //after logging in the current user can add books
    // currentUser variable has the information of the currently logged in user

    BookType book; //structure for book

    FILE* fp;

    fflush(stdin);
    printf("Book Title : ");
    gets(book.title);

    fflush(stdin);
    printf("Author Name : ");
    gets(book.author);


    while(1){
        //here we are tracking the progress of the book by the user

        printf("Enter book progress : ");
        scanf("%d", &book.progressPercentage);//user will input the percentage he completed

        if(book.progressPercentage>=0&&book.progressPercentage<=100){ //percentage can not be less than 0 or greater than 100

            break;// if percentage is between 0 and 100 we will get the right percentage
        }
        printf("Book progress must be between 0 and 100 \n");
    }

    while(1){
        // rating by the user

        printf("Enter book rating : ");
        scanf("%d", &book.rating);

        if(book.rating>=0&&book.rating<=5){ //here we are rating between 0 to 5

            break; //if rating is between 0 to 5 the loop will end
        }
        printf("Book rating must be between 0 and 5 \n"); //this message will show user the error he did
    }

    strcpy(book.userName, currentUser.userName); //we are copying current user from the user string and current user name will go to book user name


    fp= fopen("bookInfo.txt", "a");

    if(fp==NULL){

        printf("File could not be opened");
    }

    fwrite(&book, sizeof(BookType), 1, fp);

    fclose(fp);

}

int countBooks(){
    //counting the number of books here from the book file

    int count=0;//count will start from 0
    BookType book;// structure for book

    FILE *fp;

    fp= fopen("bookInfo.txt", "r");//opening the file in reading mode

    while(fread(&book, sizeof(BookType), 1, fp)){
        //counting books from file 1 by 1

        count++;
    }

    fclose(fp);

    return count;// returning number of books

}

void deleteBook(UserType currentUser){


    int index= -1;
    int i=0;
    int count= countBooks();
    char title[30];

    BookType *books=(BookType*) malloc(count * sizeof(BookType));
    //creating an array of dynamic size for BookType books[count];

    fflush(stdin);
    printf("Enter book title to delete : ");
    gets(title);// book title to delete for current user

    FILE* fp;
    fp= fopen("bookInfo.txt", "r");// opening file in reading mode

    while(fread(&books[i], sizeof(BookType), 1, fp)){
        //finding the location of book to delete

        if(strcmp(books[i].title,title)==0 && strcmp(books[i].userName,currentUser.userName)==0){
            //comparing the title provided by the user to delete and the title from file
            // also comparing the user name from file and current user name

            index =i;// the index of the book to delete
        }
        i++;
    }

    fclose(fp);

    if(index== -1){

        printf("\nThe book was not found \n");
        return; // returning to book menu
    }

    for(i=index;i<count-1;i++){

        books[i]= books[i+1];//the index of the book to delete will go to the rightmost index
    }

    fp= fopen("bookInfo.txt", "w");//opening file in writing mode

    printf("Book deleted \n");

    fwrite(books, sizeof(BookType), count-1, fp);//writing except the rightmost index in the file
    fclose(fp);
}

void printBooks(UserType currentUser){
    //printing the books from current user

    int count;
    int i=0;
    int readBooks=0;
    int readingBooks=0;
    int wishList=0;

    count= countBooks();//counting the number of books of current user

    BookType* books=(BookType*) malloc(count * sizeof(BookType));
    //creating an array of dynamic size for BookType books[count]

    FILE* fp;

    fp= fopen("bookInfo.txt", "r");
    fread(books, sizeof(BookType), count, fp);// reading all the books from file

    for(i=0;i<count;i++){

        if(books[i].progressPercentage==100){
            //if he completes reading the book readBooks variable increases

            readBooks++;
        }
        else if(books[i].progressPercentage<100&& books[i].progressPercentage>0){
            //if he is reading the book readingBooks variable increases

            readingBooks++;
        }
        else{
            //if he wants to read a book wishList increases

            wishList++;
        }
    }

    if(readBooks==0){
        //if he has read no book

        printf("\nNo read book\n");
    }
    else{

        printf("\nRead books are :\n");//list of the books read by current user
        for(i=0;i<count;i++){
            // we are checking for all the books

            if(books[i].progressPercentage==100&&strcmp(currentUser.userName,books[i].userName)==0){
                //if the percentage of book is 100 and current userName matches with book userName

                printf("%s by %s, %d%%, %d stars\n",books[i].title,books[i].author,books[i].progressPercentage,books[i].rating);
            }
        }
    }

    if(readingBooks==0){
        //if user is not reading any book

        printf("\nNo reading book\n");
    }
    else{

        printf("\nReading books are :\n");//list of the books reading by current user

        for(i=0;i<count;i++){
            // we are checking for all the books

            if(books[i].progressPercentage<100&&books[i].progressPercentage>0&&strcmp(currentUser.userName,books[i].userName)==0){
                //If the percentage of book is less than 100 and greater than 0 the user is reading the book
                // we are also comparing current user name and the user name from book array

                printf("%s by %s, %d%%, %d stars\n",books[i].title,books[i].author,books[i].progressPercentage,books[i].rating);
            }
        }
    }

    if(wishList==0){
        //if user has no book in his wish list

        printf("\nNo book in wish list \n");
    }
    else{

        printf("\nWish list books are :\n");////list of books user want to read in future

        for(i=0;i<count;i++){
            // we are checking for all the books

            if(books[i].progressPercentage==0&&strcmp(currentUser.userName,books[i].userName)==0){
                //If user wants to start reading a book in future then the progress will be 0%
                // we are also comparing current user name and the user name from book array

                printf("%s by %s, %d%%, %d stars\n",books[i].title,books[i].author,books[i].progressPercentage,books[i].rating);
            }
        }
        printf("\n"); // new line so that the program looks better
    }

    fclose(fp);
}

void updateBook(UserType currentUser){
    //here we are updating book progression of current user

    int index= -1;//Index to track the book to update. It will not update if the book title is wrong
    int i=0;
    int count= countBooks();// counting the number of total books
    char title[30];
    int newProgress;//new progression from the user to update

    BookType *books=(BookType*) malloc(count * sizeof(BookType));
    //creating an array of dynamic size for BookType books[count];

    fflush(stdin);
    printf("Enter book title to update : ");
    gets(title);//user input for the book he wants to update

    FILE* fp;
    fp= fopen("bookInfo.txt", "r");

    while(fread(&books[i], sizeof(BookType), 1, fp)){
        //here we are comparing the title and userName for book array and current user 1 by 1

        if(strcmp(books[i].title,title)==0 && strcmp(books[i].userName,currentUser.userName)==0){

            index =i;//tracking the index to update
        }
        i++;
    }

    fclose(fp);

    if(index== -1){

        printf("\nThe book was not found \n");
        return;// it will return the user to book menu
    }

    else{

        while(1){

            printf("Enter updated progress of the book : ");
            scanf("%d", &books[index].progressPercentage);

            if(books[index].progressPercentage>=0&&books[index].progressPercentage<=100){
                //if the progress is between 0 and 100 we can get the progress percentage

                break;
            }
            printf("Book progress must be between 0 and 100 \n");// the user can know his wrong input reading this message
        }
    }

    fp= fopen("bookInfo.txt", "w");//opening file in writing mode

    printf("\nBook updated \n");

    fwrite(books, sizeof(BookType), count, fp);// writing the updated version

    fclose(fp);
}

void mainMenu(UserType currentUser){
    //this is the book menu for current user

    UserType user;//structure for user
    BookType books;// structure for books

    int userChoice;//userChoice for switch case

    while(1){

        showBookMenu(); // showing the book menu
        printf("User choice : ");
        scanf("%d", &userChoice);//user will choose what to do

        switch(userChoice){

            case 1:

                addBook(currentUser);//adding books for currentUser

                break;

            case 2:

                deleteBook(currentUser);// deleting a book for currentUser

                break;

            case 3:

                printBooks(currentUser); // printing all the books of currentUser

                break;

            case 4:

                updateBook(currentUser); // updating a book of currentUser

                break;

            case 5:

                return ;//returning to user menu after logging out
                break;

            default:

                printf("Please enter a valid option \n");//if user inputs an non valid option in the book menu

        }
        printf("Enter any button to continue...\n");
        getch(); //character input
        system("cls"); //console clean
    }
}

int main(){

    int userMenuChoice;//user input for user menu
    int count; //variable for counting
    int i;// variable to use loops
    int userInput;//variable to get user input
    int result;// variable to get a result
    UserType users;// structure for users
    UserType user;// structure for user

    FILE* fp;
    fp = fopen("userInfo.txt", "r");

    if(fp==NULL){
        fp = fopen("userInfo.txt", "w");
    }
    fclose(fp);

    fp = fopen("bookInfo.txt", "r");

    if(fp==NULL){
        fp = fopen("bookInfo.txt", "w");
    }
    fclose(fp);
    // Create the database files of they don't exist already

    while(1){

        showUserMenu();// showing the user menu
        printf("User choice : ");
        scanf("%d", &userMenuChoice);

        switch(userMenuChoice){

            case 1:

                newUser();// creating a new user using this function

                break;

            case 2 :

                user=userLogIn();

                if(strcmp(user.userName,"NULL") !=0){
                    //when user log in fails a null user is returned
                    //when logged in successful we are sending to main menu with logged in user information

                    mainMenu(user);
                }
                else{
                    printf("Log in failed, please try again\n");// for null user
                }

                break;

            case 3 :

                deleteUser();// deleting a user

                break;

            case 4 :

                return 0;// exit

                break;

            case 5 :

                if(DEBUG){
                    //for the programmer to understand whats happening

                    count= countUsers();

                    UserType* users=(UserType*) malloc(count * sizeof(UserType));
                    FILE* fp;

                    fp= fopen("userInfo.txt", "r");
                    fread(users, sizeof(UserType), count, fp);

                    for(i=0;i<count;i++){

                        printf("User name : ");
                        puts(users[i].userName);
                        printf("First name : ");
                        puts(users[i].firstName);
                        printf("Last name : ");
                        puts(users[i].lastName);
                        printf("User pass : ");
                        puts(users[i].userPassword);

                    }
                fclose(fp);
                }
                break;

            default:
                // if user enters a non valid option

                printf("Please enter a valid option \n");
        }

        printf("Enter any button to continue...\n");
        getch(); //character input
        system("cls"); //console clean
    }
    return 0;
}
