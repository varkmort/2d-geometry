// Create 2d geometry.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// создать для 2d пространства классы Точка, Отрезок, Линия
// 
// В какой области будут применяться классы
//      какие поведения мы будем реализовывать в классе
//      какие свойства и назначения мы будем размещать внутри класса
// 
// Какие свойства и поведения являются внутренними компонентами класса,
// а какие необходимо дать пользователю для работы.
// 
// https://github.com/varkmort/2d-geometry

#include <cmath>

class Point2d {
public:
    //создаваться 
    // done

    Point2d():Point2d(.0,.0){}

    Point2d(double x, double y):x_(x), y_(y) {}

    virtual ~Point2d() {}//для возможности использования в наследовании

    // предоставлять информацию о местоположении
    // изменять информацию о местоположении

    void x(double x){
        x_ = x;
    }
    void y(double y){
        y_ = y;
    }

    double x() const {
        return x_;
    }
    double y() const {
        return y_;
    }

    // сравнивать себя с другими точками
    bool same(const Point2d &other) const {
        return x_ == other.x_ && y_ == other.y_;
    }
    
private:
    double x_;
    double y_;
};

class Segment2d {
public:
    //создание отрезка

    Segment2d(Point2d begin, Point2d end):begin_(begin), end_(end){}

    virtual ~Segment2d(){}

    //изменять и выводить  информацию о компонентах
    
    void begin(Point2d begin){
        begin_ = begin;
    }
    void end(Point2d end) {
        end_ = end;
    }
    
    Point2d begin() const {
        return begin_;
    }
    Point2d end() const {
        return end_;
    }

    // длинна
    double length() const {
        return  ::sqrt(
            ::pow(end_.x()-begin_.x(), 2) + 
            ::pow(end_.y() - begin_.y(), 2)
        );
    }

    static double length(Point2d a, Point2d b);

    // пересекаются ли отрезки
    bool cross(const Segment2d& other)const;


    // находится ли точка на отрезке
    bool contatin(Point2d point);

    // сравнение отрезков
    //  по длинне

    bool bigger(const Segment2d &other)const {
        return length() > other.length();
    }

    bool shorter(const Segment2d& other)const {
        return !bigger(other);
    }

private:
    Point2d begin_;
    Point2d end_;
};

class Line2d {
public:
    //создание линии(пустой, из точки, из отрезка и из другой линии)
    
    Line2d():begin_(nullptr), end_(nullptr),size_(0) {}

    Line2d(Point2d point);

    Line2d(Segment2d obj) {
        //создали точки
        begin_ = new LinePoint;
        end_ = new LinePoint;

        //заполнили данными
        begin_->point = obj.begin();
        end_->point = obj.end();

        //привязали к началу конец
        begin_->previous_ = nullptr;
        begin_->next_ = end_;
        
        //привязали к кноцу начало
        end_->previous_ = begin_;        
        end_->next_ = nullptr;
                
        size_ = 2;
    }

    Line2d(const Line2d &other): Line2d() {
        if (other.size_ > 0) {
            begin_ = new LinePoint;
            begin_->point = other.begin_->point;
            begin_->previous_ = nullptr;

            //переменная для хранения текущих переносимых данных
            auto transfer = other.begin_->next_;
            //переменная которая будет служить текущей внутренней точкой линии 
            auto current = new LinePoint;
            current->previous_ = begin_;

            while (transfer != other.end_) {
                //перенесли данные
                current->point = transfer->point;
                
                //создали место под следующий узел(точку)
                current->next_ = new LinePoint;
                //в следующем узле запомнили какой считать пердыдущим
                current->next_->previous_ = current;

                //сделали шаг вперёд по списку точек в нашей линии
                current = current->next_;
                //сделали шаг вперёд по списку точек в линии-образце
                transfer = transfer->next_;
            }

            end_ = current;
            current->point = transfer->point;
            current->next_ = nullptr;

            size_ = other.size_;
        }
    }

    virtual ~Line2d() {
        if (size_ > 0) {
            auto current = end_;
            while (current->previous_ != nullptr) {
                current = current->previous_;
                delete current->next_;
            }
            delete current;
        }
    }

    void addPoint(Point2d point, int position);
    void popPoint(int position);

    Point2d getPoint(int position)const {
        if (position > size_) {
            throw 1;
        }

        auto current = begin_;
        int i{ 0 };
        while (i < position)
        {
            current = current->next_;
            i++;
        }
        return current->point;
    }

    void pushBack(Point2d point) {
        end_->next_ = new LinePoint{};
        end_->next_->point = point;
        end_->next_->previous_ = end_;
        end_ = end_->next_;
        size_ += 1;
    }

    //задание со звёздочкой
    void pushBack(const Line2d& points);
    //создать метод который позволит изменять значение точки в линии

    void popBack() {
        if (size_==0){
            throw 1;
        }

        end_ = end_->previous_;
        delete end_->next_;
        end_->next_ = nullptr;
        size_ -= 1;
    }

    int size()const {
        return size_;
    }

    double length()const;

private:
    struct LinePoint {
    public:
        Point2d point;
        LinePoint *next_;
        LinePoint *previous_;
    };

    LinePoint *begin_;
    LinePoint *end_;
    int size_;
};



#include <iostream>

struct A {
    int a;
    float b;
};

A* f00() {
    return new A{2, 3.4};
}

int main()
{
    A obj;
    obj.a = 0;
    auto p = f00();
    (*p).a;
    p->b;
    const Point2d coord_start(6.2, 1.6);
    Segment2d a(Point2d(0.,0.), { 0., 5.});
    Segment2d b(a);
    std::cout << a.length();
}

//список библиотек
// то что всегда нужно:
// работа с файлами         fstream | stdio.h
// работа с текстом         string cstring | regex
// работа с математикой     cmath
// работа с алгоритмами     algorithm
// работа с коллекциями     vector list deque set map array...
// 
// то что очень помогает:
// работа со временем           chrono | ctime
// работа с файловой системой   filesystem
// работа со случайными числами random | cstdlib
//