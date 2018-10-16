/*LIBRARY MANAGEMENT SYSTEM OF DELHI PUBLIC LIBRARY*/
/*Made by TRIPTI SHUKLA  (Batch: F8   Enrollment:9917103253)*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>  //USED FOR RECORDING THE TIME OF BORROWING THE BOOKS

/*DEFINED FOR VARIOUS KEYWORDS USED IN THE CODE*/
#define ADMIN 1
#define NORMAL_USER 0
#define FORBIDDEN -1
#define MAXUSERNAME 100
#define MAXPASSWD 100
#define MAXPHONENUM 20
#define MAXBOOKNAME 100
#define MAXNAME 100
#define MAXDATELEN 100

/*DETAILS MAINTAINED FOR EVERY USER*/
typedef struct user
{
  char username[MAXUSERNAME];
  char phonenum[MAXPHONENUM];
  char sex[10];
  int id;
  int age;
  int usertype;

}User;

/*TO MAINTAIN A LIST OF ALL THE USERS WHETHER ADMIN OR NORMAL*/
typedef struct usernode
{
  User user;
  struct usernode *next;

}Usernode,*usrlink;

/*DETAILS MAINTAINED FOR EVERY BOOK*/
typedef struct book
{
  char name[MAXBOOKNAME];
  char author[MAXNAME];
  int totalcount;
  int borrowcount;
  int id;

}Book;

/*TO MAINTAIN A LIST OF BOOKS IN THE LIBRARY*/
typedef struct booknode
{
  Book book;
  struct booknode *next;

}Booknode,*bklink;

/*BORROWING DETAILS MAINTAINED FOR EACH BOOK*/
typedef struct borrow
{
  char borrowdate[MAXDATELEN];
  int borrow_id;
  char username[MAXUSERNAME];
  char bookname[MAXBOOKNAME];
  int borrow_counts;

}Borrow;

/*TO MAINTAIN THE LIST OF BORROWER DETAILS*/
typedef struct borrownode
{
  Borrow borrow;
  struct borrownode *next;

}Borrownode,*borrowlink;

/*DETAILS ENTERED WHEN LOGGING INTO THE SYSTEM*/
typedef struct loginnode
{
  int usertype;
  char username[MAXUSERNAME];

}Loginnode,*loginlink;

void Introduction(); /*TO MAKE USER AWARE OF LIBRARY OBJECTIVES*/
void INIT(void); /*TO INITIALIZE THE HEAD OF ALL THE LINKED LISTS*/
loginlink login_system(void); /*TO LOGIN INTO THE TERMINAL CONSOLE OF THE LIBRARY*/
int AuthorizeUser(char []); /*TO CHECK FOR THE LOGGING USER AUTHORIZATION*/
void Admin_UI(char []); /*TO LIST THE OPTIONS FOR AN ADMIN USER*/
void Normal_User_UI(char []); /*TO LIST THE OPTIONS FOR A NORMAL USER*/
usrlink Search_User_List(usrlink ,char []); /*TO SEARCH EITHER OF THE TWO USER LISTS*/
int Get_User_Name(char [],int); /*TO ENTER USER'S NAME AS A STRING*/
void Display_User(usrlink); /*TO DISPLAY THE DETAILS OF A USER*/
usrlink Search_User_by_Name(char []); /*O SEARCH FOR A USER IN THE LIBRARY'S LIST BY NAME*/
usrlink Search_User_by_ID(int); /*TO SEARCH FOR A USER IN THE LIBRARY'S RECORD LIST BY ID*/
int User_Deletion_by_Name(char []); /*TO DELETE THE RECORDS OF A USER BY NAME*/
int User_Deletion_by_ID(int); /*TO DELETE THE RECORDS OF A USER BY ID*/
void Manage_User_UI(char []); /*TO LIST THE VARIOUS AVAILABLE OPERATIONS FOR A USER*/
void Manage_Book_UI(char []); /*TO LIST THE VARIOUS AVAILABLE OPERATIONS FOR A BOOK*/
void Manage_Borrow_UI(char []); /*TO LIST THE VARIOUS AVAILABLE OPERATIONS FOR BOOK BORROWING FUNCTIONALITY*/
void Book_Addition(void); /*TO INSERT DETAILS OF BOOKS TO BE ADDED IN THE LIBRARY*/
void Book_Insertion(bklink *,bklink); /*TO INSERT THE ADDED BOOK INTO THE BOOK RECORD LIST*/
void Book_Deletion(void); /*TO DELETE A BOOK FROM THE BOOK RECORD LIST*/
int book_delete_by_name(char []);
int book_delete_by_id(int);
int Book_Search(void); /*TO SEARCH FOR A PARTICULAR BOOK*/
bklink Book_Search_by_name(char []);
bklink Book_Search_by_id(int);
void Display_Book(bklink); /*TO DISPLAY THE DETAILS OF A PARTICULAR BOOK*/
void User_Insertion(usrlink,int); /*TO INSERT A USER DETAILS IN THE LIBRARY RECORD LIST*/
void User_Deletion(void); /*TO DELETE A USER'S RECORD*/
void User_Addition(void); /*TO ADD THE DETAILS OF A USER IN THE USER RECORD LIST*/
void User_Modification(void); /*TO MODIFY THE DETAILS OF A USER*/
int search_user(void); /*TO SEARCH FOR A PARTICULAR USER*/
void modify_book(void); /*TO MODIFY THE DETAILS OF A PARTICULAR BOOK*/
int borrow_book(void); /*TO INPUT THE DETAILS OF A BOOK THAT IS BEING BORROWED*/
int return_book(void); /*TO RETURN A BORROWED BOOK*/
int search_borrow(void); /*TO SEARCH FOR A BOOK THAT HAS BEEN BORROWED*/
void borrow_insert(borrowlink *,borrowlink); /*TO INSERT THE DETAILS OF A BORROWED BOOK IN THE BORROW RECORD LIST*/
char *get_time(void); /*TO RECORD THE TIME OF BORROWING A BOOK*/
borrowlink search_borrow_by_username(char []); /*TO SEARCH FOR A BORROWED BOOK FROM THE RECORD*/
void borrow_display(borrowlink); /*TO DISPLAY THE DETAILS OF A BORROWED BOOK*/
int User_Modification_by_usrlink(usrlink); /*TO MODIFY THE DETAILS OF A USER*/


static usrlink adminlist;
static usrlink normallist;
static bklink booklist;
static borrowlink borrowlist;


int main()
{
  int c;

  loginlink llink=NULL;
  INIT();
  while(1){
  free(llink);
  llink=login_system();
  system("color fc");
  if(llink->usertype==ADMIN)
    Admin_UI(llink->username);
  else if(llink->usertype==NORMAL_USER)
    Normal_User_UI(llink->username);
  else
    printf("\nLOGIN FAILED , Can't find a match in USER DATABASE...!!!\nTry Again....!!!\n");
  printf("1. Switch user account[S|s]\n");
  printf("2. Exit?[E|e]\n\n");
  c = getchar();
  if(c=='E'||c=='e'||c=='2')
    break;
  else
    getchar();
}
return 0;
}

void INIT()
{
  adminlist=NULL;
  normallist=NULL;
  booklist=NULL;
  borrowlist=NULL;
  adminlist=(usrlink)malloc(sizeof(Usernode));
  strcpy(adminlist->user.username,"admin");
  adminlist->user.age=25;
  strcpy(adminlist->user.phonenum,"1234567890");
  adminlist->user.id=1;
  adminlist->user.usertype=1;
  strcpy(adminlist->user.sex,"male");
  adminlist->next=NULL;
}

loginlink login_system()
{
   char username[MAXUSERNAME];
   int len,usertype;
   loginlink llink = NULL;
   system("color fc");
   printf("\n************************WELCOME TO DELHI PUBLIC LIBRARY************************\n\n\n");
   Introduction();
   Get_User_Name(username,MAXUSERNAME);
   printf("Username is %s\n",username);
   usertype = AuthorizeUser(username);
   llink = (loginlink)malloc(sizeof(Loginnode));
   llink->usertype=usertype;
   strcpy(llink->username,username);
   return llink;

}

void Admin_UI(char username[])
{
  int c,flag=1;

  while(flag){
  printf("\n########################## Menu for user '%s' ########################\n",username);
  printf("1. User Management\n2. Book Management\n3. Borrow Management\n4. Exit\n");
  printf("\nWhich service do you like?[ 1 ]\n");
  c=getchar();
  getchar();
  switch(c){
    case '\n':
    case '1':
      system("color f9");
      Manage_User_UI(username);
      break;
    case '2':
      system("color fd");
      Manage_Book_UI(username);
      break;
    case '3':
      system("color f3");
      Manage_Borrow_UI(username);
      break;
    case '4':
      flag=0;
      break;
    default:
      printf("Please input an valid option\n");
      break;
  }
  }
 }
void modify_book()
{

  char name[MAXBOOKNAME];
  char author[MAXNAME];
  int totalcount,borrowcount;
  int id,option,flag,choice;
  bklink booklink=NULL;
  flag=1;
  while(flag--){
  printf("\nLocate book by name[N] or id[I]:");
  option=getchar();
  getchar();
  switch(option)
  {
     case 'N':
     case 'n':
         printf("Bookname: ");
         scanf("%[^\n]",name);
         getchar();
         booklink=Book_Search_by_name(name);
         break;
     case 'I':
     case 'i':
         printf("Book ID:");
         scanf("%d",&id);
         getchar();
         booklink=Book_Search_by_id(id);
         break;
    case 'q':
    case 'Q':
         break;
     default:
        printf("Unknown option\n");
        flag=1;
        break;
  }

}
if(booklink==NULL)
  printf("Book not found\n");
else
{
  printf("Change info for Book %s\n\n",booklink->book.name);
  printf("Book name: %s ,[m/M] to modify ,other to skip\n",booklink->book.name);
  choice=getchar();

  if(choice=='m'||choice=='M')
  {
    getchar();
    printf("New book name is: ");
    scanf("%[^\n]",name);
    strcpy(booklink->book.name,name);
    getchar();
  }

  printf("Author: %s ,[m/M] to modify ,other to skip\n",booklink->book.author);
  choice=getchar();

  if(choice=='m'||choice=='M')
  {
    getchar();
    printf("New author is: ");
    scanf("%[^\n]",author);
    strcpy(booklink->book.author,author);
    getchar();
  }

  printf("Total count: %d ,[m/M] to modify ,other to skip\n",booklink->book.totalcount);
  choice=getchar();

  if(choice=='m'||choice=='M')
  {
    getchar();
    printf("New totalcount is: ");
    scanf("%d",&totalcount);
    booklink->book.totalcount=totalcount;
    getchar();
  }
  printf("Borrow count: %d ,[m/M] to modify ,other to skip\n",booklink->book.borrowcount);
  choice=getchar();

  if(choice=='m'||choice=='M')
  {
    getchar();
    printf("New borrowcount is: ");
    scanf("%d",&borrowcount);
    booklink->book.borrowcount=borrowcount;
    getchar();
  }

  printf("User info modification done\n\nnew user info is:\n");
  Display_Book(booklink);

  }
}

void Book_Addition()
{
  char name[MAXBOOKNAME];
  char author[MAXNAME];
  int totalcount;
  bklink booklink=NULL;
    printf("\nPlease input book info that you want to add:\n");
    printf("Bookname: ");
    scanf("%[^\n]",name);
    getchar();
    printf("Author: ");
    scanf("%[^\n]",author);
    getchar();
    printf("Total book counts: ");
    scanf("%d",&totalcount);
    getchar();

    booklink=(bklink)malloc(sizeof(Booknode));
    strcpy(booklink->book.name,name);
    strcpy(booklink->book.author,author);
    booklink->book.totalcount=totalcount;
    booklink->book.borrowcount=0;
    booklink->next=NULL;

    Book_Insertion(&booklist,booklink);
    printf("book '%s' successfully added to book list\n\n",booklink->book.name);

  }

  void Book_Deletion()
  {
    char name[MAXBOOKNAME];
    int option,id;

    while(1)
    {
      printf("\nSelect book by ID[I] or by bookname[N]?\n");
      option=getchar();
      getchar();
      if(option=='N' || option=='n')
      {  printf("Please input bookname that you want to delete: ");
         scanf("%[^\n]",name);
         getchar();
         book_delete_by_name(name);
          break;
      }
    else if(option=='I'||option=='i')
    {
      printf("Please input book ID that you want to delete:\n");
      scanf("%d",&id);
      getchar();
      book_delete_by_id(id);
      break;

    }
    else
      printf("Unknown option\n");

  }
    }

int book_delete_by_id(int id)
{
  bklink booklink,temp;
  booklink=booklist;
  if(booklist==NULL)
    printf("No book in the book list\n");
  if(booklink->book.id==id)
  {
  temp=booklink;
   if(booklink->next==NULL)
     booklist=NULL;
  else
  {   booklist=booklink->next;
      booklink=booklink->next;
    }
  printf("book %s delete successfully\n\n",temp->book.name);
  free(temp);
  return 0;
  }

  while(booklink->next!=NULL)
  {
    temp=booklink;
    booklink=booklink->next;
    if(booklink->book.id==id)
    {
      temp->next=booklink->next;
      printf("book delete successfully\n\n");
      free(booklink);
      return 0;
    }

  }
  printf("book not found in booklist\n\n");
  return -1;
}

int book_delete_by_name(char name[])
{
  bklink booklink,temp;
  booklink=booklist;
  if(booklist==NULL)
    printf("No book in the list\n\n");
  if(strcmp(booklink->book.name,name)==0)
  {
   temp=booklink;
   if(booklink->next==NULL)
     booklist=NULL;
  else
     booklist=booklink->next;
  free(temp);
  printf("Book delete successfully\n\n");
  return 0;
  }

  while(booklink->next!=NULL)
  {
    temp=booklink;
    booklink=booklink->next;
    if(strcmp(booklink->book.name,name)==0)
    {
      temp->next=booklink->next;
      free(booklink);
      printf("Book delete successfully\n\n");
      return 0;
    }

  }
  printf("Book not found\n\n");
  return -1;
}

int Book_Search()
{
  char name[MAXBOOKNAME];
  int id,option,flag;
  bklink book;
  flag=1;
  while(flag--){
  printf("Search book by name[N] or id[I]:\n");
  option=getchar();
  getchar();
  switch(option)
  {
     case 'N':
     case 'n':
         printf("Please input bookname:");
         scanf("%[^\n]",name);
         getchar();
         book=Book_Search_by_name(name);
         break;
     case 'I':
     case 'i':
         printf("Please input book ID:\n");
         scanf("%d",&id);
         getchar();
         book=Book_Search_by_id(id);
         break;
     default:
        printf("Unknown option\n");
        flag=1;
        break;
  }
}
   if(book)
   {
     printf("Book is found\n\n");
     return 0;
    }
   else
   return -1;
}

bklink Book_Search_by_name(char name[])
{
  bklink booklink;
  booklink=booklist;

  while(booklink!=NULL)
  {

    if(strcmp(booklink->book.name,name)==0)
    {
      Display_Book(booklink);
      return booklink;
    }
    booklink=booklink->next;
  }
  printf("book '%s' does not exist in the library!\n\n",name);
  return NULL;
}

bklink Book_Search_by_id(int id)
{
  bklink booklink;
  booklink=booklist;
  while(booklink!=NULL)
  {

    if(booklink->book.id==id)
    {
      Display_Book(booklink);
      return booklink;
    }
  booklink=booklink->next;
  }
  printf("book id %d not exist!\n\n",id);
  return NULL;
}

void Display_Book(bklink booklink)
{

  if(booklink==NULL)
   printf("book not exist\n\n");
  else
  {
      printf("Book ID: %d\n",booklink->book.id);
      printf("Bookname: %s\n",booklink->book.name);
      printf("Author: %s\n",booklink->book.author);
      printf("Total book count: %d\n",booklink->book.totalcount);
      printf("Borrow count: %d\n",booklink->book.borrowcount);
  }
}

void borrow_display(borrowlink borrlink)
{

  if(borrlink==NULL)
   printf("borrow record not exist\n\n");
  else
  {
      printf("Borrow ID: %d\n",borrlink->borrow.borrow_id);
      printf("Borrow Date: %s\n",borrlink->borrow.borrowdate);
      printf("User: %s\n",borrlink->borrow.username);
      printf("Bookname: %s\n",borrlink->borrow.bookname);
      printf("Borrow count: %d\n",borrlink->borrow.borrow_counts);
  }
}


 void Manage_Book_UI(char username[])
 {
   int choice,flag=1;
   while(flag--){
   printf("\n################### Book Management Menu for user '%s' #####################\n",username);
   printf("1.Add book[A]\n2.Delete book[D]\n3.Search book[S]\n4.Modify book[M]\n5. Go to upper level[E]\n");
   choice=getchar();
   printf("choice is %c\n",choice);
   switch(choice)
   {
     case '1':
     case 'A':
     case 'a':
       getchar();
       Book_Addition();
       flag=1;
       break;
     case '2':
     case 'D':
     case 'd':
       getchar();
       Book_Deletion();
       flag=1;
       break;
     case '3':
     case 'S':
     case 's':
       getchar();
       Book_Search();
       flag=1;
       break;
     case '4':
     case 'M':
     case 'm':
       getchar();
       modify_book();
       flag=1;
       break;
     case '5':
     case 'E':
     case 'e':system("color fc");
              system("cls");
               printf("\n************************WELCOME TO DELHI PUBLIC LIBRARY************************\n\n\n");
       getchar();
       break;
     default:
       printf("Please input a valid option\n");
       flag=1;
       break;
   }

 }
 }

int borrow_book()
{
  char name[MAXBOOKNAME];
  char username[MAXUSERNAME];
  int counts;
  bklink booklink=NULL;
  borrowlink borrlink=(borrowlink)malloc(sizeof(Borrownode));

    printf("Please input book name that you want to borrow:\n");
    printf("Bookname: ");
    scanf("%[^\n]",name);
    getchar();
    booklink = Book_Search_by_name(name);
    if(booklink)
    {
      printf("Total count %d , %d books already borrowed out for book '%s' \n\n",booklink->book.totalcount,booklink->book.borrowcount,name);
    if(booklink->book.borrowcount==booklink->book.totalcount)
      printf("Book '%s' all borrowed out\n\n",name);
    else
    {
      while(1)
      {
      printf("Please input your name: ");
      scanf("%[^\n]",username);
      getchar();
      printf("How many copies you want to borrow: ");
      scanf("%d",&counts);
      getchar();
      if(((booklink->book.totalcount)-(booklink->book.borrowcount))<counts)
         printf("ERROR:You cannot borrow books greater than the available number....SO PLEASE TRY AGAIN\n\n");
      else
         break;
       }
      strcpy(borrlink->borrow.username,username);
      strcpy(borrlink->borrow.bookname,name);
      borrlink->borrow.borrow_counts=counts;
      booklink->book.borrowcount+=counts;
      borrlink->next=NULL;

    borrow_insert(&borrowlist,borrlink);
    printf("Book '%s' successfully borrowed to '%s' \n\n",booklink->book.name,username);
  }
  }
   return 1;
}

char *get_time(void)
{
  char *datestr=(char *)malloc(sizeof(char)*MAXDATELEN);
  time_t a;
  time(&a);
  strftime(datestr,MAXDATELEN,"%Y:%m:%d %H:%M:%s",localtime(&a));
  return datestr;
}

void borrow_insert(borrowlink * borrowlistptr,borrowlink borrlink)
{

  borrowlink temp;
  borrowlist=*borrowlistptr;
  char *timeptr;
  timeptr=get_time();
  strcpy(borrlink->borrow.borrowdate,timeptr);
  if(borrowlist==NULL)
  { borrowlist=borrlink;
    borrowlist->borrow.borrow_id=1;
    return;
  }
  for(temp=borrowlist;temp->next!=NULL;temp=temp->next)
     ;
  temp->next=borrlink;
  borrlink->borrow.borrow_id=temp->borrow.borrow_id+1;
}


int return_book(void)
{
  char username[MAXUSERNAME];
  borrowlink borrow;
  int counts;
  printf("Please input your username: ");
  scanf("%[^\n]",username);
  getchar();
  borrow=search_borrow_by_username(username);
  if(borrow)
  {
    here:printf("How many copies you want to return: ");
    scanf("%d",&counts);
    getchar();
    if(counts>borrow->borrow.borrow_counts)
    {
        printf("Cannot return greater number of books than you have borrowed\n\n");
        goto here;

    }
    else
    {
       borrow->borrow.borrow_counts-=counts;
       printf("Book '%s' return successfully\n\n",borrow->borrow.bookname);
       return 0;
  }
  return -1;
}
}

int search_borrow(void)
{
  char username[MAXUSERNAME];
  int id,option;
  borrowlink borrow;
  printf("Please input username: ");
  scanf("%[^\n]",username);
  getchar();
  borrow=search_borrow_by_username(username);
   if(borrow)
   {
     printf("Borrow record is found\n");
     return 0;
    }
   else
     return -1;
  return 0;
}

borrowlink search_borrow_by_username(char username[])
{
  borrowlink borrow;
  borrow=borrowlist;


  while(borrow!=NULL)
  {

    if(strcmp(borrow->borrow.username,username)==0)
    {
      borrow_display(borrow);
      return borrow;
    }
    borrow=borrow->next;
  }
  printf("User '%s' borrow records not found!\n",username);
  return NULL;
}

 void Manage_Borrow_UI(char username[])
 {
   int choice,flag=1;
   while(flag--){
   printf("\n###################### Borrow Management Menu for user '%s' ####################\n",username);
   printf("1.Borrow book[B]\n2.Return book[R]\n3.Search borrow[S]\n4. Go to upper level[E]\n");
   choice=getchar();
   printf("choice is %c\n",choice);
   switch(choice)
   {
     case '1':
     case 'B':
     case 'b':
       getchar();
       borrow_book();
       flag=1;
       break;
     case '2':
     case 'R':
     case 'r':
       getchar();
       return_book();
       flag=1;
       break;
     case '3':
     case 'S':
     case 's':
       getchar();
       search_borrow();
       flag=1;
       break;
     case '4':
     case 'E':
     case 'e':system("color fc");
              system("cls");
               printf("\n************************WELCOME TO DELHI PUBLIC LIBRARY************************\n\n\n");
       getchar();
       break;
     default:
       getchar();
       printf("Please input a valid option\n\n");
       flag=1;
       break;
   }

 }
 }

void Manage_User_UI(char username[])
{
  int choice,flag=1;
  while(flag--){
  printf("\n###################### User Management Menu for user '%s' ####################\n",username);
  printf("1.Add user[A]\n2.Delete user[D]\n3.Search user[S]\n4.Modify user[M]\n5. Go to upper level[E]\n");
  choice=getchar();
  printf("choice is %c\n",choice);
  switch(choice)
  {
    case '1':
    case 'A':
    case 'a':
      getchar();
      User_Addition();
      flag=1;
      break;
    case '2':
    case 'D':
    case 'd':
      getchar();
      User_Deletion();
      flag=1;
      break;
    case '3':
    case 'S':
    case 's':
      getchar();
      search_user();
      flag=1;
      break;
    case '4':
    case 'M':
    case 'm':
      getchar();
      User_Modification();
      flag=1;
      break;
    case '5':
    case 'E':
    case 'e':system("color fc");
             system("cls");
              printf("\n************************WELCOME TO DELHI PUBLIC LIBRARY************************\n\n\n");

      getchar();
      break;
    default:
      printf("Please input a valid option\n\n");
      flag=1;
      break;
  }

}
}

void User_Addition()
{
  char username[MAXUSERNAME];
  char phonenum[MAXPHONENUM];
  char sex[10];
  int usernamelen,usertype,age;
  usrlink userlink=NULL;
  usertype=FORBIDDEN;

  while(1)
  {
    printf("Please input user info that you want to add:\n\n");
    usernamelen=Get_User_Name(username,MAXUSERNAME);
    printf("USERTYPE:");
    scanf("%d",&usertype);
    printf("AGE:");
    scanf("%d",&age);
    printf("PHONENUMBER:");
    scanf("%s",phonenum);
    printf("SEX:");
    scanf("%s",sex);
    getchar();
    if(strlen(username)<6)
      printf("username should not be less than 6\n\n");
    else if(usertype!=ADMIN&&usertype!=NORMAL_USER)
      printf("usertype %d is not correct\n\n",usertype);
    else
    {
      userlink=(usrlink)malloc(sizeof(Usernode));
      strcpy(userlink->user.username,username);
      userlink->user.age=age;
      strcpy(userlink->user.phonenum,phonenum);
      strcpy(userlink->user.sex,sex);
      userlink->user.usertype=usertype;
      userlink->next=NULL;
      if(usertype==ADMIN)
      {
          User_Insertion(userlink,ADMIN);
          printf("\n-----------------------------------------------------------------------------\n");
          printf("user '%s' successfully added to admin user list\n\n",userlink->user.username);
       }
      else if(usertype==NORMAL_USER)
      {
          User_Insertion(userlink,NORMAL_USER);
          printf("\n-----------------------------------------------------------------------------\n");
          printf("user '%s' successfully added to normal user list\n\n",userlink->user.username);
      }
      break;
    }
  }

}


void User_Deletion()
{
  char username[MAXUSERNAME];
  int usernamelen,option,id;


  while(1)
  {
    printf("\nSelect user by ID[I] or by username[U]?\n");
    option=getchar();
    getchar();
    if(option=='U' || option=='u')
    {  printf("\nPlease input username that you want to delete:\n");
       usernamelen=Get_User_Name(username,MAXUSERNAME);
    if(usernamelen<6)
      printf("Username length should not be less than 6\n\n");
    else
    {
        User_Deletion_by_Name(username);
        break;
    }
  }
  else if(option=='I'||option=='i')
  {
    printf("\nPlease input user ID that you want to delete:\n\n");
    scanf("%d",&id);
    getchar();
    User_Deletion_by_ID(id);
    break;

  }
  else
    printf("Unknown option\n");

}

}

int search_user()
{
   char username[MAXUSERNAME];
   int id,option,flag;
   usrlink user;
   flag=1;
   while(flag--){
   printf("Search user by name[N] or id[I]:\n");
   option=getchar();
   getchar();
   switch(option)
   {
      case 'N':
      case 'n':
          Get_User_Name(username,MAXUSERNAME);
          user=Search_User_by_Name(username);
          break;
      case 'I':
      case 'i':
          printf("Please input user ID:\n");
          scanf("%d",&id);
          getchar();
          user=Search_User_by_ID(id);
          break;
      default:
         printf("Unknown option\n");
         flag=1;
         break;
   }
}
    if(user)
    {
      printf("User is found\n");
      return 0;
     }
    else
    return -1;
}

int User_Modification_by_usrlink(usrlink user)
{
  char sex[10];
  char phonenum[MAXPHONENUM];
  int choice,usertype,age,old_usertype;
  if(!user)
    return -1;
  else
  {
    printf("Usertype: %d ,[m/M] to modify ,other to skip\n",user->user.usertype);
    choice=getchar();
    if(choice=='m'||choice=='M')
    {
      printf("new usertype is: ");
      scanf("%d",&usertype);
      old_usertype=user->user.usertype;
      user->user.usertype=usertype;
      getchar();
    }

    printf("Phonenumber: %s ,[m/M] to modify ,other to skip\n",user->user.phonenum);
    choice=getchar();
    if(choice=='m'||choice=='M')
    {
      printf("new phonenumber is: ");
      scanf("%[^\n]",phonenum);
      strcpy(user->user.phonenum,phonenum);
      getchar();
    }
    printf("Sex: %s ,[m/M] to modify ,other to skip\n",user->user.sex);
    choice=getchar();
    if(choice=='m'||choice=='M')
    {
      printf("new sex value is: ");
      scanf("%[^\n]",sex);
      strcpy(user->user.sex,sex);
      getchar();
    }
    printf("Age: %d ,[m/M] to modify ,other to skip\n",user->user.age);
    choice=getchar();
    if(choice=='m'||choice=='M')
    {
      printf("new age is: ");
      scanf("%d",&age);
      user->user.age=age;
      getchar();
    }
    printf("User info modification done...!!!\nnew user info is:\n\n");
    Display_User(user);
    if(user->user.usertype!=old_usertype)
    {
      User_Deletion_by_Name(user->user.username);
      if(user->user.usertype==ADMIN)
        User_Insertion(user,ADMIN);
      else
        User_Insertion(user,NORMAL_USER);
  }
    return 0;
    }
  }


void User_Modification()
{
  char username[MAXUSERNAME];
  char sex[10];
  int id,option,flag,choice,usertype,age,old_usertype;
  usrlink user=NULL;
  flag=1;

  while(flag--){
  printf("\nLocate user by name[N] or id[I]: ");
  option=getchar();
  getchar();
  switch(option)
  {
     case 'N':
     case 'n':
         Get_User_Name(username,MAXUSERNAME);
         user=Search_User_by_Name(username);
         break;
     case 'I':
     case 'i':
         printf("Please input user ID:\n");
         scanf("%d",&id);
         getchar();
         user=Search_User_by_ID(id);
         break;
    case 'q':
    case 'Q':
         break;
     default:
        printf("Unknown option\n");
        flag=1;
        break;
  }

}

if(user==NULL)
  printf("User not found\n\n");
else
  User_Modification_by_usrlink(user);
}

void Display_User(usrlink user)
{
  if(user==NULL)
  {
      printf("\n-----------------------------------------------------------------------------\n");
      printf("user not exist\n\n");
  }
  else
  {
      printf("\n-----------------------------------------------------------------------------\n");
      printf("User ID: %d\n",user->user.id);
      printf("Usertype: %d\n",user->user.usertype);
      printf("Username: %s\n",user->user.username);
      printf("phonenum: %s\n",user->user.phonenum);
      printf("sex: %s\n",user->user.sex);
      printf("age: %d\n",user->user.age);
  }
}


usrlink Search_User_by_Name(char username[])
{
  usrlink user;
  user=adminlist;

  while(user!=NULL)
  {

    if(strcmp(user->user.username,username)==0)
    {
      Display_User(user);
      return user;
    }
    user=user->next;
  }
  printf("User %s does not exist in ADMIN list!\n\n",username);

  user=normallist;
  while(user!=NULL)
  {

    if(strcmp(user->user.username,username)==0)
    {
      Display_User(user);
      return user;
    }
    user=user->next;
  }
  printf("User %s does not exist in normal user list!\n\n",username);
  return NULL;
}

usrlink Search_User_by_ID(int id)
{
  usrlink user;
  user=adminlist;

  while(user!=NULL)
  {

    if(user->user.id==id)
    {
      Display_User(user);
      return user;
    }
  user=user->next;
  }
  printf("User id %d does not exist in ADMIN list!\n\n",id);
  user=normallist;
  while(user!=NULL)
  {

    if(user->user.id==id)
    {
      Display_User(user);
      return user;
    }
  user=user->next;
  }
  printf("User id %d not exist in NORMAL_USER list!\n\n",id);
  return NULL;
}

int User_Deletion_by_Name(char username[])
{
  usrlink user,temp;
  user=adminlist;
  if(adminlist==NULL)
    printf("No user in the ADMIN LIST\n\n");
  else if(strcmp(user->user.username,username)==0)
  {
   temp=user;
   if(user->next==NULL)
     adminlist=NULL;
  else
     adminlist=user->next;
  free(temp);
  printf("User deleted successfully\n\n");
  return 0;
  }
  while(user->next!=NULL)
  {
    temp=user;
    user=user->next;
    if(strcmp(user->user.username,username)==0)
    {
      temp->next=user->next;
      free(user);
      printf("User deleted successfully\n\n");
      return 0;
    }

  }
  printf("User not found in ADMIN LIST\n\n");

  user=normallist;
  if(normallist==NULL)
    printf("No user in the NORMAL USER LIST\n");
  else if(strcmp(user->user.username,username)==0)
  {
   if(user->next==NULL)
     normallist=NULL;
  else
     normallist=user->next;
  free(user);
  printf("User deleted successfully\n\n");
  return 0;
  }

  while(user->next!=NULL)
  {

    temp=user;
    user=user->next;
    if(strcmp(user->user.username,username)==0)
    {
      temp->next=user->next;
      free(user);
      printf("User deleted successfully\n\n");
      return 0;
    }

  }

  return -1;
}

int User_Deletion_by_ID(int id)
{
  usrlink user,temp;
  user=adminlist;

  if(adminlist==NULL)
    printf("No user in the ADMIN LIST\n\n");
  else if(user->user.id==id)
  {
   temp=user;
   if(user->next==NULL)
     adminlist=NULL;
  else
     adminlist=user->next;
  free(temp);
  printf("\n-----------------------------------------------------------------------------\n");
  printf("User deleted successfully\n\n");
  return 0;
  }

  while(user->next!=NULL)
  {

    temp=user;
    user=user->next;
    if(user->user.id==id)
    {
      temp->next=user->next;
      free(user);
      printf("\n-----------------------------------------------------------------------------\n");
      printf("User deleted successfully\n\n");
      return 0;
    }

  }
  printf("User not found in ADMIN LIST\n\n");

  user=normallist;

  if(normallist==NULL)
    printf("No user in the NORMAL USER LIST\n\n");
  else if(user->user.id==id)
  {
   if(user->next==NULL)
     normallist=NULL;
  else
     normallist=user->next;
  free(user);
  printf("User deleted successfully\n\n");
  return 0;
  }

  while(user->next!=NULL)
  {

    temp=user;
    user=user->next;
    if(user->user.id==id)
    {
      temp->next=user->next;
      free(user);
      printf("User deleted successfully\n\n");
      return 0;
    }

  }
  printf("User not found in the NORMAL USER LIST\n\n");

  return -1;
}

void Book_Insertion(bklink *booklistptr,bklink booklink)
{
  bklink temp;
  booklist=*booklistptr;
  if(booklist==NULL)
  { booklist=booklink;
    booklist->book.id=1;
    return;
  }
  for(temp=booklist;temp->next!=NULL;temp=temp->next)
     ;
  temp->next=booklink;
  booklink->book.id=temp->book.id+1;
}

void User_Insertion(usrlink userlink,int flag)
{
   usrlink temp,userlist;
   if(flag==ADMIN)
     userlist=adminlist;
   else
     userlist=normallist;
   if(userlist==NULL)
   {
     userlist=userlink;
     userlist->user.id=1;
     if(flag==ADMIN)
       adminlist=userlist;
     else
       normallist=userlist;
     return;
   }
   for(temp=userlist;temp->next!=NULL;temp=temp->next)
      ;
   temp->next=userlink;
   userlink->user.id=temp->user.id+1;

}

void Normal_User_UI(char username[])
{
  printf("\n###################### Menu for user '%s' #####################\n\n",username);
  int c,flag=1;
  usrlink user=NULL;
  borrowlink borrow=NULL;
  user=Search_User_by_Name(username);
  borrow=search_borrow_by_username(username);
  while(flag){
  printf("\n################### Menu for user '%s' ######################\n\n",username);
  printf("1. User Info\n2. Modify User Info\n3. My Borrow\n4. Search Book\n5. Exit\n");
  printf("Which service do you like?[ 1 ]\n");
  c=getchar();
  getchar();
  switch(c){
    case '\n':
    case '1':
      Display_User(user);
      break;
    case '2':
      User_Modification_by_usrlink(user);
      break;
    case '3':
      borrow_display(borrow);
      break;
    case '4':
      Book_Search();
      break;
    case '5':
      flag=0;
      break;
    default:
      printf("Please input an valid option\n");
      break;
  }
  }
}


void Introduction()
{
    printf("-----------------------------------------------------------------------------\n");
    printf("\tDelhi Public Library is the public library that tends to offer\n\tthe citizens of Delhi a place where people can explore about\n\t their various fields of interest and help in developing\n\t the society with their creativity....!!!\n\n ");
    printf("-----------------------------------------------------------------------------\n");
}
int Get_User_Name(char username[],int maxusername)
{
  int i=0;
  char c;
  printf("Username:");
  while(((c=getchar())!=EOF)&&(i<maxusername-1) && c!='\n')
  {
     if((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9'))
         username[i++]=c;
     else
         continue;
  }
  username[i]='\0';
  return i;

}

int AuthorizeUser(char username[])
{
  usrlink adminptr,normalptr;
  int usertype=FORBIDDEN;

  adminptr=Search_User_List(adminlist,username);
  if(adminptr)
  {  printf("User %s found in Admin_list\n\n",username);
     usertype=ADMIN;
       }
  else
  {
   normalptr=Search_User_List(normallist,username);
   if(normalptr)
   {
      printf("Username %s found in Normal_User_list\n\n",username);
      usertype=NORMAL_USER;
   }

  }

   return usertype;
}

usrlink Search_User_List(usrlink userlist,char name[])
{
  usrlink userptr=userlist;
  while(userptr!=NULL)
    {
      if(strcmp(userptr->user.username,name)==0)
         break;
      userptr=userptr->next;
}
  return userptr;
}


