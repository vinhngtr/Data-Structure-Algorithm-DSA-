#include <bits/stdc++.h>
using namespace std;
class Book{
    char* title;
    char* author;
    int publish;
    public:
    // ! QUAN TÂM ĐẾN 3 LOẠI CONSTRUCTOR QUAN TRỌNG:
        Book(){
            this->author = nullptr;
            this->title = nullptr;
            this->publish = 0;
        }
        Book(const char* title, const char *author, const int publish){
            // CÂP PHÁT ĐỘNG CHO pointer 1 kích thước bằng kích thước truyền vào cộng 1
            // Dùng strcpy để gán giá trị truyền vào cho this->ptr
            this->title = new char[strlen(title) + 1];
            strcpy(this->title, title);
            this->author = new char[strlen(author) + 1];
            strcpy(this->author, author);
            this->publish = publish;
        }
        Book(const Book &book){
            this->title = new char[strlen(book.title) + 1];
            strcpy(this->title, book.title);
            this->author = new char[strlen(book.author) + 1];
            strcpy(this->author, book.author);
            this->publish = book.publish;
        }

        void setTitle(const char *title){
            this->title = new char[strlen(title) + 1];
            strcpy(this->title, title);
        }
        char *getTitle()const{
            return this->title;
        }

        // ! DECONSTRUCTOR ---------
        ~Book(){
            if(this->title){
                delete[] this->title;
                this->title = nullptr;
            }
            if(this->author){
                delete[] this->author;
                this->author = nullptr;
            }
            this->publish = 0;
        }

        friend bool checkAuthor(Book book, const char *author){
            if(book.author != nullptr){
                // dùng hàm strtok() để tách từng tác giả ra so sánh với tham số truyền vào
                char *token = strtok(book.author, ",");
                while(token != nullptr){
                    if(strcmp(token, author) == 0){
                        return true;
                    }
                    token = strtok(nullptr, ",");
                }
            }
            return false;
        }
};

class Printer{
    public:
    /**
     * Book book1("Introduction to Algorithms", "Thomas H. Cormen, Charles E. Leiserson,   Ronald L. Rivest, Clifford Stein", 1990);
            Printer::printBook(book1);
            //!Introduction to Algorithms
                Thomas H. Cormen
                Charles E. Leiserson
                Ronald L. Rivest
                Clifford Stein
                1990
    */
        /**
         * 1. tạo 1 pointer: char *token = strtok(book.author, ",");
         * 2. while(token != nullptr){
         *      cout<< (token[0] == " " ? token + 1 : token)<<endl
         * }
         * cout<<book.publish;
         */
        static void printBook(const Book book){
            cout << book.title << endl;
            char *token = strtok(book.author, ",");
            while(token != nullptr){
                cout << (token[0] == ' ' ? token + 1 : token) << endl;
                token = strtok(nullptr, ",");
            }
            cout << book.publish;
        }
};

// !=============================== LỚP CHARACTER ======================//
class Character {
protected:
    int hp;
    int x;
    int y;
public:
    // Constructor: set the values of x and y and hp to 0
    Character();

    // Constructor: set the values of hp, x and y to each parameter
    Character(int hp, int x, int y);

    // Set and get hp
    int getHp();
    void setHp(int hp);

    // Set and get x
    int getX();
    void setX(int x);
    
    // Set and get y
    int getY();
    void setY(int y);

    // Get Manhattan distance to other character
    int getManhattanDistTo(Character* other);


    // Operator =: copy all data from Character other
    void operator=(const Character& other);

    // Operator <: Character a < Character b when a's hp is less than or equal b's hp
    bool operator<(const Character& other);

    // Operator () with zero parameters: print data of the instance with format: hp-x-y
    void operator()();
};
Character::Character(){
    this->x = 0;
    this->y = 0;
    this->hp = 0;
}
Character::Character(int x, int y, int hp){
    this->x = x;
    this->y = y;
    this->hp = hp;
}
int Character::getX(){
    return this->x;
}
void Character::setX(int x){
    this->x = x;
}
int Character::getY(){
    return this->y;
}
void Character::setY(int y){
    this->y = y;
}
int Character::getHp(){
    return this->hp;
}
void Character::setHp(int hp){
    this->hp = hp;
}
int Character::getManhattanDistTo(Character *other){
    return abs(this->x - other->x) + abs(this->y - other->y);
}
void Character::operator=(const Character& other){
    x = other.x;
    y = other.y;
    hp = other.hp;
}
bool Character::operator<(const Character& other){
    if(other.hp > hp){
            return true;
    }else{
            return false;
    }
}
void Character::operator()(){
    cout << hp << "-" << x << "-" << y;
}

class Player : private Character{
    Player() : Character(){}
    Player(int hp, int x, int y) : Character(int hp, int x, int y){}
    void PrintData(){
            cout << getHp << "-" << getX() << "-" << getY();
    }
    void MoveTo(int x, int y){
            setX(x);
            setY(y);
    }
}

class Point{
    double x, y;

public:
    Point()
    {
            this->x = 0.0;
            this->y = 0.0;
        }
    Point(double x, double y){
            this->x = x;
            this->y = y;
    }
    void setX(double x){
            this->x = x;
    }
    void setY(double y){
            this->y = y;
    }
    double getX()const{
            return this->x;
    }
    double getY()const{
            return this->y;
    }
    double disconstance(Point& pA){
            return sqrt(pow(this->x - pA.x, 2) + pow(this->y - pA.y, 2));
    }
     friend istream& operator >> (istream &in, Point &pointA)
    {
            in >> pointA.x >> pointA.y;
            return in;
    }
};

class Circle{
    private:
        Point center;
        double radius;
    public:
        Circle(){
            this->center.setX(0.0);
            this->center.setY(0.0) 
            this->radius = 0.0;
        }
        Circle(Point center, double radius){
            this->center.setX(center.getX());
            this->center.setY(center.getY());
            this->radius = radius;
        }
        void setCenter(Point point){
            this->center.setX(point.getX());
            this->center.setY(point.getY());
        }
        Point getCenter()const{
            return this->center;
        }
        void setRadius(double radius){
            this->radius = radius;
        }
        double getRadius()const{
            this->radius;
        }
        Circle(const Circle& circle){
            this->center = circle.getCenter();
            this->radius = circle.getRadius();
        }
        bool containsPoint(const Point point){
            double tem = center.disconstance(point);
            if(tem < this->radius)
                return true;
            else{
                return false;
            }
        }
         bool containsTriangle(const Point pointA, const Point pointB, const Point pointC)
    {
        /*  
         * STUDENT ANSWER   
         * TODO: check if a given triangle ABC (A, B, C are not on the same line) is entirely within the circle (does not count if any point of the triangle lies on the circle).  
                 If contain, return true.
         */
         double a = center.distanceToPoint(pointA);
         double b = center.distanceToPoint(pointB);
         double c = center.distanceToPoint(pointC);
         if(a < this->radius && b < this->radius && c < this->radius) 
            return true;
         return false;
    }

    void operator=(const Circle& circle){
         this->center = circle.center;
         this->radius = circle.radius;
    }
    bool operator==(const Circle& circle){
        if(center.disconstance(circle.center) == 0 && this->radius = circle.radius){
            return true;
        }else{
            return false;
        }
    }
      friend istream& operator >> (istream &in, Circle &circle)
    {
        /*  
         * STUDENT ANSWER
         */
         in>>circle.center>>circle.radius;
         return in;
         
    }
};

class ToyBox
{
private:
    Toy* toyBox[5];
    int numberOfItems;

public:
    ToyBox()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
         
         this->numberOfItems = 0;
         for(int i=0; i<5; i++){
             toyBox[i] = nullptr;
         }
         
    }
    
    int addItem(const CarToy& carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box. 
                 If the box is full, return -1.
         */
         if (numberOfItems > 4) return -1;
         else
         {
             toyBox[numberOfItems++] = (CarToy *)&carToy;
         }
         return numberOfItems;
    }
    void printBox(){
         for (int i = 0; i < numberOfItems;i++){
             toyBox[i]->printType();
         }
    }
};
int main(){
   
}