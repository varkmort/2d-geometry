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
//

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

    // пересекаются ли отрезки
    bool cross(const Segment2d& other)const;


    // находится ли точка на отрезке

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

    Line2d(Segment2d obj) {
        //создали точки
        begin_ = new LinePoint;
        end_ = new LinePoint;

        //заполнили данными
        begin_->point = obj.begin();
        end_->point = obj.end();

        //привязали к началу конец
        begin_->prev_ = nullptr;
        begin_->next_ = end_;
        
        //привязали к кноцу начало
        end_->prev_ = begin_;        
        end_->next_ = nullptr;
                
        size_ = 2;
    }

    Line2d(const Line2d&other){}

    void addPoint(Point2d point, int position);

    Point2d getPoint(int position)const;

private:
    struct LinePoint {
    public:
        Point2d point;
        LinePoint *next_;
        LinePoint *prev_;
    };

    LinePoint *begin_;
    LinePoint *end_;
    int size_;
};


#include <iostream>

int main()
{
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