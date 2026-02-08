#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h> // For systeminfo command
#include <time.h>


// Login System
int login();
void art();

// File Explorer
int file_exp();
void logfiles(char *filename);
void write_file();
void read_file();
void append_file();
void filelist();
void searchfile();

// Note Pad (optional if separate from File Explorer)
void note_pad();

// Student Database
int stu_data();
void add_student();
void view_student();
void search_student();

// System Information / Time
void SysTime();
void ShowTime();
void SysInfo();

void art()
{

    // Row 1
    printf("_________  /\\      _____    |\\        /|            ____     _____\n");
    // Row 2
    printf("   |      /  \\    |         | \\      / |          /    \\   /     \n");
    // Row 3
    printf("   |     /____\\   |         |  \\    /  |         /      \\ |      \n");
    // Row 4
    printf("   |    /      \\  |____     |   \\  /   |         |      |  \\____\n");
    // Row 5
    printf("   |    |      |       |    |    \\/    |         |      |       \\\n");
    // Row 6
    printf("   |    |      |       |    |          |         \\      /        \\\n");
    // Row 7
    printf("   |    |      |  _____|    |          |          \\____/   _____/\n");
}

// Login is Created by Pritom Bhowmik

int login() // Member 1 : Login
{

    art();
    printf("\n");

    FILE *fp;

    char username[20];
    char password[20];
    char cUser[20];
    char cPass[20];
    int isfound = 0;

    for (int i = 3; i > 0; i--)
    {

        printf("\nEnter User Name : ");

        fgets(username, sizeof(username), stdin);
        strtok(username, "\n");

        printf("Enter Password : ");

        fgets(password, sizeof(password), stdin);
        strtok(password, "\n");

        fp = fopen("user.txt", "r");

        // check user name and password credential

        while (fscanf(fp, "%19s %19s", cUser, cPass) == 2)
        {

            if (strcmp(username, cUser) == 0 && strcmp(password, cPass) == 0)
            {
                isfound = 1;
                break;
            }
        }

        fclose(fp);

        if (isfound)
        {
            printf("\nWelcome to Mini Terminal OS Simulator\n");
            return 1;
        }
        else
        {
            if (i - 1 > 0)
            {
                printf("\nIncorrect credentials. Try Again. You have %d attempt(s) left.\n", i - 1);
            }
            else
            {

                printf("\nIncorrect credentials. No attempts left. Shutdown....\n");
                return 0;
            }

            // Username has no spaces.
            if (strchr(username, ' ') != NULL) // strchr search a character in string
            {
                printf("\nPlease do not use any space\n");
            }
        }
    }
    return 0;
}

// Member 2 : Logic File Explorer

#define log "file_list.txt"

// Function Prototypes
void logfiles(char *filename)
{
    FILE *filelist = fopen(log, "a");

    fprintf(filelist, "%s\n", filename);
    fclose(filelist);
}

void update_logfiles(char *filename) // Added by Pritom Bhowmik
{
    FILE *filelist = fopen(log, "r");
    FILE *temp = fopen("temp.txt", "w");
    char line[256];

    if (filelist == NULL || temp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(line, sizeof(line), filelist))
    {

        strtok(line, "\n");

        if (strcmp(line, filename) != 0)
        {
            fprintf(temp, "%s\n", line); // keep only unmatched lines
        }
    }

    fclose(filelist);
    fclose(temp);

    // Replace original log file with updated temp file
    remove(log);
    rename("temp.txt", log);
}

/*
void writefile()
{
    FILE *file;

    int ch, count = 0;
    char filename[10], text[100];

    /*
        char* text = (char*)malloc(maxsize * sizeof(char));
    if(text == NULL)
    {
    printf("Memory allocation failed!\n");
    return;
    }
    ///

    printf("\nEnter File Name : ");
    getchar();
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");

    file = fopen(filename, "w");

    if (!file)
    {
        printf("\nCannot open file!\n");
        return;
    }

    printf("\nEnter text to write : \n");
    getchar(); // consume leftover newline

    fgets(text, sizeof(text), stdin);
    // fgets(text, maxsize, stdin);
    fputs(text, file);

    fclose(file);

    // Count characters
    file = fopen(filename, "r");

    count = strlen(text); // count characters from text

    if (count > 100)
    {
        // Warning Message
        printf("\nYour file content : greater that 1000 character. You surpass your character limit\n");
        fclose(file);
        return;
    }

    // Promotional Message
    printf("\nYour file content : %d character. Max Character Limit : %ld . To increase character limit pay 100 BDT\n", count, sizeof(text));
    fclose(file);

    printf("\n===Data written successfully===\n");

    // filename go to logfiles() function
    logfiles(filename);
}
*/

// File Detele feature made by Saim

void file_dlt()
{
    char filename[100];
    printf("Enter filename to delete : ");
    // scanf("%s", filename); // old code by Saim
    getchar(); // consume leftover newline
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");

    if (remove(filename) == 0) // remove function diye delete kora// 0 mane kaj hoyeche
    {
        printf("\nFile has been deleted *_* \n");

        update_logfiles(filename); // log file thekeo delete hobe added by Pritom Bhowmik
    }
    else
    {
        printf("Couldn't delete file. Maybe its non-existing \n");
    }
}

void filelist()
{
    FILE *listfile;
    char filename[100];

    listfile = fopen(log, "r");

    if (!listfile)
    {
        printf("\nNo files have been created\n");
        return;
    }

    printf("\n==== Your Created Files ====\n");

    while (fgets(filename, sizeof(filename), listfile) != NULL)
    {
        {
            printf("%s", filename);
        }
    }

    fclose(listfile);

    printf("\n==== List End ====\n");
}
void searchfile()
{
    char keyword[100];
    char filename[100]; // filename in log file
    int found = 0;

    printf("\nEnter file name to search: \n");
    getchar(); // consume leftover newline
    fgets(keyword, sizeof(keyword), stdin);
    strtok(keyword, "\n");

    FILE *file = fopen(log, "r");
    if (file == NULL)
    {
        printf("File not found!\n");
        return;
    }

    while (fgets(filename, sizeof(filename), file) != NULL)

    {
        strtok(filename, "\n");

        if (strcmp(filename, keyword) == 0)
        {

            printf("\nFile found : %s\n", filename);
            found = 1;

            // Display file content
            /*
            FILE *fileptr = fopen(filename, "r"); // open the actual file
            if (fileptr == NULL) {
                printf("Could not open file: %s\n", filename);
            } else {
                printf("\n==== File Content ====\n");
                printf("\n");
                int ch;
                while ((ch = fgetc(fileptr)) != EOF) {
                    putchar(ch);
                }
                fclose(fileptr);
                printf("\n");
                printf("\n==== End of File ====\n");
            }
                */

            break;
        }
    }

    if (!found)
    {
        printf("File with name %s not found.\n", keyword);
    }

    fclose(file);
}

int file_exp()
{

    int choice;

    while (1)
    {
        // Menu
        printf("\n==== File Manager Menu ====\n");
        printf("\n");
        printf("1. Read File\n");
        printf("2. Add text in your existing file\n");
        printf("3. List of all files you created\n");
        printf("4. Search file\n");
        printf("5. Delete file\n");
        printf("6. Exit\n");

        printf("Enter Your Choice : \n");
        scanf("%d", &choice);

        // Swtich statement for choices
        switch (choice)
        {

        case 1:
            read_file();
            break;
        case 2:
            append_file();
            break;
        case 3:
            filelist();
            break;
        case 4:
            searchfile();
            break;
        case 5:
            file_dlt();
            break;
        case 6:
            printf("\n>> Abar Asiben Dhonnobad <<\n");

            return 0;
        default:
            printf("\nEnter Valid Choice\n");
        }
    }

    return 0;
}

// Ummay : Note Pad Integration

void write_file()
{
    int choice;
    char filename[50], ch;
    FILE *fp;

    printf("Enter File Name : ");
    // getchar(); getchar(); remove by Pritom Bhowmik
    fgets(filename, sizeof(filename), stdin); // Modifid by Ummay
    strtok(filename, "\n");                   // modified by ummay

    fp = fopen(filename, "w");

    if (fp == NULL)
    {
        printf(" ERROR opening file\n");
        return;
    }
    printf("\nInstruction : Start typing (press '~' and then enter to stop)\n");

    while ((ch = getchar()) != '~')
    {
        fputc(ch, fp);
    }
    fclose(fp);

    /*
    //character count all line and limit feature added by Pritom Bhowmik
    int count = 0;
    FILE *fp_read = fopen(filename, "r");
    if (fp_read != NULL) {
        int ch;
        while ((ch = fgetc(fp_read)) != EOF) {
            count++;
        }
        fclose(fp_read);
    }
    printf("\nYour file name : %s and character count : %d\n", filename, count);
    if (count > 100)
    {
        // Warning Message
        printf("\nYour file content : greater than 100 characters. You surpass your character limit\n");
        return;
    }

    */
    printf("\n====Note saved====\n");
    logfiles(filename);
}

void read_file()

{
    int choice;
    char filename[50], ch;
    FILE *fp;

    printf("Enter the file name you want to open : ");
    printf("\n");
    getchar(); // consume leftover newline
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nFile not found\n");
        return;
    }
    printf("\n");



    printf("\n==== File Content ====\n");
    printf("\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    fclose(fp);
    printf("\n");
    printf("\n==== End of File ====\n");
    return;
}

void readfile()

{
    int choice;
    char filename[50], ch;
    FILE *fp;

    printf("Enter the file name you want to open : ");
    printf("\n");
    fgets(filename, sizeof(filename), stdin);
    strtok(filename, "\n");

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("\nFile not found\n");
        return;
    }
    printf("\n");

    printf("\n==== File Content ====\n");
    printf("\n");

    while ((ch = fgetc(fp)) != EOF)
    {
        putchar(ch);
    }
    fclose(fp);
    printf("\n");
    printf("\n==== End of File ====\n");
    return;
}


void append_file()
{
    // int choice; // removed by ummay
    char filename[50], ch;
    FILE *fp;

    printf("Enter the file name to append : ");
    // getchar();
    fgets(filename, sizeof(filename), stdin);
    filename[strcspn(filename, "\n")] = 0;

    fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("File not found\n");
        return;
    }
    printf("\nInstruction : Append your text (press '~' and then enter to stop writing):\n");
    // getchar();
    while ((ch = getchar()) != '~')
    {
        fputc(ch, fp);
    }
    fclose(fp);
    printf("\nYour note got updated\n");
    return;
}

void note_pad()
{
    int choice;
    /*
    char filename[50], ch;
    FILE *fp;
    */

    do
    {
        printf("\n==== Note Pad ====\n");
        printf(" 1. Create a new note \n");
        printf(" 2. Open your note \n");
        printf(" 3. Append your note \n");
        printf(" 4. Exit\n");

        printf("Enter choice : ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice)
        {
        case 1:
            write_file();
            break;
        case 2:
            readfile();
            break;
        case 3:
            append_file();
            break;
        case 4:
            printf("Exiting program...\n");
            return;

        default:
            printf("Invalid choice \n");
        }

    } while (1);
}

// Munni : Student Database Integration

// Testing and Debugging by Pritom Bhowmik

// Search Functionalities by Pritom Bhowmik

// ===== Student Database =====

typedef struct StudentDatabase
{
    int ID;
    char name[50];
    float attendance;
    float avg_marks;
    char grade[3];
} database;

void add_student();
void view_student();
void search_student();

int stu_data()
{

    // Unnecessary Code remove and update by Pritom Bhowmik

    printf("\n==== Student Database =====\n");

    int choice2;
    printf("\n1. Show details\n2. Search Student\n3. Add new\n4. Exit\n");

    printf("\nEnter your choice : \n");
    scanf("%d", &choice2);

    switch (choice2)
    {
    case 1:
        view_student();
        break;
    case 2:
        search_student();
        break;
    case 3:
        add_student();
        break;
    case 4:
        return 0;
    default:
        printf("Invalid choice!\n");
        break;
    }

    return 0;
}

void add_student()
{

    int n;

    printf("How many students data you want to store?\n");
    scanf("%d", &n);

    database std[n];

    int total_class;
    printf("Enter total classes: ");
    scanf("%d", &total_class);

    int n_sub;
    printf("How many subjects marks you want to calculate?\n");
    scanf("%d", &n_sub);

    FILE *file = fopen("students.txt", "a");
    if (file == NULL)
    {
        printf("File is not opened!\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        fprintf(file, "%-10s %-15s %-15s %-15s %-10s\n",
                "ID", "Name", "Attendance(%) ", "Average Marks", "Grade");
        fprintf(file, "----------------------------------------------------------------------------\n");
    }

    for (int i = 0; i < n; i++)
    {
        int attended_class, sub_sum = 0;

        // id
        printf("\nEnter ID of student :\n");
        scanf("%d", &std[i].ID);

        // name
        printf("Enter name of student:\n");

        getchar(); // to consume the newline character left by previous scanf (added by Pritom)

        // scanf("%s", std[i].name); // This will not work for names with spaces
        fgets(std[i].name, sizeof(std[i].name), stdin); // Pritom Bhowmik
        strtok(std[i].name, "\n");

        // attendance
        printf("Attended classes of student :\n");
        scanf("%d", &attended_class);
        std[i].attendance = ((float)attended_class / total_class) * 100;

        // avg marks
        int sub_marks[n_sub];
        for (int j = 0; j < n_sub; j++)
        {
            printf("Subject %d mark:\n", j + 1);
            scanf("%d", &sub_marks[j]);
            sub_sum += sub_marks[j];
        }

        std[i].avg_marks = (float)sub_sum / n_sub;

        // grade
        if (std[i].avg_marks >= 80 && std[i].avg_marks <= 100)
            strcpy(std[i].grade, "A+");
        else if (std[i].avg_marks >= 75 && std[i].avg_marks <= 79)
            strcpy(std[i].grade, "A");
        else if (std[i].avg_marks >= 70 && std[i].avg_marks <= 74)
            strcpy(std[i].grade, "A-");
        else if (std[i].avg_marks >= 65 && std[i].avg_marks <= 69)
            strcpy(std[i].grade, "B+");
        else if (std[i].avg_marks >= 60 && std[i].avg_marks <= 64)
            strcpy(std[i].grade, "B");
        else if (std[i].avg_marks >= 55 && std[i].avg_marks <= 59)
            strcpy(std[i].grade, "B-");
        else if (std[i].avg_marks >= 50 && std[i].avg_marks <= 54)
            strcpy(std[i].grade, "C+");
        else if (std[i].avg_marks >= 45 && std[i].avg_marks <= 49)
            strcpy(std[i].grade, "C");
        else if (std[i].avg_marks >= 40 && std[i].avg_marks <= 44)
            strcpy(std[i].grade, "D");
        else if (std[i].avg_marks < 40)
            strcpy(std[i].grade, "F");
        else
            printf("Invalid input!");

        fprintf(file, "%-10d %-15s %-14.2f %-15.2f %-10s\n", std[i].ID, std[i].name, std[i].attendance, std[i].avg_marks, std[i].grade);
    }
    printf("\nSir, Data added successfully!\n");
    fclose(file);

    stu_data(); // Go back to student menu ( added by Pritom)
}

void view_student()
{
    char data[100];
    FILE *file = fopen("students.txt", "r");

    // fgets(data, 100, file); // read and ignore header line
    while (fgets(data, 100, file) != NULL) // read until end of file
    {
        printf("%s", data);
    }
    fclose(file);
}

// This search function is created by Pritom Bhowmik

void search_student()
{
    int search_id;
    int found = 0;
    char line[100];
    FILE *file = fopen("students.txt", "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return;
    }

    printf("Enter student ID to search: ");
    scanf("%d", &search_id);

    
    // Skip header lines
    fgets(line, sizeof(line), file);
    fgets(line, sizeof(line), file);
    

    // prottek line read korbe and check korbe id match kore kina

    while (fgets(line, sizeof(line), file) != NULL)
    {
        database std;
sscanf(line, "%d %49[^0-9] %f %f %2s", &std.ID, std.name, &std.attendance, &std.avg_marks, std.grade); // [^0-9] eta elta negated character set। er mane, 0–9 songkha na howa porjonnto sob character porbe
 // sscanf string ney and parse kore
        if (std.ID == search_id)
        {
            printf("Student found:\n");
            printf("ID: %d\nName: %s\nAttendance: %.2f%%\nAverage Marks: %.2f\nGrade: %s\n",
                   std.ID, std.name, std.attendance, std.avg_marks, std.grade);
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("Student with ID %d not found.\n", search_id);
    }

    fclose(file);
}

void SysTime() // Added by Pritom Bhowmik
{
    time_t now;
    struct tm *t;
    char buf[100];

    time(&now);
    t = localtime(&now);

    strftime(buf, sizeof(buf) - 1, "Current Date and Time: %Y-%m-%d %I:%M:%S", t);
    printf("%s\n", buf);
}

void ShowTime() // Added by Pritom Bhowmik
{
    time_t now;
    struct tm *t;
    char buf[100];

    time(&now);
    t = localtime(&now);

    strftime(buf, sizeof(buf) - 1, "Clock: %I:%M", t);
    printf("%s\n", buf);
}

void SysInfo() // Created by Pritom Bhowmik
{
    printf("==== System Information ====\n");
    system("systeminfo"); // Windows command to print system info
}

// Main is Create by Pritom Bhowmik

int main()
{
    int option = 0;

    if (!login())
    {
        return 0;
    }

    do
    {

        printf("\n===== Main Menu =====\n");
        printf("\n");
        printf("1. File Explorer\n");      // Created by Saim
        printf("2. Note Pad\n");           // Created by Ummay
        printf("3. Student Database\n");   // Created by Munni
        printf("4. Date & Time\n");        // Created by Pritom Bhowmik
        printf("5. System Information\n"); // Created by Pritom Bhowmik
        printf("\n");
        ShowTime();
        printf("\n");
        printf("0. Shutdown\n"); // Exit option added by Pritom Bhowmik
        printf("\n");
        printf("Enter choice: "); // Prompt added by Pritom Bhowmik
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            file_exp();
            break;
        case 2:
            note_pad();
            break;
        case 3:
            stu_data();
            break;
        case 4:
            SysTime();
            break;
        case 5:
            SysInfo();
            break;
        default:
            if (option < 0 || option > 4)
            {
                printf("\nPlease Enter Valid Choice! or ShutDown me!\n");
            }
        }
    } while (option != 0);

    printf("\nGood Bye Sir... Miss You :')\n");
    printf("\n");
    printf("\nShutting down...\n");

    Sleep(2000); // Pause for 2 seconds
    return 0;
}
