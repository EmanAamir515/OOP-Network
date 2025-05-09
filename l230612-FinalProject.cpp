//23L-0612
#include<iostream>
#include<fstream>
using namespace std;
class Helper
{
private:
public:
    static int stringLength(const char* string)
    {
        int length = 0;
        if (string == nullptr)
        {
            return 0;
        }
        while (*string != '\0')//derefrencing the string to get its length
        {
            length++;
            string++;
        }
        return length;
    }
    static char* StringCopy(char* string, char* tempstring)
    {//second one is being copied into first one 
        if (string != nullptr)
        {
            delete[] string;
        }
        int len = Helper::stringLength(tempstring);
        string = new char[len + 1];
        for (int i = 0; tempstring[i] != '\0'; i++)//deep copying data from one to another
        {
            string[i] = tempstring[i];
        }
        string[len] = '\0';
        return string;
    }
    static char* GetStringFromBuffer(char* buffer)
    {
        int strLen = Helper::stringLength(buffer);
        if (buffer == nullptr || buffer[0] == '\0')
        {
            return nullptr;
        }
        char* str = 0;
        if (strLen > 0)
        {
            str = new char[strLen + 1];
            str = StringCopy(str, buffer);
        }
        return str;
    }
    static int CompareString(char* cstring1, char* cstring2)
    {
        if (cstring1 == nullptr || cstring2 == nullptr)
        {
            return -1;
        }
        int strlen1 = stringLength(cstring1);
        int strlen2 = stringLength(cstring2);
        if (strlen1 != strlen2)
        {
            return -1;
        }
        for (int j = 0; cstring1[j] != '\0' && cstring2[j] != '\0'; j++)
        {
            if (cstring1[j] != cstring2[j])
            {
                return -1;
            }
        }
        return 0;
    }
    static char* copy(const char* string, char* tempstring)
    {
        int len = stringLength(string);
        tempstring = new char[len + 1];//new memory allocate needed
        for (int i = 0; i < len; i++)//deep copying data from one to another
        {
            tempstring[i] = string[i];
        }
        tempstring[len] = '\0';
        return tempstring;
    }
    static char* StringConcatenate(char* cstring1, char* cstring2)
    {
        //this function is concatenating two strings and space is not added in between it 
        if (cstring1 == nullptr || cstring2 == nullptr)
        {
            return nullptr;
        }
        int strlen1 = stringLength(cstring1);
        int strlen2 = stringLength(cstring2);
        char* temp = new char[strlen1 + strlen2 + 1];
        for (int i = 0; i < strlen1; i++)
        {
            temp[i] = cstring1[i];
        }
        for (int j = 0; j < strlen2; j++)
        {
            temp[strlen1 + j] = cstring2[j];
        }
        temp[strlen1 + strlen2] = '\0';
        cstring1 = temp;
        return cstring1;
    }
};
class Date
{
private:
    int day;
    int month;
    int year;
public:
    Date(int d = 0, int m = 0, int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }
    void setDate(int d = 0, int m = 0, int y = 0)
    {
        day = d;
        month = m;
        year = y;
    }
    void ReadDateFromFile(ifstream& fin)
    {
        fin >> day >> month >> year;
    }
    Date(Date& rhs)
    {
        day = rhs.day;
        month = rhs.month;
        year = rhs.year;
    }
    void PrintDate()
    {
        static Date currentDate(17, 4, 2024);
        if (currentDate.month == month && currentDate.year == year)
        {
            if (currentDate.day - day < 7 && currentDate.day - day > 0)
            {
                cout << "(" << currentDate.day - day << "d)";
            }
            if (currentDate.day - day == 0)
            {
                cout << " (1h): ";
            }
        }
        else if (currentDate.day == day && currentDate.month == month && currentDate.year == year)
        {
            cout << " (1h): ";
        }
        else
        {
            cout << "( " << day << "/" << month << "/" << year << " ): " << endl;
        }
    }
    int GetDifferForMemory(Date cDate)
    {
        int difference = -1;
        if (cDate.day == day && cDate.month == month)
        {
            if (year != cDate.year)
            {
                difference = year - cDate.year;
            }
        }
        return difference;
    }
    int GetDateDifference(Date other)
    {
        int difference = -1;
        if (other.month == month && other.year == year)
        {
            if (day - other.day < 7)
            {
                difference = day - other.day;
            }
        }
        return difference;

    }
    ~Date()
    {
        //nothing is dynamic in this class
    }
};
class Post;
class User;
class Page;
class Activity;
class PostContent;
class Memory;
class Comments;
class Object
{
private:
    char* ID;
protected:
    Post** Timeline;
    int notimeline;
public:
    Object();
    void AddTimeline(Post* other);
    virtual void printName();
    void setID(char* other);
    char* getID();
    void printLatestPost();
    ~Object();
};
class Post
{
private:
    char* PostID;
    char* text;
    Object* SharedBy;
    Date shareddate;
    Object** LikedBy;
    Comments** comment;
    PostContent* Content;
    int noLikedBy;//check it if static or not 
    int totalComments;
    static int TotalPosts;
public:
    Post();
    Post(char*, Object*);
    void ReadDataFromFile3(ifstream& fin);
    void setSharedBy(Object* other);
    void printSharedby();
    void AddLikedBy(Object* other);
    void printlistview();
    void setPostID(char* pid);
    char* getPostID();
    char* getPostText();
    void viewLikedBy();
    void AddComments(Comments* other);
    void viewComment();
    void AddContent(PostContent* temp);
    virtual void printPost();
    int getDateDifference();
    int GetDifferForMemory();
    PostContent* getContent();
    void PostComment(Object* ptr, char* commentText);
    virtual ~Post();
};
int Post::TotalPosts = 0;
class Comments
{
private:
    Object* CommentBy;
    char* commentID;
    char* text;
    static int TotalComments;
public:
    Comments();
    void setValues(Object* uid, char* texts);
    void printComment();
    ~Comments();
};
int Comments::TotalComments = 0;
Comments::Comments()
{
    CommentBy = nullptr;
    commentID = nullptr;
    text = nullptr;
    TotalComments++;
}
void Comments::setValues(Object* uid, char* texts)
{
    CommentBy = uid;
    text = texts;
}
void Comments::printComment()
{
    cout << "\n\t\t\t\t";
    CommentBy->printName();
    cout << ":\"" << text << "\"";

}
Comments::~Comments()
{
    TotalComments--;
    if (text != nullptr)
    {
        delete[] text;
    }
    if (commentID != nullptr)
    {
        delete[] commentID;
    }
}
class PostContent
{
public:
    virtual void printContent();
};
void PostContent::printContent() {   }
Post::Post()
{
    TotalPosts++;
    PostID = nullptr;
    text = nullptr;
    SharedBy = nullptr;
    LikedBy = nullptr;
    comment = nullptr;
    noLikedBy = 0;
    totalComments = 0;
    Content = nullptr;
}
Post::Post(char* cptr, Object* up)
{
    TotalPosts++;
    text = Helper::GetStringFromBuffer(cptr);
    SharedBy = up;
    comment = nullptr;
    LikedBy = nullptr;
    Content = nullptr;
    noLikedBy = 0;
    totalComments = 0;
    shareddate.setDate(17, 4, 2024);

    char newid[5] = "Post";
    char num[3] = "13";
    PostID = Helper::StringConcatenate(newid, num);
}
void Post::ReadDataFromFile3(ifstream& fin)
{
    char* temp = new char[180];
    fin >> temp;
    PostID = Helper::GetStringFromBuffer(temp);
    shareddate.ReadDateFromFile(fin);

    fin.ignore();
    fin.getline(temp, 180);
    text = Helper::GetStringFromBuffer(temp);
}
void Post::setSharedBy(Object* other)
{
    SharedBy = other;
}
void Post::printSharedby()
{
    SharedBy->printName();
}
void Post::AddLikedBy(Object* other)
{
    if (LikedBy == nullptr)
    {
        LikedBy = new Object * [10];
    }
    if (noLikedBy < 10)
    {
        LikedBy[noLikedBy] = other;
        noLikedBy++;
    }
    else
    {
        cout << "\nCannot have more than 10 Likes .\n";
    }
}
void Post::printlistview()
{
    shareddate.PrintDate();
}
void Post::setPostID(char* pid)
{
    PostID = pid;
}
char* Post::getPostID()
{
    return PostID;
}
char* Post::getPostText()
{
    return text;
}
void Post::viewLikedBy()
{
    cout << "Command :\t View Liked Posts\n";
    cout << " Post Liked By: \n\n ";
    if (noLikedBy == 0)
    {
        cout << PostID << "  has no Likes yet.\n";
    }
    for (int i = 0; i < noLikedBy; i++)
    {
        cout << LikedBy[i]->getID();
        cout << "__";
        LikedBy[i]->printName();
        cout << endl;
    }
    cout << "------------------------------------------------------------------------\n";
}
void Post::AddComments(Comments* other)
{
    if (comment == nullptr)
    {
        comment = new Comments * [10];
    }
    if (totalComments < 10)
    {
        comment[totalComments] = other;
        totalComments++;
    }
    else
    {
        cout << "\nCannot have more than 10 Comments .\n";
    }
}
void Post::viewComment()
{
    for (int i = 0; i < totalComments; i++)
    {
        comment[i]->printComment();
    }
}
void Post::AddContent(PostContent* temp)
{
    Content = temp;
}
void Post::printPost()
{
    cout << "--";
    SharedBy->printName();
    if (getContent() != nullptr)
    {
        getContent()->printContent();
    }
    printlistview();

    cout << "\n\t\t\t\"" << getPostText() << "\"";
}
int Post::getDateDifference()
{
    static Date currentDate(17, 4, 2024);
    return currentDate.GetDateDifference(shareddate);
}
int Post::GetDifferForMemory()
{
    static Date currentDate(17, 4, 2024);
    return currentDate.GetDifferForMemory(shareddate);
}
PostContent* Post::getContent()
{
    return Content;
}
void Post::PostComment(Object* ptr, char* commentText)
{
    Comments* newComment = new Comments();
    newComment->setValues(ptr, commentText);
    AddComments(newComment);
}
Post::~Post()
{
    TotalPosts--;
    if (PostID != nullptr)
        delete[] PostID;
    if (Content != nullptr)
        delete[] Content;
    if (comment != nullptr)
    {
        for (int i = 0; i < totalComments; i++)
        {
            delete comment[i];
        }
        delete[] comment;
    }
    if (text != nullptr)
    {
        delete[] text;
    }
    SharedBy = nullptr;
    if (LikedBy != nullptr)
        delete[] LikedBy;
}
Object::Object()
{
    ID = nullptr;
    Timeline = nullptr;
    notimeline = 0;
}
void Object::AddTimeline(Post* other)
{
    if (Timeline == nullptr)
    {
        Timeline = new Post * [10];
    }
    if (notimeline < 10)
    {
        Timeline[notimeline] = other;
        notimeline++;
    }
    else
    {
        cout << "\nCannot have more than 10 Posts .\n";
    }
}
void Object::printName() { }
void Object::setID(char* other)
{
    ID = other;
}
char* Object::getID()
{
    return ID;
}
void Object::printLatestPost()
{
    if (notimeline != 0)
    {
        for (int i = 0; i < notimeline; i++)
        {
            if (Timeline[i] != nullptr)
            {
                int dateDiff = Timeline[i]->getDateDifference();//year and month same but different date
                if (dateDiff <= 2 && dateDiff != -1)//i ma taking posts for today and yesterday only
                {
                    Timeline[i]->printPost();
                    Timeline[i]->viewComment();
                    cout << endl << endl;
                }
            }
        }
    }
}
Object::~Object()
{
    if (ID != nullptr)
        delete[] ID;
    if (Timeline != nullptr)
    {
        for (int i = 0; i < notimeline; i++)
        {
            if (Timeline[i])
                delete Timeline[i];
        }
        delete[] Timeline;
    }
}
class Activity :public PostContent
{
private:
    int type;
    char* value;
public:
    Activity();
    Activity(int t, char* v);
    void setValues(int t, char* v);
    void printContent();
    ~Activity();
};
Activity::Activity()
{
    type = 0;
    value = nullptr;
}
Activity::Activity(int t, char* v)
{
    type = t;
    value = v;
}
void Activity::setValues(int t, char* v)
{
    type = t;
    value = v;
}
void Activity::printContent()
{
    if (type == 1)
    {
        cout << " is feeling ";
    }
    else if (type == 2)
    {
        cout << " is thinking about ";
    }
    else if (type == 3)
    {
        cout << " is Making ";
    }
    else if (type == 4)
    {
        cout << " is celebrating ";
    }
    else
    {
        cout << "\nActivity type is not correct \n";
    }
    cout << value;
}
Activity::~Activity()
{
    if (value != nullptr)
        delete[] value;
}
class Memory :public Post
{
    Post* prevPost;
public:
    Memory(char*, Post*, Object*);
    void printPost();
};
Memory::Memory(char* cptr = nullptr, Post* postPtr3 = nullptr, Object* cu = nullptr) :Post(cptr, cu), prevPost(postPtr3)
{   }
void Memory::printPost()
{
    cout << "\n~~~~~~\t";
    printSharedby();
    cout << " shared a Memory\t~~~~~~";
    printlistview();
    cout << endl;
    cout << "\t\"" << getPostText() << "\"";
    cout << "\n\t~~~~~ " << prevPost->GetDifferForMemory() << " years ago  ~~~~~\n";
    cout << "-~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n";
    prevPost->printPost();
    viewComment();///it will not print anything because new post has no comments
    cout << "\n-~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~-\n";
}
class Page :public Object
{
    char* ID;
    char* Title;
public:
    Page();
    void ReadDataFromFile2(ifstream& fin);
    char* getPageID();
    char* getPageTitle();
    void ViewPage();
    void printName();
    ~Page();
};
Page::Page()
{
    ID = nullptr;
    Title = nullptr;
}
void Page::ReadDataFromFile2(ifstream& fin)
{
    char* temp = new char[100];
    fin >> temp;
    fin.ignore();
    ID = Helper::GetStringFromBuffer(temp);
    setID(ID);

    fin.getline(temp, 100);
    Title = Helper::GetStringFromBuffer(temp);
}
char* Page::getPageID()
{
    return ID;
}
char* Page::getPageTitle()
{
    return Title;
}
void Page::ViewPage()
{
    cout << "Command:\tView Page(" << ID << ")\n";
    cout << "---------------------------------------------------------------------------\n";
    cout << Title << "-Timeline\n\n";
    for (int i = 0; i < notimeline; i++)
    {
        Timeline[i]->printPost();
        Timeline[i]->viewComment();
        cout << endl << endl;
    }
    cout << "-----------------------------------------------------------------------------\n";
}
void Page::printName()
{
    cout << Title;
}
Page::~Page()
{
    if (Title != nullptr)
        delete[] Title;
}
class User :public Object
{
private:
    char* ID;
    char* Fname;
    char* Lname;
    int friendcount;
    int pagescount;
    User** FriendList;//null or 10 pointers max
    Page** LikedPages;//null or 10 pointers max
public:
    User();
    ~User();
    char* getUserID();
    void AddFriend(User*);
    void ReadDataFromFile(ifstream&);
    void LikePage(Page*);
    void ViewFriendList();
    void ViewLikedPages();
    void ViewTimeline();
    void printName();
    void viewHome();
    void viewMemory();
};
User::User()
{
    ID = nullptr;
    Fname = nullptr;
    Lname = nullptr;
    FriendList = nullptr;
    LikedPages = nullptr;
    friendcount = 0;
    pagescount = 0;
}
char* User::getUserID()
{
    return ID;
}
void User::ReadDataFromFile(ifstream& fin)
{
    char* temp = new char[100];
    fin >> temp;
    fin.ignore();
    ID = Helper::GetStringFromBuffer(temp);
    setID(ID);

    fin >> temp;
    Fname = Helper::GetStringFromBuffer(temp);
    fin >> temp;
    Lname = Helper::GetStringFromBuffer(temp);
}
void User::AddFriend(User* other)
{
    if (FriendList == nullptr)
    {
        FriendList = new User * [10];
    }
    if (friendcount < 10)
    {
        FriendList[friendcount] = other;
        friendcount++;
    }
    else
    {
        cout << "\nCannot have more than 10 friends .\n";
    }
}
void User::LikePage(Page* other)
{
    if (LikedPages == nullptr)
    {
        LikedPages = new Page * [10];
    }
    if (pagescount < 10)
    {
        LikedPages[pagescount] = other;
        pagescount++;
    }
    else
    {
        cout << "\nCannot have more than 10 liked pages .\n";
    }
}
void User::ViewFriendList()
{
    cout << Fname << " " << Lname << " is set as Current User\n\n";
    cout << "-----------------------------------------------------------------------------------------------------\n";
    cout << "Command :\t View Friend List";
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
    cout << Fname << " " << Lname << " - " << "Friend List \n\n ";
    if (friendcount == 0)
    {
        cout << Fname << " " << Lname << " has no friend yet.\n";
    }
    for (int i = 0; i < friendcount; i++)
    {
        cout << FriendList[i]->ID << "--" << FriendList[i]->Fname << " " << FriendList[i]->Lname << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------\n";
}
void User::ViewLikedPages()
{
    cout << "Command :\t View Liked Pages";
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
    cout << Fname << " " << Lname << " - " << "Liked Pages \n\n ";
    if (pagescount == 0)
    {
        cout << Fname << " " << Lname << " has not liked any pages.\n";
    }
    for (int i = 0; i < pagescount; i++)
    {
        cout << LikedPages[i]->getPageID() << "--" << LikedPages[i]->getPageTitle() << endl;
    }
    cout << "-----------------------------------------------------------------------------------------------------\n";
}
void User::ViewTimeline()
{
    cout << "Command:\tView TimeLine\n";
    cout << "-----------------------------------------------------------------------------------------------------\n";
    cout << Fname << " " << Lname << "-Time Line\n\n";
    for (int i = 0; i < notimeline; i++)
    {
        Timeline[i]->printPost();//to make it shorter we use this function
        Timeline[i]->viewComment();
        cout << "\n\n";
    }
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
}
void User::printName()
{
    cout << Fname << " " << Lname;
}
void User::viewHome()
{
    cout << "Command:\tView Home (" << getID() << ")";
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
    cout << Fname << " " << Lname << "-Home Page\n\n";
    printLatestPost();

    for (int i = 0; i < friendcount; i++)
    {
        FriendList[i]->printLatestPost();
    }
    for (int i = 0; i < pagescount; i++)
    {
        LikedPages[i]->printLatestPost();
    }
    cout << "-----------------------------------------------------------------------------------------------------\n";
}
void User::viewMemory()
{
    bool found = false;
    for (int i = 0; i < notimeline; i++) {
        int difference = Timeline[i]->GetDifferForMemory();
        if (difference != -1)
        {
            found = true;
            cout << difference << " Years Ago\n";
            Timeline[i]->printPost();
            Timeline[i]->viewComment();
        }
    }
    if (!found)
    {
        cout << "No memories found.\n";
    }
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
}
User::~User()
{
    if (Fname != nullptr)
    {
        delete[] Fname;
    }
    if (Lname != nullptr)
    {
        delete[] Lname;
    }

    if (FriendList != nullptr)
        delete[] FriendList;
    if (LikedPages != nullptr)
        delete[] LikedPages;
}
class controller
{
    int totalusers;
    int totalpages;
    int totalposts;
    int totalComments;
    int totalActivities;
    User** AllUsers;
    Page** AllPages;
    Post** AllPosts;
public:

    controller();
    void LoadAllUser(const char* fileName);
    void LoadAllPages(const char* fileName);
    void LoadAllPosts(const char* fileName);
    void LinkUsersAndPages(const char* fileName);
    void LoadAllComments(const char* fileName);
    void LoadAllActivites(const char* fileName);
    void LoadData();
    User* SearchUserByID(char* ID);
    Page* SearchPageByID(char* ID);
    Post* SearchPostByID(char* ID);
    Object* SearchObjectByID(char* ID);
    void Run();
    ~controller();
};
controller::controller()
{
    totalusers = 0;
    totalpages = 0;
    totalposts = 0;
    totalComments = 0;
    totalActivities = 0;
    AllUsers = nullptr;
    AllPages = nullptr;
    AllPosts = nullptr;
}
void controller::LoadAllUser(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
        return;
    }
    fin >> totalusers;
    AllUsers = new User * [totalusers];
    for (int i = 0; i < totalusers; i++)
    {
        AllUsers[i] = new User();
        AllUsers[i]->ReadDataFromFile(fin);
    }
    cout << "READ user file\n";
    fin.close();
}
void controller::LoadAllPages(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
    }
    fin >> totalpages;
    AllPages = new Page * [totalpages];
    for (int i = 0; i < totalpages; i++)
    {
        AllPages[i] = new Page();
        AllPages[i]->ReadDataFromFile2(fin);
    }
    cout << "READ pages file\n";
    fin.close();
}
void controller::LinkUsersAndPages(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
    }

    char* temp = new char[180];
    fin >> temp;
    char delimiter[3] = "-1";
    while (Helper::CompareString(temp, delimiter) != 0)
    {
        User* currentUser = SearchUserByID(temp);
        if (currentUser)
        {
            fin >> temp;
            while (Helper::CompareString(temp, delimiter) != 0)
            {

                User* UserFriend = SearchUserByID(temp);
                if (UserFriend)
                {
                    currentUser->AddFriend(UserFriend);
                }
                fin >> temp;
            }
            fin >> temp;
            while (Helper::CompareString(temp, delimiter) != 0)
            {

                Page* UserPage = SearchPageByID(temp);
                if (UserPage)
                {
                    currentUser->LikePage(UserPage);
                }
                fin >> temp;
            }
        }
        fin >> temp;
    }
    cout << "READ link file\n";
    fin.close();
}
void controller::LoadAllPosts(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
    }
    fin >> totalposts;
    AllPosts = new Post * [totalposts];
    for (int i = 0; i < totalposts; i++)
    {
        AllPosts[i] = new Post();
        AllPosts[i]->ReadDataFromFile3(fin);

        char* temp = new char[180];
        fin >> temp;
        Object* ptrshareBy = SearchObjectByID(temp);
        AllPosts[i]->setSharedBy(ptrshareBy);
        ptrshareBy->AddTimeline(AllPosts[i]);

        fin >> temp;

        char delimiter[3] = "-1";
        while (Helper::CompareString(temp, delimiter) != 0)
        {
            Object* likedBy = SearchObjectByID(temp);
            AllPosts[i]->AddLikedBy(likedBy);
            fin >> temp;
            fin.ignore();
        }
    }
    cout << "READ posts file\n";

    fin.close();
}
void controller::LoadAllComments(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
        return;
    }
    fin >> totalComments;
    char* cid;
    char* pid;
    char* uid;
    char* text;
    for (int i = 0; i < totalComments; i++)
    {
        char temp[100];
        fin >> temp;
        cid = Helper::GetStringFromBuffer(temp);
        fin >> temp;
        pid = Helper::GetStringFromBuffer(temp);
        fin >> temp;
        uid = Helper::GetStringFromBuffer(temp);
        fin.ignore();
        fin.getline(temp, 100);
        text = Helper::GetStringFromBuffer(temp);
        Post* tempPost = SearchPostByID(pid);

        Object* tempobj = SearchObjectByID(uid);

        Comments* ptr = new Comments;
        ptr->setValues(tempobj, text);

        Post* postPtr = SearchPostByID(pid);
        if (postPtr)
        {
            postPtr->AddComments(ptr);
        }

    }
    cout << "READ comments file\n";
    fin.close();
}
void controller::LoadAllActivites(const char* fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "Error opening file\n";
        return;
    }
    fin >> totalActivities;
    char* pid;
    int aid;
    char* valueagainstActivity;
    for (int i = 0; i < totalActivities; i++)
    {
        char temp[100];
        fin >> temp;
        pid = Helper::GetStringFromBuffer(temp);
        fin >> aid;
        fin.ignore();
        fin.getline(temp, 100);
        valueagainstActivity = Helper::GetStringFromBuffer(temp);
        Post* tempPost = SearchPostByID(pid);

        Activity* ptr = new Activity(aid, valueagainstActivity);

        Post* postPtr = SearchPostByID(pid);
        if (postPtr)
        {
            postPtr->AddContent(ptr);
        }

    }
    cout << "READ Activities file\n";
    fin.close();
}
void controller::LoadData()
{
    LoadAllUser("socialnetworkusers.txt");
    LoadAllPages("socialnetworkpages.txt"); //Keep it easily configurable
    LinkUsersAndPages("userfriendsandlinkedpages.txt");//
    LoadAllPosts("SocialNetworkPosts.txt");
    LoadAllComments("socialNetworkComments.txt");
    LoadAllActivites("socialNetworkActivities.txt");
}
User* controller::SearchUserByID(char* ID)
{
    for (int i = 0; i < totalusers; i++)
    {
        if (Helper::CompareString(AllUsers[i]->getUserID(), ID) == 0)
        {
            return AllUsers[i];
        }
    }
    return nullptr;
}
Page* controller::SearchPageByID(char* ID)
{
    for (int i = 0; i < totalpages; i++)
    {
        if (Helper::CompareString(AllPages[i]->getPageID(), ID) == 0)
        {
            return AllPages[i];
        }
    }
    return nullptr;
}
Post* controller::SearchPostByID(char* ID)
{
    for (int i = 0; i < totalposts; i++)
    {
        if (Helper::CompareString(AllPosts[i]->getPostID(), ID) == 0)
        {
            return AllPosts[i];
        }
    }
    return nullptr;
}
Object* controller::SearchObjectByID(char* ID)
{
    Object* ptrshareBy = nullptr;
    if (ID[0] == 'u')
    {
        ptrshareBy = SearchUserByID(ID);
    }
    else if (ID[0] == 'p')
    {
        ptrshareBy = SearchPageByID(ID);
    }
    return ptrshareBy;
}
void controller::Run()
{
    char currentUserID[4] = "u7";
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
    cout << "Command:\t Set current System Date 17 4 2024 \n";
    cout << "\n-----------------------------------------------------------------------------------------------------\n";
    cout << "System Date:\t\t 17/4/202024\n";
    User* currentUser = SearchUserByID(currentUserID);
    if (currentUser)
    {
        cout << "\n-----------------------------------------------------------------------------------------------------\n";
        cout << "Command:\tSet current user \"" << currentUserID << "\"\n";
        cout << "\n-----------------------------------------------------------------------------------------------------\n";
        cout << currentUser->getUserID() << " successfully set as Current User\n\n";

        currentUser->ViewFriendList();
        currentUser->ViewLikedPages();
        currentUser->ViewTimeline();
    }
    else {
        cout << "Error: User \"" << currentUserID << "\" not found.\n";
    }
    char currentPostNo[6] = "post5";
    Post* postPtr = SearchPostByID(currentPostNo);
    if (postPtr)
    {
        postPtr->viewLikedBy();
        cout << "Command:\tLikePost (" << currentPostNo << ")\n";
        postPtr->AddLikedBy(currentUser);
        postPtr->viewLikedBy();
    }
    char currentPageNo[3] = "p1";
    Page* pagePtr = SearchPageByID(currentPageNo);
    if (pagePtr)
    {
        pagePtr->ViewPage();
    }
    if (currentUser)
    {
        currentUser->viewHome();
    }
    char currentPost7[7] = "post4";
    Post* postPtr2 = SearchPostByID(currentPost7);
    if (postPtr2)
    {
        cout << "Command:\tPostComment(" << currentPost7 << ", Good Luck for your Result)\n";
        cout << " Command:\t ViewPost(" << currentPost7 << ")\n";
        const char* newcomment = "Good Luck for your Result";
        char* commentTextPtr = new char[Helper::stringLength(newcomment) + 1];
        commentTextPtr = Helper::copy(newcomment, commentTextPtr);
        postPtr2->PostComment(currentUser, commentTextPtr);
        postPtr2->printPost();
        postPtr2->viewComment();
        cout << "\n-----------------------------------------------------------------------------------------------------\n";
    }
    char currentPost2[6] = "post8";
    Post* postPtr4 = SearchPostByID(currentPost2);
    if (postPtr4)
    {
        cout << "Command:\tPostComment(" << currentPost2 << ", Thanks for the wishes)\n";
        cout << " Command:\t ViewPost(" << currentPost2 << ")\n";
        const char* newcomment2 = "Thanks for the wishes";
        char* commentTextPtr2 = new char[Helper::stringLength(newcomment2) + 1];
        commentTextPtr2 = Helper::copy(newcomment2, commentTextPtr2);
        postPtr4->PostComment(currentUser, commentTextPtr2);
        postPtr4->printPost();
        postPtr4->viewComment();
        cout << "\n-----------------------------------------------------------------------------------------------------\n";
    }
    if (currentUser)
    {
        cout << "Command:\t SeeYourMemories()\n";
        cout << "\n-----------------------------------------------------------------------------------------------------\n";
        cout << "\nWe hope you enjoy looking back and sharing your memories on Facebook, from the most recent to those long ago.\n";
        cout << "\nOn this Day:\n";
        currentUser->viewMemory();
        char currentPostNumber[7] = "post10";
        Post* postPtr3 = SearchPostByID(currentPostNumber);
        if (postPtr3)
        {
            const char* newcaption = "Never thought I will be specialist in this field";
            char* captionPtr = new char[Helper::stringLength(newcaption) + 1];
            captionPtr = Helper::copy(newcaption, captionPtr);
            Memory* ptr = new Memory(captionPtr, postPtr3, currentUser);
            cout << "Command:\tShareMemory (" << currentPostNumber << ",\" Never thought I will be specialist in this field\" )\n";
            currentUser->AddTimeline(ptr);
            currentUser->ViewTimeline();
        }
    }
}
controller::~controller()
{
    if (AllUsers != nullptr)
    {
        for (int i = 0; i < totalusers; i++)
        {
            delete AllUsers[i];
        }
        delete[] AllUsers;
    }

    if (AllPages != nullptr)
    {
        for (int i = 0; i < totalpages; i++)
        {
            delete AllPages[i];
        }
        delete[] AllPages;
    }

    if (AllPosts != nullptr)
    {
        delete[] AllPosts;
    }
}
int main()
{
    controller mainApp;
    mainApp.LoadData();
    mainApp.Run();
}


